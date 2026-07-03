 #ifndef CLOCK_MONITOR_H
 #define CLOCK_MONITOR_H

 void initClockMonitor(void);

 void destroyClockMonitor(void);

 int getThreadId(void);

 void registerThread(int id);

 void *tick(void *arg);

 void sleepTicks(int ticks);

 #endif