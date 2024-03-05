// template based on material from learnopengl.com
#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include "models.h" //Models Class

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

const char *gradientVertexShader = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

const char* gradientFragShader = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\0";

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "ClassGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // // glew: load all OpenGL function pointers
    glewInit();


    // build and compile our shader program
    // ------------------------------------


    // Vertex shader
    // This is creating the only vertex shader in this program
    unsigned int vertexShader[2];
    vertexShader[0] = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader[0], 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader[0]);

    vertexShader[1] = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader[1], 1, &gradientVertexShader, NULL);
    glCompileShader(vertexShader[1]);


    // Check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader[0], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader[0], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(vertexShader[1], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader[1], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Making it an array just in case I want to add more

    unsigned int fragmentShader[2];
    //Default Shader
    fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[0], 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader[0]);

    // Gradient Fragment Shader
    fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader[1], 1, &gradientFragShader, NULL);
    glCompileShader(fragmentShader[1]);

    // check for shader compile errors
    glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Links all the shaders
    // Creating THREE Shaders for each color WOOOOO
    unsigned int shaderProgram[2];

    //Base One
    shaderProgram[0] = glCreateProgram();
    glAttachShader(shaderProgram[0], vertexShader[0]);
    glAttachShader(shaderProgram[0], fragmentShader[0]);

    //Custom Shaders
    shaderProgram[1] = glCreateProgram();
    glAttachShader(shaderProgram[1], vertexShader[1]);
    glAttachShader(shaderProgram[1], fragmentShader[1]);

    glLinkProgram(shaderProgram[0]);
    glLinkProgram(shaderProgram[1]);

    // check for linking errors
    glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader[0]);
    glDeleteShader(vertexShader[1]);
    glDeleteShader(fragmentShader[0]);
    glDeleteShader(fragmentShader[1]);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // Vertices are split into two seperate triangles
    float triangles[] = {
        -0.5f, -.25f, 0.0f, 1.0f, 0.0f, 0.0f, // left,  red
         0.5f, -.75f, 0.0f, 0.0f, 1.0f, 0.0f,//  right, green
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, //  top,   blue
         
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // left  
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// right 
         0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f  // bottom
    };

    unsigned int triIndices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
        3, 4, 5    // second triangle
    };

    unsigned int numVertices = sizeof(triangles)/3;

    float rectangle[] = {
        0.25f,  0.25f, 0.0f,   1.0f, 0.0f, 0.0f,   // top right
        0.25f, -0.25f, 0.0f,   0.0f, 1.0f, 0.0f,   // bottom right
        -0.25f, -0.25f, 0.0f,  0.0f, 0.0f, 1.0f, // bottom left
        -0.25f,  0.25f, 0.0f,  1.0f, 1.0f, 1.0f  // top left 
    };

    unsigned int rectIndices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    float testCube[] = {
        -1.0f,  -1.0f, 1.0f, 
        -1.0f,  1.0f, 1.0f,  
        -1.0f,  -1.0f, -1.0f, 
        -1.0f,  1.0f, -1.0f, 
        1.0f,  -1.0f, 1.0f, 
        1.0f,  1.0f, 1.0f, 
        1.0f,  -1.0f, -1.0f, 
        1.0f,  1.0f, -1.0f, 
    };

    unsigned int testCubeInd[] = {  // note that we start from 0!
        2, 3, 1, 
        4, 7, 3,
        8, 5, 7,
        6, 1, 5,
        7, 1, 3, 
        4, 6, 8, 
        2, 4, 3, 
        4, 8, 7, 
        8, 6, 5, 
        6, 2, 1, 
        7, 5, 1, 
        4, 2, 6
    };

    char modelFile[] = "../model/cube.obj";
    //Creating a model object
    Model cube(modelFile);

    //Creating an array of VBOs and VAOs because there are two triangles
    unsigned int VBO[3];
    unsigned int VAO[3];
    unsigned int EBO[3];
    glGenBuffers(3, VBO);
    glGenVertexArrays(3, VAO);
    glGenBuffers(3, EBO);



    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    //Working with Triangles
    //glBindVertexArray(VAO[0]);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);
    ////Bind EBOs
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triIndices), triIndices, GL_STATIC_DRAW);
    ////Position Attribute
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    ////Color Attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
//
    //glBindVertexArray(0);
//
    ////Working with Rectangle
    //glBindVertexArray(VAO[1]);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
    ////Bind EBOs
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectIndices), rectIndices, GL_STATIC_DRAW);
    ////Position Attribute
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    ////Color Attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);
//
    //glBindVertexArray(0);

    //Working with Cube
    //glBindVertexArray(VAO[0]);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(cube.vertices), cube.vertices, GL_STATIC_DRAW);
    ////Bind EBOs
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube.indices), cube.indices, GL_STATIC_DRAW);
    ////Position Attribute
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    // render loop
    // -----------

    double lasttime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glUseProgram(shaderProgram[1]);
        //glBindVertexArray(VAO[0]); 
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
        //glBindVertexArray(VAO[1]); 
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       // glUseProgram(shaderProgram[0]);
        cube.Draw();

        //glBindVertexArray(0);
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

        while (glfwGetTime() < lasttime + 1.0/30) {
            //NOTHING
        }
        lasttime += 1.0/30;
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(3, VAO);
    glDeleteBuffers(3, VBO);
    glDeleteProgram(shaderProgram[0]);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}