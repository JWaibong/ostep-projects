#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <sys/stat.h>

void reverse_file(FILE *f, FILE *out) {

    char *buf;
    size_t bufsize = 256;
    ssize_t characters;

    char **lines = (char **)calloc(bufsize, sizeof(char *));
    if (!lines) {
        fprintf(stderr, "malloc failed\n");
        exit(1);     
    }


    int line_num = 0;

    while(1) {

        buf = (char *)calloc(bufsize, sizeof(char));
        if (buf == NULL) {
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        characters = getline(&buf,&bufsize,f);

        if (characters == -1) {
            break;
        }

        lines[line_num] = buf;
        line_num++;
    }

    for (int i=line_num-1; i>=0; i--) {

        char* line = lines[i];
        if (!line) {
            continue;
        }

        int j=0;
        while (line[j] != '\n') {
            fputc(line[j], out);
            j++;
        }
        fputc('\n', out);

    }
    free(lines);
    free(buf);




}

int main(int argc, char** argv) {

    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }

    if (argc == 1) {
        reverse_file(stdin, stdout);
    }
    else if (argc == 2) {

        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "reverse: cannot open file \'%s\'\n", argv[1]);
            return 1;
        }
        reverse_file(f, stdout);
    }
    else if (!strcmp(argv[1], argv[2])) {

        fprintf(stderr, "reverse: input and output file must differ\n");
        return 1;

    }
    else {

        struct stat s1 = {0};
        struct stat s2 = {0};
        stat(argv[1], &s1);
        stat(argv[2], &s2);

        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(stderr, "reverse: cannot open file \'%s\'\n", argv[1]);
            return 1;
        }
        FILE *out = fopen(argv[2], "w");
        if (!out) {
            fprintf(stderr, "reverse: cannot open file \'%s\'\n", argv[2]);
            return 1;
        }

        if (s1.st_ino == s2.st_ino && s1.st_dev == s2.st_dev) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            return 1;
        }

        reverse_file(f, out);
    }







    return EXIT_SUCCESS;


}