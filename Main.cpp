#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shaders.h"
#include "Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool firstMouse = 1;
float lastx = 500.0f;
float lasty = 500.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastx = xpos;
        lasty = ypos;
        firstMouse = 0;
    }
    float xoffset = lastx - xpos;
    float yoffset = lasty - ypos;
    lastx = xpos;
    lasty = ypos;
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset,double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(-yoffset));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "-1" << std::endl;
    }

    std::cout << glGetString(GL_VERSION)<<std::endl;

    //Declar colturile cubului

    float puncte[] = {
        //fata
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        //dreapta
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        //spate
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        //stanga
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        //sus
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        //jos
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    
    //declar pozitiile la 10 cuburi, pe care le vom render-ui

    float positions[] = {
        0.0f,  0.0f,  0.0f,
        2.0f,  5.0f, -15.0f,
        -1.5f, -2.2f, -2.5f,
        -3.8f, -2.0f, -12.3f,
        2.4f, -0.4f, -3.5f,
        -1.7f,  3.0f, -7.5f,
        1.3f, -2.0f, -2.5f,
        1.5f,  2.0f, -2.5f,
        1.5f,  0.2f, -1.5f,
        -1.3f,  1.0f, -1.5f
    };

    float materials[] = {
        0.0215,	0.1745,	0.0215,	0.07568, 0.61424, 0.07568, 0.633, 0.727811, 0.633, 0.6,
        0.05375, 0.05, 0.06625, 0.18275, 0.17, 0.22525, 0.332741, 0.328634, 0.346435, 0.3,
        0.2125, 0.1275, 0.054, 0.714, 0.4284, 0.18144, 0.393548, 0.271906, 0.166721, 0.2,
        0.25, 0.25, 0.25, 0.4, 0.4, 0.4, 0.774597, 0.774597, 0.774597, 0.6,
        0.0, 0.05, 0.05, 0.4, 0.5, 0.5, 0.04, 0.7, 0.7, 0.078125
    };

    float lightCubePos[] = {
        -3.0f,-3.0f,-8.0f,
        -3.0f,-3.0f,1.0f,
        3.0f,-3.0f,-8.0f,
        3.0f,-3.0f,1.0f
    };

    Shader Material("Shaders/vsMaterial.txt", "Shaders/fsMaterial.txt");
    Shader Texturi("Shaders/vsTexturi.txt", "Shaders/fsTexturi.txt");
    Shader CubLumina("Shaders/vsLight.txt", "Shaders/fsLight.txt");

    unsigned int buffer,VAO,lightVAO;
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &buffer);
    //glGenBuffers(1, &elementBuffer);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(puncte), puncte, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, 0, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(puncte), puncte, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //lucru cu texturi

    int width, height, nrculori;
    unsigned char* tex = stbi_load("container2.png", &width, &height, &nrculori, 0);


    unsigned int texture1, texture2;

    glGenTextures(1, &texture1);
    glGenTextures(1, &texture2);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex);
    tex = stbi_load("container2_specular.png", &width, &height, &nrculori, 0);
    //std::cout << tex << std::endl;
    glActiveTexture(GL_TEXTURE1);

    glBindTexture(GL_TEXTURE_2D, texture2);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex);
    Texturi.use();
    Texturi.setInt("material.diffuse", 0);
    Texturi.setInt("material.specular", 1);
    //CubLumina.use();
    //Material.use();

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glm::mat4 model;
    int modelLoc = glGetUniformLocation(Texturi.ID, "model");
    int modelLocL = glGetUniformLocation(CubLumina.ID, "model");
    glm::mat4 view = glm::mat4(1.0f);
    int viewLoc = glGetUniformLocation(Texturi.ID, "view");
    int viewLocL = glGetUniformLocation(CubLumina.ID, "view");
    glm::mat4 projection = glm::mat4(1.0f);
    int projectionLoc = glGetUniformLocation(Texturi.ID, "projection");
    int projectionLocL = glGetUniformLocation(CubLumina.ID, "projection");
    int lightPosLoc = glGetUniformLocation(Texturi.ID, "light.lightPos");
    int viewPosLoc = glGetUniformLocation(Texturi.ID, "viewPos");
    float angle = 0.0f;
    glm::vec3 lightPos;
    /* Loop until the user closes the window */
    Texturi.setFloat("material.shininess", 32);
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        //Seteaza shader-ul utilizat la cel creat acum si array-ul cu obiectul nostru
        Texturi.use();
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        projection = glm::perspective(glm::radians(camera.Fov), 1.0f, 0.1f, 100.0f);
        glUniformMatrix4fv(projectionLoc, 1, 0, glm::value_ptr(projection));
        view = camera.GetViewMatrix();
        glUniformMatrix4fv(viewLoc, 1, 0, glm::value_ptr(view));
        Texturi.setVec3("viewPos", camera.Position);
        glBindVertexArray(VAO);
        for (int i = 0; i < 10; i++) {
            model = glm::mat4(1.0f);
            angle = 20.0f * i;
            model = glm::translate(model, glm::vec3(positions[3*i], positions[3*i + 1], positions[3*i + 2]));
            model = glm::rotate(model, glm::radians(angle), glm::vec3(0.57735f, 0.57735f, 0.57735f));
            glUniformMatrix4fv(modelLoc, 1, 0, glm::value_ptr(model));
            //glm::vec3 ambientColor = glm::vec3(materials[i % 5 * 10], materials[i % 5 * 10 + 1], materials[i % 5 * 10 + 2]);
            //Material.setVec3("block.ambient", ambientColor);
            //glm::vec3 diffuseColor = glm::vec3(materials[i % 5 * 10 + 3], materials[i % 5 * 10 + 4], materials[i % 5 * 10 + 5]);
            //Material.setVec3("block.diffuse", diffuseColor);
            //glm::vec3 specColor = glm::vec3(materials[i % 5 * 10 + 6], materials[i % 5 * 10 + 7], materials[i % 5 * 10 + 8]);
            //Material.setVec3("block.specular", specColor);
            //Material.setFloat("block.shininess", 128 * materials[i % 5 * 10 + 9]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        float lightC = 1.0f;
        glm::vec3 lightAmb = glm::vec3(0.2f*lightC, 0.2f*lightC, 0.2f*lightC);
        glm::vec3 lightDiff = glm::vec3(0.6f*lightC, 0.6f*lightC, 0.6f*lightC);
        glm::vec3 lightSpec = glm::vec3(1.0f*lightC, 1.0f*lightC, 1.0f*lightC);
        Texturi.setVec3("light.lightAmbient", lightAmb);
        Texturi.setVec3("light.lightDiffuse", lightDiff);
        Texturi.setVec3("light.lightSpecular", lightSpec);
        Texturi.setFloat("cub[0].constant", 1.0f);
        Texturi.setFloat("cub[0].linear", 0.14f);
        Texturi.setFloat("cub[0].quadratic", 0.07f);
        lightPos = camera.Position;
        Texturi.setVec3("light.lightPos", lightPos);
        Texturi.setVec3("light.lightDir", camera.Front);
        Texturi.setFloat("light.lightCosInner", (float)glm::cos(glm::radians(12.5f)));
        Texturi.setFloat("light.lightCosOuter", (float)glm::cos(glm::radians(15.0f)));
        Texturi.setVec3("cub[0].lightAmbient", lightAmb);
        Texturi.setVec3("cub[0].lightDiffuse", lightDiff);
        Texturi.setVec3("cub[0].lightSpecular", lightSpec);
        Texturi.setVec3("cub[1].lightAmbient", lightAmb);
        Texturi.setVec3("cub[1].lightDiffuse", lightDiff);
        Texturi.setVec3("cub[1].lightSpecular", lightSpec);
        Texturi.setFloat("cub[1].constant", 1.0f);
        Texturi.setFloat("cub[1].linear", 0.14f);
        Texturi.setFloat("cub[1].quadratic", 0.07f);
        Texturi.setVec3("cub[2].lightAmbient", lightAmb);
        Texturi.setVec3("cub[2].lightDiffuse", lightDiff);
        Texturi.setVec3("cub[2].lightSpecular", lightSpec);
        Texturi.setFloat("cub[2].constant", 1.0f);
        Texturi.setFloat("cub[2].linear", 0.14f);
        Texturi.setFloat("cub[2].quadratic", 0.07f);
        Texturi.setVec3("cub[3].lightAmbient", lightAmb);
        Texturi.setVec3("cub[3].lightDiffuse", lightDiff);
        Texturi.setVec3("cub[3].lightSpecular", lightSpec);
        Texturi.setFloat("cub[3].constant", 1.0f);
        Texturi.setFloat("cub[3].linear", 0.14f);
        Texturi.setFloat("cub[3].quadratic", 0.07f);
        glm::vec3 cuburi;
        cuburi = glm::vec3(-3.0f, -3.0f, -8.0f);
        Texturi.setVec3("cub[0].lightPos", cuburi);
        cuburi = glm::vec3(-3.0f, -3.0f, 1.0f);
        Texturi.setVec3("cub[1].lightPos", cuburi);
        cuburi = glm::vec3(3.0f, -3.0f, -8.0f);
        Texturi.setVec3("cub[2].lightPos", cuburi);
        cuburi = glm::vec3(3.0f, -3.0f, 1.0f);
        Texturi.setVec3("cub[3].lightPos", cuburi);

        CubLumina.use();
        for (int i = 0; i < 4; i++) {
            glm::vec3 lightColor = glm::vec3(lightC, lightC, lightC);
            CubLumina.setVec3("lightColor", lightColor);
            glBindVertexArray(lightVAO);
            glUniformMatrix4fv(projectionLocL, 1, 0, glm::value_ptr(projection));
            glUniformMatrix4fv(viewLocL, 1, 0, glm::value_ptr(view));
            lightPos = glm::vec3(lightCubePos[3 * i], lightCubePos[3 * i + 1], lightCubePos[3 * i + 2]);
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.2f));
            glUniformMatrix4fv(modelLocL, 1, 0, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        //inchide fereastra la apasare pe esc,si determina inputurile pentru fereastra
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

    glfwTerminate();
    return 0;
}