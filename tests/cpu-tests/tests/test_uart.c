#include "am.h"
#include <stdint.h>
#include "klib.h"

#define UART_BASE 0x10000000L
#define UART_TX   0x0L
#define UART_LCR  0X3L
#define UART_DL1  0x0L

static inline uint8_t  inb(uintptr_t addr) { return *(volatile uint8_t  *)addr; }
static inline uint16_t inw(uintptr_t addr) { return *(volatile uint16_t *)addr; }
static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }

static inline void outb(uintptr_t addr, uint8_t  data) { *(volatile uint8_t  *)addr = data; }
static inline void outw(uintptr_t addr, uint16_t data) { *(volatile uint16_t *)addr = data; }
static inline void outl(uintptr_t addr, uint32_t data) { *(volatile uint32_t *)addr = data; }


void putstr(char *p, int size) {
    for (int i = 0; i < size-1; i++) // size - 1: not write '\0' of it
        outb(UART_BASE + UART_TX, p[i]);
}

void set_baud_rate() {
// set lcr bit to write baud rate
  uint8_t lcr = inb(UART_BASE + UART_LCR);

  outb(UART_BASE + UART_LCR, 0x80 | lcr);
// write baud rate
  outb(UART_BASE + UART_DL1, 1); // this value * 16 should == divisor that set in uart.cpp
// clear lcr bit
  outb(UART_BASE + UART_LCR, lcr);
}

int main() {
  // set_baud_rate();
  ioe_init();
  // char p[] = "123456789\n";
  // char p[] = "hello you should give me your pencil!\n";
  // putstr(p, sizeof(p)/sizeof(char));
  printf("hello you should give me your pencil!\n");

  
//   outb(UART_BASE + UART_TX, 'h');
//   outb(UART_BASE + UART_TX, 'e');
//   outb(UART_BASE + UART_TX, 'l');
//   outb(UART_BASE + UART_TX, 'l');
//   outb(UART_BASE + UART_TX, 'o');
// 
//   outb(UART_BASE + UART_TX, ' ');
// 
//   outb(UART_BASE + UART_TX, 'y');
//   outb(UART_BASE + UART_TX, 'o');
//   outb(UART_BASE + UART_TX, 'u');
// 
//   outb(UART_BASE + UART_TX, ' ');
// 
//   outb(UART_BASE + UART_TX, 's');
//   outb(UART_BASE + UART_TX, 'h');
//   outb(UART_BASE + UART_TX, 'o');
//   outb(UART_BASE + UART_TX, 'u');
//   outb(UART_BASE + UART_TX, 'l');
//   outb(UART_BASE + UART_TX, 'd');
// 
//   outb(UART_BASE + UART_TX, ' ');
// 
//   outb(UART_BASE + UART_TX, 'g');
//   outb(UART_BASE + UART_TX, 'i');
//   outb(UART_BASE + UART_TX, 'v');
//   outb(UART_BASE + UART_TX, 'e');
// 
//   outb(UART_BASE + UART_TX, ' ');
// 
//   outb(UART_BASE + UART_TX, 'm');
//   outb(UART_BASE + UART_TX, 'e');
// 
//   outb(UART_BASE + UART_TX, 'y');
//   outb(UART_BASE + UART_TX, 'o');
//   outb(UART_BASE + UART_TX, 'u');
//   outb(UART_BASE + UART_TX, 'r');
// 
//   outb(UART_BASE + UART_TX, ' ');
// 
//   outb(UART_BASE + UART_TX, 'p');
//   outb(UART_BASE + UART_TX, 'e');
//   outb(UART_BASE + UART_TX, 'n');
//   outb(UART_BASE + UART_TX, 'c');
//   outb(UART_BASE + UART_TX, 'i');
//   outb(UART_BASE + UART_TX, 'l');
//   outb(UART_BASE + UART_TX, '!');
//   outb(UART_BASE + UART_TX, '\n');

  // outb(UART_BASE + UART_TX, (uint8_t)0b10101010);
  // outb(UART_BASE + UART_TX, (uint8_t)0b01010101);
  while(1);
  return 0;
}
