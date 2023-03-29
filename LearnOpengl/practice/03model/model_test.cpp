#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../../locallibs/model.h"
#include "../../locallibs/shader_s.h"
#include "../../locallibs/imgui_helper.h"
#include "../../locallibs/imgloder.h"
#include "../../locallibs/camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool enableMouse = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//gui
ImguiHelper guiHelper;

//img
ImgLoader imgLoader;

float modelScale = 0.11f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.5f, 3.0f);
float rotation = 0.0f;

//material
float shiniess = 32.0f;
float ambient = 0.2f;
float diffuse = 0.7f;
float specular = 1.0f;

//diretion light
glm::vec3 dirLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 dirLightDirection = glm::vec3(1.0f, 0.0f, -1.0f);
float dirLightRate = 1.0f;

//point light position
glm::vec3 pointLightPositions[] = {
    glm::vec3(-1.0f,  1.0f,  0.0f),
    glm::vec3(1.0f, 1.0f, 0.0f),
    glm::vec3(0.0f,  -1.0f, -1.0f)
};

//point light color
glm::vec3 pointLightColor[] = {
    glm::vec3(1.0f,  0.0f,  0.0f),
    glm::vec3(0.0f,  1.0f,  0.0f),
    glm::vec3(0.0f,  0.0f,  1.0f)
};

float pointLightConstant[3] = { 1.0f, 1.0f, 1.0f };
float pointLightLinear[3] = { 0.09f, 0.09f, 0.09f };
float pointLightQuadratic[3] = { 0.032f, 0.032f, 0.032f };
float pointLightRate[3] = {1.0f, 1.0f, 1.0f};

//spot light
glm::vec3 spotLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 spotLightPos = glm::vec3(0.0f, 0.8f, 2.0f);
glm::vec3 spotLightDirection = glm::vec3(0.0f, 0.0f, -1.0f);
float spotCutOff = 10.5f;
float spotOuterCutOff = 12.5f;
float spotConstant = 1.0f;
float spotLinear = 0.09f;
float spotQuadratic = 0.032f;
float spotLightRate = 1.0f;

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    guiHelper.bindGui(window, true);

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    Shader ourShader("practice/03model/1.model_loading.vs", "practice/03model/model_comprehensive.fs");

    // load models
    Model ourModel("resources/objects/nanosuit/nanosuit.obj");


    // draw in wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Position = cameraPos;

        // don't forget to enable shader before setting uniforms
        ourShader.use();
        //view positon
        ourShader.setVec3("viewPos", cameraPos);
        //material
        ourShader.setFloat("shininess", shiniess);
        ourShader.setFloat("ambientRate", ambient);
        ourShader.setFloat("diffuseRate", diffuse);
        ourShader.setFloat("specRate", specular);

        // directional light
        ourShader.setVec3("dirLight.direction", dirLightDirection);
        ourShader.setVec3("dirLight.color", dirLightColor);
        ourShader.setFloat("dirLightRate", dirLightRate);

        // point light 1
        ourShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        ourShader.setVec3("pointLights[0].color", pointLightColor[0]);
        ourShader.setFloat("pointLights[0].constant", pointLightConstant[0]);
        ourShader.setFloat("pointLights[0].linear", pointLightLinear[0]);
        ourShader.setFloat("pointLights[0].quadratic", pointLightQuadratic[0]);
        ourShader.setFloat("pointRate[0]", pointLightRate[0]);

        // point light 2
        ourShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        ourShader.setVec3("pointLights[1].color", pointLightColor[1]);
        ourShader.setFloat("pointLights[1].constant", pointLightConstant[1]);
        ourShader.setFloat("pointLights[1].linear", pointLightLinear[1]);
        ourShader.setFloat("pointLights[1].quadratic", pointLightQuadratic[1]);
        ourShader.setFloat("pointRate[1]", pointLightRate[1]);

        // point light 3
        ourShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        ourShader.setVec3("pointLights[2].color", pointLightColor[2]);
        ourShader.setFloat("pointLights[2].constant", pointLightConstant[2]);
        ourShader.setFloat("pointLights[2].linear", pointLightLinear[2]);
        ourShader.setFloat("pointLights[2].quadratic", pointLightQuadratic[2]);
        ourShader.setFloat("pointRate[2]", pointLightRate[2]);

        // spotLight
        ourShader.setVec3("spotLight.position", spotLightPos);
        ourShader.setVec3("spotLight.color", spotLightColor);
        ourShader.setVec3("spotLight.direction", spotLightDirection);
        ourShader.setFloat("spotLight.constant", spotConstant);
        ourShader.setFloat("spotLight.linear", spotLinear);
        ourShader.setFloat("spotLight.quadratic", spotQuadratic);
        ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(spotCutOff)));
        ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(spotOuterCutOff)));
        ourShader.setFloat("spotLightRate", spotLightRate);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(modelScale, modelScale, modelScale));	
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        guiHelper.guiRenderBengin();
        ImGui::SliderFloat("mod scale", &modelScale, 0.01f, 2.0f);
        ImGui::SliderFloat("mod y rotation", &rotation, -180.0f, 180.0f);
        ImGui::SliderFloat("ambient", &ambient, 0.0f, 1.0f);
        ImGui::SliderFloat("diffuse", &diffuse, 0.0f, 1.0f);
        ImGui::SliderFloat("specular", &specular, 0.0f, 1.0f);
        ImGui::SliderFloat("shininess", &shiniess, 8.0f, 128.0f);
        ImGui::SliderFloat3("point rate", pointLightRate, 0.0f, 1.0f);
        ImGui::SliderFloat("dir rate", &dirLightRate, 0.0f, 1.0f);
        ImGui::SliderFloat("spot rate", &spotLightRate, 0.0f, 1.0f);
        ImGui::Checkbox("mouse enable", &enableMouse);
        guiHelper.guiRenderEnd();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    ourShader.clear();
    guiHelper.guiClear();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS) {
        firstMouse = true;
        return;
    }

    if (!enableMouse)
    {
        return;
    }

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}