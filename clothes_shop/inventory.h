#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_ITEMS 10
#define MSG_SIZE 256
#define SHM_KEY 1234
#define MSG_KEY 5678
#define SEM_KEY 91011

// Structure for inventory items
typedef struct 
{
    char name[50];
    int quantity;
    float price;

} Item;

// Shared memory structure
typedef struct 
{
    Item stock[MAX_ITEMS];
    int totalItems;

} Inventory;

// Message structure for orders
typedef struct 
{
    long msg_type;
    char data[MSG_SIZE];

} Message;

void acquire_lock();
void release_lock();
void shop_handler();
void user_interface();

#endif