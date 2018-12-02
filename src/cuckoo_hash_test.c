#include "cuckoo_hash.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    int i;
    CuckooHash hashTbl;
    KeyType list[] = { 20, 50, 53, 75, 100, 67, 105, 3, 36, 39 };

    CuckooHashInit(&hashTbl);
    for (i = 0; i < sizeof(list) / sizeof(list[0]); i++) {
	fprintf(stdout, "%d\n", i);
	hashTbl.insert(&hashTbl, list[i]);
	hashTbl.print(&hashTbl);
    }

    return EXIT_SUCCESS;
}
