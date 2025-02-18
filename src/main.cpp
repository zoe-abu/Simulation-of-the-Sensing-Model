// main.cpp

#include <iostream>
#include <filesystem> // C++17 filesystem
#include <sstream>    // For std::ostringstream
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h> // Corrected include path

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common/Utils.h"   // Assumed to contain utility functions like initGLFW, isImageFile, etc.
#include "common/Shader.h"  // Shader class
#include "common/Camera.h"  // Camera class

// Use the standard filesystem namespace
namespace fs = std::filesystem;

// // Screen settings
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;

// Function declarations
void myProcessInput(GLFWwindow *window);

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Lighting parameters
const float ambientStart = 0.12f, ambientEnd = 0.12f, ambientStep = 0.02f;
const float diffuseStart = 0.15f, diffuseEnd = 0.15f, diffuseStep = 0.05f;
const float specularStart = 0.05f, specularEnd = 0.3f, specularStep = 0.05f;
const float linearStart = 0.09f, linearEnd = 0.09f, linearStep = 0.15f;
const float quadraticStart = 0.03f, quadraticEnd = 0.03f, quadraticStep = 0.01f;
const float shininessStart = 5.0f, shininessEnd = 5.0f, shininessStep = 16.0f;


const int NUM_ITERATIONS = 8;
int main()
{
    // Initialize GLFW
    GLFWwindow* window = initGLFW("MultiLight");
    if (!window)
    {
        return -1;
    }

    // Tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);

    // Build and compile our shader programs
    Shader ourShader("resource/shader.vs", "resource/shader.fs");
    Shader lampShader("resource/lamp.vs", "resource/lamp.fs");

    // Set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
        // positions          // normals           // texture coords
        -2.0f, -2.0f,  2.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         2.0f, -2.0f,  2.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         2.0f,  2.0f,  2.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         2.0f,  2.0f,  2.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -2.0f,  2.0f,  2.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -2.0f, -2.0f,  2.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    };

    // Create cube VAO
    unsigned int cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    // Create VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Create lamp VAO
    unsigned int lampVAO;
    glGenVertexArrays(1, &lampVAO);
    glBindVertexArray(lampVAO);
    // Reuse VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Reset state
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Positions of all containers
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, -0.0f)
    };

    // Define input and output folder paths
    const std::string inputFolder = "G:/NC_distance_data/palmprint_gray";    // Input images
    const std::string baseOutputFolder = "G:/NC_distance_data/stimulates_illus"; // Output folder

    // Point light positions and offsets
    glm::vec3 pointLightPositions[NUM_ITERATIONS];

    glm::vec3 pointLightOffsets[] = {
        glm::vec3( 1.0f,  0.0f,   0.0f),
        glm::vec3( 0.71f, 0.71f,  0.0f),
        glm::vec3( 0.0f,  1.0f,   0.0f),
        glm::vec3(-0.71f, 0.71f,  0.0f),
        glm::vec3(-1.0f,  0.0f,   0.0f),
        glm::vec3(-0.71f, -0.71f, 0.0f),
        glm::vec3( 0.0f,  -1.0f,  0.0f),
        glm::vec3( 0.71f, -0.71f, 0.0f),
    };


    // Define start and end distances
    float startDistance = 5.0f;
    float endDistance = 14.0f;
    float stepDistance = 1.0f;

    // Render loop: iterate over lighting parameters
    for (float ambientValue = ambientStart; ambientValue <= ambientEnd; ambientValue += ambientStep) {
        for (float diffuseValue = diffuseStart; diffuseValue <= diffuseEnd; diffuseValue += diffuseStep) {
            for (float specularValue = specularStart; specularValue <= specularEnd; specularValue += specularStep) {
                for (float linear = linearStart; linear <= linearEnd; linear += linearStep) {
                    for (float quadratic = quadraticStart; quadratic <= quadraticEnd; quadratic += quadraticStep) {
                        for (float shininess = shininessStart; shininess <= shininessEnd; shininess += shininessStep) {
                            // Construct output folder path
                            std::ostringstream folderPathStream;
                            folderPathStream << baseOutputFolder
                                             << "/ambient_" << ambientValue
                                             << "_diffuse_" << diffuseValue
                                             << "_specular_" << specularValue
                                             << "_linear_" << linear
                                             << "_quadratic_" << quadratic
                                             << "_shininess_" << shininess;
                            std::string outputFolder = folderPathStream.str();

                            // Check and create output folder if it doesn't exist
                            if (!fs::exists(outputFolder))
                            {
                                fs::create_directory(outputFolder);
                            }

                            // Iterate over input images
                            for (const auto& entry : fs::directory_iterator(inputFolder))
                            {
                                std::string imagePath = entry.path().string();
                                if (isImageFile(imagePath))
                                {
                                    std::string fileName = entry.path().stem().string();

                                    // Load textures
                                    unsigned int textureDiffuse = loadTexture(imagePath.c_str());
                                    unsigned int textureSpecular = loadTexture(imagePath.c_str());

                                    // Initialize image index
                                    int imageIndex = 0;

                                    // Initialize pointLightPositions
                                    for (int i = 0; i < NUM_ITERATIONS; i++) {
                                        pointLightPositions[i] = camera.Position + pointLightOffsets[i];
                                    }

                                    // Loop over distances
                                    for (float currentDistance = startDistance; currentDistance <= endDistance; currentDistance += stepDistance) {
                                        float distance = currentDistance;

                                        // Update camera position
                                        camera.Position = glm::vec3(0.0f, 0.0f, 0.0f) - camera.Front * distance;

                                        // Update point light positions
                                        for (int i = 0; i < NUM_ITERATIONS; i++) {
                                            pointLightPositions[i] = camera.Position + pointLightOffsets[i];
                                        }

                                        // Process input
                                        myProcessInput(window);

                                        // Render
                                        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                                        ourShader.use();
                                        ourShader.setInt("material.diffuse", 0);
                                        ourShader.setInt("material.specular", 1);
                                        ourShader.setVec3f("viewPos", glm::value_ptr(camera.Position));

                                        const int numPointLights = 10;
                                        // Set point lights
                                        for (int i = 0; i < numPointLights; ++i) {
                                            std::string base = "pointLights[" + std::to_string(i) + "].";
                                            ourShader.setVec3f(base + "position", glm::value_ptr(pointLightPositions[i]));
                                            ourShader.setVec3f(base + "ambient", ambientValue, ambientValue, ambientValue);
                                            ourShader.setVec3f(base + "diffuse", diffuseValue, diffuseValue, diffuseValue);
                                            ourShader.setVec3f(base + "specular", specularValue, specularValue, specularValue);
                                            ourShader.setFloat(base + "constant", 1.0f);
                                            ourShader.setFloat(base + "linear", linear);
                                            ourShader.setFloat(base + "quadratic", quadratic);
                                        }

                                        // Material properties
                                        ourShader.setFloat("material.shininess", shininess);

                                        // Bind diffuse map
                                        glActiveTexture(GL_TEXTURE0);
                                        glBindTexture(GL_TEXTURE_2D, textureDiffuse);
                                        glActiveTexture(GL_TEXTURE1);
                                        glBindTexture(GL_TEXTURE_2D, textureSpecular);

                                        // Create transformations
                                        glm::mat4 view = camera.GetViewMatrix();
                                        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
                                        ourShader.setMatrix4fv("view", glm::value_ptr(view));
                                        ourShader.setMatrix4fv("projection", glm::value_ptr(projection));

                                        // Calculate the model matrix for each object and pass it to shader before drawing
                                        glm::mat4 model = glm::mat4(1.0f);
                                        model = glm::translate(model, cubePositions[0]);
                                        ourShader.setMatrix4fv("model", glm::value_ptr(model));

                                        // Render the cube
                                        glBindVertexArray(cubeVAO);
                                        glDrawArrays(GL_TRIANGLES, 0, 36);


                                        // Also draw the lamp object (if needed)
                                        lampShader.use();
                                        lampShader.setMatrix4fv("view", glm::value_ptr(view));
                                        lampShader.setMatrix4fv("projection", glm::value_ptr(projection));

                                        // Update point light positions in shader
                                        for (int i = 0; i < numPointLights; i++) {
                                            // Update positions if necessary
                                        }

                                        // Save framebuffer to image
                                        char outputFile[512];
                                        snprintf(outputFile, sizeof(outputFile), "%s/%s_%03d.png", outputFolder.c_str(), fileName.c_str(), imageIndex++);
                                        saveFramebufferToImage(outputFile, SCR_WIDTH, SCR_HEIGHT);

                                        // GLFW: swap buffers and poll IO events
                                        glfwSwapBuffers(window);
                                        glfwPollEvents();
                                    }

                                    // Clean up textures
                                    glDeleteTextures(0, &textureDiffuse);
                                    glDeleteTextures(1, &textureSpecular);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Clean up resources
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lampVAO);
    glDeleteBuffers(1, &VBO);
    ourShader.clear();
    lampShader.clear();

    // Terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void myProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Camera controls (if needed)
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}
