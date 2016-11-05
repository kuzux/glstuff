#include <stdint.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SDL2/SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "object.h"

float vertices[] = {
    // posx posy color (r g b) texcoords (x y)
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
};

GLuint elements[] = {
    0,1,2,
    2,3,0
};

int compile_shader(const char* filename, GLenum type, GLuint* res) {
    static char* shader_buf;
    static char error_buf[512];

    FILE* f;
    int filelen;

    GLint status;

    f = fopen(filename, "r");
    fseek(f, 0, SEEK_END);
    filelen = ftell(f);
    fseek(f, 0, SEEK_SET);
    shader_buf = (char*)malloc(filelen+1);
    fread(shader_buf, 1, filelen, f);
    shader_buf[filelen] = 0;
    fclose(f);

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shader_buf, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE){
        glGetShaderInfoLog(shader, 512, NULL, error_buf);
        printf("Shader compile error\n%s\n", error_buf);
        return 1;
    }

    free(shader_buf);

    *res = shader;
    return 0;
}

object_t* new_object(){
    object_t* res = (object_t*)malloc(sizeof(object_t));

    if(!res){
        return NULL;
    }

    // init array objects
    glGenVertexArrays(1, &res->vao);
    glBindVertexArray(res->vao);

    // init buffers
    glGenBuffers(1, &res->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, res->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // init element buffer objects
    glGenBuffers(1, &res->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, res->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    return res;
}

int compile_shaders(object_t* obj) {
    if(compile_shader("vertex.gl", GL_VERTEX_SHADER, &obj->vShader)) {
        printf("vertex shader compile error\n");
        return 1;
    }

    if(compile_shader("fragment.gl", GL_FRAGMENT_SHADER, &obj->fShader)) {
        printf("fragment shader compile error\n");
        return 1;
    }

    return 0;
}

int link_shaders(object_t* obj) {
    obj->shader = glCreateProgram();
    glAttachShader(obj->shader, obj->vShader);
    glAttachShader(obj->shader, obj->fShader);

    glBindFragDataLocation(obj->shader, 0, "outColor");

    glLinkProgram(obj->shader);

    GLint status;
    glGetShaderiv(obj->shader, GL_LINK_STATUS, &status);
    if(status != GL_TRUE) {
        printf("shader link error\n");
        return 1;
    }

    glUseProgram(obj->shader);

    return 0;
}

int load_texture(object_t* obj) {
    glGenTextures(1, &obj->tex);
    glBindTexture(GL_TEXTURE_2D, obj->tex);

    int img_x, img_y, img_n;
    uint8_t* img_data = stbi_load("tex.png", &img_x, &img_y, &img_n, 3);

    if(!img_data) {
        printf("error loading data\n");
        return 1;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_x, img_y, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    stbi_image_free(img_data);

    return 0;
}

int bind_data_to_shaders(object_t* obj) {
    // specify the shape of the vertex data
    GLint posAttrib = glGetAttribLocation(obj->shader, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 
        7*sizeof(float), 0);

    GLint colAttrib = glGetAttribLocation(obj->shader, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
        7*sizeof(float), (void*)(2*sizeof(float)));

    GLint texAttrib = glGetAttribLocation(obj->shader, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
        7*sizeof(float), (void*)(5*sizeof(float)));

    // load the model matrix
    GLint uniModel = glGetUniformLocation(obj->shader, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(obj->model));

    return 0;
}

void object_update(object_t* obj, SDL_Event evt, uint64_t ticks) {
    // modify the model matrix
    obj->model = glm::rotate(glm::mat4(), 
        ticks / 60.0f * glm::radians(180.0f), 
        glm::vec3(0.0f, 0.0f, 1.0f));

    // reload the model matrix
    GLint uniModel = glGetUniformLocation(obj->shader, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(obj->model));
}

void bind_buffers(object_t* obj) {
    glBindVertexArray(obj->vao);

    glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->ebo);

    glUseProgram(obj->shader);

    glBindTexture(GL_TEXTURE_2D, obj->tex);
}

void object_draw(object_t* obj) {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void destroy_object(object_t* obj) {
    free(obj);
}
