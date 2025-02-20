#include "inventory.h"

int create_shared_memory() {
    int shmid = shmget(SHM_KEY, sizeof(Inventory), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }
    return shmid;
}

Inventory* attach_shared_memory(int shmid) {
    Inventory* inventory = (Inventory*)shmat(shmid, NULL, 0);
    if (inventory == (void*)-1) {
        perror("shmat failed");
        exit(1);
    }
    return inventory;
}

void detach_shared_memory(Inventory* inventory) {
    shmdt(inventory);
}

void remove_shared_memory(int shmid) {
    shmctl(shmid, IPC_RMID, NULL);
}

int create_semaphore() {
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget failed");
        exit(1);
    }
    return semid;
}

void set_semaphore_value(int semid, int value) {
    union semun sem_union;
    sem_union.val = value;
    semctl(semid, 0, SETVAL, sem_union);
}

void semaphore_wait(int semid) {
    struct sembuf sem_op = {0, -1, 0};
    semop(semid, &sem_op, 1);
}

void semaphore_signal(int semid) {
    struct sembuf sem_op = {0, 1, 0};
    semop(semid, &sem_op, 1);
}

int create_message_queue() {
    int msgid = msgget(MSG_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }
    return msgid;
}

void send_message(int msgid, OrderMessage* order) {
    msgsnd(msgid, order, sizeof(OrderMessage) - sizeof(long), 0);
}

int receive_message(int msgid, OrderMessage* order, long msg_type) {
    return msgrcv(msgid, order, sizeof(OrderMessage) - sizeof(long), msg_type, 0);
}

void remove_message_queue(int msgid) {
    msgctl(msgid, IPC_RMID, NULL);
}