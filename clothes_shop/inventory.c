#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>

extern int sem_id;
extern Inventory *inventory;
extern int shm_id;

void acquire_lock() 
{
    struct sembuf operation = {0, -1, 0};
    semop(sem_id, &operation, 1);
}

void release_lock() 
{
    struct sembuf operation = {0, 1, 0};
    semop(sem_id, &operation, 1);
}

void shop_handler() 
{
    int msg_id = msgget(MSG_KEY, 0666 | IPC_CREAT);
    Message msg;
    
    while (1) 
    {
        msgrcv(msg_id, &msg, sizeof(msg.data), 1, 0);
        acquire_lock();
        
        char item_name[50];
        int quantity;
        sscanf(msg.data, "%s %d", item_name, &quantity);
        
        for (int i = 0; i < inventory->totalItems; i++) {
            if (strcmp(inventory->stock[i].name, item_name) == 0) 
            {
                if (inventory->stock[i].quantity >= quantity) {
                    inventory->stock[i].quantity -= quantity;
                    printf("Processed Order: %s x %d\n", item_name, quantity);

                } else 
                {
                    printf("Insufficient stock: %s\n", item_name);
                }
                break;
            }
        }
        
        release_lock();
    }
}

void user_interface() 
{
    int msg_id = msgget(MSG_KEY, 0666 | IPC_CREAT);
    Message msg;
    msg.msg_type = 1;
    
    while (1) 
    {
        int action;
        printf("1. Purchase Item\n2. Modify Inventory\nSelect an option: ");
        scanf("%d", &action);
        getchar();

        if (action == 1) 
        {
            printf("Enter item and quantity: ");
            fgets(msg.data, MSG_SIZE, stdin);
            msgsnd(msg_id, &msg, sizeof(msg.data), 0);
            printf("Order placed.\n");

        } else if (action == 2) 
        {
            acquire_lock();
            printf("Enter item name, new stock, and updated price: ");
            char item_name[50];
            int quantity;
            float price;
            scanf("%s %d %f", item_name, &quantity, &price);
            
            for (int i = 0; i < inventory->totalItems; i++) 
            {
                if (strcmp(inventory->stock[i].name, item_name) == 0) 
                {
                    inventory->stock[i].quantity += quantity;
                    inventory->stock[i].price = price;
                    printf("Inventory Updated: %s - Stock: %d, Price: %.2f\n", item_name, inventory->stock[i].quantity, inventory->stock[i].price);
                    break;
                }
            }
            release_lock();
        }
    }
}