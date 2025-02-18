# Non-Blocking Wait Alternative for Child Processes

## Overview

This project demonstrates how to handle terminated child processes in a **non-blocking** way using `sigaction()` and `waitpid()`. The implementation ensures that no child process becomes a **zombie** by properly reaping them.

## Features

- Uses `` signal to detect terminated children.
- Handles multiple child processes efficiently.
- Prints the **PID**, exit status, and termination reason (signal or normal exit).
- Avoids zombie processes by calling **non-blocking **`` with `WNOHANG`.

## Code Implementation

The core of this implementation is the **signal handler** that executes when a child process terminates.

### Signal Handler Implementation


## Explanation

1. ``:

   - Registers a **signal handler** for `SIGCHLD`.
   - Uses `SA_SIGINFO` for detailed signal info.
   - Uses `SA_RESTART` to prevent interrupted system calls.

2. **Parent Process (**``**)**:

   - Forks **3 child processes** that exit after a few seconds.
   - Parent remains active, simulating real-world process execution.

## Compilation & Execution

### Compile the Program:

```sh
gcc -g myOwnWait.c -o myOwnWait.elf
```

### Run the Program:

```sh
./myOwnWait.elf
```

## Expected Output

```sh
Parent working...
Parent working...
Child PID 12345 exited normally with status 1
Parent working...
Child PID 12346 exited normally with status 2
Parent working...
Child PID 12347 exited normally with status 3
Parent working...

```
