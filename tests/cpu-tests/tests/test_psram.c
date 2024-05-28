/**
 * @file test_psram.c
 * @author Yangyang Zhu (1929772352@qq.com)
 * @version 0.1
 * @date 2024-05-03
 * 
 * @copyright Copyright (c) 2024
 * write to psram, and then read from it. 
 */

#include "am.h"
#include <stdint.h>
#include "klib.h"

#define PSRAM_ADDR 0x80000000
#define PSRAM_SIZE 0x400000

#define UART_BASE 0x10000000L
#define UART_TX   0x0L

static inline uint8_t  inb(uintptr_t addr) { return *(volatile uint8_t  *)addr; }
static inline uint16_t inw(uintptr_t addr) { return *(volatile uint16_t *)addr; }
static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }

static inline void outb(uintptr_t addr, uint8_t  data) { *(volatile uint8_t  *)addr = data; }
static inline void outw(uintptr_t addr, uint16_t data) { *(volatile uint16_t *)addr = data; }
static inline void outl(uintptr_t addr, uint32_t data) { *(volatile uint32_t *)addr = data; }

void putstr(char *p, int size) {
    for (int i = 0; i < size; i++)
        outb(UART_BASE + UART_TX, p[i]);
}


int main(void) {
    outl(PSRAM_ADDR, 0xdeadbeef);
    int n = 1000;
    while(n--);
    // uint32_t a = inl(PSRAM_ADDR + PSRAM_SIZE - 4);
    uint32_t a = inl(PSRAM_ADDR);
    // printf("a:%x\n", a);

    // if (a == 0xbeefdead) {
    if (a == 0xdeadbeef) {
        char p[] = "test pass!\n";
        putstr(p, sizeof(p)/sizeof(char));
    } else {
        char p[] = "test failed!\n";
        putstr(p, sizeof(p)/sizeof(char));
    }
    return 0;
}
