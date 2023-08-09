//Original Tutorial Followed: https://open.gl/context
//Code Copier/Writer: Nolan Murphy
//Version 0.1

#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    glewInit();

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    SDL_Event windowEvent;
    while (true)
    {
        float vertices[] = {
            0.0f, 0.0f,
            0.0f, 0.4f,
            0.3f, 0.0f
        };
        GLuint vertexBufObj;
        glGenBuffers(1, &vertexBufObj);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufObj);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //TODO: Import the shader by reading the .vert file
        const char* vertexSource = R"glsl(
            #version 150 core
            in vec2 position;
            void main() {
                gl_Position = vec4(position, 0.0, 1.0);
            }
        )glsl";

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, NULL);
        glCompileShader(vertexShader);
        GLint vertStatus;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertStatus);

        //TODO: Import the shader by reading the .frag file
        const char* fragmentSource = R"glsl(
            #version 150 core
            out vec4 outColor;
            void main() {
                outColor = vec4(1.0, 1.0, 1.0, 1.0);
            }
        )glsl";

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
        glCompileShader(fragmentShader);
        GLint fragStatus;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragStatus);

        printf("Vertex Status: %d\nFragment Status: %d", vertStatus, fragStatus);

        GLuint shaderPrgram = glCreateProgram();
        glAttachShader(shaderPrgram, vertexShader);
        glAttachShader(shaderPrgram, fragmentShader);
        
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) break;
            if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
        }
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}