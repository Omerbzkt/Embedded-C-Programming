#include <stdint.h>


volatile uint16_t adcValue = 0;

volatile uint32_t *pUSART2DataReg     = (uint32_t *) 0x40004404; // USART_DR    Register (address offset 0x04)
volatile uint32_t *pUSART2StatReg     = (uint32_t *) 0x40004400; // USART_SR    Register (address offset 0x00)

void USART2_SendData(uint8_t data) {
    // Wait until TXE (Transmit Data Register Empty) flag is set
    while (!(*pUSART2StatReg & (1 << 7)));
    *pUSART2DataReg = data;
}

int main(void)
{
	uint32_t *pClockRegisterAHB1 = (uint32_t *) 0x40023830; // RCC_AHB1ENR Register (address offset 0x30)
	uint32_t *pClockRegisterAPB2 = (uint32_t *) 0x40023844; // RCC_APB2ENR Register (address offset 0x44)
	uint32_t *pModeRegister      = (uint32_t *) 0x40020000; // GPIOA_MODER Register (address offset 0x00)
	uint32_t *pADC1ControlReg2   = (uint32_t *) 0x40012008; // ADC_CR2     Register (address offset 0x08)
	uint32_t *pADC1TimeReg       = (uint32_t *) 0x40012010; // ADC_SMPR2   Register (address offset 0x10)
	uint32_t *pADC1RSRegister3   = (uint32_t *) 0x40012034; // ADC_SQR3    Register (address offset 0x34)
	uint32_t *pADC1StatusReg     = (uint32_t *) 0x40012000; // ADC_SR      Register (address offset 0x00)
	uint32_t *pADC1DataRegister  = (uint32_t *) 0x4001204C; // ADC_DR      Register (address offset 0x4C)
	uint32_t *pClockRegisterAPB1 = (uint32_t *) 0x40023840; // RCC_APB1ENR Register (address offset 0x40)
	uint32_t *pGPIOAFRL          = (uint32_t *) 0x40020020; // GPIO_AFRL   Register (address offset 0x20)
	uint32_t *pUSART2BaudRate    = (uint32_t *) 0x40004408; // USART_BRR   Register (address offset 0x08)
	uint32_t *pUSART2Control     = (uint32_t *) 0x4000440C; // USART_CR1   Register (address offset 0x0C)
	uint32_t *pADC1ControlReg1   = (uint32_t *) 0x40012004; // ADC_CR1     Register (address offset 0x04)

	*pClockRegisterAHB1 |= (1 << 0);  // Enable GPIOA
	*pClockRegisterAPB2 |= (1 << 8);  // Enable ADC1
	*pClockRegisterAPB1 |= (1 << 17); // Enable USART2


	*pModeRegister &= ~((3 << 4) | (3 << 6)); // Clear bit space
	*pModeRegister |= (2 << 4) | (2 << 6);    // make alternate mode

	*pGPIOAFRL &= ~((0xF << 8) | (0xF << 12)); // Clear bit space
	*pGPIOAFRL |= (7 << 8) | (7 << 12);        // set AF7
	*pUSART2BaudRate = 0x0683; //9600 Baudrate, 16MHz APB1 clock
	*pUSART2Control = 0x000C;  // RX and TX enable
	*pUSART2Control |= 0x2000; // USART enable


	*pModeRegister &= ~(3 << 0); // Clear selected bits first
	*pModeRegister |= (3 << 0);  // Set PA0 to analog mode

	// ADC Configuration
	*pADC1ControlReg2 &= ~(1 << 0); // Close ADC
	//Select Resolution
	*pADC1ControlReg1 &= ~(3 << 24);
	*pADC1ControlReg1 |= (0 << 24);

	*pADC1RSRegister3 = 0;
	*pADC1TimeReg |= (3 << 0);
	*pADC1ControlReg2 |= (1 << 0);

	while(1){
	*pADC1ControlReg2 |= (1 << 30);
	while (!(*pADC1StatusReg & (1 << 1)));
	adcValue = (uint16_t)(*pADC1DataRegister);
	//USART2_SendData(adcValue);

	USART2_SendData((uint8_t)(adcValue & 0xFF));        // Send lower byte
	USART2_SendData((uint8_t)((adcValue >> 8) & 0xFF)); // Send upper byte

	}
}