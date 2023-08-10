// Original Tutorial Followed: https://open.gl/context
// Code Copier/Writer: Nolan Murphy
// Version 0.2.1

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <chrono>

// TODO: Import the shader by reading the .vert file
const char *vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    in vec3 color;
    out vec3 Color;
    void main() {
        Color = color;
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";

// TODO: Import the shader by reading the .frag file
const char *fragmentSource = R"glsl(
    #version 150 core
    in vec3 Color;
    out vec4 outColor;
    void main() {
        outColor = vec4(Color, 1.0);
    }
)glsl";

int main(int argc, char *argv[])
{
    auto t_start = std::chrono::high_resolution_clock::now();

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_Window *window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    glewInit();

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    SDL_Event windowEvent;

    float vertices[] = {
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.4f, 0.0f, 1.0f, 0.0f,
        0.3f, 0.0f, 1.0f, 0.0f, 0.0f
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vertexBufObj;
    glGenBuffers(1, &vertexBufObj);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Optional data to ensure the vertex shader compiled correctly.
    GLint vertStatus;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertStatus);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Optional data to ensure the shaders compiled correctly.
    GLint fragStatus;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragStatus);
    // 1 - Success; 0 - Compiler Error;
    printf("Vertex Status: %d\nFragment Status: %d\n", vertStatus, fragStatus);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Not necessary at the moment but useful when there are multiple outputs to manage to multiple framebuffers.
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    glLinkProgram(shaderProgram);
    // Only 1 program can be active at a time.
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    // GL_FALSE since the position values don't need to be normalized.
    // Fifth arg indicates the number of bytes until the next vertex position data.
    // The second zero (last arg) is because there is zero bytes of offset to find the first position.
    /// 'Position" is the first attribute given to a vertex in this example.
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, (5*sizeof(GLfloat)), 0);
    glEnableVertexAttribArray(posAttrib);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, (5*sizeof(GLfloat)), (void*)(2 * sizeof(GLfloat)));

    // vertices is an array of floats, but has 2 values per vertex.
    int numberOfVertices = (sizeof(vertices) / sizeof(float)) / 2;

    bool drawing = true;

    while (drawing)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
                drawing = false;
            if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE)
                drawing = false;
        }

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 0 - Number of vertices to skip.
        glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
        SDL_GL_SwapWindow(window);
    }

    //Clean Up
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vertexBufObj);
    glDeleteVertexArrays(1, &vao);

    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}