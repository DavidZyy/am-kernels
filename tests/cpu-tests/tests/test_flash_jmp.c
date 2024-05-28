#include "am.h"
#include <stdint.h>

#define SPI_BASE 0x10001000
#define SPI_TX0 0x00
#define SPI_TX1 0x04
#define SPI_RX0 0x00
#define SPI_CTRL 0x10
#define SPI_DIVIDER 0x14
#define SPI_SS 0x18

#define UART_BASE 0x10000000L
#define UART_TX   0x0L

// the begin of sram is data segment of this program, the end is stack of this program,
// so the load progarm to sram should in the middle of it, and have no data or stack.
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

int main() {
    outl(SPI_BASE + SPI_DIVIDER, 0x2); // set divider to 2

    outl(SPI_BASE + SPI_SS, 0x01); // flash is 0, set ss[0] to 1. 32 bit totally, 8 bit cmd, 24 bit addr.

    int inst_num = 100; // the number of instructions
    for (int i = 0; i < inst_num; i++) {
        uint32_t cmd = 0x03000000 + i*4; // addr and cmd of flash

        outl(SPI_BASE + SPI_TX1, cmd);
        // 0x100 means set go busy, 0x2040 means from left to right, ass = 1, chen_len = 64
        outl(SPI_BASE + SPI_CTRL, (0x100 | 0x2040));

        // cpu wait for spi to finsh tranfer.
        while (inl(SPI_BASE + SPI_CTRL) & 0x100);

        // read data.
        uint32_t b = inl(SPI_BASE + SPI_RX0);
        b = bswap32(b);

        uint32_t sramAddr = sramBase + i*4;
        // write data to sram
        outl(sramAddr, b);
    }
 
    // Define a function pointer type for functions that take no arguments and return void
    typedef void (*func)(void);
 
    // jmp sram to execute
    // Define a function pointer and assign it the address to jump to
    func funcPtr = (func)sramBase;
    funcPtr();

    // return here
    char p[] = "finish execute and return.\n";
    putstr(p, sizeof(p)/sizeof(char));

    return 0;
}

