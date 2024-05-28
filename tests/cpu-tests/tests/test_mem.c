#include <stdint.h>
#include "am.h"
#include "klib.h"

// Define memory range boundaries
// #define MEM_START_ADDR 0x0F000000
// #define MEM_END_ADDR   0x0F001EFF

// test psram
// #define MEM_START_ADDR 0x80000000
// #define MEM_END_ADDR   0x80001000

// test dsram
#define MEM_START_ADDR 0xa0000000
#define MEM_END_ADDR   0xa0001000


#define UART_BASE 0x10000000L
#define UART_TX   0x0L
static inline void outb(uintptr_t addr, uint8_t  data) { *(volatile uint8_t  *)addr = data; }
void putstr(char *p, int size) {
    for (int i = 0; i < size; i++)
        outb(UART_BASE + UART_TX, p[i]);
}

// Memory test function
void memory_test(void) {
    uint32_t addr;
    char p[] = "test failed!\n";

    // printf("Starting memory test...\n");

    // Loop through memory range
    for (addr = MEM_START_ADDR; addr <= MEM_END_ADDR; addr++) {
        
        // 8-bit write and read
        uint8_t wdata8 = (uint8_t)addr;
        *(volatile uint8_t*)addr = wdata8;
        uint8_t rdata8 = *(volatile uint8_t*)addr;
        if (rdata8 != wdata8) {
            printf("8-bit write and read failed at address 0x%08x\n", addr);
            printf("write: 0x%x, read: 0x%x", wdata8, rdata8);
            putstr(p, sizeof(p)/sizeof(char));
            halt(1);
        }

        // 16-bit write and read
        if (addr % 2 == 0) {
            uint16_t wdata16 = (uint16_t)addr;
            *(volatile uint16_t*)addr = wdata16;
            uint16_t rdata16 = *(volatile uint16_t*)addr;
            if (rdata16 != wdata16) {
                printf("16-bit write and read failed at address 0x%08x\n", addr);
                printf("write: 0x%x, read: 0x%x", wdata16, rdata16);
                putstr(p, sizeof(p)/sizeof(char));
                halt(1);
            }
        }

        // 32-bit write and read
        if (addr % 4 == 0) {
            uint32_t wdata32 = (uint32_t)addr;
            *(volatile uint32_t*)addr = wdata32;
            uint32_t rdata32 = *(volatile uint32_t*)addr;
            if (rdata32 != wdata32) {
                printf("32-bit write and read failed at address 0x%08x\n", addr);
                printf("write: 0x%x, read: 0x%x", wdata32, rdata32);
                putstr(p, sizeof(p)/sizeof(char));
                halt(1);
            }
        }

        // 64-bit write and read
        if (addr % 8 == 0) {
            uint64_t wdata64 = (uint64_t)addr;
            *(volatile uint64_t*)addr = wdata64;
            uint64_t rdata64 = *(volatile uint64_t*)addr;
            if (rdata64 != wdata64) {
                printf("64-bit write and read failed at address 0x%08x\n", addr);
                printf("write: 0x%lx, read: 0x%lx", wdata64, rdata64);
                putstr(p, sizeof(p)/sizeof(char));
                halt(1);
            }
        }
    }

    char p2[] = "test pass!\n";
    putstr(p2, sizeof(p2)/sizeof(char));
    // printf("Memory test completed successfully.\n");
}

int main(void) {
    // Run memory test
    memory_test();

    return 0;
}
