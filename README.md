<div align="center">

# Operating Systems

### Educational implementations of operating systems concepts using C

**C • Operating Systems • POSIX Threads • Unix • xv6**

</div>

---

## Overview

This repository contains educational implementations covering fundamental topics in **Operating Systems** using the C programming language.

Each project explores a core operating systems concept through practical implementation, including thread synchronization, monitor-based concurrency, Unix systems programming, process management, and kernel development. The implementations emphasize clean software design, practical experimentation, and a deeper understanding of the mechanisms that modern operating systems rely on.

Rather than serving as a collection of individual programming assignments, this repository is designed to evolve into a comprehensive educational resource that combines practical systems programming with the theoretical foundations of modern operating systems.

Each project includes detailed documentation, implementation notes, architecture diagrams, and example executions to facilitate both learning and future extension.

---

## Projects

| Project | Main Concept | Description |
|----------|--------------|-------------|
| [**Clock Monitor in C**](src/clock-monitor/) | Monitor Synchronization | Thread synchronization using monitors, mutexes, and condition variables. |
| [**Synchronization Using POSIX Semaphores**](src/synchronization/) | Semaphore Synchronization | Waiter–Clients synchronization problem implemented with POSIX semaphores. |
| [**Unix Shell in C**](src/tiny-shell/) | Unix Systems Programming | Lightweight Unix shell supporting command execution, pipes, and I/O redirection. |
| [**xv6 System Call Tracing**](src/xv6-system-call-tracing/) | Kernel Development | Kernel-level system call tracing extension for the xv6 operating system. |

---

## Repository Philosophy

The goal of this repository is not only to provide working implementations, but also to explain the operating systems concepts behind them.

Each project combines:

- Complete source code
- Technical documentation
- Architecture diagrams
- Example executions
- Educational explanations

This approach transforms every implementation into a self-contained learning resource that can be studied independently while contributing to a coherent collection of operating systems projects.

---

## Repository Structure

```text
operating-systems-c/
│
├── images/
│   ├── clock-monitor-architecture.png
│   ├── shell-architecture.png
│   ├── synchronization-architecture.png
│   └── system-call-tracing-architecture.png
│
├── .gitignore
├── LICENSE
├── README.md
│
└── src/
    ├── clock-monitor/
    ├── synchronization/
    ├── tiny-shell/
    └── xv6-system-call-tracing/
```

The repository is organized as a collection of independent educational projects, each focusing on a specific operating systems concept.

Each project includes its own implementation, documentation, examples, and supporting resources, while architecture diagrams are maintained in the shared `images/` directory to provide a consistent visual style across the repository.

---

## Topics Covered

The current projects in this repository cover a broad range of fundamental operating systems concepts, including:

### Concurrency and Synchronization

- POSIX Threads (pthreads)
- Monitors
- POSIX Semaphores
- Mutexes
- Condition Variables
- Thread Synchronization
- Concurrent Programming

### Process Management

- Process Creation
- Process Synchronization
- Unix Process Lifecycle
- Pipes and I/O Redirection

### Kernel Development

- xv6 Operating System
- System Calls
- Kernel Extensions
- User Space and Kernel Space Interaction

### Unix Systems Programming

- Unix Shell Implementation
- Process Execution
- File Descriptors
- Inter-Process Communication (IPC)

---

## Future Projects

This repository will continue to expand with additional educational projects covering a wider range of operating systems concepts.

### Process Management

- CPU Scheduling
- Process Scheduling Algorithms
- Process Control Blocks (PCB)

### Memory Management

- Virtual Memory
- Paging and Segmentation
- Dynamic Memory Allocation

### Synchronization

- Readers–Writers Problem
- Dining Philosophers Problem
- Deadlock Detection and Prevention
- Advanced Synchronization Algorithms

### Inter-Process Communication

- Shared Memory
- Message Passing
- Signals
- Pipes and Named Pipes

### File Systems

- File System Organization
- File Allocation Methods
- Directory Management

### Kernel Development

- Additional xv6 Kernel Extensions
- Device Drivers
- Interrupt and Trap Handling

---

## Educational Objectives

The primary objective of this repository is to develop a deeper understanding of operating systems through practical implementation.

Each project is designed to bridge the gap between theoretical concepts and real-world systems programming by providing complete, well-documented implementations of fundamental operating systems mechanisms.

The repository emphasizes:

- Understanding the internal mechanisms of modern operating systems
- Applying operating systems theory through practical C implementations
- Developing clean, modular, and maintainable systems software
- Studying concurrency, synchronization, process management, and kernel development
- Building a long-term educational reference for operating systems concepts

The repository is intended to support both academic study and independent learning while continuing to expand with additional projects covering advanced operating systems topics.

---

## License

This repository is licensed under the **MIT License**.

See the [LICENSE](LICENSE) file for details.

---

<div align="center">

**Developed by Anastasis Zachariou**

</div>
