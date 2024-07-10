#include <SDL2/SDL.h>
#include <glad/glad.h>

#include <emscripten.h>

// Standard C++ Lib
#include <iostream>
#include <vector>

// Globals
// 
int gScreenHeight = 480;
int gScreenWidth = 640;
SDL_Window*   gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;
bool gQuit = false; //If true we quit

//Vertex Array Object
GLuint gVertexArrayObject = 0;

//Vertex Buffer Object
GLuint gVertexBufferObject = 0;

// Program Object for out shaders
GLuint gGraphicsPipelineShaderProgram = 0;

const std::string gVertexShaderSource = 
    "#version 300 es\n"
    "in vec4 position;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(position.x, position.y, position.z, position.w);\n"
    "}\n";


const std::string gFragmentShaderSource = 
    "#version 300 es\n"
    "precision mediump float;\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "   color = vec4(1.0f, 0.5f, 1.0f, 0.5f);\n"
    "}\n";


GLuint CompileShader(GLuint type, const std::string source){

    GLuint shaderObject;

    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    } else if(type == GL_FRAGMENT_SHADER){
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    const char* src = source.c_str();

    glShaderSource(shaderObject, 1, &src, nullptr);
    glCompileShader(shaderObject);

    GLint status;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(shaderObject, 512, nullptr, buffer);
        std::cerr << "Shader compilation error: " << buffer << std::endl;
    }
    return shaderObject;
}

GLuint CreateShaderProgram(const std::string& vertexshadersource, 
                         const std::string& fragmentshadersource){
    GLuint programObject = glCreateProgram();

    GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER, vertexshadersource);
    GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentshadersource);

    glAttachShader(programObject,myVertexShader);
    glAttachShader(programObject,myFragmentShader);
    glLinkProgram(programObject);

    GLint status;
    glGetProgramiv(programObject, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetProgramInfoLog(programObject, 512, nullptr, buffer);
        std::cerr << "Program linking error: " << buffer << std::endl;
    }
    // Validate program
    glValidateProgram(programObject);
    glDeleteShader(myVertexShader);
    glDeleteShader(myFragmentShader);


    return programObject;

}

void CreateGraphicsPipeline(){
    gGraphicsPipelineShaderProgram = CreateShaderProgram(gVertexShaderSource,gFragmentShaderSource);
}

void GetOpenGLVersionInfo(){

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}


// 
void VertexSpecification(){

    const std::vector<GLfloat> vertexPosition{
        -0.8f, -0.8f, 0.0f, // vertex 1
         0.8f, -0.8f, 0.0f, // vertex 2
         0.0f,  0.8f, 0.0f, // vertex 3
        -0.8f, -0.5f, 1.0f, // vertex 1
         0.8f, -0.3f, 0.0f, // vertex 2
         0.0f,  0.2f, 0.0f, // vertex 3
    };

    // We start setting things up on the GPU
    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    // Start generting out VBO
    glGenBuffers(1, &gVertexBufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, 
                 vertexPosition.size()*sizeof(GLfloat),
                 vertexPosition.data(), 
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          (void*)0
                          );


    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
};


void InitializeProgram(){
    if(SDL_Init(SDL_INIT_VIDEO) <0){
        std::cout << "SDL2 could not initialize video subsystem\n";
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    gGraphicsApplicationWindow = SDL_CreateWindow("OpenGL Window",
                                    0, 0, gScreenWidth,
                                    gScreenHeight, SDL_WINDOW_OPENGL);

    if (gGraphicsApplicationWindow ==nullptr){
        std::cout << "SDL_Window was not able to be created\n";
        exit(1);
    }


    gOpenGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);

    if (gOpenGLContext==nullptr){
        std::cout << "SDL_Context not available\n";
        exit(1);
    }

    // initialize Glad Library
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        std::cout << "Glad is not initialized\n";
        exit(1);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    GetOpenGLVersionInfo();
};

void Input(){

    SDL_Event e;
    while(SDL_PollEvent(&e) !=0){
        if(e.type == SDL_QUIT){
            std::cout <<"Good bye\n";
            gQuit = true;
        }
    }
};

void PreDraw(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0,0,gScreenWidth,gScreenHeight);
    //Yellow background
    glClearColor(1.f,1.f,0.f,1.f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(gGraphicsPipelineShaderProgram);
}

void Draw(){
    glBindVertexArray(gVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 3, 3);
}
void MainLoop(void* mainLoopArg){

    glClear(GL_COLOR_BUFFER_BIT);

    // User input
    Input();

    //prior to drawiing
    PreDraw();

    //Draw stuff
    Draw();

    // Update the screen
    // Uses doublebuffer to animate per frame
    SDL_GL_SwapWindow(gGraphicsApplicationWindow);


};

void CleanUp(){
    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_Quit();
};


int main(){

    InitializeProgram();

    VertexSpecification();

    CreateGraphicsPipeline();


    void* mainLoopArg = nullptr;

    #ifdef __EMSCRIPTEN__
        int fps = 0; // Use browser's requestAnimationFrame
        emscripten_set_main_loop_arg(MainLoop, mainLoopArg,  fps, true);
    #else
        while(!gQuit) { MainLoop(mainLoopArg); }
    #endif

    CleanUp();

    return 0;
}