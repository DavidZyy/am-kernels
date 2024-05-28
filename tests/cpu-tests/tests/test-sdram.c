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

#define SDRAM_ADDR 0xa0000000
#define SDRAM_SIZE 0x2000000

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

/**
0xa0001404 or
0xa0001403

row (24:12) = 1
bank (11:10) = 1
col Cat((9:2), 0) = 2
*/
uint32_t test_naive () {
    outl(0xa0001404, 0xdeadbeef);
    uint32_t a = inl(0xa0001404);
    return a;
}

/**
     ________________   ___________
0b 0000 0000 0000 0010 1000 0000 0100

= 0xa0002804
row(25:13) = 1
bank[12:11] = 1
col[10:2] = 1

 */
uint32_t test_bit_extension() {
    uint32_t addr = 0xa0002804;
    outl(addr, 0xdeadbeef);
    uint32_t a = inl(addr);
    return a;
}

uint32_t test_bit_extension_and_byte_extension() {
    uint32_t addr1 = 0xa0002804;
    uint32_t addr2 = 0xa4002804;
    uint32_t a, b;

    a = inl(addr1);
    b = inl(addr2);
    printf("addr:%x, data:%x\n",addr1, a);
    printf("addr:%x, data:%x\n",addr2, b);

    // sdram 0, 1
    outl(addr1, 0xfeedabcd);

    a = inl(addr1);
    b = inl(addr2);
    printf("addr:%x, data:%x\n",addr1, a);
    printf("addr:%x, data:%x\n",addr2, b);
    
    // sdram 2, 3
    outl(addr2, 0xdeadbeef);

    a = inl(addr1);
    b = inl(addr2);
    printf("addr:%x, data:%x\n",addr1, a);
    printf("addr:%x, data:%x\n",addr2, b);
    return a;
}

extern char __mytext_start_lma;
extern char __mytext_start_vma;
int main(void) {
    // outl(SDRAM_ADDR, 0xdeadbeef);
    // uint32_t a = inl(SDRAM_ADDR);
    // uint32_t a = test_naive();
    // uint32_t a = test_bit_extension();
    uint32_t a = test_bit_extension_and_byte_extension();

  printf("lma: %x\n", &__mytext_start_lma);
  printf("vma: %x\n", &__mytext_start_vma);
    // printf("a:%x\n", a);

    // if (a == 0xbeefdead) {
    if (a == 0xfeedabcd) {
        char p[] = "test pass!\n";
        putstr(p, sizeof(p)/sizeof(char));
    } else {
        char p[] = "test failed!\n";
        putstr(p, sizeof(p)/sizeof(char));
    }
    return 0;
}

