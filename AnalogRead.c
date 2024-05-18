#include <stdint.h>

volatile uint16_t adcValue = 0;

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
	uint32_t *pADC1ControlReg1   = (uint32_t *) 0x40012004; // ADC_CR1     Register (address offset 0x04)

	*pClockRegisterAHB1 |= (1 << 0);  // Enable GPIOA
	*pClockRegisterAPB2 |= (1 << 8);  // Enable ADC1

	*pModeRegister &= ~(3 << 0); // Clear selected bits first
	*pModeRegister |= (3 << 0);  // Set PA0 to analog mode

	// ADC Configuration
	*pADC1ControlReg2 &= ~(1 << 0); // Close ADC

	// Define Resolution
	*pADC1ControlReg1 &= ~(3 << 24);
	*pADC1ControlReg1 |= (2 << 24);

	// Select Channel
	*pADC1RSRegister3 = 0;

	// Select Sample rate
	*pADC1TimeReg |= (3 << 0);

	// Open ADC
	*pADC1ControlReg2 |= (1 << 0);

	while(1){
	*pADC1ControlReg2 |= (1 << 30);
	while (!(*pADC1StatusReg & (1 << 1)));
	adcValue = (uint16_t)(*pADC1DataRegister);
	}
}