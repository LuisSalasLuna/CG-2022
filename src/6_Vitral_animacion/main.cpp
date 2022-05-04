//Luis Enrrique Salas Luna - Computacion Grafica

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Windows.h>
#include <iostream>
#include <vector>
using namespace std;

#define PI 3.14159265

//Funciones auxiliares
vector<float> DrawLeaf(float a, float b, float G, float B);
vector<float> EspejoX(vector<float> vec);
vector<float> EspejoY(vector<float> vec);
vector<float> Rotar(vector<float> vec);
vector<float> Mover(vector<float> vec, float x, float y);

//PARTES
//Hojas
vector<float> Hoja();
vector<float> Leaves();
//Flor
vector<float> Base();

//ANIMACION
//aux
vector<vector<float>> rotacion(int a) {
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
//Cruzar-Hojas
void Cruce(vector<float> &vec, int inicio, int fin, int a); // inicio = 144, fin = 18144 /3000 pts
void CruceM2(vector<float>& vec, int inicio, int fin, int a); // inicio = 144, fin = 18144 /3000 pts
//Girar-flor
void Giro(vector<float> &vec, int inicio, int fin, int a); //inicio = 18144, fin =21348 /1068 pts
void GiroM2(vector<float>& vec, int inicio, int fin, int a); //inicio = 18144, fin =21348 /1068 pts

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

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

//Buffers
unsigned int VBO, VAO;
vector<float> vertices;
int anima1, anima2 = 0;
int main()
{
    // glfw: initialize and configure
    // ------------------------------
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

    vertices = {
        //position(x,y,z)      //color(R,G,B) 
     //Marco negro exterior
       -0.73f,  0.81f, 0.0f,   0.0f,  0.0f, 0.0f,
       -0.73f, -0.81f, 0.0f,   0.0f,  0.0f, 0.0f,
        0.73f, -0.81f, 0.0f,   0.0f,  0.0f, 0.0f,

       -0.73f,  0.81f, 0.0f,   0.0f,  0.0f, 0.0f,
        0.73f,  0.81f, 0.0f,   0.0f,  0.0f, 0.0f,
        0.73f, -0.81f, 0.0f,   0.0f,  0.0f, 0.0f,

     //Fondo azul
       -0.71f,  0.79f, 0.0f,   0.0f,  0.0f, 1.0f,
       -0.71f, -0.79f, 0.0f,   0.0f,  0.0f, 1.0f,
        0.71f, -0.79f, 0.0f,   0.0f,  0.0f, 1.0f,

       -0.71f,  0.79f, 0.0f,   0.0f,  0.0f, 1.0f,
        0.71f,  0.79f, 0.0f,   0.0f,  0.0f, 1.0f,
        0.71f, -0.79f, 0.0f,   0.0f,  0.0f, 1.0f,

 //Tallo
     //Contorno
       -0.03f, -0.07f, 0.0f,   0.0f,  0.0f, 0.0f,
       -0.03f, -0.79f, 0.0f,   0.0f,  0.0f, 0.0f,
        0.03f, -0.79f, 0.0f,   0.0f,  0.0f, 0.0f,

       -0.03f, -0.07f, 0.0f,   0.0f,  0.0f, 0.0f,
        0.03f, -0.07f, 0.0f,   0.0f,  0.0f, 0.0f,
        0.03f, -0.79f, 0.0f,   0.0f,  0.0f, 0.0f,

     //Cuerpo
       -0.02f, -0.08f, 0.0f,   0.2f,  0.2f, 0.0f,
       -0.02f, -0.79f, 0.0f,   0.2f,  0.2f, 0.0f,
        0.02f, -0.79f, 0.0f,   0.2f,  0.2f, 0.0f,

       -0.02f, -0.08f, 0.0f,   0.2f,  0.2f, 0.0f,
        0.02f, -0.08f, 0.0f,   0.2f,  0.2f, 0.0f,
        0.02f, -0.79f, 0.0f,   0.2f,  0.2f, 0.0f,
    };

    vector<float> vertices2 = Leaves();
    //cout << "inicioHoja" << vertices.size() << "\n";

    vector<float>::iterator it = vertices.end();
    vertices.insert(it, vertices2.begin(), vertices2.end());
    //cout << "FHoja" << vertices.size() << "\n";

    vector<float> vertices3 = Base();

    it = vertices.end();
    vertices.insert(it, vertices3.begin(), vertices3.end());
    //cout << "Fflor" << vertices.size() << "\n";


    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, a.size()*sizeof(float), &a.front(), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, ver.size() * sizeof(Vertex), &ver.front(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

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
    int a = 3;
    int c = 5;
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        
        //animacion continua
        if (c %10 == 0) a = -a;
        c += 1;
        CruceM2(vertices, 144, 18144, a);
        GiroM2(vertices, 18144, 21348, 30);
        
        //por teclado
        /*if (anima1 > 0) {
            if (anima1 == 5) a = -a;
            CruceM2(vertices, 144, 18144, a);
            anima1--;
        }
        if (anima2 > 0) {
            GiroM2(vertices, 18144, 21348, 36);
            anima2--;
        }*/
        
        Sleep(100);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        //now render triangle
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        //Triangulos -------------------------------------------------------------
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/2);// Con triangulos
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
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        anima1 = 10;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        anima2 = 10;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

vector<float> DrawLeaf(float a, float b, float G, float B = 0.0f) {
    vector<float> Leaf;
    vector<float> aux;
    //float a, b;
    //a = 0.21;
    //b = 0.62;
    //Color

    float y = 0;

    for (float i = b*(-1); i < b; i += 0.01) {
        y = sqrt((1 - (i * i) / (b * b)) * a * a);
        aux.push_back(i);    //x
        aux.push_back(y);    //y
        aux.push_back(0.0f); //z
        aux.push_back(0.0f); //R
        aux.push_back(G); //G
        aux.push_back(B); //B
    }

    vector<float> orig = { 0.0f, 0.0f, 0.0f, 0.0f, G, B }; // G = 1.0f, efecto degradado
    int i = 0;
    for (int i = 0; i < aux.size() -6; i += 6) {
        Leaf.push_back(aux[i]);
        Leaf.push_back(aux[i + 1]);
        Leaf.push_back(aux[i + 2]);
        Leaf.push_back(aux[i + 3]);
        Leaf.push_back(aux[i + 4]);
        Leaf.push_back(aux[i + 5]);
        vector<float>::iterator it = Leaf.end();
        Leaf.insert(it, orig.begin(), orig.end());
        Leaf.push_back(aux[i + 6]);
        Leaf.push_back(aux[i + 7]);
        Leaf.push_back(aux[i + 8]);
        Leaf.push_back(aux[i + 9]);
        Leaf.push_back(aux[i + 10]);
        Leaf.push_back(aux[i + 11]);
    }
    //Complemento-----
    Leaf.push_back(aux[i]);
    Leaf.push_back(aux[i + 1]);
    Leaf.push_back(aux[i + 2]);
    Leaf.push_back(aux[i + 3]);
    Leaf.push_back(aux[i + 4]);
    Leaf.push_back(aux[i + 5]);
    vector<float>::iterator it = Leaf.end();
    Leaf.insert(it, orig.begin(), orig.end());
    Leaf.push_back(aux[0]);
    Leaf.push_back(aux[1]);
    Leaf.push_back(aux[2]);
    Leaf.push_back(aux[3]);
    Leaf.push_back(aux[4]);
    Leaf.push_back(aux[5]);
    //--------
    return Leaf;

}

vector<float> EspejoX(vector<float> vec) {
    vector<float> Espejo;
    for (int i = 0; i < vec.size(); i+=6) {
        Espejo.push_back(vec[i]);
        Espejo.push_back(-vec[i + 1]);
        Espejo.push_back(vec[i + 2]);
        Espejo.push_back(vec[i + 3]);
        Espejo.push_back(vec[i + 4]);
        Espejo.push_back(vec[i + 5]);
    };
    return Espejo;
}
vector<float> EspejoY(vector<float> vec) {
    vector<float> Espejo;
    for (int i = 0; i < vec.size(); i += 6) {
        Espejo.push_back(-vec[i]);
        Espejo.push_back(vec[i + 1]);
        Espejo.push_back(vec[i + 2]);
        Espejo.push_back(vec[i + 3]);
        Espejo.push_back(vec[i + 4]);
        Espejo.push_back(vec[i + 5]);
    };
    return Espejo;
}

vector<float> Rotar(vector<float> vec) {
    vector<float> Giro;
    float ang = 61.13 * PI / 180; // modificar angulo
    for (int i = 0; i < vec.size(); i += 6) {
        Giro.push_back(cos(ang) * vec[i] + sin(ang) * vec[i + 1]);
        Giro.push_back(-sin(ang) * vec[i] + cos(ang) * vec[i + 1]);
        Giro.push_back(vec[i + 2]);
        Giro.push_back(vec[i + 3]);
        Giro.push_back(vec[i + 4]);
        Giro.push_back(vec[i + 5]);
    };
    return Giro;
}

vector<float> Mover(vector<float> vec, float x, float y) {
    vector<float> New;
    for (int i = 0; i < vec.size(); i += 6) {
        New.push_back(vec[i] + x);
        New.push_back(vec[i + 1] + y);
        New.push_back(vec[i + 2]);
        New.push_back(vec[i + 3]);
        New.push_back(vec[i + 4]);
        New.push_back(vec[i + 5]);
    };
    return New;
}

vector<float> Hoja() {
    float a = 0.20;
    float b = 0.61;
    //Marco negro
    vector<float> _top = DrawLeaf(a+0.01, b+0.015, 0.0f);
    vector<float> _down = EspejoX(_top);
    vector<float>::iterator it = _top.end();
    _top.insert(it, _down.begin(), _down.end());

    //Hoja
    vector<float> top = DrawLeaf(a,b,1.0f);
    vector<float> down = EspejoX(top);
    vector<float>::iterator it2 = top.end();
    top.insert(it2, down.begin(), down.end());

    vector<float>::iterator it3 = _top.end();
    _top.insert(it3, top.begin(), top.end());

    //Linea
    vector<float> linea{
      -b,  0.005f, 0.0f,   0.0f,  0.0f, 0.0f,
      -b, -0.005f, 0.0f,   0.0f,  0.0f, 0.0f,
       b, -0.005f, 0.0f,   0.0f,  0.0f, 0.0f,

      -b,  0.005f, 0.0f,   0.0f,  0.0f, 0.0f,
       b,  0.005f, 0.0f,   0.0f,  0.0f, 0.0f,
       b, -0.005f, 0.0f,   0.0f,  0.0f, 0.0f
    };

    vector<float>::iterator it4 = _top.end();
    _top.insert(it4, linea.begin(), linea.end());
    
    return _top;
}

vector<float> Leaves() {
    vector<float> aux = Hoja();
    aux = Rotar(aux);
    aux = Mover(aux,-0.38f,-0.24f);
    vector<float> aux2 = EspejoY(aux);

    vector<float>::iterator it4 = aux.end();
    aux.insert(it4, aux2.begin(), aux2.end());

    return aux;
}

vector<float> Base() {
    float a = 0.42;
    float b = 0.42;
    vector<float> _base = DrawLeaf(a, b, 0.0f);
    _base = EspejoX(_base);
    vector<float> base = DrawLeaf(a-0.01,b-0.01, 0.5f,0.5f);
    base = EspejoX(base);


    vector<float>::iterator it = _base.end();
    _base.insert(it, base.begin(), base.end());

    _base = Mover(_base, 0.0, 0.323);

    vector<float> petalo{
       //Contorno
      -0.42, 0.81, 0.0f,   0.0f,  0.0f, 0.0f,
      -0.42, 0.32, 0.0f,   0.0f,  0.0f, 0.0f,
       0.0, 0.31, 0.0f,   0.0f,  0.0f, 0.0f,
       //Cuerpo
      -0.41, 0.79, 0.0f,   0.0f,  0.5f, 0.5f,
      -0.41, 0.31, 0.0f,   0.0f,  0.5f, 0.5f,
       -0.01, 0.31, 0.0f,   0.0f,  0.5f, 0.5f,

       //PETALO MEDIO
       //Contorno
        -0.25, 0.60, 0.0f,   0.0f,  0.0f, 0.0f,
         0.0, 0.80, 0.0f,   0.0f,  0.0f, 0.0f,
         0.0, 0.31, 0.0f,   0.0f,  0.0f, 0.0f,
         //Cuerpo
        -0.235, 0.597, 0.0f,   0.0f,  0.5f, 0.5f,
         0.0, 0.79, 0.0f,   0.0f,  0.5f, 0.5f,
         0.0, 0.33, 0.0f,   0.0f,  0.5f, 0.5f,
    };
    vector<float> petalo2 = EspejoY(petalo);

    it = _base.end();
    _base.insert(it, petalo.begin(), petalo.end());

    it = _base.end();
    _base.insert(it, petalo2.begin(), petalo2.end());

    vector<float> linea{
    -0.012, 0.32f, 0.0f,   0.0f,  0.0f, 0.0f,
    -0.012, -0.09, 0.0f,   0.0f,  0.0f, 0.0f,
     0.012, -0.09, 0.0f,   0.0f,  0.0f, 0.0f,

    -0.012, 0.32f, 0.0f,   0.0f,  0.0f, 0.0f,
     0.012, 0.32f, 0.0f,   0.0f,  0.0f, 0.0f,
     0.012, -0.09, 0.0f,   0.0f,  0.0f, 0.0f,

    };

    it = _base.end();
    _base.insert(it, linea.begin(), linea.end());

    return _base;
}


//Version Directa ---------------------------
//Cruzar-Hojas // GirarF-lor 
void Giro(vector<float>& vec, int inicio, int fin, int a) { //inicio = 18144, fin =21348 /1068 pts
    float ang = a * PI / 180; // modificar angulo
    for (int i = inicio; i < fin; i+=6) {
        float aux = vec[i];
        vec[i] = cos(ang) * vec[i] + sin(ang) * vec[i + 1];
        vec[i+1] = -sin(ang) * aux + cos(ang) * vec[i + 1];
    }
}
void Cruce(vector<float>& vec, int inicio, int fin, int a) { // inicio = 144, fin = 18144 /3000 pts 
    float ang = a * PI / 180; // modificar angulo
    for (int i = inicio; i < fin; i += 6) {
        float aux = vec[i];
        vec[i+1] = tan(ang) * vec[i] + vec[i+1];
    }
}

//Con matrices
/*void GiroM(vector<float>& vec, int inicio, int fin, int a) { //inicio = 18144, fin =21348 /1068 pts
    vector<vector<float>> mat = rotacion(a);
    for (int i = inicio; i < fin; i += 6) { // 4 vecs
        for (int j = 0; j < mat.size(); j++) {
            float aux = 0;
            for (int k = 0; k < mat.size(); k++) {
                if ((i + k) % 3 == 2) { vec[i + k] = 1.0; } // paso innecesario?
                aux += mat[j][k] * vec[i + k];
            }
            res.push_back(aux);
            //cout << "aux:" << aux << endl;
        }
    }
}*/
void GiroM2(vector<float>& vec, int inicio, int fin, int a) { //inicio = 18144, fin =21348 /1068 pts
    vector<vector<float>> mat = rotacion(a);
    for (int i = inicio; i < fin; i += 6) { // 4 vecs
        vector<float> coord = {vec[i], vec[i+1], 1};
        for (int j = 0; j < mat.size()-1; j++) { //Solo se consideran x e y [No tercera dimension]
            float aux = 0;
            for (int k = 0; k < mat.size(); k++) {
                if ((i + k) % 3 == 2) { vec[i + k] = 1.0; } // paso innecesario?
                aux += mat[j][k] * coord[k];
            }
            vec[i + j] = aux;
        }
    }
}
void CruceM2(vector<float>& vec, int inicio, int fin, int a) { // inicio = 144, fin = 18144 /3000 pts 
    vector<vector<float>> mat = shearY(a);
    for (int i = inicio; i < fin; i += 6) { // 4 vecs
        vector<float> coord = { vec[i], vec[i + 1], 1 };
        for (int j = 0; j < mat.size() - 1; j++) { //Solo se consideran x e y [No tercera dimension]
            float aux = 0;
            for (int k = 0; k < mat.size(); k++) {
                if ((i + k) % 3 == 2) { vec[i + k] = 1.0; } // paso innecesario?
                aux += mat[j][k] * coord[k];
            }
            vec[i + j] = aux;
        }
    }
}
