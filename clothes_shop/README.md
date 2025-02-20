Clothing Shop Simulation

Overview

This project is a multi-process simulation of a clothing shop using Inter-Process Communication (IPC) mechanisms. It consists of three main components:

Shop Process: Manages the shop's inventory, periodically prints stock and prices, and processes customer orders.

Customer Process: Allows users to place orders, which are sent to the Shop Process.

Inventory Manager: Enables inventory restocking and price modifications.

IPC mechanisms used:

Message Queues (for order placement)

Shared Memory (for inventory management)

Semaphores (for synchronization)

Flowchart

graph TD;
    A[Start] -->|Initialize Inventory| B[Shop Process];
    B -->|Periodically Print Inventory| C[Output Inventory Data];
    B -->|Receive Order via IPC (Message Queue/Shared Memory)| D[Customer Process];
    D -->|Send Order Details via IPC| B;
    B -->|Check Inventory| E{Stock Available?};
    E --Yes--> F[Confirm Order];
    E --No--> G[Reject Order];
    B -->|Receive Restock/Price Update via IPC| H[Inventory Manager];
    H -->|Send Updates via IPC| B;
    B -->|Update Inventory and Prices| C;
    C -->|Repeat Process| B;

How to Compile and Run

1. Compile the Program

gcc -o shop main.c inventory.c -lpthread -lrt

2. Run the Program

./shop

Expected Behavior

The Shop Process continuously prints inventory updates.

The Customer Process allows users to place orders, which are processed if stock is available.

The Inventory Manager enables restocking items and modifying prices.

IPC ensures smooth communication between processes.
