#ifndef IPC_UTILS_H
#define IPC_UTILS_H

#include "inventory.h"

int create_shared_memory();
Inventory* attach_shared_memory(int shmid);
void detach_shared_memory(Inventory* inventory);
void remove_shared_memory(int shmid);

int create_semaphore();
void set_semaphore_value(int semid, int value);
void semaphore_wait(int semid);
void semaphore_signal(int semid);

int create_message_queue();
void send_message(int msgid, OrderMessage* order);
int receive_message(int msgid, OrderMessage* order, long msg_type);
void remove_message_queue(int msgid);

#endif /* IPC_UTILS_H */