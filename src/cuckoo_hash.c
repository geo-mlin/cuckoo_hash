#include "cuckoo_hash.h"
#include <assert.h>
#include <stdio.h>

static unsigned int HashFunc1 (KeyType key);
static unsigned int HashFunc2 (KeyType key);
static Bool CuckooHashLookup (CuckooHash *tbl, KeyType key);
static void CuckooHashInsert (CuckooHash *tbl, KeyType key);
static void CuckooHashDelete (CuckooHash *tbl, KeyType key);
static void CuckooHashPrint (CuckooHash *tbl);

void CuckooHashInit (CuckooHash *tbl)
{
    int i, j;

    for (i = 0; i < HASH_FUNCS_NUM; i++) {
	for (j = 0; j < BUCKETS_NUM; j++) {
	    tbl->buckets[i][j].used = FALSE;
	}
    }
    tbl->funcs[0] = HashFunc1;
    tbl->funcs[1] = HashFunc2;

    tbl->lookup = CuckooHashLookup;
    tbl->insert = CuckooHashInsert;
    tbl->del    = CuckooHashDelete;
    tbl->print  = CuckooHashPrint;
}

unsigned int HashFunc1 (KeyType key)
{
    return key % BUCKETS_NUM;
}

unsigned int HashFunc2 (KeyType key)
{
    return (key / BUCKETS_NUM) % BUCKETS_NUM;
}

Bool CuckooHashLookup (CuckooHash *tbl, KeyType key)
{
    int i;
    unsigned int index;

    for (i = 0; i < HASH_FUNCS_NUM; i++) {
	index = tbl->funcs[i](key);
	if (tbl->buckets[i][index].used == TRUE &&
		tbl->buckets[i][index].key == key) {
	    return TRUE;
	}
    }

    return FALSE;
}

void CuckooHashInsert (CuckooHash *tbl, KeyType key)
{
    int i, j;
    unsigned int index;
    KeyType kicked;

    if (tbl->lookup(tbl, key) == TRUE) {
	return;
    }
    for (i = 0; i < MAX_KICK_INSERT_TIMES; i++) {
	for (j = 0; j < HASH_FUNCS_NUM; j++) {
	    index = tbl->funcs[j](key);
	    if (tbl->buckets[j][index].used == FALSE) {
		tbl->buckets[j][index].key = key;
		tbl->buckets[j][index].used = TRUE;
		return;
	    } else {
		kicked = tbl->buckets[j][index].key;
		tbl->buckets[j][index].key = key;
		key = kicked;
	    }
	}
    }

    assert("rehash is needed.");
}

void CuckooHashDelete (CuckooHash *tbl, KeyType key)
{
    int i;
    unsigned int index;

    for (i = 0; i < HASH_FUNCS_NUM; i++) {
	index = tbl->funcs[i](key);
	if (tbl->buckets[i][index].used != TRUE &&
		tbl->buckets[i][index].key == key) {
	    tbl->buckets[i][index].used = FALSE;
	    return;
	}
    }
}

void CuckooHashPrint (CuckooHash *tbl)
{
    int i, j;

    for (i = 0; i < HASH_FUNCS_NUM; i++) {
	for (j = 0; j < BUCKETS_NUM; j++) {
	    if (tbl->buckets[i][j].used == TRUE) {
		fprintf(stdout, "%3d ", tbl->buckets[i][j].key);
	    } else {
		fprintf(stdout, "%3s ", "-");
	    }
	}
	fprintf(stdout, "\t");
    }
    fprintf(stdout, "\n");
}
