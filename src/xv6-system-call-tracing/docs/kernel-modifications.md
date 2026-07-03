# Kernel Modifications

## Overview

This document describes the source code modifications required to implement the **System Call Tracing** extension in the xv6 operating system.

The implementation introduces a new kernel system call, extends the process control block with per-process tracing information, integrates tracing into the system call dispatcher, and provides a user-space interface for enabling and using the tracing mechanism.

---

## Modified Files

### Makefile

The xv6 build system was updated to include the new user-space tracing utility.

#### Changes

- Added the `trace` user program to the `UPROGS` list.
- Ensures that the tracing utility is compiled and included in the xv6 file system image.

#### Purpose

This modification allows the tracing utility to be executed directly from the xv6 shell.

---

### kernel/syscall.h

The system call table was extended by introducing a new system call identifier.

#### Changes

```c
#define SYS_trace 22
```

#### Purpose

The new identifier uniquely associates the tracing functionality with a system call number that can be dispatched by the kernel.

---

### kernel/sysproc.c

A new kernel handler was implemented.

#### Changes

- Added the `sys_trace()` system call implementation.
- Retrieves the tracing mask provided by the user.
- Stores the tracing mask inside the current process.

#### Purpose

This function acts as the kernel entry point for configuring process-specific tracing.

---

### kernel/proc.h

The process control block (`struct proc`) was extended.

#### Changes

```c
int traceMask;
```

#### Purpose

Each process maintains its own tracing mask, allowing tracing to be configured independently for different processes.

---

### kernel/proc.c

The process management subsystem was modified.

#### Changes

- Initializes the tracing mask for newly created processes and propagates the tracing configuration from parent to child during `fork()`.

#### Purpose

These modifications ensure that tracing remains consistent throughout the lifetime of a process and is inherited by child processes.

---

### kernel/syscall.c

The system call dispatcher was extended.

#### Changes

- Registered the new `trace` system call.
- Added a lookup table mapping system call numbers to readable names.
- Added tracing logic to the system call dispatcher, allowing selected system calls to be reported after execution.

When tracing is enabled, the kernel reports:

- Process ID (PID)
- System call name
- Return value

#### Purpose

This file implements the core tracing functionality by checking the process tracing mask and printing tracing information whenever a selected system call is executed.

---

### user/user.h

The user-space interface was extended.

#### Changes

```c
int trace(int);
```

#### Purpose

Makes the new system call available to user programs.

---

### user/usys.pl

The xv6 system call stub generator was updated.

#### Changes

```perl
entry("trace");
```

#### Purpose

Generates the assembly stub required for invoking the new system call through `ecall`.

---

### user/trace.c

A new user-space utility was implemented.

#### Changes

The program:

- Parses the tracing mask supplied by the user.
- Invokes the `trace()` system call.
- Executes the requested command using `exec()`.
- Reports an error if command execution fails.

#### Purpose

Provides a simple command-line interface for enabling tracing without requiring modifications to existing user programs.

---

## Summary

The System Call Tracing extension required coordinated modifications across both the kernel and user-space components of xv6.

The implementation introduces a new system call, extends the process data structure, integrates tracing into the system call dispatcher, and provides a user-level utility for configuring tracing. Together, these modifications demonstrate how new kernel functionality can be integrated into the xv6 operating system while preserving its modular design and system call architecture.