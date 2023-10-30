/* only used on npc */
#include "trap.h"
#include "npc.h"
// 
// uint32_t read_kb() {
//     return (*(volatile uint32_t *)KBD_ADDR);
// }
// 
// uint32_t read_swt() {
//     return (*(volatile uint32_t *)SWT_ADDR);
// }
// 
// void write_seg(uint32_t a) {
//     volatile uint32_t *p = (uint32_t *)SEG_ADDR;
//     *p = a;
// }
// 
// void write_led(uint32_t a) {
//     volatile uint32_t *p = (uint32_t *)LED_ADDR;
//     *p = a;
// }
// 
// #define  FB_ADDR  0xa1000000

int func1(int n) {
    if(n <= 0) return 0;
    return n + func1(n-1);
}

int func2(int n) {
    int sum = 0;
label1:
    if(n > 0){
        sum += n;
        n--;
        goto label1; 
    }
    return sum;
}

int main() {
    // check(func1(10) == func2(10));
    return func1(10) - func2(9);
//     while(1) {
//         // ioe_init();
//     // int n = 10; while(n--){
//         // uint32_t b = read_swt();
//         /* 两种方式读键盘，分别写入seg和led，对比结果。 */
//         // uint32_t b = read_kb();
//         // write_led(b);
// 
//         /* if read zero (the default value for kb not ready), not wirte seg )*/
//         // AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
//         // if(ev.keycode != AM_KEY_NONE) {
//         //     int data = (ev.keydown << 8) | ev.keycode;
//         //     write_seg(data);
//         // }
// 
//         // int rtcus = io_read(AM_TIMER_UPTIME).us;
//         // rtcus++;
//         // printf("rtc in kb_test: %llx\n", rtcus);
//         // printf("***************************\n");
//         // while(1);
// 
// 
//         // uint32_t a = read_kb();
//         // if (a) write_seg(a);
// 
// 
//         // uint32_t blank[50*50];
//         // for(int i = 0; i < 50*50; i++){
//         //     blank[i] = 0xffffffff;
//         // }
//         // io_write(AM_GPU_FBDRAW, 100, 100, blank, 50, 50, false);
//         for(int i = 0; i < 4 * 512; i = i+4) {
//             *((uint32_t *)((uintptr_t)FB_ADDR + i)) = 0xffffffff;
//             // *((uint32_t *)((uint64_t)FB_ADDR + i)) = 0xffffffff;
//         }
//     }
    // int a = 2-1;
//     volatile int a = 1;
//     volatile int b = 2;
//     volatile int e = -1;
//     volatile int c = b - a;
//     volatile int d = a - b;
//     volatile int f = a - e;
// 
//     return c + d + f;
// f1:
    // volatile uint64_t addr = 0x82000000;
    // for(int i = 0; i < 100; i++) {
    //     *((uint32_t *)addr)  = i;
    // }
    // goto f1;
    return 0;
}
