//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <iostream>
//#include "../../../locallibs/model.h"
//#include "../../../locallibs/shader_s.h"
//#include "../../../locallibs/imgui_helper.h"
//#include "../../../locallibs/imgloder.h"
//#include "../../../locallibs/camera.h"
//
//// ps: By default, triangles defined with counter-clockwise vertices are processed as front-facing triangles.
////glEnable(GL_CULL_FACE);
////glCullFace(GL_BACK);  //GL_BACK£¨default£©¡¢GL_FRONT ¡¢GL_FRONT_AND_BACK
////glFrontFace(GL_CW);  //GL_CCW(default) ¡¢GL_CW 
//
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//bool enableMouse = false;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
////gui
//ImguiHelper guiHelper;
//
////img
//ImgLoader imgLoader;
//
//float cameraPos[3] = { 0.0f, 0.0f, 3.0f };
//float cubePos[3] = { 0.0f, 0.0f, 0.0f };
//
//bool isEnableCull = false;
//bool cullBack = true;
//
//int main()
//{
//    // glfw: initialize and configure
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
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//
//    // glad: load all OpenGL function pointers
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    guiHelper.bindGui(window, true);
//
//    // configure global opengl state
//    glEnable(GL_DEPTH_TEST);
//
//
//    // build and compile shaders
//    Shader shader("practice/04advanced/04face_culling/face_cull.vs", "practice/04advanced/04face_culling/face_cull.fs");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    float cubeVertices[] = {
//        // Back face
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
//         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right    
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right              
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left                
//        // Front face
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right        
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left        
//        // Left face
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left       
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//        // Right face
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right      
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right          
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//        // Bottom face          
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left        
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//        // Top face
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right                 
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // bottom-left  
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // top-left   
//    };
//
//    //cube vertex data bind
//    unsigned int cubeVBO, cubeVAO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//
//    //load texture
//    //imgLoader.setYFlip(true);
//    unsigned int cubeTexture = imgLoader.loadTexture("resources/textures/marble.jpg");
//
//    // shader configuration
//    shader.use();
//    shader.setInt("texture1", 0);
//
//    while (!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        processInput(window);
//
//        // render
//        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        if (isEnableCull) 
//        {
//            glEnable(GL_CULL_FACE);
//            glFrontFace(GL_CCW);
//            if (cullBack) 
//            {
//                glCullFace(GL_BACK);
//            }
//            else {
//                glCullFace(GL_FRONT);
//            }
//        }
//
//        //mvp
//        shader.use();
//        camera.Position = glm::vec3(cameraPos[0], cameraPos[1], cameraPos[2]);
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_WIDTH, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        glm::mat4 model = glm::mat4(1.0f);
//        shader.setMat4("projection", projection);
//        shader.setMat4("view", view);
//        model = glm::translate(model, glm::vec3(cubePos[0], cubePos[1], cubePos[2]));
//        shader.setMat4("model", model);
//
//        //draw cubes
//        glBindVertexArray(cubeVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, cubeTexture);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        guiHelper.guiRenderBengin();
//        ImGui::SliderFloat3("camera pos", cameraPos, -6.0f, 6.0f);
//        ImGui::SliderFloat3("cube pos", cubePos, -6.0f, 6.0f);
//        ImGui::Checkbox("cull enable", &isEnableCull);
//        ImGui::Checkbox("cull back", &cullBack);
//        ImGui::Checkbox("mouse enable", &enableMouse);
//        guiHelper.guiRenderEnd();
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteBuffers(1, &cubeVBO);
//    shader.clear();
//
//    glfwTerminate();
//    guiHelper.guiClear();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//
//// glfw: whenever the mouse moves, this callback is called
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS) {
//        firstMouse = true;
//        return;
//    }
//
//    if (!enableMouse)
//    {
//        return;
//    }
//
//    float xpos = static_cast<float>(xposIn);
//    float ypos = static_cast<float>(yposIn);
//
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}