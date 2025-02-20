#include "ipc_utils.h"
#include <signal.h>

int shmid, semid, msgid;
Inventory *inventory;

void cleanup(int signum) {
    detach_shared_memory(inventory);
    remove_shared_memory(shmid);
    remove_message_queue(msgid);
    exit(0);
}

void print_inventory() {
    semaphore_wait(semid);
    printf("\nCurrent Inventory:\n");
    for (int i = 0; i < MAX_ITEMS; i++) {
        printf("%s - Count: %d, Price: %.2f\n", inventory->items[i].name, inventory->items[i].count, inventory->items[i].price);
    }
    semaphore_signal(semid);
}

void process_orders() {
    OrderMessage order;
    while (1) {
        if (receive_message(msgid, &order, 1) != -1) {
            semaphore_wait(semid);
            for (int i = 0; i < MAX_ITEMS; i++) {
                if (strcmp(inventory->items[i].name, order.item_name) == 0) {
                    if (inventory->items[i].count >= order.quantity) {
                        inventory->items[i].count -= order.quantity;
                        printf("Order processed: %s x %d\n", order.item_name, order.quantity);
                    } else {
                        printf("Not enough stock for %s\n", order.item_name);
                    }
                    break;
                }
            }
            semaphore_signal(semid);
        }
        sleep(2);
        print_inventory();
    }
}

int main() {
    signal(SIGINT, cleanup);
    
    shmid = create_shared_memory();
    inventory = attach_shared_memory(shmid);
    semid = create_semaphore();
    set_semaphore_value(semid, 1);
    msgid = create_message_queue();
    
    process_orders();
    return 0;
}