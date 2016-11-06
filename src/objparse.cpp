#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <map>

#include <glm/glm.hpp>

#include <objparse.h>

void parse_face(char* word, int* vi, int* vti, int* vni) {
    char* num;
    num = strtok(word, "/");
    *vi = atoi(num)-1;

    num = strtok(NULL, "/");
    *vti = atoi(num)-1;

    num = strtok(NULL, "/");
    *vni = atoi(num)-1;
}

void parse_string(char** lines, int num_lines, GLfloat** vertices, GLuint** faces) {
    // find the number of vertices and faces we'll need
    int num_vertices = 0;
    int num_faces = 0;

    std::map<char*, int> faceIndices;

    std::map<int, int> posIndices;
    std::map<int, int> normalIndices;
    std::map<int, int> texcoordIndices;

    int num_v = 0;
    int num_vt = 0;
    int num_vn = 0;

    for(int i=0; i<num_lines; i++) {
        char* word = strtok((char*)lines[i], " ");

        if(strcmp(word, "f") == 0) {
            int vi, vti, vni;

            word = strtok(NULL, " ");
            *(word-1) = ' ';
            
            char* nextword;
            nextword = word + strlen(word) + 1;

            if(faceIndices.find(word)==faceIndices.end()){
                faceIndices[word] = num_vertices;

                parse_face(word, &vi, &vti, &vni);

                posIndices[num_vertices] = vi;
                normalIndices[num_vertices] = vni;
                texcoordIndices[num_vertices] = vti;

                num_vertices++;
            }

            word = strtok(nextword, " ");
            *(word-1) = ' ';
            nextword = word + strlen(word) + 1;

            if(faceIndices.find(word)==faceIndices.end()){
                faceIndices[word] = num_vertices;

                parse_face(word, &vi, &vti, &vni);

                posIndices[num_vertices] = vi;
                normalIndices[num_vertices] = vni;
                texcoordIndices[num_vertices] = vti;

                num_vertices++;
            }

            word = strtok(nextword, " ");
            *(word-1) = ' ';
            if(faceIndices.find(word)==faceIndices.end()){
                faceIndices[word] = num_vertices;

                parse_face(word, &vi, &vti, &vni);

                posIndices[num_vertices] = vi;
                normalIndices[num_vertices] = vni;
                texcoordIndices[num_vertices] = vti;

                num_vertices++;
            }

            num_faces += 3;
        } else if(strcmp(word, "v") == 0) {
            *(word+1)=' ';

            num_v++;
        } else if(strcmp(word, "vt") == 0) {
            *(word+2)=' ';

            num_vt++;
        } else if(strcmp(word, "vn") == 0) {
            *(word+2)=' ';

            num_vn++;
        } else {
            // ignore
        }
    }

    if(vertices) {
        *vertices = (GLfloat*)malloc(DATAPT_PER_VERTEX*num_vertices*sizeof(GLfloat));
    }

    if(faces) {
        *faces = (GLuint*)malloc(num_vertices*sizeof(GLuint));
    }

    glm::vec3* v = (glm::vec3*)malloc(num_v*sizeof(glm::vec3));
    glm::vec2* vt = (glm::vec2*)malloc(num_vt*sizeof(glm::vec2));
    glm::vec3* vn = (glm::vec3*)malloc(num_vn*sizeof(glm::vec3));

    int v_i = 0;
    int vt_i = 0;
    int vn_i = 0;

    for(int i=0; i<num_lines; i++) {
        char* word = strtok((char*)lines[i], " ");
        if(strcmp(word, "f") == 0) {
            word = strtok(NULL, " ");
            (*faces)[3*i] = faceIndices[word];
            
            word = strtok(NULL, " ");
            (*faces)[3*i+1] = faceIndices[word];

            word = strtok(NULL, " ");
            (*faces)[3*i+2] = faceIndices[word];
        } else if(strcmp(word, "v") == 0) {
            word = strtok(NULL, " ");
            v[v_i].x = atof(word);

            word = strtok(NULL, " ");
            v[v_i].y = atof(word);

            word = strtok(NULL, " ");
            v[v_i].z = atof(word);

            v_i++;
        } else if(strcmp(word, "vt") == 0) {
            word = strtok(NULL, " ");
            vt[vt_i].x = atof(word);

            word = strtok(NULL, " ");
            vt[vt_i].y = atof(word);

            vt_i++;
        } else if(strcmp(word, "vn") == 0) {
            word = strtok(NULL, " ");
            vn[vn_i].x = atof(word);

            word = strtok(NULL, " ");
            vn[vn_i].y = atof(word);

            word = strtok(NULL, " ");
            vn[vn_i].z = atof(word);

            vn_i++;
        } else {
            // ignore
        }
    }


    for(int i=0; i<num_vertices; i++) {
        int base = i*DATAPT_PER_VERTEX;
        (*vertices)[base] = v[posIndices[i]].x;
        (*vertices)[base+1] = v[posIndices[i]].y;
        (*vertices)[base+2] = v[posIndices[i]].z;

        (*vertices)[base+3] = vn[normalIndices[i]].x;
        (*vertices)[base+4] = vn[normalIndices[i]].y;
        (*vertices)[base+5] = vn[normalIndices[i]].z;

        (*vertices)[base+6] = vt[texcoordIndices[i]].x;
        (*vertices)[base+7] = vt[texcoordIndices[i]].y;
    }

    free(v);
    free(vt);
    free(vn);
}

int parse_file(const char* filename, GLfloat** vertices, GLuint** faces) {
    FILE* f = fopen(filename, "r");

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

    parse_string(lines, num_lines, vertices, faces);

    for(int i=0;i<num_lines;i++){
        free(lines[i]);
    }

    return 0;
}
