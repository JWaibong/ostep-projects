#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void zip_files(FILE **files) {
    uint32_t count = 1;
    char prev;

    int i = 0;
    FILE *f = files[i];

    while (f) {
        char c = fgetc(f);
        while (c != EOF) {
            prev = c;
            c = fgetc(f);

            if (c == EOF && files[i+1] != NULL) {
                count++;
                goto next_file;
            }

            if (prev != c) {
                fwrite(&count, sizeof(count), 1, stdout);
                printf("%c", prev);
                count = 0;
            }
            count++;
        }

        next_file:
        i++;
        f = files[i];
    }
}

int main(int argc, char** argv) {

    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    FILE **files = calloc(argc, sizeof(FILE *));
    for (int i=1; i<argc; i++) {
        char *file_name = argv[i];
        FILE *f = fopen(file_name, "r");
        if (!f) {
            fprintf(stderr, "failed to open file");
            return 1;
        }
        files[i-1] = f;
    }
    
    zip_files(files);
    
    for (int i=0; i<argc-1; i++) {
        fclose(files[i]);
    }
    free(files);



    return EXIT_SUCCESS;


}