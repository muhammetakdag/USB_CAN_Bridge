
#include <stdint.h>

/*------------------------------------------------------
                ##### MACRO DEFINATIONS ##### 
------------------------------------------------------*/

#define GPIOC_BASE_ADDRESS 0x40011000UL

#define GPIO_OUTPUT_PP 0U
#define GPIO_OUTPUT_10MHz 1U

/*------------------------------------------------------
                ##### USER DEFINE TYPES ##### 
------------------------------------------------------*/

typedef struct _GPIO_typedef_t{
    volatile uint32_t GPIOx_CRL; /* represents pin 0 to pin 7 */
    volatile uint32_t GPIOx_CRH; /* represents pin 8 to pin 15 */
    volatile uint32_t GPIOx_IDR;
    volatile uint32_t GPIOx_ODR;
    volatile uint32_t GPIOx_BSRR;
    volatile uint32_t GPIOx_BRR;
    volatile uint32_t GPIOx_LCKR;
}GPIO_typedef_t;

/*------------------------------------------------------
                ##### STATIC GLOBAL VARIABLE ##### 
------------------------------------------------------*/

static GPIO_typedef_t* s_gpio_port_c = (GPIO_typedef_t*) GPIOC_BASE_ADDRESS;

/*------------------------------------------------------
                ##### STATIC FUNCTIONS ##### 
------------------------------------------------------*/

static void s_port_c_pin_init(void){
    /* First clear the bits */
    s_gpio_port_c->GPIOx_CRH &= ~(0xF << 20U);
    /* Then write the config */
    s_gpio_port_c->GPIOx_CRH |= (GPIO_OUTPUT_PP << 22U);
    s_gpio_port_c->GPIOx_CRH |= (GPIO_OUTPUT_10MHz << 20U);
}

/*------------------------------------------------------
                ##### GLOBAL FUNCTIONS ##### 
------------------------------------------------------*/

void gpio_init(void){
    s_port_c_pin_init();
}

void LED_pin_high(void){
    s_gpio_port_c->GPIOx_ODR |= (1U << 13U);
}

void LED_pin_low(void){
    s_gpio_port_c->GPIOx_ODR &= ~(1U << 13U);
}