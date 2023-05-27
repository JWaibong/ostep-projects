#include <stdio.h>
#include <stdlib.h>
#include <string.h>




void print_lines_containing_query(FILE *f, char* query) {

    size_t query_len = strlen(query);
    char *buffer;
    size_t bufsize = 1024;
    ssize_t characters;

    buffer = (char *)calloc(bufsize, sizeof(char));
    if (buffer == NULL) {
        exit(1);
    }


    int line_num = 0;
    while(1) {

        next_line:
        characters = getline(&buffer,&bufsize,f);

        if (characters == -1) {
            break;
        }

        for (int i=0; i<bufsize; i++) {
            if (buffer[i] == '\n') {
                goto next_line;
            }
            if (buffer[i] == query[0] && (i + query_len < bufsize)) {
                if (!strncmp(query, &buffer[i], query_len)) {
                    //fprintf(stderr, "found matching line at line_num %d at position %d", line_num, i);
                    printf("%s", buffer);
                    line_num++;
                    goto next_line;
                }
            }
        }

    }

    free(buffer);


}


int main(int argc, char** argv) {

    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }


    char *query = argv[1];
    if(!strcmp(query, "")) {
        return EXIT_SUCCESS;
    }

    if (!argv[2]) {
        print_lines_containing_query(stdin, query);
    }
    else {
        for (int i=2; i<argc; i++) {
            char *file_name = argv[i];
            FILE *f = fopen(file_name, "r");
            if (!f) {
                fprintf(stdout, "wgrep: cannot open file\n");
                return 1;
            }
            print_lines_containing_query(f, query);
        }
    }
    
    return EXIT_SUCCESS;


}