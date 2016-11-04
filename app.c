#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "app.h"

float vertices[] = {
    0.0f,  0.5f, // Vertex 1 (X, Y)
    0.5f, -0.5f, // Vertex 2 (X, Y)
    -0.5f, -0.5f // Vertex 3 (X, Y)
};

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
    shader_buf = malloc(filelen+1);
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

    //free(shader_buf);

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

    // init shaders
    GLuint vShader, fShader;

    if(compile_shader("vertex.gl", GL_VERTEX_SHADER, &vShader)) {
        return 1;
    }

    if(compile_shader("fragment.gl", GL_FRAGMENT_SHADER, &fShader)) {
        return 1;
    }

    // link the shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);

    glBindFragDataLocation(shaderProgram, 0, "outColor");

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // specify the shape of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    return 0;
}

int app_clean(){
    return 0;
}

int update(SDL_Event evt, uint64_t ticks){
    return 0;
}

int draw(SDL_Window* win, SDL_GLContext* ctx){
    // clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);

    return 0;
}
