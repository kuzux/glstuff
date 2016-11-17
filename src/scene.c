#include <jansson.h>
#include <scene.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <objparse.h>

#define JSON_PARSE_ERROR {printf("JSON parsing error\n");json_decref(root);return 1;}

scene_t* make_scene(const char* filename) {
    scene_t* res = (scene_t*)malloc(sizeof(scene_t));

    res->filename = filename;

    return res;
}

int parse_scene_file(scene_t* scn) {
    FILE* f = fopen(scn->filename, "r");

    if(!f) {
        printf("Error opening scn file. errno %d\n", errno);
        return 1;
    }

    json_t* root;
    json_t* child;

    json_error_t error;

    root = json_loadf(f, 0, &error);

    if(!root) JSON_PARSE_ERROR

    if(!json_is_object(root)) JSON_PARSE_ERROR

    child = json_object_get(root, "name");
    if(!json_is_string(child)) JSON_PARSE_ERROR
    scn->name = (char*)malloc(strlen(json_string_value(child))+1);
    strcpy(scn->name, json_string_value(child));

    child = json_object_get(root, "version");
    if(!json_is_string(child)) JSON_PARSE_ERROR
    scn->version = (char*)malloc(strlen(json_string_value(child))+1);
    strcpy(scn->name, json_string_value(child));

    child = json_object_get(root, "objects");
    if(!json_is_array(child)) JSON_PARSE_ERROR
    scn->num_objects = json_array_size(child);
    scn->objects = (obj_file_t**)malloc(scn->num_objects*sizeof(obj_file_t*));

    for(int i=0;i<scn->num_objects;i++){
        json_t* elem = json_array_get(child,i);
        json_t* obj_child;

        if(!json_is_object(elem)) JSON_PARSE_ERROR
        obj_child = json_object_get(elem, "objfile");
        char* filename = malloc(strlen(json_string_value(obj_child))+1);
        strcpy(filename, json_string_value(obj_child));
        scn->objects[i] = make_obj_file(filename);

        obj_child = json_object_get(elem, "vertexShader");
        scn->objects[i]->vertex_shader = malloc(strlen(json_string_value(obj_child))+1);
        strcpy(scn->objects[i]->vertex_shader, json_string_value(obj_child));

        obj_child = json_object_get(elem, "fragmentShader");
        scn->objects[i]->fragment_shader = malloc(strlen(json_string_value(obj_child))+1);
        strcpy(scn->objects[i]->fragment_shader, json_string_value(obj_child));

        if(parse_obj_file(scn->objects[i])) {
            return 1;
        }
    }

    fclose(f);

    return 0;
}

void delete_scene(scene_t* scn) {
    for(int i=0;i<scn->num_objects;i++){
        delete_obj_file(scn->objects[i]);
    }

    free(scn);
}
