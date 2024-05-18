#include <stdint.h>

int main(void)
{
		uint32_t *pClockReg = (uint32_t*) 0x40023830;
		uint32_t *pModeReg  = (uint32_t*) 0x40020800;
		uint32_t *pOutReg   = (uint32_t*) 0x40020814;
		uint32_t *pModeRegA = (uint32_t*) 0x40020000;
		uint32_t *pInRegA   = (uint32_t*) 0x40020010;

		// Enable the Clock
		*pClockReg |= (1<<2); // GPIOC
		*pClockReg |= (1<<0); // GPIOA

		// configure mode register as an output
		*pModeReg &= ~(3<<26);
		*pModeReg |= (1<<26);

		// configure PA0 as input
		*pModeRegA &= ~(3<<0);


		while(1){
			// read the pin status PA0
			uint8_t pinStatus = (uint8_t) (*pInRegA & 0x1);
			if(pinStatus){
				*pOutReg |= (1<<13);
			}else{
				*pOutReg &= ~(1<<13);
			}
		}
}