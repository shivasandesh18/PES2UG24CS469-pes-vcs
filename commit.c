#include "commit.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void generate_fake_hash(ObjectID *id) {
    sprintf(id->hash, "%ld", time(NULL));
}

int head_read(ObjectID *id) {
    FILE *f = fopen(".pes/HEAD", "r");
    if (!f) return -1;

    fscanf(f, "%s", id->hash);
    fclose(f);
    return 0;
}

int head_update(const ObjectID *id) {
    FILE *f = fopen(".pes/HEAD", "w");
    if (!f) return -1;

    fprintf(f, "%s\n", id->hash);
    fclose(f);
    return 0;
}

int commit_create(const char *message, ObjectID *id) {

    Commit commit;
    strcpy(commit.author, "sanjith_PES2UG24CS445");
    strcpy(commit.message, message);
    commit.timestamp = time(NULL);

    if (head_read(&commit.parent) == 0)
        commit.has_parent = 1;
    else
        commit.has_parent = 0;

    generate_fake_hash(id);

    char path[200];
    sprintf(path, ".pes/%s.commit", id->hash);

    FILE *f = fopen(path, "w");
    if (!f) return -1;

    fprintf(f, "author %s\n", commit.author);
    fprintf(f, "time %ld\n", commit.timestamp);
    fprintf(f, "%s\n", commit.message);

    fclose(f);

    head_update(id);

    printf("Committed\n");
    return 0;
}
