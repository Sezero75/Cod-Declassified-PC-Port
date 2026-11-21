/* ENet connections carry the existing signed-in peers' sealed datagrams. The game still
 * implements its own reliable delivery, so avoid a second retransmission queue. */
#include <enet/enet.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <netinet/in.h>
#endif
#include "relay_transport.h"

static ENetHost *host;
static int server_mode;
static pthread_mutex_t guard = PTHREAD_MUTEX_INITIALIZER;

int relay_transport_open(uint16_t port, int server) {
    ENetAddress bind_address = { ENET_HOST_ANY, port };
    if (enet_initialize() != 0) return 0;
    const char *bind_ip = server ? getenv("DECLASSIFIED_RELAY_BIND") : NULL;
    if (bind_ip && *bind_ip && enet_address_set_host_ip(&bind_address, bind_ip) != 0) return 0;
    host = enet_host_create(&bind_address, server ? 64 : 1, 1, 0, 0);
    if (!host) return 0;
    host->maximumPacketSize = 1500;
    host->maximumWaitingData = 65536;
    server_mode = server;
    return host->address.port;
}

void relay_transport_send(const struct sockaddr_in *address, const uint8_t *data, size_t size) {
    ENetAddress to = { address->sin_addr.s_addr, ntohs(address->sin_port) };
    pthread_mutex_lock(&guard);
    ENetPeer *peer = NULL;
    for (size_t i = 0; i < host->peerCount; i++) {
        ENetPeer *p = &host->peers[i];
        if (p->state != ENET_PEER_STATE_DISCONNECTED && p->address.host == to.host && p->address.port == to.port) {
            peer = p;
            break;
        }
    }
    if (!peer && !server_mode) peer = enet_host_connect(host, &to, 1, 0);
    if (peer && peer->state == ENET_PEER_STATE_CONNECTED) {
        ENetPacket *packet = enet_packet_create(data, size, ENET_PACKET_FLAG_UNSEQUENCED | ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
        if (packet && enet_peer_send(peer, 0, packet) != 0) enet_packet_destroy(packet);
        enet_host_flush(host);
    }
    pthread_mutex_unlock(&guard);
}

int relay_transport_receive(struct sockaddr_in *from, uint8_t *data, size_t capacity) {
    int size = 0;
    ENetEvent event;
    pthread_mutex_lock(&guard);
    while (enet_host_service(host, &event, 0) > 0) {
        if (event.type != ENET_EVENT_TYPE_RECEIVE) continue;
        if (event.packet->dataLength <= capacity) {
            size = (int)event.packet->dataLength;
            memset(from, 0, sizeof *from);
            from->sin_family = AF_INET;
            from->sin_addr.s_addr = event.peer->address.host;
            from->sin_port = htons(event.peer->address.port);
            memcpy(data, event.packet->data, size);
        }
        enet_packet_destroy(event.packet);
        break;
    }
    pthread_mutex_unlock(&guard);
    return size;
}
