<div align="center">

# xv6 System Call Tracing

### Kernel-level system call tracing extension for the xv6 operating system

**C • Operating Systems • xv6 • Kernel Development**

</div>

---

## Overview

This project extends the **xv6 educational operating system** with a kernel-level **System Call Tracing** mechanism.

The implementation introduces a new `trace` system call that enables selective tracing of system calls using a bitmask. When tracing is enabled for a process, the kernel reports the process identifier (PID), the invoked system call, and its return value whenever a traced system call is executed.

The tracing configuration is stored on a per-process basis and is inherited by child processes created through `fork()`, allowing tracing to continue across parent and child processes.

The project was developed as part of my study of **Operating Systems**, with emphasis on kernel development, system call implementation, process management, and understanding the interaction between user space and kernel space.

The repository contains the original xv6 source code together with my implementation of the System Call Tracing kernel extension.

---

## Features

- Kernel-level implementation of a new `trace` system call
- Selective system call tracing using a bitmask
- Per-process tracing configuration
- Automatic inheritance of the tracing mask through `fork()`
- Reporting of process ID (PID), system call name, and return value
- User-space `trace` utility for enabling system call tracing
- Integration with the xv6 system call dispatch mechanism
- Clean and modular implementation following the xv6 architecture

---

## Repository Structure

```text
.
├── README.md
├── LICENSE
│ 
├── docs/
│   ├── kernel-modifications.md
│   └── system-call-flow.md
│ 
├── examples/
│   ├── trace-all.txt
│   ├── trace-fork.txt
│   └── trace-read.txt
│ 
└── xv6/
    ├── Makefile
    ├── kernel/
    ├── user/
    ├── fs/
    ├── mkfs/
    ├── README
    └── ...
```

The repository contains the original **xv6** source tree together with the implementation, documentation, and usage examples for the **System Call Tracing** kernel extension.

---

## Building and Running

### Requirements

- RISC-V GCC toolchain
- QEMU for RISC-V
- `make`

Compile and start xv6

```bash
cd xv6
make qemu
```

Run the tracing utility

```bash
trace <mask> <command> [arguments]
```

---

## Usage

The tracing utility is executed from the xv6 shell using the following syntax:

```bash
trace <mask> <command> [arguments]
```

Where:

- `<mask>` specifies which system calls should be traced using a bitmask.
- `<command>` is the program to execute.
- `[arguments]` are the optional command-line arguments passed to the program.

Only system calls whose corresponding bits are enabled in the tracing mask are reported by the kernel.

---

## Example

The following example traces all `read()` system calls executed by `grep`:

```bash
trace 32 grep hello README
```

Sample output:

```text
3: syscall read -> 1023
3: syscall read -> 966
3: syscall read -> 70
3: syscall read -> 0
```

Actual process identifiers (PIDs) and return values may differ between executions.

Additional example sessions are available in the `examples/` directory:

- `trace-read.txt` — Tracing `read()` system calls
- `trace-fork.txt` — Tracing inherited system calls after `fork()`
- `trace-all.txt` — Tracing multiple system calls using a broader tracing mask

---

## Architecture

The following diagram illustrates how the System Call Tracing extension integrates with the xv6 kernel. It shows the execution flow from the user-level `trace` utility to the kernel system call dispatcher and the generation of tracing output.

<p <img src="../../images/xv6-system-call-tracing-architecture.png"
     alt="xv6 System Call Tracing Architecture"
     width="900">
</p>

---

## Operating Systems Concepts

This project demonstrates the implementation and practical use of several fundamental operating systems concepts, including:

- Kernel-level system call implementation
- User space to kernel space transitions via `ecall`
- System call dispatching and handling
- Per-process kernel data structures
- Process management through `struct proc`
- Parent-child process relationships and inheritance through `fork()`
- Kernel and user space interaction
- Bitmask-based configuration mechanisms
- Kernel extensions to an existing operating system

---

## Implementation Details

The tracing mechanism is implemented by extending the existing xv6 kernel with a new trace system call and the supporting kernel infrastructure.

The implementation introduces a per-process tracing mask stored in `struct proc`. The `trace` system call updates this mask, allowing each process to independently control which system calls should be traced.

The system call dispatcher checks the tracing mask whenever a system call is executed. If the corresponding bit is enabled, the kernel prints:

- Process ID (PID)
- System call name
- Return value

The tracing mask is inherited during `fork()`, ensuring that child processes continue to be traced using the same configuration as their parent.

---

## Educational Objectives

This project demonstrates:

- Extending an existing operating system kernel
- Implementing custom system calls
- Understanding the xv6 system call interface
- Managing per-process kernel state
- Working with process creation and inheritance
- Understanding user/kernel communication
- Practical kernel development in C

---

## Future Improvements

Potential future extensions include:

- Tracing of system call arguments
- Timestamped tracing output
- Filtering by process identifier (PID)
- Logging trace output to files
- Runtime enabling and disabling of tracing

---

## Acknowledgments

This project is based on the **xv6** educational operating system developed by the MIT PDOS group. The original xv6 source code provides the foundation on which the System Call Tracing extension presented in this repository was implemented.

---

## License

This project is licensed under the **MIT License**.

The repository includes the original **xv6** source code, which is distributed under the MIT License by the MIT PDOS group. This repository also includes my implementation of the **System Call Tracing** kernel extension, together with the accompanying documentation and examples.

---

<div align="center">

**Developed by Anastasis Zachariou**

</div>
