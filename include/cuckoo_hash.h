#ifndef _CUCKOO_HASH_H
#define _CUCKOO_HASH_H

typedef unsigned int Bool;
typedef int KeyType; // support int only at present

#define HASH_FUNCS_NUM 2
#define BUCKETS_NUM    11
#define MAX_KICK_INSERT_TIMES 10
#define TRUE 1
#define FALSE 0

typedef struct CuckooHashType {
    struct {
	Bool used;
	KeyType  key;
    } buckets[HASH_FUNCS_NUM][BUCKETS_NUM];
    unsigned int (*funcs[HASH_FUNCS_NUM]) (KeyType key);

    //void (*init) (struct CuckooHashType *tbl);
    Bool (*lookup) (struct CuckooHashType *tbl, KeyType key);
    void (*insert) (struct CuckooHashType *tbl, KeyType key);
    void (*del) (struct CuckooHashType *tbl, KeyType key);
    void (*print) (struct CuckooHashType *tbl);
} CuckooHash;

void CuckooHashInit (CuckooHash *tbl);

#endif
