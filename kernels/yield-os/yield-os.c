#include <am.h>
#include <klib-macros.h>
// #include<stdio.h>
#include <klib.h>

#define STACK_SIZE (4096 * 8)
typedef union {
  uint8_t stack[STACK_SIZE];
  struct { Context *cp; };
} PCB;
static PCB pcb[2], pcb_boot, *current = &pcb_boot;

static void f(void *arg) {
  while (1) {
    putch("?AB"[(uintptr_t)arg > 2 ? 0 : (uintptr_t)arg]);
    for (int volatile i = 0; i < 10; i++) ;
    yield();
  }
}

static Context *schedule(Event ev, Context *prev) {
  current->cp = prev;
  current = (current == &pcb[0] ? &pcb[1] : &pcb[0]);
  return current->cp;
}

int main() {
  cte_init(schedule);
  // printf("start:%p\n", pcb[0].stack);
  // printf("end:%p\n", &pcb[0] + 1);
  // should be changed below
  void *para[1];
  para[0] = (void *)1L;
  pcb[0].cp = kcontext((Area) { pcb[0].stack, &pcb[0] + 1 }, f, para);
  para[0] = (void *)2L;
  pcb[1].cp = kcontext((Area) { pcb[1].stack, &pcb[1] + 1 }, f, para);
  // printf("cp");
  // printf("cp:%p\n", pcb[0].cp);
  putch('2');
  // printf("12");
  yield();
  panic("Should not reach here!!!");
}
