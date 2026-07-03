# Monitor Design

## Overview

This document describes the internal design of the **Clock Monitor** and explains how synchronization is achieved using mutexes and condition variables.

The monitor provides a thread-safe interface that allows worker threads to sleep for a specified number of clock ticks while a dedicated clock thread periodically advances the global clock.

---

## Shared Data

The monitor maintains several shared data structures:

### Global Clock

```c
static int clockTick;
```

Represents the current clock tick shared by all threads.

---

### Mutex

```c
static pthread_mutex_t mutex;
```

Protects all shared monitor state and guarantees mutual exclusion.

---

### Condition Variables

```c
static pthread_cond_t cond[MAX_THREADS];
```

Each worker thread owns a dedicated condition variable used to block and later resume execution.

---

### Waiting Tick Array

```c
static int waitingTicks[MAX_THREADS];
```

Stores the clock tick at which each worker thread should wake up.

A value of `-1` indicates that the thread is not currently waiting.

---

### Thread Mapping

```c
static pthread_t threadIds[MAX_THREADS];
```

Associates each internal worker identifier with its corresponding POSIX thread.

---

## Monitor Operations

The monitor provides the following public operations:

### initClockMonitor()

Initializes the mutex, condition variables, and internal monitor state.

---

### registerThread()

Associates a worker thread with its internal identifier.

---

### sleepTicks()

Blocks the calling worker until the requested number of clock ticks has elapsed.

---

### tick()

Executed by the dedicated clock thread.

This function:

- increments the global clock,
- checks all waiting worker threads,
- signals every thread whose wake-up time has been reached.

---

### destroyClockMonitor()

Releases all synchronization resources allocated by the monitor.

---

## Synchronization Strategy

The monitor guarantees that:

- shared variables are always protected by the mutex,
- worker threads sleep without busy waiting,
- only eligible worker threads are awakened,
- concurrent access to shared state is thread-safe.

---

## Summary

The Clock Monitor demonstrates a classical monitor implementation using POSIX mutexes and condition variables to coordinate multiple concurrent threads safely and efficiently.