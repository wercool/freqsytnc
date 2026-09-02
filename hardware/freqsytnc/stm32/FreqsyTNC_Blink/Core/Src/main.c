#include <stdint.h>

// RCC: GPIOE enable (bit 4)
#define RCC_BASE        0x58000000U
#define RCC_AHB2ENR     (*((volatile uint32_t *)(RCC_BASE + 0x4C)))

// GPIOE: Pin 4 (WeAct D1 Blue LED, Active-HIGH)
#define GPIOE_BASE      0x48001000U
#define GPIOE_MODER     (*((volatile uint32_t *)(GPIOE_BASE + 0x00)))
#define GPIOE_ODR       (*((volatile uint32_t *)(GPIOE_BASE + 0x14)))

int main(void) {
    // 1. Включаем тактирование GPIOE
    RCC_AHB2ENR |= (1U << 4);

    // 2. PE4 на выход (General Purpose Output, bits 9:8 -> 01)
    GPIOE_MODER &= ~(3U << (4 * 2));
    GPIOE_MODER |=  (1U << (4 * 2));

    while (1) {
        // Мигаем PE4
        GPIOE_ODR ^= (1U << 4);

        for (volatile uint32_t i = 0; i < 200000; i++) {
            __asm__("nop");
        }
    }
}