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
//float cameraPos[3] = { 0.0f, 0.0f, 6.0f };
//float cubePos[3] = { 0.0f, 0.0f, 0.0f };
//bool wireFrame = false;
//float modelScale = 0.11f;
//float rotation = 0.0f;
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
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
//
//    float skyboxVertices[] = {
//        // positions          
//        -1.0f,  1.0f, -1.0f,
//        -1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//         1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//
//        -1.0f, -1.0f,  1.0f,
//        -1.0f, -1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f, -1.0f,
//        -1.0f,  1.0f,  1.0f,
//        -1.0f, -1.0f,  1.0f,
//
//         1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//
//        -1.0f, -1.0f,  1.0f,
//        -1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f, -1.0f,  1.0f,
//        -1.0f, -1.0f,  1.0f,
//
//        -1.0f,  1.0f, -1.0f,
//         1.0f,  1.0f, -1.0f,
//         1.0f,  1.0f,  1.0f,
//         1.0f,  1.0f,  1.0f,
//        -1.0f,  1.0f,  1.0f,
//        -1.0f,  1.0f, -1.0f,
//
//        -1.0f, -1.0f, -1.0f,
//        -1.0f, -1.0f,  1.0f,
//         1.0f, -1.0f, -1.0f,
//         1.0f, -1.0f, -1.0f,
//        -1.0f, -1.0f,  1.0f,
//         1.0f, -1.0f,  1.0f
//    };
//
//    float cubeVertices[] = {
//        // Back face
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right  
//         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right    
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left  
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right             
//        // Front face
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right  
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left     
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//            
//        // Left face
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left 
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//
//        // Right face
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right  
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right      
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//        // Bottom face          
//         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left 
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//        // Top face
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right  
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // bottom-left  
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f // bottom-right
//    };
//
//    // skybox VAO
//    unsigned int skyboxVAO, skyboxVBO;
//    glGenVertexArrays(1, &skyboxVAO);
//    glGenBuffers(1, &skyboxVBO);
//    glBindVertexArray(skyboxVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//
//    // cube VAO
//    unsigned int cubeVAO, cubeVBO;
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
//
//    Shader skyboxShader("practice/04advanced/06cubemaps/skybox.vs", "practice/04advanced/06cubemaps/skybox.fs");
//    skyboxShader.use();
//    skyboxShader.setInt("skybox", 0);
//    Shader sceneShader("practice/04advanced/06cubemaps/scene.vs", "practice/04advanced/06cubemaps/scene.fs");
//    sceneShader.use();
//    sceneShader.setInt("texture1", 0);
//
//    Shader modelShader("practice/03model/1.model_loading.vs", "practice/03model/1.model_loading.fs");
//    Model ourModel("resources/objects/nanosuit/nanosuit.obj");
//
//    vector<std::string> faces
//    {
//        "right.jpg",
//        "left.jpg",
//        "top.jpg",
//        "bottom.jpg",
//        "front.jpg",
//        "back.jpg"
//    };
//
//    imgLoader.setYFlip(false);
//    unsigned int cubemapTexture = imgLoader.loadCubemap(faces, "resources/textures/skybox/");
//    unsigned int cubeTexture = imgLoader.loadTexture("resources/textures/container.jpg");
//    imgLoader.setYFlip(true);
//    unsigned int sexTexture = imgLoader.loadTexture("resources/textures/sex.jpg");
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
//        // draw as wireframe
//        if (wireFrame) {
//            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//        }
//        else
//        {
//            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//        }
//
//        // render
//        //clear the framebuffer's content
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        camera.Position = glm::vec3(cameraPos[0], cameraPos[1], cameraPos[2]);
//
//        //draw cube1
//        glDepthFunc(GL_LESS);
//        sceneShader.use();
//        glm::mat4 cubemodel = glm::mat4(1.0f);
//        glm::mat4 cubeview = camera.GetViewMatrix();
//        glm::mat4 cubeprojection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        sceneShader.setMat4("view", cubeview);
//        sceneShader.setMat4("projection", cubeprojection);
//        cubemodel = glm::translate(cubemodel, glm::vec3(cubePos[0], cubePos[1], cubePos[2]));
//        sceneShader.setMat4("model", cubemodel);
//        glBindVertexArray(cubeVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, cubeTexture);
//        glDrawArrays(GL_TRIANGLES,0, 36);
//        //draw cube2
//        cubemodel = glm::translate(cubemodel, glm::vec3(cubePos[0]+3, cubePos[1], cubePos[2]));
//        glBindTexture(GL_TEXTURE_2D, sexTexture);
//        sceneShader.setMat4("model", cubemodel);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//        //draw model
//        modelShader.use();
//        modelShader.setMat4("view", cubeview);
//        modelShader.setMat4("projection", cubeprojection);
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); 
//        model = glm::scale(model, glm::vec3(modelScale, modelScale, modelScale));	
//        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
//        modelShader.setMat4("model", model);
//        ourModel.Draw(modelShader);
//
//        //draw sky box
//        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
//        skyboxShader.use();
//        glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        skyboxShader.setMat4("view", view);
//        skyboxShader.setMat4("projection", projection);
//        glBindVertexArray(skyboxVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
//        glDepthFunc(GL_LESS);
//
//        guiHelper.guiRenderBengin();
//        ImGui::SliderFloat3("camera pos", cameraPos, -6.0f, 6.0f);
//        ImGui::SliderFloat3("cube pos", cubePos, -6.0f, 6.0f);
//        ImGui::Checkbox("wireframe", &wireFrame);
//        ImGui::Checkbox("enable mouse", &enableMouse);
//        guiHelper.guiRenderEnd();
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    sceneShader.clear();
//    modelShader.clear();
//    skyboxShader.clear();
//    guiHelper.guiClear();
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteVertexArrays(1, &skyboxVAO);
//    glDeleteBuffers(1, &cubeVBO);
//    glDeleteBuffers(1, &skyboxVBO);
//    glfwTerminate();
//
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