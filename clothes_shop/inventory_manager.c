#include "ipc_utils.h"

int shmid, semid;
Inventory *inventory;

void update_inventory() {
    char item_name[ITEM_NAME_LEN];
    int new_count;
    float new_price;
    
    printf("Enter item name to update: ");
    scanf("%s", item_name);
    
    semaphore_wait(semid);
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (strcmp(inventory->items[i].name, item_name) == 0) {
            printf("Enter new quantity: ");
            scanf("%d", &new_count);
            printf("Enter new price: ");
            scanf("%f", &new_price);
            
            inventory->items[i].count = new_count;
            inventory->items[i].price = new_price;
            printf("Updated %s: Count = %d, Price = %.2f\n", item_name, new_count, new_price);
            break;
        }
    }
    semaphore_signal(semid);
}

int main() {
    shmid = create_shared_memory();
    inventory = attach_shared_memory(shmid);
    semid = create_semaphore();
    
    while (1) {
        update_inventory();
        sleep(1);
    }
    
    return 0;
}