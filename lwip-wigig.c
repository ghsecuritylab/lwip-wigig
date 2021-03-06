#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "lwip/tcpip.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/ip_addr.h"

#include "ethernetif.h"
#include "ethernetif_driver.h"
#include "lowlevel_wigig.h"

#include "udpecho.h"

void wigigif_init(struct ethernetif *wigigif);

int main(int argc, char** argv)
{
    struct ethernetif wigigif;
    struct netif netif;
    ip4_addr_t ip, netmask, gw;

    tcpip_init(NULL, NULL);

    wigigif_init(&wigigif);

    IP4_ADDR(&ip, 10, 0, 0, 2);
    IP4_ADDR(&netmask, 255, 255, 255, 0);
    IP4_ADDR(&gw, 10, 0, 0, 1);
    netif_add(&netif, &ip, &netmask, &gw,
            &wigigif, ethernetif_init, tcpip_input);
    netif_set_default(&netif);
    netif_set_up(&netif);

    if (argc != 2)
        return 0;

    udpecho_init(argv[1]);

    pause();

    return 0;
}

void wigigif_init(struct ethernetif *wigigif)
{
    memset(wigigif, 0, sizeof(struct ethernetif));

    wigigif->low_level_init = low_level_init;
    wigigif->low_level_endinput = low_level_endinput;
    wigigif->low_level_input = low_level_input;
    wigigif->low_level_startinput = low_level_startinput;
    wigigif->low_level_endoutput = low_level_endoutput;
    wigigif->low_level_output = low_level_output;
    wigigif->low_level_startoutput = low_level_startoutput;

    wigigif->internals = NULL;

    wigigif->address[0] = 0x1;
    wigigif->address[1] = 0x2;
    wigigif->address[2] = 0x3;
    wigigif->address[3] = 0x4;
    wigigif->address[4] = 0x5;
    wigigif->address[5] = 0x6;
}
