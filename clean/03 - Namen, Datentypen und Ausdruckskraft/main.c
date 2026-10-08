#include <stdio.h>
#include <stdbool.h>
typedef enum { SHIPMENT_CREATED, SHIPMENT_PACKED, SHIPMENT_SENT } ShipmentStatus;
int main(int argc, char *argv[])
{
    int input_status, input_paid, input_invalid_address, input_id;
    ShipmentStatus status;
    bool payment_received, address_invalid;
    unsigned int shipment_id;
    if (argc != 5 || sscanf(argv[1], "%d", &input_status) != 1 ||
        sscanf(argv[2], "%d", &input_paid) != 1 ||
        sscanf(argv[3], "%d", &input_invalid_address) != 1 ||
        sscanf(argv[4], "%d", &input_id) != 1 ||
        input_status < SHIPMENT_CREATED || input_status > SHIPMENT_SENT ||
        (input_paid != 0 && input_paid != 1) ||
        (input_invalid_address != 0 && input_invalid_address != 1) || input_id < 0) {
        fprintf(stderr, "Usage: %s STATUS(0-2) PAID(0/1) INVALID_ADDRESS(0/1) ID(>=0)\n", argv[0]);
        return 1;
    }
    status = (ShipmentStatus)input_status;
    payment_received = input_paid != 0;
    address_invalid = input_invalid_address != 0;
    shipment_id = (unsigned int)input_id;
    if (status == SHIPMENT_SENT && payment_received && !address_invalid)
        printf("Shipment %u: ready\n", shipment_id);
    else
        printf("Shipment %u: not ready\n", shipment_id);
    return 0;
}
