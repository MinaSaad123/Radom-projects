# Signal Handling Demonstration

This project consists of two applications: Sender and Receiver, designed to demonstrate inter-process communication using signals. The sender application sends termination signals to the receiver application based on user input, and the receiver application responds to these signals appropriately.

## Project Files

**sender.c:** The sender program that sends signals (SIGTERM or SIGABRT) to the receiver.

**receiver.c:** The receiver program that handles the signals and performs actions accordingly.

## Compilation Instructions

### Step 1: Compile the Receiver Program

` gcc -o receiver receiver.c
`

### Step 2: Compile the Sender Program

` gcc -o sender sender.c
`
## Execution Steps

### Step 1: Run the Receiver Program

Start the receiver in one terminal to continuously listen for signals:

` ./receiver `


The receiver will display its process ID (PID) and wait for signals.

### Step 2: Run the Sender Program

In another terminal, start the sender and provide the PID of the receiver:

` ./sender ` 

Follow the prompts to send signals:

Enter 0 to send a SIGTERM signal (terminate).

Enter 1 to send a SIGABRT signal (abort with a core dump).

## Example Output

### Receiver Terminal

`Receiver process started. PID: 12345
Waiting for signals...
Received SIGTERM (signal 15). Terminating...`

### Sender Terminal

`Enter the PID of the receiver process: 12345
Enter 0 to terminate, 1 to abort: 0
SIGTERM signal sent to process 12345`

## Important Notes

System Call Validation: The code checks the return values of system calls like kill and signal. Any failures are logged with appropriate error messages.

Signal Handlers: Custom handlers for SIGTERM and SIGABRT ensure proper handling of termination and abort signals.

Example Signals and Behaviors

SIGTERM: Gracefully terminates the receiver process.

SIGABRT: Aborts the receiver process and generates a core dump for debugging.

# Video
