#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>




void unzip_files(FILE **files) {
    uint32_t count = 0;

    int i = 0;
    FILE *f = files[i];

    while (f) {

        while (1) {

            char c = fgetc(f);
            if (c == EOF) {
                goto next_file;
            }
            ungetc(c, f);
            fread(&count, sizeof(count), 1, f);
            // if (bytes_read < sizeof(count)) {
            //     goto next_file;
            // }
            c = fgetc(f);
            for (int i=0; i<count; i++) {
                fputc(c, stdout);
            }

        }

        next_file:
        i++;
        f = files[i];
    }
    

}


int main(int argc, char **argv) {
    
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    FILE **files = calloc(argc, sizeof(FILE *));
    for (int i=1; i<argc; i++) {
        char *file_name = argv[i];
        FILE *f = fopen(file_name, "r");
        if (!f) {
            printf("failed to open file");
            return 1;
        }
        files[i-1] = f;
    }

    unzip_files(files);

    for (int i=0; i<argc-1; i++) {
        fclose(files[i]);
    }
    free(files);

    return EXIT_SUCCESS;



}