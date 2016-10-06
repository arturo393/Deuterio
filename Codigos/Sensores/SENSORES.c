#include <avr/io.h>
#include <math.h> 
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h> 
 
#define BLINK_DELAY_MS 20
#define T_US_CLK_SPI_SOFT 3// con 3 da un un ciclo de 7us
//pravda
//puerto B
const int SPI_SOFT_MISO=0;
//puerto D
const int SPI_SOFT_CLK=7;
const int SPI_SOFT_MOSI=6;
const int SPI_SOFT_CS=5;
const int SPI_SOFT_S0=4;
const int SPI_SOFT_S1=3;
const int SPI_SOFT_S2=2;

//structura de los sensores
typedef struct SENSORES
{
	char Tipo[8]; // B T 0
	int32_t T[8];// solo se envian 12 y 13 bits
	int32_t P[8];// solo se envian 18 bits
	//secuencia recomendada para sensor barometrico:::::::::::::::::::::::::::::::::::::::::::::::::::
	//0-enviar reset
	//1-esperar tiempo a resear app 2.8 ms desde el envio del reset
	//2,enviar codigo de lectura de parametro y obtener los 8 parametros Ci de 16 bits, 24clk cada uno.
	//3 mandar codigo de conversion de temperatura
	//4 esperar  8.2 ms conversion tipica
	//5 mandar codigo de conversion de presion
	//6 esperar  8.2 ms conversion tipica3
	uint16_t C[8][6];//parametros a leer //hay memoria de sobra	
}SENSORES;

//variables globales

uint8_t BYTE0,BYTE1,BYTE2,BYTE3;	
SENSORES Sensores={0};
uint8_t VAL_IN=0;
uint8_t ID=0;
uint8_t CODE=0;
uint8_t bytes;

uint8_t send_byte_spi_soft(unsigned char DATA_OUT)
{
	uint8_t DATA_IN=0x00;
	uint8_t i;	
	for(i=0;i<8;i++)
	{
		//escribe en MOSI
		if((DATA_OUT&0x80)&0x80)PORTD |= _BV(SPI_SOFT_MOSI);
		else PORTD &= ~_BV(SPI_SOFT_MOSI);
		//Mover buffer
		DATA_OUT=DATA_OUT<<1;	
		//sube el clock
		PORTD |= _BV(SPI_SOFT_CLK);//clk=1 SPI_SOFT_CLK
		_delay_us(T_US_CLK_SPI_SOFT);
		//leer
		DATA_IN=DATA_IN<<1;//Mover buffer
		DATA_IN=(PINB & _BV(SPI_SOFT_MISO))?(DATA_IN|0x01):(DATA_IN|0x00);

		//baja el clock
		PORTD &= ~_BV(SPI_SOFT_CLK);//clk=0 SPI_SOFT_CLK
		_delay_us(T_US_CLK_SPI_SOFT);
		//hay un retardo de un 1us entre subir y bajar
	}

	return DATA_IN;
}

void set_cs()
{
	PORTD|=_BV(SPI_SOFT_CS);
}

void clear_cs()
{
	PORTD &=~_BV(SPI_SOFT_CS);
}

void init_spi_soft()
{
	//configuracion de los pines 
	//puerto B  0=entrada
	DDRB &= ~_BV(SPI_SOFT_MISO);//ENTRADA!! PB0
	//puerto D 1=salida
	DDRD |= _BV(SPI_SOFT_CLK);//salida PD7
	DDRD |= _BV(SPI_SOFT_MOSI);//salida PD6	
	DDRD |= _BV(SPI_SOFT_CS);//salida	PD5
	DDRD |= _BV(SPI_SOFT_S0);//salida PD4
	DDRD |= _BV(SPI_SOFT_S1);//salida	PD3
	DDRD |= _BV(SPI_SOFT_S2);//salida	PD2
	set_cs();
}

void refresh_addr_pin(unsigned char addr)
{
	//configura la direccion addr para los dispositivos
	PORTD=((addr&0x01)&0x01)? PORTD|_BV(SPI_SOFT_S0):PORTD&~_BV(SPI_SOFT_S0);
	PORTD=((addr&0x02)&0x02)? PORTD|_BV(SPI_SOFT_S1):PORTD&~_BV(SPI_SOFT_S1);
	PORTD=((addr&0x04)&0x04)? PORTD|_BV(SPI_SOFT_S2):PORTD&~_BV(SPI_SOFT_S2);	
}



void reset_barometricos()
{
	uint8_t addr;
	//resetear sensores barometricos
	for(addr=0;addr<8;addr++)
	{	
		if(Sensores.Tipo[addr]=='B')
		{
			
			refresh_addr_pin(addr);
			clear_cs();//cs=0
			BYTE0=send_byte_spi_soft(0x1E);//codigo de reset
			_delay_ms(3); //tiempo necesario para el reseteo de sensores
			set_cs();//cs=1
		}
	}
}

void get_parametros_barometricos()
{
	uint8_t addr,c;
	//resetear sensores barometricos
	for(addr=0;addr<8;addr++)
	{	
		if(Sensores.Tipo[addr]=='B')
		{
			refresh_addr_pin(addr);
			clear_cs();//cs=0
			for(c=0;c<6;c++)
			{
				BYTE0=send_byte_spi_soft(0xA2+c*2);//0x1010_0010+[0x0000_0000><0x0000_1100] 
				//en total son 8 pero dos son de uso interno
				BYTE1=send_byte_spi_soft(0x00);
				BYTE0=send_byte_spi_soft(0x00);
				Sensores.C[addr][c]=((uint16_t)BYTE1)<<8+(uint16_t)BYTE0;
			}
			set_cs();
		}
				
	}	
}

//N:ninguno, T:termocupla, B:barometrico
void set_T(int32_t c0,int32_t c1,int32_t c2,int32_t c3,int32_t c4,int32_t c5,int32_t c6,int32_t c7)
{
	Sensores.T[0]=c0;
	Sensores.T[1]=c1;
	Sensores.T[2]=c2;
	Sensores.T[3]=c3;
	Sensores.T[4]=c4;
	Sensores.T[5]=c5;
	Sensores.T[6]=c6;
	Sensores.T[7]=c7;
}

void set_tipo_sensor(char c0,char c1,char c2,char c3,char c4,char c5,char c6,char c7)
{
	Sensores.Tipo[0]=c0;
	Sensores.Tipo[1]=c1;
	Sensores.Tipo[2]=c2;
	Sensores.Tipo[3]=c3;
	Sensores.Tipo[4]=c4;
	Sensores.Tipo[5]=c5;
	Sensores.Tipo[6]=c6;
	Sensores.Tipo[7]=c7;
}


void get_mediciones()
{
	uint8_t addr,c;
	uint32_t D1,D2;
	int32_t dT;
	int64_t OFF, SENS, P_temp,T_temp;
	
 

	for(addr=0;addr<8;addr++)
	{
		if(Sensores.Tipo[addr]=='T')//<----si es un sensor termocupla
		{	
			//check last
			refresh_addr_pin(addr);//configura la direccion del dispositivo
			clear_cs();//cs=0
			_delay_us(T_US_CLK_SPI_SOFT*3);//delay por seguridad
			BYTE1=send_byte_spi_soft(0x00);
			BYTE0=send_byte_spi_soft(0x00);
			_delay_us(T_US_CLK_SPI_SOFT*3);//delay por seguridad
			set_cs();
			T_temp=((  (((int32_t)BYTE1)<<8) + ((int32_t)BYTE0) )*10);//sin division por 4, lsb=0.25
			Sensores.T[addr]=T_temp;
		}
	
		if(Sensores.Tipo[addr]=='B')//<----si es un sensor Barometrico
		{
			refresh_addr_pin(addr);	
			//obtener datos de presion
			clear_cs();
			BYTE0=send_byte_spi_soft(0x48);//0x48:leer D1 OSR=4096
			_delay_ms(9);
			set_cs();

			clear_cs();//cs=0
			BYTE0=send_byte_spi_soft(0x00);//no-data
			BYTE2=send_byte_spi_soft(0x00);
			BYTE1=send_byte_spi_soft(0x00);
			BYTE0=send_byte_spi_soft(0x00);
			set_cs();
			//hacer los calculos:
			D2=(uint32_t)BYTE0+((uint32_t)BYTE1)<<8+((uint32_t)BYTE2)<<16;// solo necesita 24 bits
			dT=(int32_t)D2-((int32_t)Sensores.C[addr][4])<<8;
			T_temp=2000+(dT*((int32_t)Sensores.C[addr][5])>>23);
			Sensores.T[addr]=(int32_t)T_temp;
			//Sensores.T[addr]=D2;
			
			//obtener datos de temperatura
			clear_cs();
			BYTE0=send_byte_spi_soft(0x58);//0x58:leer D2 OSR=4096
			_delay_ms(9);
			set_cs();

			clear_cs();//cs=0
			BYTE0=send_byte_spi_soft(0x00);//no-data
			BYTE2=send_byte_spi_soft(0x00);
			BYTE1=send_byte_spi_soft(0x00);
			BYTE0=send_byte_spi_soft(0x00);
			set_cs();
			//hacer los calculos:
			D1=(uint32_t)BYTE0+((uint32_t)BYTE1)<<8+((uint32_t)BYTE2)<<16;
			OFF= ((int64_t)Sensores.C[addr][1])<<16+(((int64_t)Sensores.C[addr][3])* ((int64_t)dT))>>7;
			SENS=((int64_t)Sensores.C[addr][0])<<15+(((int64_t)Sensores.C[addr][2])* ((int64_t)dT))>>8;
			P_temp=(((int64_t)D1)*SENS>>21-OFF)>>15;
			//Sensores.P[addr]=D1;	

		}		
	}	
}

void init_timer(void)
{
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	TCCR1B |=  (1 << CS10);//preescaler 1024
	TIMSK1 |= (1<<TOIE1);//habilita interrupcion de overflow

}

volatile uint8_t TIMER1_4,TIMER1_3;
uint8_t counter_byte=0;

ISR(TIMER1_OVF_vect)
{
//	TIMER1_3=TIMER1_3+1;

	if(TIMER1_3<0xff)
	{
		TIMER1_3=TIMER1_3+1;	}		
	else
	{

		TIMER1_3=0;
		TIMER1_4=TIMER1_4+1;
	}
		
				//LAST=TIMER1_4<<8+TIMER1_3;
		/*		if( (PORTB &_BV(PORTB1))==_BV(PORTB1))
					PORTB &= ~_BV(PORTB1);
				else 
					PORTB |= _BV(PORTB1);*/
			
}
void init_spi_slave_HW(void)
{
	DDRB &= ~_BV(DDB5);//CLK INPUT
	DDRB |= _BV(DDB4);//MISO OUTPUT
	DDRB &= ~_BV(DDB3);//MOSI INPUT
	DDRB &= ~_BV(DDB2);//SS INPUT

	SPCR = (1<<SPE)|(1<<SPIE);//enable SPi
}



char CONFIGURE_DATA_1( void )
{
	uint8_t ESP=0x00;

	if((VAL_IN &0xa0)==0xa0)//pedir tipo de sensor
	{
		ESP=(Sensores.Tipo[VAL_IN&0x0f]=='T')?0x20:(Sensores.Tipo[VAL_IN&0x0f]=='B')?0x80:0x00;
		ESP=ESP+VAL_IN&0x0f;
		CODE=VAL_IN &0x50;
	}
	else if((VAL_IN &0x50)==0x50)//pedir lectura
	{
		counter_byte=0;
		ID=VAL_IN &0x0f;
		CODE=VAL_IN &0x50;
	}

	if(CODE==0x50)
	{
	
		if(Sensores.Tipo[ID]=='T')
		{
			switch(counter_byte)
			{
				case 0:ESP=(uint8_t)((Sensores.T[ID]>>8)&0xff)|(ID<<4); break;
				case 1:ESP=(uint8_t)((Sensores.T[ID]   )&0xff);CODE=0x00; break;
				default : ESP=0;
			}
		}
		else if(Sensores.Tipo[ID]=='B')
		{
			switch(counter_byte)
			{
				case 0:ESP=((uint8_t)( (Sensores.P[ID]>>16)&0xff))|(ID<<4) ;break;
				case 1:ESP= (uint8_t)( (Sensores.P[ID]>>8 )&0xff);break;
				case 2:ESP= (uint8_t)( (Sensores.P[ID]	  )&0xff);break;
				case 3:ESP= (uint8_t)( (Sensores.T[ID]>>8 )&0xff);break;
				case 4:ESP= (uint8_t)( (Sensores.T[ID]    )&0xff);CODE=0x00;break;
				default : ESP=0x00;
			}
		}
		else ESP=0x00;

		counter_byte=counter_byte+1;
	}
	

		 
	return ESP;

}
CONFIGURE_DATA_2(void)
{
	//secuencia devuelve secuencia 
	//al ingrsar clock
	uint8_t ESP=0x00;
	if(counter_byte>14) counter_byte=0;
	else counter_byte=counter_byte+1;

	switch(counter_byte){
		case 0:ESP=0;break;
		case 1:ESP=1;break;
		case 2:ESP=2;break;
		case 3:ESP=3;break;
		case 4:ESP=4;break;
		case 5:ESP=5;break;
		case 6:ESP=6;break;
		case 7:ESP=7;break;
		case 8:ESP=8;break;
		case 9:ESP=9;break;
		case 10:ESP=10;break;
		case 11:ESP=11;break;
		case 12:ESP=12;break;
		case 13:ESP=13;break;
		case 14:ESP=14;break;
		case 15:ESP=15;break;
	default :ESP=0x00;
		}

	return ESP;

}

CONFIGURE_DATA_3(void )
{
	//revisar si se estan guardando la informacion de calibracion
	//del sensor barometrico SS.
	uint8_t ESP=0x00;
	uint8_t SS=0;
	if(counter_byte>10) counter_byte=0;
	else counter_byte=counter_byte+1;

	switch(counter_byte)
	{
		case 0:ESP=(uint8_t)((Sensores.C[SS][0]>>8)&0xff);break;
		case 1:ESP=(uint8_t)((Sensores.C[SS][0]>>0)&0xff);break;
		case 2:ESP=(uint8_t)((Sensores.C[SS][1]>>8)&0xff);break;
		case 3:ESP=(uint8_t)((Sensores.C[SS][1]>>0)&0xff);break;
		case 4:ESP=(uint8_t)((Sensores.C[SS][2]>>8)&0xff);break;
		case 5:ESP=(uint8_t)((Sensores.C[SS][2]>>0)&0xff);break;
		case 6:ESP=(uint8_t)((Sensores.C[SS][3]>>8)&0xff);break;
		case 7:ESP=(uint8_t)((Sensores.C[SS][3]>>0)&0xff);break;
		case 8:ESP=(uint8_t)((Sensores.C[SS][4]>>8)&0xff);break;
		case 9:ESP=(uint8_t)((Sensores.C[SS][4]>>0)&0xff);break;
		case 10:ESP=(uint8_t)((Sensores.C[SS][5]>>8)&0xff);break;
		case 11:ESP=(uint8_t)((Sensores.C[SS][5]>>0)&0xff);break;
		default :ESP=0x00;
	}

	return ESP;

}





ISR(SPI_STC_vect)
{
	//check SPSR WCOL SPIF
	//SPSR=0;
	
	VAL_IN=SPDR;
	SPDR=CONFIGURE_DATA_1();
	//SPDR=CONFIGURE_DATA_2();//para probar comunicacion se entre secuencia [0,15]
	//SPDR=CONFIGURE_DATA_1();//revisa los parametros guardados para un sensor barometrico


}
int set_delay_loop(){

	//INFO DE LOS TIEMPOS
	//Sensor barometrico tiene pausas de espera desde que se inicia la conversion hasta que el valor es obtenible
	//durante el tiempo de espera no hay qe subir el ChipSelect
	//OSR/tiempo[ms]
	//4096/7.4-9.04
	//2048/3.72-4.54
	//1024/1.88-2.28
	//512/0.95-1.17
	//256/0.48-0.6
	//8 clock pedir dato
	//32 clock lectura
	//(80 clock despreciable clk=7 us)0.560[ms] +18.8[ms] conversion=18.360[ms]

	//Sensor de temperatura siempre convierte, esperar entre tiempos un total de 220[ms]
	//(16 clock despreciable clk=7 us)0.116[ms] 
	int i;
	uint8_t delay_ms_loop=0;
	uint8_t delay_us_loop=0;
	char need_delay=0;
	
	for(i=0;i<8;i++)
	{	
		if(Sensores.Tipo[i]=='T')
		{
			delay_us_loop=delay_us_loop+116;
			need_delay=1;		
		}	
		if(Sensores.Tipo[i]=='B')
			delay_us_loop=delay_us_loop+18360;
	}

	delay_us_loop=220000-delay_us_loop;
	if(need_delay==1)delay_ms_loop=delay_us_loop/1000;
	else delay_ms_loop=0;

	return delay_ms_loop;


}
	

int main (void)
{
	int j;
	//inilizacion perifericos------------------------------------+++++++++++++++++++++++++++
	init_spi_slave_HW();//inicilaizacion del SPI HW y activacion de interrupcion
	// esta la funcion para un contador mas grande init_timer();//inicilaizacion del timer y activacion de interrupcion
	sei();//activa interrupciones globales	
	//------------------------------------------------------------++++++++++++++++++++++++++

	//inicilaizacion sensores-------------------------------------+++++++++++++++++++++++++++
	//set_tipo_sensor('T','T','T','T','T','T','T','T');//N=ninguno, B=barometrico, T=termocupla	
	set_tipo_sensor('B','T','N','N','N','N','N','N');//N=ninguno, B=barometrico, T=termocupla	
	int delay_loop_ms=set_delay_loop();
	//set_T(0x01020304,0x05060708,0x090a0b0c,0x0d0e0f10,0x11121314,0x15161718,0x191a1b1c,0x1d1e1f20);	
	set_T(0x01010101,0x01020304,0x03030303,0x04040404,0x05050505,0x06060606,0x07070707,0x08080808);	
	//set_T(0,0,0,0,0,0,0,0);
	init_spi_soft();//inicilaizacion del SPIsoftware
	reset_barometricos();
	get_parametros_barometricos();
	//------------------------------------------------------------+++++++++++++++++++++++++++
	uint16_t LAST=0;
	DDRB |= _BV(DDB1);
	


 	while(1) {
  		
		get_mediciones();
		for(j=0;j<delay_loop_ms;j++)_delay_ms(1);// si esto hace problema comentar y poner delay de 220
		//_delay_ms(220);
		
		}
}





