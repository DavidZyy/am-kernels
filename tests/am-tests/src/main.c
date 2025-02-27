#include <amtest.h>

void (*entry)() = NULL; // mp entry

static const char *tests[256] = {
  ['h'] = "hello",
  ['H'] = "display this help message",
  ['i'] = "interrupt/yield test",
  ['d'] = "scan devices",
  ['m'] = "multiprocessor test",
  ['t'] = "real-time clock test",
  ['k'] = "readkey test",
  ['v'] = "display test",
  ['a'] = "audio test",
  ['p'] = "x86 virtual memory test",
};

/* mainargs is defined in abstract-machine in am
  when mainargs is changed, we should go to there
  and make clean. */
int main(const char *args) {
//   printf("%c\n", args[0]);
//   printf("%s\n", args[0]);
  char a = args[0];
  putch('\n');
  putch(a);
//   putch('\n');
//   for(int i = 0; i < 10; i++){
//     putch(args[i]);
//   }
//   putch('\n');
//   printf("%s\n", args[0]);

  switch (args[0]) {
    CASE('h', hello);
    CASE('i', hello_intr, IOE, CTE(simple_trap));
    CASE('d', devscan, IOE);
    CASE('m', mp_print, MPE);
    CASE('t', rtc_test, IOE);
    CASE('k', keyboard_test, IOE);
    CASE('v', video_test, IOE);
    CASE('a', audio_test, IOE);
    CASE('p', vm_test, CTE(vm_handler), VME(simple_pgalloc, simple_pgfree));
    case 'H':
    default:
      printf("Usage: make run mainargs=*\n");
      for (int ch = 0; ch < 256; ch++) {
        if (tests[ch]) {
          printf("  %c: %s\n", ch, tests[ch]);
        }
      }
  }

  // void rtc_test();
  // void keyboard_test();
  // ioe_init();
  // keyboard_test();
  // rtc_test();
  return 0;
}
