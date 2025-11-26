#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#define ERROR -1

int main(int ac, char **av)
{
    char buffer[65535];
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    struct ether_header *eth = (struct ether_header *) buffer;
    struct ip *ip_address = (struct ip *)(buffer + sizeof(struct ether_header)); 
 

    if (sock == -1)
    {
        perror("ERROR\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        int paquet_recv = recv(sock, buffer, sizeof(buffer), 0);
        printf("Paquet capturé : %d octets \n Adresse MAC --> ", paquet_recv);

        for (int i = 0; i < 6; i++)
        {
            printf("%02x:", eth->ether_shost[i]);
            printf("IP source = %s", inet_ntoa(ip_address->ip_src));
        }
        printf("\n");
    }

}