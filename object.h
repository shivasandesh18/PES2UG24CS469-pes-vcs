#ifndef OBJECT_H
#define OBJECT_H

#define HASH_SIZE 32
#define HASH_HEX_SIZE 64

typedef struct {
    char hash[HASH_HEX_SIZE + 1];
} ObjectID;

#endif
