#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <threads.h>

#define __STDC_WANT_LIB_EXT1__ 1

static void sleep_ms(long milliseconds) {
    struct timespec duration = {
        .tv_sec = milliseconds / 1000,
        .tv_nsec = (milliseconds % 1000) * 1000000L
    };

    thrd_sleep(&duration, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("\nPlay text art animations in the terminal\n\n");
        printf("Usage: text_art <folder> <loops>\n");
        printf("\t<folder>\tFolder containing text art frames\n");
        printf("\t<loops>\t\tNumber of times to loop the animation or use -1 to loop until the user terminates the program\n");
        printf("\n");
        return 0;
    }

    char *folder_name = argv[1];
    int loops = atoi(argv[2]);

    char path[512];
    snprintf(path, sizeof(path), "%s/0.txt", folder_name);
    FILE *test_file = fopen(path, "r");
    if (!test_file) {
        printf("%s could not be found\n", folder_name);
        return 0;
    }
    fclose(test_file);

    char **text_files = NULL;
    int num_found = 0;

    while (1) {
        snprintf(path, sizeof(path), "%s/%d.txt", folder_name, num_found);
        FILE *f = fopen(path, "r");
        if (!f) break;

        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fseek(f, 0, SEEK_SET);

        text_files = realloc(text_files, (num_found + 1) * sizeof(char *));
        text_files[num_found] = malloc(size + 1);
        fread(text_files[num_found], 1, size, f);
        text_files[num_found][size] = '\0';
        fclose(f);
        num_found++;
    }

    if (num_found == 0) {
        printf("%s did not have text art files\n", folder_name);
        return 0;
    }

    int lines = 1;
    for (int i = 0; text_files[0][i]; i++) {
        if (text_files[0][i] == '\n') lines++;
    }

    char *backspace_adjust = malloc(lines * 4 + 1);
    backspace_adjust[0] = '\0';
    for (int i = 0; i < lines; i++) {
        strcat(backspace_adjust, "\033[A");
    }

    int i = 0;
    int first = 1;

    while (i < loops || loops == -1) {
        for (int j = 0; j < num_found; j++) {
            if (!first) {
                printf("%s", backspace_adjust);
            }
            printf("%s", text_files[j]);
            fflush(stdout);
            sleep_ms(50);
            first = 0;
        }
        i++;
    }

    for (int j = 0; j < num_found; j++) {
        free(text_files[j]);
    }
    free(text_files);
    free(backspace_adjust);

    return 0;
}
