# System Call Execution Flow

## Overview

This document explains how the **System Call Tracing** extension operates from the moment a user executes the `trace` command until the kernel produces tracing output.

The tracing mechanism spans both user space and kernel space, demonstrating how a custom system call is integrated into the xv6 operating system.

---

## Execution Flow

### Step 1 — User Executes the Trace Utility

The tracing process begins when the user runs the `trace` utility from the xv6 shell.

Example:

```bash
trace 32 grep hello README
```

The command receives:

- A tracing mask
- The program to execute
- Optional command-line arguments

The tracing mask determines which system calls should be monitored.

---

### Step 2 — User-Space Configuration

The `trace` utility parses the command-line arguments and converts the tracing mask into an integer value.

It then invokes the newly implemented `trace()` system call.

```c
trace(mask);
```

At this point, execution transitions from user space into the kernel.

---

### Step 3 — System Call Invocation

Calling `trace()` transfers control to the automatically generated user-space system call stub (`usys.S`), which executes the `ecall` instruction.

The processor then transfers control to the xv6 kernel, where the system call dispatcher identifies the requested system call using its assigned system call number.

---

### Step 4 — Kernel Configuration

The kernel executes `sys_trace()`.

This function:

- Retrieves the tracing mask from the user process.
- Stores the tracing mask in the current process (`struct proc::traceMask`).

Each process therefore maintains its own independent tracing configuration.

---

### Step 5 — Process Execution

After configuring the tracing mask, the `trace` utility executes the requested program using:

```c
exec(...)
```

The program begins executing normally.

If the process creates child processes using `fork()`, the tracing mask is inherited by each child process.

---

### Step 6 — System Call Dispatching

Whenever the traced process performs a system call, execution enters the xv6 system call dispatcher.

The dispatcher:

1. Identifies the requested system call.
2. Executes the corresponding kernel function.
3. Obtains the return value.
4. Checks whether the corresponding bit is enabled in the process tracing mask.

This decision is made using the process-specific tracing mask.

---

### Step 7 — Trace Output

If the corresponding bit is enabled in the tracing mask, the kernel prints tracing information containing:

- Process ID (PID)
- System call name
- Return value

System calls whose bits are not enabled execute normally without generating tracing output.

---

## Summary

The System Call Tracing extension integrates seamlessly into the existing xv6 system call architecture.

The implementation combines a user-space utility, a new kernel system call, per-process kernel state, and extensions to the system call dispatcher to provide configurable runtime tracing with minimal modifications to the overall xv6 design.

The implementation demonstrates how additional functionality can be integrated into an existing operating system by extending both user-space and kernel-space components while preserving the overall xv6 architecture.