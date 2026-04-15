#ifndef COMMIT_H
#define COMMIT_H

#include "object.h"

typedef struct {
    char author[100];
    char message[1024];
    long timestamp;

    int has_parent;
    ObjectID parent;
} Commit;

int commit_create(const char *message, ObjectID *id);

int head_read(ObjectID *id);
int head_update(const ObjectID *id);

#endif
