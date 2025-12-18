#ifndef SCANNER_H
#define SCANNER_H

#include <netinet/in.h>

typedef struct {
    char *ip;
    int start_port;
    int end_port;
} scan_range_t;

// Function prototype for the thread worker
void* scan_ports(void* arg);

#endif
