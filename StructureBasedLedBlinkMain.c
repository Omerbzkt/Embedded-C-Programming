#include <stdio.h>
#include <stdint.h>
#include "main.h"

int main(void){

	RCC_AHB1ENR_t volatile *const pClkCtrlReg = (RCC_AHB1ENR_t*)0x40023830;
	GPIOx_MODER_t volatile *const pModerReg = (GPIOx_MODER_t*)0x40020400;
	GPIOx_ODR_t volatile *const pOutReg = (GPIOx_ODR_t*)0x40020414;

	// enable RCC clock
	pClkCtrlReg ->   GPIOCEN = 1;

	// configure moder as output
	pModerReg   ->   MODER13 = 1;

	while(1){
		// configure ODR as HIGH
		pOutReg     ->   ODR13   = 1;

		for(uint32_t i=0; i<300000;i++);

		// configure ODR as LOW
		pOutReg     ->   ODR13   = 1;

		for(uint32_t i=0; i<300000;i++);
	}
}
