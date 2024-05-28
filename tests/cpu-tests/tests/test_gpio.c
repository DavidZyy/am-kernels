
#include "am.h"
#include <stdint.h>
#include "klib.h"

#define gpioBase 0x10002000L
#define gpioSize 0x10L

static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }
static inline void outl(uintptr_t addr, uint32_t data) { *(volatile uint32_t *)addr = data; }

int main() {
    uint32_t data = 1;
    uint32_t switch_data = 0;
    // for (int i=0; i<100; i++) {
    while(1) {
        data = (data == 1<<15) ? 1 : (data<<1);
        outl(gpioBase, data);

        uint32_t new_switch_data = inl(gpioBase + 4);
        if(new_switch_data != switch_data) {
            switch_data = new_switch_data;
            printf("new switch data: %x\n", switch_data);
        }
    }

    return 0;
}
