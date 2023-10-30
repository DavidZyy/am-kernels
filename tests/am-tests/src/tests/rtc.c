#include <amtest.h>
/* no printf, serial should be supported in npc */

void rtc_test() {
  AM_TIMER_RTC_T rtc;
  int sec = 1;
  int n = 1000;
  while (n--){
    while(io_read(AM_TIMER_UPTIME).us / 1000000 < sec);
    rtc = io_read(AM_TIMER_RTC);
    printf("%d-%d-%d %02d:%02d:%02d GMT (", rtc.year, rtc.month, rtc.day, rtc.hour, rtc.minute, rtc.second);
    // printf("%d-%d-%d %d:%d:%d GMT (", rtc.year, rtc.month, rtc.day, rtc.hour, rtc.minute, rtc.second);
    if (sec == 1) {
      printf("%d second).\n", sec);
    } else {
      printf("%d seconds).\n", sec);
    }
    // printf("aaa\n");
    sec ++;
  }
}
