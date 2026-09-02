#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sdata, _edata, _sidata;
extern uint32_t _sbss, _ebss;

int main(void);

void Default_Handler(void) {
    while (1);
}

void Reset_Handler(void) {
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }

    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }

    main();
    while (1);
}

__attribute__((section(".isr_vector"), used, aligned(256)))
const uint32_t g_pfnVectors[] = {
    (uint32_t)&_estack,
    (uint32_t)&Reset_Handler,
    (uint32_t)&Default_Handler, // NMI
    (uint32_t)&Default_Handler, // HardFault
    (uint32_t)&Default_Handler, // MemManage
    (uint32_t)&Default_Handler, // BusFault
    (uint32_t)&Default_Handler, // UsageFault
    0, 0, 0, 0,                 // Reserved
    (uint32_t)&Default_Handler, // SVCall
    (uint32_t)&Default_Handler, // DebugMon
    0,                          // Reserved
    (uint32_t)&Default_Handler, // PendSV
    (uint32_t)&Default_Handler, // SysTick
};