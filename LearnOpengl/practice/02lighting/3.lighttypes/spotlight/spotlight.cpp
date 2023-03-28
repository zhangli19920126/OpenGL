//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <iostream>
//#include "../../../../locallibs/shader_s.h"
//#include "../../../../locallibs/camera.h"
//#include "../../../../locallibs/imgui_helper.h"
//#include "../../../../locallibs/imgloder.h"
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
////material params
//float ambient = 0.3f;
//float emission = 1.0f;
//int shininess = 32;
//float diffuseStrength = 0.7f;
//float specularStrength = 0.6f;
//
////spot light params
//float lightPos[3] = { 0.0f, 0.0f, 1.0f };
//float lightCol[3] = { 1.0f, 1.0f, 1.0f };
//float lightDir[3] = { 0.0f, 0.0f, -1.0f };
//float lightCutoff = 12.5f;
//float lightOutCutoff = 20.0f;
//float constant = 1.0f;
//float linear = 0.09f;
//float quadratic = 0.032f;
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
//    // configure global opengl state£ºenable Depth test
//    glEnable(GL_DEPTH_TEST);
//
//    //gui 
//    guiHelper.bindGui(window, true);
//
//    // build and compile our shader program
//    Shader lightingShader("practice/02lighting/3.lighttypes/spotlight/spot_light.vs", "practice/02lighting/3.lighttypes/spotlight/spot_light.fs");
//
//    float vertices[] = {
//        // positions          // normals           // texture coords
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
//
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
//    };
//
//    // positions all containers
//    glm::vec3 cubePositions[] = {
//        glm::vec3(0.0f,  0.0f,  0.0f),
//        glm::vec3(2.0f,  5.0f, -15.0f),
//        glm::vec3(-1.5f, -2.2f, -2.5f),
//        glm::vec3(-3.8f, -2.0f, -12.3f),
//        glm::vec3(2.4f, -0.4f, -3.5f),
//        glm::vec3(-1.7f,  3.0f, -7.5f),
//        glm::vec3(1.3f, -2.0f, -2.5f),
//        glm::vec3(1.5f,  2.0f, -2.5f),
//        glm::vec3(1.5f,  0.2f, -1.5f),
//        glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//
//    unsigned int VBO, VAO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    
//    glBindVertexArray(VAO);
//
//    //pos attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    //normal attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    //ui
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//    //load text to gpu
//    imgLoader.setYFlip(true);
//    unsigned int diffuseMap, specularMap, emissionMap;
//    int width, height, nrChannels;
//    imgLoader.bindTexture(&diffuseMap, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
//    imgLoader.loadImg("resources/textures/container2.png", &width, &height, &nrChannels, 0, GL_RGBA);
//    imgLoader.bindTexture(&specularMap, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
//    imgLoader.loadImg("resources/textures/container2_specular.png", &width, &height, &nrChannels, 0, GL_RGBA);
//    imgLoader.bindTexture(&emissionMap, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
//    imgLoader.loadImg("resources/textures/matrix.jpg", &width, &height, &nrChannels, 0, GL_RGB);
//
//    lightingShader.use();
//    lightingShader.setInt("material.diffuseTex", 0);
//    lightingShader.setInt("material.specularTex", 1);
//    lightingShader.setInt("material.emissionTex", 2);
//
//    while (!glfwWindowShouldClose(window))
//    {
//        //calculate delta time
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        processInput(window);
//
//        // render
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // bind Texture
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, diffuseMap);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, specularMap);
//        glActiveTexture(GL_TEXTURE2);
//        glBindTexture(GL_TEXTURE_2D, emissionMap);
//
//        lightingShader.use();
//        //set material data
//        lightingShader.setFloat("material.emission", emission);
//        lightingShader.setFloat("material.ambient", ambient);
//        lightingShader.setInt("material.shininess", shininess);
//        lightingShader.setFloat("material.diffuse", diffuseStrength);
//        lightingShader.setFloat("material.specular", specularStrength);
//
//        ////set light data
//        lightingShader.setVec3("light.color", glm::vec3(lightCol[0], lightCol[1], lightCol[2]));
//        lightingShader.setVec3("light.position", glm::vec3(lightPos[0], lightPos[1], lightPos[2]));
//        //lightingShader.setVec3("light.position", camera.Position);
//        lightingShader.setVec3("light.direction", glm::vec3(lightDir[0], lightDir[1], lightDir[2]));
//        //lightingShader.setVec3("light.direction", camera.Front);
//        lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(lightCutoff)));
//        lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(lightOutCutoff)));
//        lightingShader.setFloat("light.constant", constant);
//        lightingShader.setFloat("light.linear", linear);
//        lightingShader.setFloat("light.quadratic", quadratic);
//        //camera pos
//        lightingShader.setVec3("viewPos", camera.Position);
//
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        lightingShader.setMat4("projection", projection);
//        lightingShader.setMat4("view", view);
//
//        glBindVertexArray(VAO);
//        for (unsigned int i = 0; i < 10; i++)
//        {
//            glm::mat4 model;
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            lightingShader.setMat4("model", model);
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        guiHelper.guiRenderBengin();
//        ImGui::SliderFloat("ambient", &ambient, 0.0f, 1.0f);
//        ImGui::SliderFloat("emission", &emission, 0.0f, 3.0f);
//        ImGui::SliderFloat("diffuseStrength", &diffuseStrength, 0.0f, 10.0f);
//        ImGui::SliderFloat("specularStrength", &specularStrength, 0.0f, 10.0f);
//        ImGui::SliderFloat("linear", &linear, 0.0f, 1.0f);
//        ImGui::SliderFloat("quadratic", &quadratic, 0.0f, 2.0f);
//        ImGui::SliderInt("shininess", &shininess, 1, 128);
//        ImGui::Checkbox("enable mouse", &enableMouse);
//        ImGui::SliderFloat3("lightPos", lightPos, -3.0f, 3.0f);
//        ImGui::SliderFloat3("lightColor", lightCol, 0.0f, 1.0f);
//        ImGui::SliderFloat3("lightDirection", lightDir, -1.0f, 1.0f);
//        ImGui::SliderFloat("cutoff", &lightCutoff , 0.0f, 100.0f);
//        ImGui::SliderFloat("out cutoff", &lightOutCutoff , 0.0f, 100.0f);
//        guiHelper.guiRenderEnd();
//
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    lightingShader.clear();
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    guiHelper.guiClear();
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
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
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
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
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}