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

Enter 0 to send a termination signal.

Enter 1 to send an abort signal (with core dump).

## Example Output

### Receiver Terminal

`Receiver process started. PID: 12345
Waiting for real-time signals...
Received data 0. Terminating gracefully...`

### Sender Terminal

Enter the PID of the receiver process: 12345
Enter 0 to terminate, 1 to abort: 0
Signal sent with data 0 to process 12345`

## Key Features

Real-Time Signals: The project uses SIGRTMIN for inter-process communication, allowing the sender to pass data along with the signal.

Signal Handling: The receiver processes the data sent with the signal and performs actions such as termination or aborting with a core dump.

Error Handling: Both applications validate system calls and display appropriate error messages if a failure occurs.

## Example Signals and Behaviors

Data = 0: Receiver terminates gracefully.

Data = 1: Receiver aborts with a core dump.

Invalid Data: Receiver ignores the signal and logs the invalid data.


# Video
