#include <stdint.h>

/*------------------------------------------------------
                ##### MACRO DEFINATIONS ##### 
------------------------------------------------------*/

#define FLASH_BASE_ADDRESS 0x40022000UL

#define FLASH_LATENCY_2_WAIT_STATE (2U << 0U)
#define FLASH_ACR_PRFTBE (1U << 4U)

/*------------------------------------------------------
                ##### USER DEFINE TYPES ##### 
------------------------------------------------------*/
//TODO: Add  comment to member, what is the stand for.
typedef struct _FLASH_typedef_t{
    volatile uint32_t ACR; /* Access control register. */
    volatile uint32_t KEYR; 
    volatile uint32_t OPTKEYR;
    volatile uint32_t SR;
    volatile uint32_t CR;
    volatile uint32_t AR;
    volatile uint32_t RFU; /* Reserved feature use. */
    volatile uint32_t OBR;
    volatile uint32_t WRPR; 
}FLASH_typedef_t;

/*------------------------------------------------------
                ##### STATIC GLOBAL VARIABLE ##### 
------------------------------------------------------*/

static FLASH_typedef_t* flash = (FLASH_typedef_t*) FLASH_BASE_ADDRESS;

/*------------------------------------------------------
                ##### GLOBAL FUNCTIONS ##### 
------------------------------------------------------*/

void set_flash_latency(void){
    flash->ACR &= ~(7U << 0U);
    flash->ACR |= FLASH_LATENCY_2_WAIT_STATE;
    flash->ACR |= FLASH_ACR_PRFTBE;
}