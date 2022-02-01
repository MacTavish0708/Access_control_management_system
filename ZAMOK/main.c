#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "string.h"



int tiktak = 0;
char str0[5];
int i;
int error = 0;
char str1[5] ="1111";



//delay//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Delay(u32 ticks){
	while(ticks != 0) ticks--;
}



//clean//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void clean(char var[]){
	for(int k=strlen(var)-1; k>=0; k--)
	{
		var[k] = '\0';
	}
}



//all_init//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GPIO_InitTypeDef port;
SPI_InitTypeDef spi;
uint8_t data;
uint8_t needUpdate;

void initAll() {
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    SPI_StructInit(&spi);
    spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    spi.SPI_Mode = SPI_Mode_Slave;
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
    port.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |  GPIO_Pin_8 | GPIO_Pin_9;
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

void funbut(char str[5]){
	//1//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak1=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0) {
		blink();
		if (tiktak1==0){
			strcat(str, "1");
			tiktak1=1;
		}
	}

	//2/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak2=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0) {
		blink();
		if (tiktak2==0){
			strcat(str, "2");
			tiktak2=1;
		}
	}

	//3/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak3=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) {
		blink();
		if (tiktak3==0){
			strcat(str, "3");
			tiktak3=1;
		}
	}

	//4/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak4=0;
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14) == 0) {
		blink();
		if (tiktak4==0){
			strcat(str, "4");
			tiktak4=1;
		}
	}

	//5/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak5=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0) {
		blink();
		if (tiktak5==0){
			strcat(str, "5");
			tiktak5=1;
		}
	}

	//6/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak6=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == 0) {
		blink();
		if (tiktak6==0){
			strcat(str, "6");
			tiktak6=1;
		}
	}

	//7/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak7=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0) {
		blink();
		if (tiktak7==0){
			strcat(str, "7");
			tiktak7=1;
		}
	}

	//8/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak8=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0) {
		blink();
		for(i=0;i<0x100000;i++);
		if (tiktak8==0){
			strcat(str, "8");
			tiktak8=1;
		}
	}

	//9/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak9=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) == 0) {
		blink();
		if (tiktak9==0){
			strcat(str, "9");
			tiktak9=1;
		}
	}

	//0/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	tiktak0=0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0) {
		blink();
		if (tiktak0==0){
			strcat(str, "0");
			tiktak0=1;
		}
	}
}



//check/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void tik_tak(){
	switch(tiktak){

		case 0:
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0) {
				for(i=0;i<0x100000;i++);
			    GPIO_SetBits(GPIOA, GPIO_Pin_0);
			    tiktak = 1;
			}
			if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_15) == 0) {
				for(i=0;i<0x100000;i++);
			    GPIO_SetBits(GPIOA, GPIO_Pin_2);
			    tiktak = 3;
			}
			break;

		case 1:
			funbut(str0);
			if (error < 3){
				if (strlen(str0) == 4){
						if (strcmp(str0, str1) == 0){
							GPIO_ResetBits(GPIOA, GPIO_Pin_0);
							GPIO_SetBits(GPIOA, GPIO_Pin_2);
							clean(str0);
							error = 0;
							GPIO_SetBits(GPIOA, GPIO_Pin_8);
							Delay(50000000);
							GPIO_ResetBits(GPIOA, GPIO_Pin_2);
							GPIO_ResetBits(GPIOA, GPIO_Pin_8);
							tiktak = 0;
						}
						else {
							GPIOA->ODR ^= GPIO_Pin_3;
							for(i=0;i<0x100000;i++);
							GPIOA->ODR ^= GPIO_Pin_3;
							for(i=0;i<0x100000;i++);
							error++;
							clean(str0);
						}
					}
			}
			else {
				GPIO_ResetBits(GPIOA, GPIO_Pin_0);
				tiktak = 2;
				clean(str0);
				error = 0;
			}
			break;

		case 2:
			GPIO_SetBits(GPIOA, GPIO_Pin_9);
			break;

		case 3:
			clean(str0);
			error = 0;
			GPIO_SetBits(GPIOA, GPIO_Pin_8);
			Delay(50000000);
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);
			tiktak = 0;
			break;
		}
}



//case//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void case_case(char str[4]){
	switch (data) {
	case 0x01:
		strcat(str, "1");
		blink();
		break;

	case 0x02:
		strcat(str, "2");
		blink();
		break;

	case 0x03:
		strcat(str, "3");
		blink();
		break;

	case 0x04:
		strcat(str, "4");
		blink();
		break;

	case 0x05:
		strcat(str, "5");
		blink();
		break;

	case 0x06:
		strcat(str, "6");
		blink();
		break;

	case 0x07:
		strcat(str, "7");
		blink();
		break;

	case 0x08:
		strcat(str, "8");
		blink();
		break;

	case 0x09:
		strcat(str, "9");
		blink();
		break;

	case 0x10:
		strcat(str, "0");
		blink();
		break;
	}
}



//main//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void) {
    __enable_irq();
    initAll();
    SPI_Cmd(SPI2, ENABLE);
    NVIC_EnableIRQ(SPI2_IRQn);

    SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);

    while (1) {
    	 if (needUpdate == 1){
		switch(data){
		case 0x00:
			tik_tak();
			break;

		case 0x11:
			GPIO_ResetBits(GPIOA, GPIO_Pin_9);
			tiktak = 0;
			data = 0x00;
			break;

		case 0x12:
			GPIO_SetBits(GPIOA, GPIO_Pin_0);
			clean(str1);
			int q = 0;
			while(q != 4)
			{
				q = strlen(str1);
				case_case(str1);
				data = 0x12;
			}
			blink();
			blink();
			blink();
			blink();
			blink();
			data = 0x00;
			q = 0;
			GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			break;
		}
        needUpdate = 0;
		}
	}
}



//data_spi//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SPI2_IRQHandler(){
    data = SPI_I2S_ReceiveData(SPI2);
    needUpdate = 1;
}





