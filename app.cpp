#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "app.h"

#include "camera.h"

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

GLuint shaderProgram;

glm::mat4 model;
camera_t* cam;

int compile_shader(char* filename, GLenum type, GLuint* res) {
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

int app_start(){
    // init array objects
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // init buffers
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // init element buffer objects
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    cam = new_camera(
        glm::vec3(1.2f, 1.2f, 1.2f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f));

    // init shaders
    GLuint vShader, fShader;

    if(compile_shader("vertex.gl", GL_VERTEX_SHADER, &vShader)) {
        return 1;
    }

    if(compile_shader("fragment.gl", GL_FRAGMENT_SHADER, &fShader)) {
        return 1;
    }

    // link the shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);

    glBindFragDataLocation(shaderProgram, 0, "outColor");

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // init textures
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    int img_x, img_y, img_n;
    uint8_t* img_data = stbi_load("tex.png", &img_x, &img_y, &img_n, 3);

    if(!img_data) {
        printf("texture loading error\n");
        return 1;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_x, img_y, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    stbi_image_free(img_data);

    // rotate across Z axis
    model = glm::rotate(model, 
        glm::radians(120.0f), 
        glm::vec3(0.0f, 0.0f, 1.0f));

    // specify the shape of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 
        7*sizeof(float), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
        7*sizeof(float), (void*)(2*sizeof(float)));

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
        7*sizeof(float), (void*)(5*sizeof(float)));

    // load the matrices
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

    camera_bind_shader(cam, shaderProgram);

    return 0;
}

int app_clean(){
    return 0;
}

int update(SDL_Event evt, uint64_t ticks){
    // modify the trans matrix
    model = glm::rotate(glm::mat4(), 
        ticks / 60.0f * glm::radians(180.0f), 
        glm::vec3(0.0f, 0.0f, 1.0f));

    // reload the trans matrix
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

    return 0;
}

int draw(SDL_Window* win, SDL_GLContext* ctx){
    // clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our shape
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    return 0;
}
