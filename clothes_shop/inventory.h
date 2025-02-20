#ifndef INVENTORY_H
#define INVENTORY_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ITEMS 10
#define ITEM_NAME_LEN 20

typedef struct {
    char name[ITEM_NAME_LEN];
    int count;
    float price;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
} Inventory;

#define SHM_KEY 1234
#define SEM_KEY 5678
#define MSG_KEY 9012

typedef struct {
    long msg_type;
    char item_name[ITEM_NAME_LEN];
    int quantity;
} OrderMessage;

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

#endif /* INVENTORY_H */