
#include <stdint.h>
#include "../Inc/flash.h"

/*------------------------------------------------------
                ##### MACRO DEFINATIONS ##### 
------------------------------------------------------*/

#define RCC_BASE_ADDRES 0x40021000UL

#define RCC_ENABLE_HSE_BIT (1U << 16U)
#define RCC_HSE_IS_READY_BIT (1U << 17U)

#define RCC_PLL_ENABLE_BIT (1U << 24U)
#define RCC_PLL_IS_READY_BIT (1U << 25U)
#define RCC_PLL_HSE_CLK_BIT (1U << 16U)
#define RCC_PLL_MULTIP_FACTOR_BIT (7U << 18U)

#define RCC_SYS_CLK_SW_PLL_BIT (2U << 0U)
#define RCC_SYS_CLK_SW_PLL_CONF (0x08U)
#define RCC_SYS_CLK_SWS_MASK (0x0CU)

#define RCC_SET_APB_PSC (4U << 8U)

#define RCC_CAN_CLK_ENABLE_BIT (1U << 25U)
#define RCC_USB_CLK_ENABLE_BIT (1U << 23U)
#define RCC_GPIOC_CLK_ENABLE_BIT (1U << 4U)


/*------------------------------------------------------
                ##### USER DEFINE TYPES ##### 
------------------------------------------------------*/

typedef struct _RCC_typedef_t {
    volatile uint32_t CR; /* Clock control reg. */
    volatile uint32_t CFGR; /* Clock configuration reg. */
    volatile uint32_t CIR; /* Clock interrupt reg. */
    volatile uint32_t APB2RSTR; /* APB2 peripheral reset reg. */
    volatile uint32_t APB1RSTR; /* APB1 peripheral reset reg. */
    volatile uint32_t AHBENR; /* AHB peripheral clock enable reg. */
    volatile uint32_t APB2ENR; /* APB2 peripheral clock enable reg. */
    volatile uint32_t APB1ENR; /* APB1 peripheral clock enable reg. */
    volatile uint32_t BDCR; /* Backup domain control register. */
    volatile uint32_t CSR; /* Control/status reg. */
}RCC_typedef_t;

/*------------------------------------------------------
                ##### STATIC GLOBAL VARIABLE ##### 
------------------------------------------------------*/

static RCC_typedef_t* rcc = (RCC_typedef_t*) RCC_BASE_ADDRES;

/*------------------------------------------------------
                ##### STATIC FUNCTIONS ##### 
------------------------------------------------------*/

/* Enable the HSE bit on the RCC reg */
static void s_hse_init(void){
    /* enable the external crystal */
    rcc->CR |= RCC_ENABLE_HSE_BIT;
    /* wait for the untill external crystal being ready */
    while(!((rcc->CR) & RCC_HSE_IS_READY_BIT));

}

/* Configure the PLL. */
static void s_pll_init(void){
    /* select the pll clk source */
    rcc->CFGR |= RCC_PLL_HSE_CLK_BIT;
    /* 72mhz/8mhz = 9 rm0008 page:102, for x9 = 0111 */
    rcc->CFGR &= ~(0xFU << 18U);
    rcc->CFGR |= RCC_PLL_MULTIP_FACTOR_BIT;
    /* enable the pll*/
    rcc->CR |= RCC_PLL_ENABLE_BIT;
    /* wait for the untill pll became ready */
    while(!((rcc->CR) & RCC_PLL_IS_READY_BIT));
}

/* Switch the clock source. */
static void s_sys_clk_sw(void){
    rcc->CFGR |= RCC_SYS_CLK_SW_PLL_BIT;
    while((rcc->CFGR & RCC_SYS_CLK_SWS_MASK) != RCC_SYS_CLK_SW_PLL_CONF);
}

/* Set the APB1 bus prescelar. RM0008 page:103, APB1 max = 36MHz */
static void s_set_APB_1_psc(void){
    rcc->CFGR |= RCC_SET_APB_PSC;
}

/* Enable the CAN peripheral clk. */
static void s_CAN_clk_enable(void){
    rcc->APB1ENR |= RCC_CAN_CLK_ENABLE_BIT;
} 

/* Enable the USB peripheral clk. */
static void s_USB_clk_enable(void){
    rcc->APB1ENR |= RCC_USB_CLK_ENABLE_BIT;
}

/* Enable the GPIOC peripheral clk. */
static void s_GPIOC_clk_enable(void){
    rcc->APB2ENR |= RCC_GPIOC_CLK_ENABLE_BIT;
}

/*------------------------------------------------------
                ##### GLOBAL FUNCTIONS ##### 
------------------------------------------------------*/

void mcu_clk_init(void){
    s_hse_init();
    set_flash_latency();
    s_set_APB_1_psc();
    s_pll_init();
    s_sys_clk_sw();
}

void peripheral_clk_init(void){
    s_CAN_clk_enable();
    s_USB_clk_enable();
    s_GPIOC_clk_enable();
}