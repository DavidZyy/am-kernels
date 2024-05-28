#include "am.h"
#include <stdint.h>

#define SPI_BASE 0x10001000
// #define SPI_BASE 0x00000000
#define SPI_TX0 0x00
#define SPI_TX1 0x04
#define SPI_RX0 0x00
#define SPI_CTRL 0x10
#define SPI_DIVIDER 0x14
#define SPI_SS 0x18

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

uint32_t bswap32(uint32_t x) {
    return ((x & 0x000000FF) << 24) |
           ((x & 0x0000FF00) << 8)  |
           ((x & 0x00FF0000) >> 8)  |
           ((x & 0xFF000000) >> 24);
}

int main() {
    // outl(SPI_BASE + SPI_DIVIDER, 0x2); // set divider to 2

    outl(SPI_BASE + SPI_SS, 0x01); // flash is 0, set ss[0] to 1. 32 bit totally, 8 bit cmd, 24 bit addr.

    // char_len is set to 64, so spi assume the data is 64, it see it as
    // 0x00000000 03000000, and transfer from 00000000(MSB), should 
    // adjust this first, as 0x03000000 00000000.
    // outl(SPI_BASE + SPI_TX0, 0x00000000); // send command and address of flash

    // transfer bits width is 64, and mode is MSB, so begin from TX1.
    outl(SPI_BASE + SPI_TX1, 0x03000004); // send command and address of flash


    // 0x100 means set go busy, 0x2040 means from left to right, ass = 1, chen_len = 64
    outl(SPI_BASE + SPI_CTRL, (0x100 | 0x2040)); // write 1 to GO_BSY to start transfer

    int n = 50;
    while (n--) {
        uint32_t a = inl(SPI_BASE + SPI_CTRL);
        if (a & 0x100) { // still in transfer(master to slave)
                char p[] = "in transfer\n";
                putstr(p, sizeof(p)/sizeof(char));
        } else { // maybe should wait for slave to master finish (see waveform if it reversed)
            uint32_t b = inl(SPI_BASE + SPI_RX0);
            b = bswap32(b);
            // b = __builtin_bswap32(b);
            if (b == 0xdeadbeef) {
                char p[] = "yes\n";
                putstr(p, sizeof(p)/sizeof(char));
            }
            else {
                char p[] = "no\n";
                putstr(p, sizeof(p)/sizeof(char));
            }
            break;
        }
    }

    return 0;
}
