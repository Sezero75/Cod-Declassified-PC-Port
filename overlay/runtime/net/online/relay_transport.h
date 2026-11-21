#ifndef NATIV_RELAY_TRANSPORT_H
#define NATIV_RELAY_TRANSPORT_H
#include <stdint.h>
#include <stddef.h>
struct sockaddr_in;
int relay_transport_open(uint16_t port, int server);
void relay_transport_send(const struct sockaddr_in *address, const uint8_t *data, size_t size);
int relay_transport_receive(struct sockaddr_in *from, uint8_t *data, size_t capacity);
#endif
