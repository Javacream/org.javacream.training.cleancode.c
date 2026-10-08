#include <stdio.h>
#include <stdbool.h>
typedef enum { SHIPMENT_CREATED, SHIPMENT_PACKED, SHIPMENT_SENT } ShipmentStatus;
int main(void)
{
    ShipmentStatus status = SHIPMENT_SENT;
    bool payment_received = true;
    bool address_invalid = false;
    unsigned int shipment_id = 3;
    if (status == SHIPMENT_SENT && payment_received && !address_invalid)
        printf("Shipment %u: ready\n", shipment_id);
    else
        printf("Shipment %u: not ready\n", shipment_id);
    return 0;
}
