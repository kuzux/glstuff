#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <mtlparse.h>

mtl_file_t* make_mtl_file(const char* filename) {
    mtl_file_t* res = (mtl_file_t*)malloc(sizeof(mtl_file_t));

    res->filename = filename;

    return res;
}

int parse_mtl_lines(char** lines, int num_lines, mtl_file_t* mtl) {
    for (int i = 0; i < num_lines; i++) {
        char* word = strtok(lines[i], " ");

        if(strcmp(word, "Ka")==0) {
            word = strtok(NULL, " ");
            mtl->ka.r = atof(word);

            word = strtok(NULL, " ");
            mtl->ka.g = atof(word);

            word = strtok(NULL, " ");
            mtl->ka.b = atof(word);
        } else if(strcmp(word, "Kd")==0) {
            word = strtok(NULL, " ");
            mtl->kd.r = atof(word);

            word = strtok(NULL, " ");
            mtl->kd.g = atof(word);

            word = strtok(NULL, " ");
            mtl->kd.b = atof(word);
        } else if(strcmp(word, "Ks")==0) {
            word = strtok(NULL, " ");
            mtl->ks.r = atof(word);

            word = strtok(NULL, " ");
            mtl->ks.g = atof(word);

            word = strtok(NULL, " ");
            mtl->ks.b = atof(word);
        } else if(strcmp(word, "Ns")==0) {
            word = strtok(NULL, " ");
            mtl->ns = atof(word);
        } else {
            // ignore
        }
    }

    return 0;
}

int parse_mtl_file(mtl_file_t* mtl) {
    FILE* f = fopen(mtl->filename, "r");

    if(!f) {
        printf("Error opening file. errno %d\n", errno);
        return 1;
    }

    char ch;
    int num_lines = 0;

    while(!feof(f)) {
        ch = fgetc(f);
        if(ch == '\n') num_lines++;
    }

    fseek(f, 0, SEEK_SET);

    char** lines = (char**)malloc(num_lines*sizeof(char*));

    for(int i=0;i<num_lines;i++) {
        lines[i] = (char*)malloc(255);
        fgets(lines[i], 255, f);

        if(!lines[i]) {
            printf("Error reading file. errno %d\n", errno);
        }
    }

    fclose(f);

    if(parse_mtl_lines(lines, num_lines, mtl)) {
        return 1;
    }

    for(int i=0;i<num_lines;i++){
        free(lines[i]);
    }

    return 0;
}

void delete_mtl_file(mtl_file_t* mtl) {
    free(mtl);
}