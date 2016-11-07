#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

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
#include <stb_image.h>

#include <object.h>

int compile_shader(const char* filename, GLenum type, GLuint* res) {
    static char* shader_buf;
    static char error_buf[512];

    FILE* f;
    int filelen;

    GLint status;

    f = fopen(filename, "r");

    if(!f){
        printf("Error opening shader file. errno %d\n", errno);
        return 1;
    }

    fseek(f, 0, SEEK_END);
    filelen = ftell(f);
    fseek(f, 0, SEEK_SET);
    shader_buf = (char*)malloc(filelen+1);
    
    if(!shader_buf) {
        return 1;
    }

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

int init_buffers(object_t* obj) {
    // init array objects
    glGenVertexArrays(1, &obj->vao);
    glBindVertexArray(obj->vao);

    // init buffers
    glGenBuffers(1, &obj->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
    glBufferData(GL_ARRAY_BUFFER, obj->num_vertices*sizeof(GLfloat), obj->vertices, GL_STATIC_DRAW);

    // init element buffer objects
    glGenBuffers(1, &obj->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj->num_faces*sizeof(GLuint), obj->faces, GL_STATIC_DRAW);

    return 0;
}

object_t* make_object(){
    object_t* res = (object_t*)malloc(sizeof(object_t));

    if(!res){
        return NULL;
    }

    return res;
}

int init_from_obj_file(object_t* obj, obj_file_t* objfile) {
    if(!obj) {
        return 1;
    }

    if(!objfile) {
        return 1;
    }

    if(objfile->num_vertices > MAX_VERTICES) {
        printf("Too many vertices\n");
        return 1;
    }

    if(objfile->num_vertices > MAX_VERTICES) {
        printf("Too many faces\n");
        return 1;
    }

    obj->vertices = objfile->vertices;
    obj->num_vertices = objfile->num_vertices * DATAPT_PER_VERTEX;

    obj->faces = objfile->faces;
    obj->num_faces = objfile->num_faces;

    if(init_buffers(obj)) {
        return 1;
    }

    if(compile_shaders(obj)) {
        return 1;
    }
    
    if(link_shaders(obj)) {
        return 1;
    }

    if(objfile->texture_file) {
        if(load_texture(obj, objfile->texture_file)) { 
            return 1;
        }
    }

    if(bind_data_to_shaders(obj)) {
        return 1;
    }

    return 0;
}

int compile_shaders(object_t* obj) {
    if(compile_shader("resource/vertex.gl", GL_VERTEX_SHADER, &obj->vShader)) {
        printf("vertex shader compile error\n");
        return 1;
    }

    if(compile_shader("resource/fragment.gl", GL_FRAGMENT_SHADER, &obj->fShader)) {
        printf("fragment shader compile error\n");
        return 1;
    }

    return 0;
}

int link_shaders(object_t* obj) {
    char error_buf[512];

    obj->shader = glCreateProgram();
    glAttachShader(obj->shader, obj->vShader);
    glAttachShader(obj->shader, obj->fShader);

    glBindFragDataLocation(obj->shader, 0, "outColor");

    glLinkProgram(obj->shader);

    GLint status;
    glGetShaderiv(obj->shader, GL_LINK_STATUS, &status);
    if(status != GL_TRUE) {
        glGetShaderInfoLog(obj->shader, 512, NULL, error_buf);

        printf("shader link error%s\n", error_buf);
        return 1;
    }

    glUseProgram(obj->shader);

    return 0;
}

int load_texture(object_t* obj, const char* filename) {
    glGenTextures(1, &obj->tex);
    glBindTexture(GL_TEXTURE_2D, obj->tex);

    int img_x, img_y, img_n;
    uint8_t* img_data = stbi_load(filename, &img_x, &img_y, &img_n, 3);

    if(!img_data) {
        printf("error loading texture data\n");
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
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 
        8*sizeof(float), 0);

    GLint normalAttrib = glGetAttribLocation(obj->shader, "normal");    
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE,
        8*sizeof(float), (void*)(3*sizeof(float)));

    GLint texAttrib = glGetAttribLocation(obj->shader, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
        8*sizeof(float), (void*)(6*sizeof(float)));

    // load the model transformation matrix
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
    glDrawElements(GL_TRIANGLES, obj->num_faces, GL_UNSIGNED_INT, 0);
}

void delete_object(object_t* obj) {
    free(obj);
}
