#include "ipc_utils.h"

int msgid;

void place_order() {
    OrderMessage order;
    order.msg_type = 1;
    
    printf("Enter item name: ");
    scanf("%s", order.item_name);
    
    printf("Enter quantity: ");
    scanf("%d", &order.quantity);
    
    send_message(msgid, &order);
    printf("Order placed: %s x %d\n", order.item_name, order.quantity);
}

int main() {
    msgid = create_message_queue();
    
    while (1) {
        place_order();
        sleep(1);
    }
    
    return 0;
}