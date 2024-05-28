#include "am.h"
#include <stdint.h>

#define flashBase 0x30000000
#define flashSize 0x10000000

#define UART_BASE 0x10000000L
#define UART_TX   0x0L

#define SPI_BASE 0x10001000
#define SPI_TX0 0x00
#define SPI_TX1 0x04
#define SPI_RX0 0x00
#define SPI_CTRL 0x10
#define SPI_DIVIDER 0x14
#define SPI_SS 0x18

#define UART_BASE 0x10000000L
#define UART_TX   0x0L

// the begin is data segment of this program, the end is stack of this program,
// so the load progarm should in the middle, and have no data or stack.
#define sramBase  0x0f000000L
#define sramSize  0x2000L

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

uint32_t bswap32(uint32_t x) {
    return ((x & 0x000000FF) << 24) |
           ((x & 0x0000FF00) << 8)  |
           ((x & 0x00FF0000) >> 8)  |
           ((x & 0xFF000000) >> 24);
}

/**
 *  the addr in flash, get addr(23,0)
 */
uint32_t flash_xip_method(uint32_t addr) {
    uint32_t a = inl(addr);
    return a;
}

/**
 *  the addr in flash, geth addr(23,0)
 */
uint32_t flash_no_xip(uint32_t addr) {
    outl(SPI_BASE + SPI_SS, 0x01); // flash is 0, set ss[0] to 1. 32 bit totally, 8 bit cmd, 24 bit addr.
    uint32_t cmd = 0x03000000 | ((uint16_t)addr & 0xffffffff);
    outl(SPI_BASE + SPI_TX1, cmd);
    // 0x100 means set go busy, 0x2040 means from left to right, ass = 1, chen_len = 64
    outl(SPI_BASE + SPI_CTRL, (0x100 | 0x2040));
    while (inl(SPI_BASE + SPI_CTRL) & 0x100); //polling
    uint32_t a = inl(SPI_BASE + SPI_RX0);
    return a;
}


int main() {
    uint32_t a = flash_xip_method(flashBase + 4);
    // uint32_t a = flash_no_xip(flashBase + 4);

    if (a == 0xdf002117) {
        char p[] = "test pass!\n";
        putstr(p, sizeof(p)/sizeof(char));
    } else {
        char p[] = "test failed!\n";
        putstr(p, sizeof(p)/sizeof(char));
    }
    
    return 0;
}
