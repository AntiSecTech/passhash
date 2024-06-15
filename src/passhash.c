#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_help() {
    printf("\n");
    printf(" ██▓███   ▄▄▄        ██████   ██████  ██░ ██  ▄▄▄        ██████  ██░ ██ \n");
    printf("▓██░  ██▒▒████▄    ▒██    ▒ ▒██    ▒ ▓██░ ██▒▒████▄    ▒██    ▒ ▓██░ ██▒\n");
    printf("▓██░ ██▓▒▒██  ▀█▄  ░ ▓██▄   ░ ▓██▄   ▒██▀▀██░▒██  ▀█▄  ░ ▓██▄   ▒██▀▀██░\n");
    printf("▒██▄█▓▒ ▒░██▄▄▄▄██   ▒   ██▒  ▒   ██▒░▓█ ░██ ░██▄▄▄▄██   ▒   ██▒░▓█ ░██ \n");
    printf("▒██▒ ░  ░ ▓█   ▓██▒▒██████▒▒▒██████▒▒░▓█▒░██▓ ▓█   ▓██▒▒██████▒▒░▓█▒░██▓\n");
    printf("▒▓▒░ ░  ░ ▒▒   ▓▒█░▒ ▒▓▒ ▒ ░▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒ ▒▒   ▓▒█░▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒\n");
    printf("░▒ ░       ▒   ▒▒ ░░ ░▒  ░ ░░ ░▒  ░ ░ ▒ ░▒░ ░  ▒   ▒▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░\n");
    printf("░░         ░   ▒   ░  ░  ░  ░  ░  ░   ░  ░░ ░  ░   ▒   ░  ░  ░   ░  ░░ ░\n");
    printf("               ░  ░      ░        ░   ░  ░  ░      ░  ░      ░   ░  ░  ░\n");
    printf("\n");
    printf("Usage: passhash [password] | [-p:[password]] [-u:[username]] [-s:[salt]]\n");
    printf("\n");
    printf("Options:\n");
    printf("  -p:[password]   Password for hash generation (required)\n");
    printf("  -u:[username]   Username (optional, default: root)\n");
    printf("  -s:[salt]       Salt for hash generation (optional, default: salted)\n");
    printf("\n");
}

int main(int argc, char *argv[]) {
    char *username = "root";
    char *salt = "salted";
    char *password = NULL;
    char *prefix = NULL;
    char *suffix = ":0:0:root:/root:/bin/bash";

    if (argc == 1) {
        show_help();
        return 1;
    }

    if (argc == 2 && argv[1][0] != '-') {
        password = argv[1];
    } else {
        for (int i = 1; i < argc; i++) {
            if (strncmp(argv[i], "-u:", 3) == 0) {
                username = argv[i] + 3;
            } else if (strncmp(argv[i], "-p:", 3) == 0) {
                password = argv[i] + 3;
            } else if (strncmp(argv[i], "-s:", 3) == 0) {
                salt = argv[i] + 3;
            } else {
                printf("Unknown parameter: %s\n", argv[i]);
                show_help();
                return 1;
            }
        }
    }

    if (password == NULL) {
        printf("Error: The password must be provided with the -p:[password] option.\n");
        show_help();
        return 1;
    }

    char command[256];
    snprintf(command, sizeof(command), "openssl passwd -6 -salt %s %s", salt, password);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Failed to run openssl command");
        return 1;
    }

    char hashed_password[256];
    if (fgets(hashed_password, sizeof(hashed_password), fp) == NULL) {
        perror("Failed to read hashed password");
        pclose(fp);
        return 1;
    }
    pclose(fp);

    size_t len = strlen(hashed_password);
    if (len > 0 && hashed_password[len - 1] == '\n') {
        hashed_password[len - 1] = '\0';
    }

    prefix = malloc(strlen(username) + 2);
    if (prefix == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }
    sprintf(prefix, "%s:", username);

    printf("%s%s%s\n", prefix, hashed_password, suffix);

    free(prefix);

    return 0;
}
