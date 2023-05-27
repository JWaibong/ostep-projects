#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


void print_file(FILE* f) {

    char c = fgetc(f);
    while (c != EOF) {
        fputc(c, stdout);
        c = fgetc(f);
    }

    
}

int main(int argc, char** argv) {

    if (argc < 2) {
        //printf("wcat: file1 [file2 ...]\n");
        return 0;
    }

    for (int i=1; i<argc; i++) {
        char *file_name = argv[i];
        FILE *f = fopen(file_name, "r");


        if (!f) {
            fprintf(stdout, "wcat: cannot open file\n");
            return 1;
        }

        print_file(f);
        fclose(f);
    }




    return EXIT_SUCCESS;


}