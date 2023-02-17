//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//#include "../../locallibs/imgui_helper.h"
//
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\0";
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";
//
//bool show_demo_window = false;
//ImguiHelper imguiHelper;
//
//
//int main()
//{
//
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    imguiHelper.bindGui(window, true);
//
//
//    // build and compile our shader program
//    // ------------------------------------
//    // vertex shader
//    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//    // check for shader compile errors
//    int success;
//    char infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//    // fragment shader
//    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//    // check for shader compile errors
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//    // link shaders
//    unsigned int shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//    // check for linking errors
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if (!success) {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//    }
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float firstTriangle[] = {
//        -0.9f, 0.9f, 0.0f,   -0.5f, 0.9f, 0.0f,  0.0f, 0.9f, 0.0f,   0.5f, 0.9f, 0.0f,  0.9f, 0.9f, 0.0f,
//        -0.9f, 0.5f, 0.0f,   -0.5f, 0.5f, 0.0f,  0.0f, 0.5f, 0.0f,   0.5f, 0.5f, 0.0f,  0.9f, 0.5f, 0.0f,
//        -0.9f, 0.0f, 0.0f,   -0.5f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,   0.5f, 0.0f, 0.0f,  0.9f, 0.0f, 0.0f,
//        -0.9f, -0.5f, 0.0f,   -0.5f, -0.5f, 0.0f,  0.0f, -0.5f, 0.0f,   0.5f, -0.5f, 0.0f,  0.9f, -0.5f, 0.0f,
//        -0.9f, -0.9f, 0.0f,   -0.5f, -0.9f, 0.0f,  0.0f, -0.9f, 0.0f,   0.5f, -0.9f, 0.0f,  0.9f, -0.9f, 0.0f,  0.9f, -0.3f, 0.0f,
//    };
//
//    unsigned int indices[] = {
//        0, 6, 2, 
//        2, 8, 4,  
//        5, 11, 7,  
//        7, 13, 9,  
//    };
//
//    unsigned int indices1[] = {
//        15, 11, 17, 
//        17, 13, 19,  
//        20, 16, 22,  
//        22, 18, 24,
//    };
//
//    unsigned int VBO, VAOs[2], EBOs[2];
//    glGenVertexArrays(2, VAOs); 
//    glGenBuffers(1, &VBO);
//    glGenBuffers(2, EBOs);
//    
//    glBindVertexArray(VAOs[0]);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    glBindVertexArray(VAOs[1]);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
//
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        processInput(window);
//
//        //clear
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        // opengl render
//        glUseProgram(shaderProgram);
//        
//        glBindVertexArray(VAOs[0]);
//        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));
//
//        glBindVertexArray(VAOs[1]);
//        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));
//
//        imguiHelper.guiRender(&show_demo_window);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    imguiHelper.guiClear();
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(2, VAOs);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(2, EBOs);
//    glDeleteProgram(shaderProgram);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}