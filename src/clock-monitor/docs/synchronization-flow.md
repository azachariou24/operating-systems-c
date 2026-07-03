# Synchronization Flow

## Overview

This document explains how the Clock Monitor coordinates worker threads and the clock thread to implement tick-based sleeping without busy waiting.

The synchronization mechanism relies on a mutex protecting the monitor state and one condition variable per worker thread.

---

## Execution Flow

### Step 1 — Worker Thread Starts

Each worker thread is created by the main program and registers itself with the monitor using

```c
registerThread(id);
```

The monitor associates the calling POSIX thread with an internal worker identifier.

---

### Step 2 — Sleep Request

The worker generates a random sleep duration and requests to sleep by calling

```c
sleepTicks(ticks);
```

The requested duration is expressed in clock ticks rather than real time.

---

### Step 3 — Entering the Monitor

The monitor acquires the mutex before accessing any shared state.

The worker calculates its wake-up tick

```text
wakeUpTick = currentClockTick + requestedTicks
```

The value is stored in the monitor's waiting table.

---

### Step 4 — Blocking the Worker

The worker blocks on its own condition variable.

During this period

- the mutex is released automatically,
- the worker consumes no CPU time,
- execution remains suspended until the monitor signals the thread.

This avoids busy waiting.

---

### Step 5 — Clock Thread Execution

A dedicated clock thread executes continuously.

Every two seconds it

- acquires the monitor mutex,
- increments the global clock,
- checks every waiting worker,
- signals workers whose wake-up time has been reached,
- releases the mutex.

---

### Step 6 — Worker Resumes

Once signaled, the worker reacquires the mutex and continues execution.

After leaving the monitor, the worker performs its simulated work before requesting another sleep interval.

---

### Step 7 — Continuous Operation

The process repeats indefinitely.

Workers repeatedly

1. perform work,
2. request to sleep,
3. block inside the monitor,
4. wake when their target clock tick is reached.

Meanwhile, the clock thread continuously advances the global clock.

---

## Synchronization Properties

The monitor guarantees that

- only one thread accesses shared monitor state at a time,
- worker threads never busy wait,
- workers wake only after the requested number of clock ticks,
- shared data remains consistent under concurrent execution.

---

## Summary

The Clock Monitor demonstrates a classical monitor-based synchronization mechanism using POSIX mutexes and condition variables.

By combining mutual exclusion with blocking synchronization, the implementation provides an efficient and thread-safe solution for coordinating multiple concurrent worker threads.