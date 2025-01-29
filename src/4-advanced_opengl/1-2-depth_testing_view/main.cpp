#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
//
#include <GL/glew.h>
//
#include <GL/gl.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
//
#include <GLFW/glfw3.h>
//
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//
#include <camera.h>
#include <model.h>
#include <shader.h>
#include <shader_m.h>
//
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <map>

// settings
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float  lastX      = (float)SCR_WIDTH / 2.0;
float  lastY      = (float)SCR_HEIGHT / 2.0;
bool   firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const *path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int            width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Window   *window  = SDL_CreateWindow("4-advanced_opengl/1-2-depth_testing_view", SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_SetWindowMinimumSize(window, 200, 200);
    SDL_GL_MakeCurrent(window, context);
    glewExperimental = GL_TRUE;
    glewInit();
    SDL_Event event;
    bool      run = true;

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // build and compile shaders
    // -------------------------
    Shader shader("1.2.depth_testing.vs", "1.2.depth_testing.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cubeVertices[] = {

        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,  0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,
        0.5f,  -0.5f, 1.0f,  1.0f, -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f, -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,  0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,
        0.5f,  0.5f,  1.0f,  1.0f, -0.5f, 0.5f,  0.5f,  0.0f,  1.0f, -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,  -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,  -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f,
        -0.5f, -0.5f, 0.0f,  1.0f, -0.5f, -0.5f, 0.5f,  0.0f,  0.0f, -0.5f, 0.5f,  0.5f,  1.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,  0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,
        -0.5f, -0.5f, 0.0f,  1.0f, 0.5f,  -0.5f, 0.5f,  0.0f,  0.0f, 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,  0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,
        -0.5f, 0.5f,  1.0f,  0.0f, -0.5f, -0.5f, 0.5f,  0.0f,  0.0f, -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f,  0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,
        0.5f,  0.5f,  1.0f,  0.0f, -0.5f, 0.5f,  0.5f,  0.0f,  0.0f, -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f

    };
    float planeVertices[] = {

        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this
        // will cause the floor texture to repeat)
        5.0f, -0.5f, 5.0f,  2.0f,  0.0f,  -5.0f, -0.5f, 5.0f,
        0.0f, 0.0f,  -5.0f, -0.5f, -5.0f, 0.0f,  2.0f,

        5.0f, -0.5f, 5.0f,  2.0f,  0.0f,  -5.0f, -0.5f, -5.0f,
        0.0f, 2.0f,  5.0f,  -0.5f, -5.0f, 2.0f,  2.0f

    };
    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);
    // plane VAO
    unsigned int planeVAO, planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);

    // load textures
    // -------------
    unsigned int cubeTexture  = loadTexture("../../resources/textures/marble.jpg");
    unsigned int floorTexture = loadTexture("../../resources/textures/metal.png");

    // shader configuration
    // --------------------
    shader.use();
    shader.setInt("texture1", 0);

    unsigned int currentTime       = SDL_GetTicks();
    float        cameraSpeedFactor = 1;
    // render loop
    // -----------
    while (run) {
        // per-frame time logic
        // --------------------
        float delta        = std::lerp(currentTime, currentTime + 100, 0.01f) / 1000;
        float currentFrame = static_cast<float>(delta);
        deltaTime          = currentFrame - lastFrame;
        lastFrame          = currentFrame;

        // input
        // -----
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                run = false;
                break;
            }

            if (event.type == SDL_EVENT_MOUSE_WHEEL) {
                camera.ProcessMouseScroll(static_cast<float>(event.wheel.y));
            }

            if (event.type == SDL_EVENT_MOUSE_MOTION) {

                if (event.button.button != SDL_BUTTON_LEFT) {
                    continue;
                }

                float xoffset = event.motion.xrel;
                float yoffset = -event.motion.yrel;

                // change this value to your liking
                float sensitivity = 0.5f;
                xoffset *= sensitivity;
                yoffset *= sensitivity;

                camera.ProcessMouseMovement(xoffset, yoffset);
            }
        }

        auto keys = SDL_GetKeyboardState(nullptr);

        if (keys[SDL_SCANCODE_ESCAPE]) {
            run = false;
        }
        if (keys[SDL_SCANCODE_W]) {
            camera.ProcessKeyboard(FORWARD, deltaTime);
        }
        if (keys[SDL_SCANCODE_S]) {
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        }
        if (keys[SDL_SCANCODE_A]) {
            camera.ProcessKeyboard(LEFT, deltaTime);
        }
        if (keys[SDL_SCANCODE_D]) {
            camera.ProcessKeyboard(RIGHT, deltaTime);
        }

        // --------------------------------------------------------------------------------------------------------

        if (!run) {
            break;
        }

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 model      = glm::mat4(1.0f);
        glm::mat4 view       = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        // cubes
        glBindVertexArray(cubeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTexture);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // floor
        glBindVertexArray(planeVAO);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        shader.setMat4("model", glm::mat4(1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        currentTime = SDL_GetTicks();
        SDL_Delay(17);
        SDL_GL_SwapWindow(window);
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &planeVBO);

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
