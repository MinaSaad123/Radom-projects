#include "inventory.h"
#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>

int sem_id;
Inventory *inventory;
int shm_id;

int main() 
{
    shm_id = shmget(SHM_KEY, sizeof(Inventory), 0666 | IPC_CREAT);
    inventory = (Inventory *)shmat(shm_id, NULL, 0);
    sem_id = semget(SEM_KEY, 1, 0666 | IPC_CREAT);
    semctl(sem_id, 0, SETVAL, 1);
    
    inventory->totalItems = 2;
    strcpy(inventory->stock[0].name, "T-Shirt");
    inventory->stock[0].quantity = 12;
    inventory->stock[0].price = 18.5;
    
    strcpy(inventory->stock[1].name, "Jeans");
    inventory->stock[1].quantity = 7;
    inventory->stock[1].price = 30.0;
    
    printf("Store System Initialized\n");
    
    if (fork() == 0) 
    {
        shop_handler();

    } else 
    {
        user_interface();
    }
    
    while (1);
    return 0;
}