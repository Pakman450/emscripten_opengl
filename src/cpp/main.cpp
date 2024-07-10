#include <SDL2/SDL.h>
#include <emscripten.h>
#include <GLES3/gl3.h>

// Standard C++ Lib
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//////////
// Globals
int gScreenHeight = 480;
int gScreenWidth = 640;
SDL_Window*   gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;
bool gQuit = false; //If true we quit

//Vertex Array Object
GLuint gVertexArrayObject = 0;

//Vertex Buffer Object
GLuint gVertexBufferObject = 0;

//Index Buffer Object
//Stores an array of indices to draw from 
// when we doing indexed drawing
GLuint gIndexBufferObject = 0; 

// Program Object for out shaders
GLuint gGraphicsPipelineShaderProgram = 0;

// Globals end
///////////

std::string LoadShaderAsString( const std::string& filename){

    // REsulting shader program loaded as a single string
    std::string result = "";

    std::string line = ""; 
    std::ifstream myFile(filename.c_str());

    if (myFile.is_open()){
        while(std::getline(myFile, line)){
            result += line + '\n';
        }
        myFile.close();
    }else{
        std::cout << "Can't open a shader file: " << filename << std::endl;
        exit(1);
    }
    return result;
}


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
    std::string vertexShaderSource = LoadShaderAsString("shaders/vertex.glsl");
    std::string fragmentShaderSource = LoadShaderAsString("shaders/fragment.glsl");
    gGraphicsPipelineShaderProgram = CreateShaderProgram(vertexShaderSource,fragmentShaderSource);
}

void GetOpenGLVersionInfo(){
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

// 
void VertexSpecification(){

    const std::vector<GLfloat> vertexData{
        //0 - Verteix
        -0.5f, -0.5f, 0.0f, // vertex 1 Left
        1.0f, 0.0f, 0.0f, // color 1

        // 1 - vertex
         0.5f, -0.5f, 0.0f, // vertex 2 Right
         0.0f, 1.0f, 0.0f, // color 2
        // 2 - vertex
         -0.5f,  0.5f, 0.0f, // vertex 3 TOp
         0.0f, 0.0f, 1.0f,  // color 3

        // 3 - vertex
         0.5f,  0.5f, 0.0f, // vertex 3 right
         0.0f, 0.0f, 1.0f  // color 3
    };

    // We start setting things up on the GPU
    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    // Start generting out VBO
    glGenBuffers(1, &gVertexBufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, 
                 vertexData.size()*sizeof(GLfloat),
                 vertexData.data(), 
                 GL_STATIC_DRAW);


    const std::vector<GLuint> indexBufferData {2,0,1, 3,2,1};
    // Setup the index Buffer object (IBO ie EBO)
    glGenBuffers(1, &gIndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferObject);

    //populate our index buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indexBufferData.size()*sizeof(GLuint),
                 indexBufferData.data(),
                 GL_STATIC_DRAW
                );

    // No linking up the attrivutes in our VAO
    // positions
    glEnableVertexAttribArray(0); // The index for the Attribution array
    glVertexAttribPointer(0, // Which should match this too...
                          3, // x y z How many elements are there in this section?
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GL_FLOAT)*6, // How far are we going with our in our VAO in Bytes
                          (void*)0 // starting at index 0
                          );

    // Color information
    glEnableVertexAttribArray(1);  // The index for the Attribution array
    glVertexAttribPointer(1, // Which should match this too...
                          3, // r g b. How many elements are there in this section?
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GL_FLOAT)*6, // How far are we going with our in our VAO in Bytes
                          (GLvoid*)(sizeof(GL_FLOAT)*3) // Where are we starting at? in Bytes
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

    // // Draw first triangle
    // glDrawArrays(GL_TRIANGLES, 
    //              0, // start at index 3 of our VBO
    //              6  // we are rendering up to 6 elements
    //              );

    // // Draw second triangle
    // glDrawArrays(GL_TRIANGLES, 
    //             3, //start at index 3 or the second triangle
    //             3); // and we are rendering up to 3 elements becuase it is a triangle

    
    // Draw a quad based on index-based array drawing
    glDrawElements(GL_TRIANGLES, 
                 6, // number of elements in your index buffer object
                 GL_UNSIGNED_INT, // type of data
                 0 // no offset
                 );

    
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