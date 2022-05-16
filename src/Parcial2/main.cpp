//Luis Enrrique Salas Luna - Computacion Grafica

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h> 
#include <vector>
#define PI 3.14159265

using namespace std;
//Comandos
/*
 T = Triangulo
 S = Estrella
 P = Pizza

 M = Mover(1,1)
 E = Escala (1.1,1.1)
 R = Rotacion (30°)
 X = ShearX(15°)
 Y = ShearY(15°)
*/

//Formas
vector<float> Triangle(float R, float G, float B) {
    vector<float> t = {
        -0.1f, -0.1f, 0.0f, R, G, B, // left
         0.1f, -0.1f, 0.0f, R, G, B,// right
         0.0f,  0.1f, 0.0f, R, G, B, // top
    };
    return t;
}
vector<float> Star(float R, float G, float B) {
    vector<float> e = {
        //Triangulos
        0.00f,  0.50f, 0.0f, R, G, B,   // A  
        0.29f, -0.41f, 0.0f, R, G, B,   // E 
       -0.18f,  -0.06f, 0.0f, R, G, B,  // H 

        0.11f,  0.15f, 0.0f, R, G, B,  // B
        0.48f,  0.15f, 0.0f, R, G, B,  // C   
        0.18f, -0.06f, 0.0f, R, G, B,  // D

        0.0f,  -0.19f, 0.0f, R, G, B,  // F
       -0.3f,  -0.41f, 0.0f, R, G, B,  // G
       -0.18f, -0.06f, 0.0f, R, G, B,  // H

       -0.18f,  -0.06f, 0.0f, R, G, B,  // H
       -0.48f,  0.15f, 0.0f, R, G, B,   // I
       -0.11f,  0.15f, 0.0f, R, G, B,   // J
    };
    return e;
}
vector<float> Pizza(float R, float G, float B) {
    vector<float> p = {
        //Punto
        0.000f,  0.000f, 0.0f, R, G, B,
        0.000f,  0.500f, 0.0f, R, G, B,
        0.355f,  0.355f, 0.0f, R, G, B,
        0.500f,  0.000f, 0.0f, R, G, B,
        0.355f, -0.355f, 0.0f, R, G, B,
        0.000f, -0.500f, 0.0f, R, G, B,
       -0.355f, -0.355f, 0.0f, R, G, B,
       -0.500f,  0.000f, 0.0f, R, G, B,
       -0.355f,  0.355f, 0.0f, R, G, B,

       //Linea
        0.000f,  0.500f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        0.355f,  0.355f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        0.500f,  0.000f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        0.355f, -0.355f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        0.000f, -0.500f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        -0.355f, -0.355f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        -0.500f,  0.000f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        -0.355f,  0.355f, 0.0f, R, G, B,

        //Connect
        0.000f,  0.500f, 0.0f, R, G, B,
        0.355f,  0.355f, 0.0f, R, G, B,
        0.500f,  0.000f, 0.0f, R, G, B,
        0.355f, -0.355f, 0.0f, R, G, B,
        0.000f, -0.500f, 0.0f, R, G, B,
        -0.355f, -0.355f, 0.0f, R, G, B,
        -0.500f,  0.000f, 0.0f, R, G, B,
        -0.355f,  0.355f, 0.0f, R, G, B,

        //Triangulo
        0.000f,  0.500f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        0.355f,  0.355f, 0.0f, R, G, B,

        0.355f,  0.355f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        0.500f,  0.000f, 0.0f, R, G, B,

        0.500f,  0.000f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        0.355f, -0.355f, 0.0f, R, G, B,

        0.355f, -0.355f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        0.000f, -0.500f, 0.0f, R, G, B,

        0.000f, -0.500f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        -0.355f, -0.355f, 0.0f, R, G, B,

        -0.355f, -0.355f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        -0.500f,  0.000f, 0.0f, R, G, B,

        -0.500f,  0.000f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        -0.355f,  0.355f, 0.0f, R, G, B,

        -0.355f,  0.355f, 0.0f, R, G, B,
        0.000f,  0.000f, 0.0f, R, G, B,  //0.0
        0.000f,  0.500f, 0.0f, R, G, B
    };

    return p;
}
vector<float> Cuadrado(float R, float G, float B) {
    vector<float> r = {
         -0.5f, 0.5f, 0.0f, R, G, B, // left
         0.5f, 0.5f, 0.0f, R, G, B,// right
         0.5f, -0.5f, 0.0f, R, G, B, // top

        -0.5f, 0.5f, 0.0f, R, G, B, // left
         -0.5f, -0.5f, 0.0f, R, G, B,// right
         0.5f, -0.5f, 0.0f, R, G, B, // top
    };
    return r;
}
vector<float> Rombo(float R, float G, float B) {
    vector<float> r = {
         0.0f, 0.5f, 0.0f, R, G, B, // left
         0.5f, 0.0f, 0.0f, R, G, B,// right
         0.0f, -0.5f, 0.0f, R, G, B, // top

        0.0f, 0.5f, 0.0f, R, G, B, // left
        -0.5f, 0.0f, 0.0f, R, G, B,// right
        0.0f, -0.5f, 0.0f, R, G, B, // top
    };
    return r;
}

vector<float> Sharspinski(int gen) {
    float R, G, B;
    R = G = B = 0.8;  
    vector<float> compl = { 0.0f, 0.8f, 0.8f, 0.8f };
    vector<float> compl2 = { 0.0f, 0.2f, 0.2f, 0.2f };
    //Origen
    vector<vector<float>> comps = { compl, compl2}; // G = 1.0f, efecto degradado
    //Base
    vector<float> t = {
        -0.5f, -0.5f, 0.0f, R, G, B, // left
         0.5f, -0.5f, 0.0f, R, G, B,// right
         0.0f,  0.5f, 0.0f, R, G, B, // top
    };
    for (int i = 1; i < gen; i++) {    
        for (int j = 0; j < 2; j++) {
            //cout << t.size() << endl;
            float x = (t[t.size() - 18] + t[t.size() - 12]) / 2;
            t.push_back(x);
            //cout << t.size() << endl;
            float y = (t[t.size() - 18] + t[t.size() - 12]) / 2;
            t.push_back(y);
            vector<float>::iterator it = t.end();
            t.insert(it, comps[i%2].begin(), comps[i%2].end()); //z,r,g,b
            //cout << x << y << endl;
        }
        float x = (t[t.size() - 30] + t[t.size() - 18]) / 2;
        t.push_back(x);
        float y = (t[t.size() - 30] + t[t.size() - 18]) / 2;
        //cout << x << y << endl;
        t.push_back(y);
        vector<float>::iterator it = t.end();
        t.insert(it, comps[i % 2].begin(), comps[i % 2].end()); //z,r,g,b
    }
    return t;

}

//Matrices
vector<vector<float>> mover(float x, float y) {
    vector<vector<float>> aux = {
        {1,0,x},
        {0,1,y},
        {0,0,1},
    };
    return aux;
}
vector<vector<float>> escala(float x, float y) {
    vector<vector<float>> aux = {
        {x,0,0},
        {0,y,0},
        {0,0,1},
    };
    return aux;
}
float angR, angX, angY = 0.0f;
vector<vector<float>> rotacion(float a) {
    float ang = a * PI / 180; // modificar angulo(sexagesimales)
    vector<vector<float>> aux = {
        {cos(ang),sin(ang),0},
        {-sin(ang),cos(ang),0},
        {0,0,1},
    };
    return aux;
}
vector<vector<float>> shearX(int a) {
    float ang = a * PI / 180; // modificar angulo(sexagesimales)
    vector<vector<float>> aux = {
        {1,tan(ang),0},
        {0,1,0},
        {0,0,1},
    };
    return aux;
}
vector<vector<float>> shearY(int a) {
    float ang = a * PI / 180; // modificar angulo(sexagesimales)
    vector<vector<float>> aux = {
        {1,0,0},
        {tan(ang),1,0},
        {0,0,1},
    };
    return aux;
}

//Mat
void MultMat(vector<float>& vec, vector<vector<float>> matrix, int inicio, int fin) {
    vector<vector<float>> mat = matrix;
    for (int i = inicio; i < fin; i += 6) {
        vector<float> coord = { vec[i], vec[i + 1], 1 };
        for (int j = 0; j < mat.size() - 1; j++) { //Solo se consideran x e y [No tercera dimension]
            float aux = 0;
            for (int k = 0; k < mat.size(); k++) {
                aux += mat[j][k] * coord[k];
            }
            vec[i + j] = aux;
        }
    }
};
//Mat
int phase = 0;


vector<float> DrawCircle(float radius, float R, float G, float B);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";

//Color
float greenValue = 0;
float redValue = 0;
float blueValue = 0;
//Modo
int modo = 2;
//Forma
int forma = 0;

unsigned int VBO, VAO;
vector<float> t = Triangle(0.9f, 0.1f, 0.1f);
vector<float> e = Star(0.1f, 0.1f, 0.9f); // adaptado luego
vector<float> r = Rombo(0.1f, 0.9f, 0.1f); // adaptado luego
vector<float> c = Cuadrado(0.9f, 0.2f, 0.7f); // adaptado luego
vector<float> Formas = t;
//quadaux
vector<float> c_aux = Cuadrado(0.9f, 0.2f, 0.7f); // adaptado luego
vector<float> c_aux2; // adaptado luego
//staraux
vector<float> e_aux = Star(0.1f, 0.1f, 0.9f); // adaptado luego
vector<float> e_aux2; // adaptado luego
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
 //ModificarFormaBase----------------------------------------------------------------------------------------
    //Cuadrado
    cout << Formas.size() <<endl;
    vector<vector<float>> mat = escala(0.2f, 0.2f);
    MultMat(c, mat, 0, c.size());
    mat = mover(0.25f, 0.0f);
    MultMat(c, mat, 0, c.size());
    vector<float>::iterator it = Formas.end();
    Formas.insert(it, c.begin(), c.end()); //z,r,g,b
    cout << Formas.size() << endl;
    //Cuadrado
    mat = escala(0.2f, 0.2f);
    MultMat(r, mat, 0, r.size());
    mat = mover(0.5f, 0.0f);
    MultMat(r, mat, 0, r.size());
    it = Formas.end();
    Formas.insert(it, r.begin(), r.end()); //z,r,g,b
    cout << Formas.size() << endl;
    //star
    mat = escala(0.2f, 0.2f);
    MultMat(e, mat, 0, e.size());
    mat = mover(0.75f, 0.0f);
    MultMat(e, mat, 0, e.size());
    it = Formas.end();
    Formas.insert(it, e.begin(), e.end()); //z,r,g,b
    cout << Formas.size() << endl;

    //star aux
    mat = escala(0.2f, 0.2f);
    MultMat(e_aux, mat, 0, e_aux.size());
    e_aux2 = e_aux;

    //quad aux
    MultMat(c_aux, mat, 0, c_aux.size());
    c_aux2 = c_aux;



    //unsigned int VBO, VAO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        Formas.size() * sizeof(float),
        &Formas[0],
        GL_STATIC_DRAW
    );

    //pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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


        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

        //now render triangle
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized


        glDrawArrays(GL_TRIANGLES, 0, Formas.size());// Con triangulos
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
int actionR = 0;
//starAux


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) // Compliment
    {
        vector<vector<float>> temp = rotacion(22.5);
        //Triangle
        vector<vector<float>> T1 = escala(1.1, 1.1);
        vector<vector<float>> T2 = escala(0.9, 0.9);
        vector<vector<vector<float>>> Ts = { T1,T2 };
        if (phase == 2) { phase = 0; }
        MultMat(Formas, Ts[phase], 0, 18);
        phase += 1;

        //Cuadrado
        vector<vector<float>> C = rotacion(-22.5);
        MultMat(Formas, C, 18, 54);
        //quadAux
        MultMat(c_aux, temp, 0, c_aux.size());
        for (int i = 18; i < 54; i += 6) {
            float x = c_aux[i - 18] - c_aux2[i - 18];
            float y = c_aux[i - 18 + 1] - c_aux2[i - 18 + 1];
            Formas[i] += x;
            Formas[i + 1] += y;
        }
        c_aux2 = c_aux;

        //Rombo
        vector<vector<float>> R1 = mover(0.0, 0.25);
        vector<vector<float>> R2 = mover(-0.25, 0.0);
        vector<vector<float>> R3 = mover(0.0, -0.25);
        vector<vector<float>> R4 = mover(0.25, 0.0);
        vector<vector<vector<float>>> Rs = { R1,R1,R2,R2,R2,R2,R3,R3,R3,R3,R4,R4,R4,R4,R1,R1 };
        if (actionR == 16) { actionR = 0; }
        MultMat(Formas, Rs[actionR], 54, 90);
        
        //Star
        vector<vector<float>> E = rotacion(360 - 45);
        vector<vector<float>> E1 = mover(0.0, 0.375);
        vector<vector<float>> E2 = mover(-0.375, 0.0);
        vector<vector<float>> E3 = mover(0.0, -0.375);
        vector<vector<float>> E4 = mover(0.375, 0.0);
        vector<vector<vector<float>>> Es = { E1,E1,E2,E2,E2,E2,E3,E3,E3,E3,E4,E4,E4,E4,E1,E1 };
        //if (actionR == 16) { actionR = 0; }
          
        //starAux
        MultMat(e_aux, C, 0, e_aux.size());
        for (int i = 90; i < 162; i+=6) {
            float x = e_aux[i-90] - e_aux2[i-90];
            float y = e_aux[i - 90+1] - e_aux2[i - 90+1];
            Formas[i] += x;
            Formas[i+1] += y;
        }
        e_aux2 = e_aux;

        MultMat(Formas, Es[actionR], 90, 162);
        actionR += 1;

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(
            GL_ARRAY_BUFFER,
            Formas.size() * sizeof(float),
            &Formas[0],
            GL_STATIC_DRAW
        );
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        float timeValue = glfwGetTime();
        if (redValue == 0)
        {
            redValue = 1;
        }
        else
        {
            redValue = 0;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        float timeValue = glfwGetTime();
        if (greenValue == 0)
        {
            greenValue = 1;
        }
        else
        {
            greenValue = 0;
        }

    }

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        float timeValue = glfwGetTime();
        if (blueValue == 0)
        {
            blueValue = 1;
        }
        else
        {
            blueValue = 0;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


vector<float> DrawCircle(float radius, float R, float G, float B) {
    vector<float> Circle;
    float ang = 1 * PI / 180;
    float radio = radius;

    //Origen
    vector<float> compl = { 0.0f, R, G, B }; // G = 1.0f, efecto degradado
    //Origen
    vector<float> orig = { 0.0f, 0.0f, 0.0f, R, G, B }; // G = 1.0f, efecto degradado
    //Base
    Circle.push_back(radio); //x
    Circle.push_back(radio); //y
    vector<float>::iterator it = Circle.end();
    Circle.insert(it, compl.begin(), compl.end()); //z,r,g,b
    it = Circle.end();
    Circle.insert(it, orig.begin(), orig.end()); // origen
    Circle.push_back(cos(ang) * Circle[0] + sin(ang) * Circle[1]); //x
    Circle.push_back(-sin(ang) * Circle[0] + cos(ang) * Circle[1]); //y
    it = Circle.end();
    Circle.insert(it, compl.begin(), compl.end()); //z,r,g,b

    for (int i = 1; i <= 360; i++) {
        Circle.push_back(cos(ang) * Circle[Circle.size() - 9] + sin(ang) * Circle[Circle.size() - 9 + 1]);
        Circle.push_back(-sin(ang) * Circle[Circle.size() - 9 - 1] + cos(ang) * Circle[Circle.size() - 9]);
        it = Circle.end();
        Circle.insert(it, compl.begin(), compl.end()); //z,r,g,b
        it = Circle.end();
        Circle.insert(it, orig.begin(), orig.end());
        Circle.push_back(cos(ang) * Circle[Circle.size() - 9] + sin(ang) * Circle[Circle.size() - 9 + 1]);
        Circle.push_back(-sin(ang) * Circle[Circle.size() - 9 - 1] + cos(ang) * Circle[Circle.size() - 9]);
        it = Circle.end();
        Circle.insert(it, compl.begin(), compl.end()); //z,r,g,b
    }
    return Circle;

}