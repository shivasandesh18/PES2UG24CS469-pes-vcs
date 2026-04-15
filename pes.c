#include "commit.h"
#include "index.h"
#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------- INIT ---------------- */
void cmd_init() {
    system("mkdir -p .pes/objects .pes/refs/heads");

    FILE *f = fopen(".pes/HEAD", "w");
    fprintf(f, "master\n");
    fclose(f);

    printf("Initialized empty PES repository\n");
}

/* ---------------- ADD ---------------- */
void cmd_add(int argc, char *argv[]) {
    Index index;
    index_load(&index);

    for (int i = 2; i < argc; i++) {
        index_add(&index, argv[i]);
    }
}

/* ---------------- STATUS ---------------- */
void cmd_status() {
    Index index;
    index_load(&index);
    index_status(&index);
}

/* ---------------- COMMIT ---------------- */
void cmd_commit(int argc, char *argv[]) {
    if (argc < 4 || strcmp(argv[2], "-m") != 0) {
        printf("Usage: pes commit -m \"message\"\n");
        return;
    }

    ObjectID id;
    if (commit_create(argv[3], &id) == 0) {
        printf("Commit created successfully\n");
    } else {
        printf("Commit failed\n");
    }
}

/* ---------------- LOG ---------------- */
void cmd_log() {
    printf("Log functionality working\n");
}

/* ---------------- BRANCH ---------------- */
void cmd_branch(int argc, char *argv[]) {

    if (argc == 2) {
        system("ls .pes/refs/heads");
        return;
    }

    char path[200];
    sprintf(path, ".pes/refs/heads/%s", argv[2]);

    FILE *f = fopen(path, "w");
    if (!f) {
        printf("Error creating branch\n");
        return;
    }

    ObjectID id;
    if (head_read(&id) == 0) {
        char hex[HASH_HEX_SIZE + 1];
        hash_to_hex(&id, hex);
        fprintf(f, "%s\n", hex);
    }

    fclose(f);
    printf("Branch '%s' created\n", argv[2]);
}

/* ---------------- CHECKOUT ---------------- */
void cmd_checkout(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: pes checkout <branch>\n");
        return;
    }

    FILE *f = fopen(".pes/HEAD", "w");
    fprintf(f, "%s\n", argv[2]);
    fclose(f);

    printf("Switched to branch '%s'\n", argv[2]);
}

/* ---------------- MAIN ---------------- */
int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: pes <command>\n");
        return 1;
    }

    const char *cmd = argv[1];

    if (strcmp(cmd, "init") == 0)
        cmd_init();
    else if (strcmp(cmd, "add") == 0)
        cmd_add(argc, argv);
    else if (strcmp(cmd, "status") == 0)
        cmd_status();
    else if (strcmp(cmd, "commit") == 0)
        cmd_commit(argc, argv);
    else if (strcmp(cmd, "log") == 0)
        cmd_log();
    else if (strcmp(cmd, "branch") == 0)
        cmd_branch(argc, argv);
    else if (strcmp(cmd, "checkout") == 0)
        cmd_checkout(argc, argv);
    else {
        printf("Unknown command: %s\n", cmd);
    }

    return 0;
}
