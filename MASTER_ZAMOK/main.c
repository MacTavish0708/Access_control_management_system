#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"



//all_init//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GPIO_InitTypeDef port;
SPI_InitTypeDef spi;
uint8_t sendData;
uint16_t data;
int tiktak = 0;
int i;

void initAll() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    SPI_StructInit(&spi);
    spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spi.SPI_Mode = SPI_Mode_Master;
    spi.SPI_DataSize = SPI_DataSize_8b;
    spi.SPI_CPOL = SPI_CPOL_Low;
    spi.SPI_CPHA = SPI_CPHA_2Edge;
    spi.SPI_NSS = SPI_NSS_Soft;
    spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    spi.SPI_FirstBit = SPI_FirstBit_MSB;
    spi.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &spi);

    GPIO_StructInit(&port);
    port.GPIO_Mode = GPIO_Mode_AF_PP;
    port.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    port.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &port);

	//button//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    port.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_1 | GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    port.GPIO_Mode = GPIO_Mode_IPU;
    port.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &port);

    port.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    port.GPIO_Mode = GPIO_Mode_IPU;
    port.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &port);

	//led_and_buzzer//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    port.GPIO_Mode = GPIO_Mode_Out_PP;
    port.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    port.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &port);
}



//blink/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void blink(){
	GPIOA->ODR ^= GPIO_Pin_1;
	for(i=0;i<0x100000;i++);
	GPIOA->ODR ^= GPIO_Pin_1;
	for(i=0;i<0x100000;i++);
}



//fun_button//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int tiktak1 = 0;
int tiktak2 = 0;
int tiktak3 = 0;
int tiktak4 = 0;
int tiktak5 = 0;
int tiktak6 = 0;
int tiktak7 = 0;
int tiktak8 = 0;
int tiktak9 = 0;
int tiktak0 = 0;

int funbut(int r){
	//1//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak1=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0) {
		blink();
		if (tiktak1==0){
			sendData = 0x01;
			tiktak1=1;
			r++;
		}
	}

	//2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak2=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0) {
		blink();
		if (tiktak2==0){
			sendData = 0x02;
			tiktak2=1;
			r++;
		}
	}

	//3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak3=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) {
		blink();
		if (tiktak3==0){
			sendData = 0x03;
			tiktak3=1;
			r++;
		}
	}

	//4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	tiktak4=0;
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14) == 0) {
		blink();
		if (tiktak4==0){
			sendData = 0x04;
			tiktak4=1;
			r++;
		}
	}

	//5/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak5=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0) {
		blink();
		if (tiktak5==0){
			sendData = 0x05;
			tiktak5=1;
			r++;
		}
	}

	//6/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak6=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0) {
		blink();
		if (tiktak6==0){
			sendData = 0x06;
			tiktak6=1;
			r++;
		}
	}

	//7/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak7=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0) {
		blink();
		if (tiktak7==0){
			sendData = 0x07;
			tiktak7=1;
			r++;
		}
	}

	//8/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak8=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0) {
		blink();
		if (tiktak8==0){
			sendData = 0x08;
			tiktak8=1;
			r++;
		}
	}

	//9/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak9=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0) {
		blink();
		if (tiktak9==0){
			sendData = 0x09;
			tiktak9=1;
			r++;
		}
	}

	//0/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak0=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0) {
		blink();
		if (tiktak0==0){
			sendData = 0x10;
			tiktak0=1;
			r++;
		}
	}
	return r;
}



//check/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tik_tak(){
	switch(tiktak){

		case 0:
			sendData = 0x00;
			SPI_I2S_SendData(SPI2, sendData);
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0) {
				for(i=0;i<0x100000;i++);
			    GPIO_SetBits(GPIOA, GPIO_Pin_0);
			    tiktak = 1;
			}
			if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15) == 0) {
				for(i=0;i<0x100000;i++);
			    GPIO_SetBits(GPIOA, GPIO_Pin_3);
			    tiktak = 2;
			}
			break;

		case 1:
			sendData = 0x12;
			SPI_I2S_SendData(SPI2, sendData);
			int q = 0;

			while(q != 4) {
				q = funbut(q);
				if ((tiktak1 == 1)||(tiktak2 == 1)||(tiktak3 == 1)||(tiktak4 == 1)||(tiktak5 == 1)||(tiktak6 == 1)||(tiktak7 == 1)||(tiktak8 == 1)||(tiktak9 == 1)||(tiktak0 == 1)){
					SPI_I2S_SendData(SPI2, sendData);
					sendData = 0x12;
				}
			}

			for(i=0;i<0x100000;i++);
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			q = 0;
			tiktak = 0;
			break;

		case 2:
			for(i=0;i<0x100000;i++);
			for(i=0;i<0x100000;i++);
			GPIO_ResetBits(GPIOA, GPIO_Pin_3);
			blink();
			blink();
			sendData = 0x11;
			SPI_I2S_SendData(SPI2, sendData);
			tiktak = 0;
			break;
		}
}


uint16_t counter;
//main//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void) {
    __enable_irq();
    initAll();
    SPI_Cmd(SPI2, ENABLE);

    sendData = 0x00;
    while (1) {
    	counter++;
    	if(counter == 15000){
    		counter = 0;
    		tik_tak();
    	}
	}
}
