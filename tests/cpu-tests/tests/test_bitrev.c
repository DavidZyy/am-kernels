#include "am.h"
#include <stdint.h>

#define SPI_BASE 0x10001000
#define SPI_TX0 0x00
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


int main() {
    outl(SPI_BASE + SPI_DIVIDER, 0x2); // set divider to 2

    outl(SPI_BASE + SPI_SS, 0x80); // bitrev is 7, set ss[7] to 1

    outl(SPI_BASE + SPI_TX0, 0xaa00); // send 0xaa

    // outl(SPI_BASE + SPI_CTRL, 0x2010); // ass = 1, chen_len = 16, others = 0
    outl(SPI_BASE + SPI_CTRL, (0x100 | 0x2010)); // write 1 to GO_BSY to start transfer

    // should set char_len correctly

    int n = 1000;
    while (n--) {
        uint32_t a = inl(SPI_BASE + SPI_CTRL);
        if (a & 0x100) { // still in transfer(master to slave)
            outb(UART_BASE + UART_TX, 0xaa);
        } else { // maybe should wait for slave to master finish (see waveform if it reversed)
            uint32_t b = inl(SPI_BASE + SPI_RX0);
            outb(UART_BASE + UART_TX, (uint8_t)b);
        }
    }

    return 0;
}
