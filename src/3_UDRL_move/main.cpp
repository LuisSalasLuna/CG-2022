//Luis Enrrique Salas Luna - Computacion Grafica

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h> 
#define PI 3.14159265
#include <vector>

using namespace std;

void Mover(vector<int> vec);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 700;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

//Color
float greenValue = 0;
float redValue = 0;
float blueValue = 0;
//Modo
int modo = 0;
//Forma
int forma = 0;
//Size
int tam = 0;
//Arr
float* arr;
//Random
bool aleatorio = false;

unsigned int VBO, VAO;
float t[] = {
    -0.5f, -0.5f, 0.0f, // left
     0.5f, -0.5f, 0.0f, // right
     0.0f,  0.5f, 0.0f,  // top
    -0.5f, -0.5f, 0.0f // left
};

float e[] = {
    0.00f,  0.50f, 0.0f, // top  
    0.11f,  0.15f, 0.0f, // | 
    0.48f,  0.15f, 0.0f,  // right_top   
    0.18f, -0.06f, 0.0f, // | 
    0.29f, -0.41f, 0.0f,  // right_bottom 
    0.0f,  -0.19f, 0.0f,  // - 
   -0.3f,  -0.41f, 0.0f,  // left_bottom 
   -0.18f, -0.06f, 0.0f,  // | 
   -0.48f,  0.15f, 0.0f,  // left_top 
   -0.11f,  0.15f, 0.0f, // | 
    0.00f,  0.50f, 0.0f, // bucle para lineas 

    //Triangulos
    0.00f,  0.50f, 0.0f,   // A  
    0.29f, -0.41f, 0.0f,   // E 
   -0.18f,  -0.06f, 0.0f,  // H 

    0.11f,  0.15f, 0.0f,  // B
    0.48f,  0.15f, 0.0f,  // C   
    0.18f, -0.06f, 0.0f,  // D

    0.0f,  -0.19f, 0.0f,  // F
   -0.3f,  -0.41f, 0.0f,  // G
   -0.18f, -0.06f, 0.0f,  // H

   -0.18f,  -0.06f, 0.0f,  // H
   -0.48f,  0.15f, 0.0f,   // I
   -0.11f,  0.15f, 0.0f   // J
};

float p[] = {
    //Punto
    0.000f,  0.000f, 0.0f,
    0.000f,  0.500f, 0.0f,
    0.355f,  0.355f, 0.0f,
    0.500f,  0.000f, 0.0f,
    0.355f, -0.355f, 0.0f,
    0.000f, -0.500f, 0.0f,
   -0.355f, -0.355f, 0.0f,
   -0.500f,  0.000f, 0.0f,
   -0.355f,  0.355f, 0.0f,

   //Linea
    0.000f,  0.500f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    0.355f,  0.355f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    0.500f,  0.000f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    0.355f, -0.355f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    0.000f, -0.500f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    -0.355f, -0.355f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    -0.500f,  0.000f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    -0.355f,  0.355f, 0.0f,

    //Connect
    0.000f,  0.500f, 0.0f,
    0.355f,  0.355f, 0.0f,
    0.500f,  0.000f, 0.0f,
    0.355f, -0.355f, 0.0f,
    0.000f, -0.500f, 0.0f,
    -0.355f, -0.355f, 0.0f,
    -0.500f,  0.000f, 0.0f,
    -0.355f,  0.355f, 0.0f,

    //Triangulo
    0.000f,  0.500f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    0.355f,  0.355f, 0.0f,

    0.355f,  0.355f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    0.500f,  0.000f, 0.0f,

    0.500f,  0.000f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    0.355f, -0.355f, 0.0f,

    0.355f, -0.355f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    0.000f, -0.500f, 0.0f,

    0.000f, -0.500f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    -0.355f, -0.355f, 0.0f,

    -0.355f, -0.355f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    -0.500f,  0.000f, 0.0f,

    -0.500f,  0.000f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    -0.355f,  0.355f, 0.0f,

    -0.355f,  0.355f, 0.0f,
    0.000f,  0.000f, 0.0f, //0.0
    0.000f,  0.500f, 0.0f
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    //unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(t), t, GL_STATIC_DRAW);
    tam = sizeof(t);
    arr = t;
    //cout << arr[0] << " " << arr[1] << " " << arr[2] << " test ";

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    glPointSize(4);
    glLineWidth(4);
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        // draw our first triangle
        glUseProgram(shaderProgram);
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        float timeValue = glfwGetTime();
        if (greenValue != 0) greenValue = sin(timeValue) / 2.0f + 0.5f;       //Red
        if (redValue != 0) redValue = sin(timeValue) / 2.0f + 0.5f;  //Yellow
        if (blueValue != 0) blueValue = sin(timeValue) / 2.0f + 0.5f;     //Green

        vector<vector<int>>Dir = { {1,0,0},{-1,0,0},{0,1,0},{0,-1,0} };
        if(aleatorio) Mover(Dir[int(timeValue) % 4]);



        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);   
        
        //now render triangle
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        //Triangulos -------------------------------------------------------------
        if (forma == 0) {
            if (modo == 0) glDrawArrays(GL_POINTS, 0, 3);// Con triangulos
            if (modo == 1) glDrawArrays(GL_LINE_STRIP, 0, 4);// Con triangulos
            if (modo == 2) glDrawArrays(GL_TRIANGLES, 0, 3);// Con triangulos
        }

        //Estrella -------------------------------------------------------------
        if (forma == 1) {
            if (modo == 0) glDrawArrays(GL_POINTS, 0, 10);// Con triangulos
            if (modo == 1) glDrawArrays(GL_LINE_STRIP, 0, 11);// Con triangulos
            if (modo == 2) glDrawArrays(GL_TRIANGLES, 11, 12);// Con triangulos
        }

        //Pizza -------------------------------------------------------------
        if (forma == 2) {
            if (modo == 0) glDrawArrays(GL_POINTS, 0, 9);// Con triangulos
            if (modo == 1) glDrawArrays(GL_LINE_STRIP, 9, 24);// Con triangulos
            if (modo == 2) glDrawArrays(GL_TRIANGLES, 32, 24);// Con triangulos
        }

        //glDrawArrays(GL_TRIANGLES, 0, 3);// Con triangulos
        //glDrawArrays(GL_TRIANGLES, 0, 3);// Con triangulos

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
       glBindBuffer(GL_ARRAY_BUFFER, VBO);
       glBufferData(GL_ARRAY_BUFFER, sizeof(t), t, GL_STATIC_DRAW);
       forma = 0;
       tam = sizeof(t);
       arr = t;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(e), e, GL_STATIC_DRAW);
        forma = 1;
        tam = sizeof(e);
        arr = e;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(p), p, GL_STATIC_DRAW);
        forma = 2;
        tam = sizeof(p);
        arr = p;
    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        if (modo != 2) modo++;
        else modo = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        float timeValue = glfwGetTime();
        if (redValue == 0){
            redValue = 1;
        }
        else{
            redValue = 0;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        float timeValue = glfwGetTime();
        if (greenValue == 0){
            greenValue = 1;
        }
        else{
            greenValue = 0;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        float timeValue = glfwGetTime();
        if (blueValue == 0){
            blueValue = 1;
        }
        else{
            blueValue = 0;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        vector<int> aux = { 0,1,0 };
        Mover(aux);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        vector<int> aux = { 0,-1,0 };
        Mover(aux);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        vector<int> aux = { 1,0,0 };
        Mover(aux);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        vector<int> aux = { -1,0,0 };
        Mover(aux);
    }
    //Aleatorio Switch
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (aleatorio == false) {
            aleatorio = true;
        }
        else {
            aleatorio = false;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Mover(vector<int> vec) {
    int count = 0;
    float k = 0.1;
    cout << "Move: "<<vec[0] << " " << vec[1] << " " << vec[2]<<"\n";
    for (int i = 0; i < tam/4; i++) {
        cout << arr[count] << " " << arr[count+1] << " " << arr[count+2] << "\t->\t";
        arr[count] += k*vec[0];
        arr[count+1] += k*vec[1];
        arr[count+2] += k*vec[2];
        cout << arr[count] << " " << arr[count + 1] << " " << arr[count + 2] << "\n ";
        count += 3;
    }
    cout << "\n";
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, tam, arr, GL_STATIC_DRAW);

}