//
// Implementing Areal Lights with Linearly Transformed Cosines.
//
// Inspiration:
// https://advances.realtimerendering.com/s2016/s2016_ltc_rnd.pdf
// https://eheitzresearch.wordpress.com/415-2/

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>
//
#include <GL/glew.h>
//
#include <GL/gl.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
//
#include <GLFW/glfw3.h>
//
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//

#include <camera.h>
#include <entity.h>
#include <model.h>
#include <shader_common.h>
//
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// CUSTOM
#include "colors.hpp" // LOOK FOR DIFFERENT COLORS!
#include "ltc_matrix.hpp"

// FUNCTION PROTOTYPES
void         framebuffer_size_callback(GLFWwindow *window, int width, int height);
void         key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void         mouse_callback(GLFWwindow *window, double xpos, double ypos);
void         scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void         do_movement(GLfloat deltaTime);
unsigned int loadTexture(const char *path, bool gammaCorrection);
void         renderQuad();
void         renderCube();

// SETTINGS AND GLOBALS
const unsigned int SCR_WIDTH   = 800;
const unsigned int SCR_HEIGHT  = 600;
const glm::vec3    LIGHT_COLOR = Color::BurlyWood; // CHANGE AREA LIGHT COLOR HERE!
bool               keys[1024];                     // activated keys
glm::vec3          areaLightTranslate;
Shader            *ltcShaderPtr;

// camera
Camera camera(glm::vec3(0.0f, 1.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f);
float  lastX      = (float)SCR_WIDTH / 2.0;
float  lastY      = (float)SCR_HEIGHT / 2.0;
bool   firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//
// 2---3-5
// |  / /|
// | / / |
// |/ /  |
// 1-4---6
//
struct VertexAL {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texcoord;
};

const GLfloat psize            = 10.0f;
VertexAL      planeVertices[6] = {
    {{-psize, 0.0f, -psize}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    { {-psize, 0.0f, psize}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    {  {psize, 0.0f, psize}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{-psize, 0.0f, -psize}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {  {psize, 0.0f, psize}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    { {psize, 0.0f, -psize}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}
};
VertexAL areaLightVertices[6] = {
    {{-8.0f, 2.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 0 1 5 4
    { {-8.0f, 2.4f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    { {-8.0f, 0.4f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{-8.0f, 2.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    { {-8.0f, 0.4f, 1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{-8.0f, 0.4f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}
};

GLuint planeVBO, planeVAO;
GLuint areaLightVBO, areaLightVAO;

void configureMockupData() {
    // PLANE
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);

    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    // AREA LIGHT
    glGenVertexArrays(1, &areaLightVAO);
    glBindVertexArray(areaLightVAO);

    glGenBuffers(1, &areaLightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, areaLightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(areaLightVertices), areaLightVertices, GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // texcoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    glBindVertexArray(0);
}

void renderPlane() {
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void renderAreaLight() {
    glBindVertexArray(areaLightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

struct LTC_matrices {
    GLuint mat1;
    GLuint mat2;
};

GLuint loadMTexture() {
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_FLOAT, LTC1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

GLuint loadLUTTexture() {
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_FLOAT, LTC2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

void incrementRoughness(float step) {
    static glm::vec3 color     = Color::SlateGray;
    static float     roughness = 0.5f;
    roughness += step;
    roughness = glm::clamp(roughness, 0.0f, 1.0f);
    // std::cout << "roughness: " << roughness << '\n';
    ltcShaderPtr->use();
    ltcShaderPtr->setVec4("material.albedoRoughness", glm::vec4(color, roughness));
    glUseProgram(0);
}

void incrementLightIntensity(float step) {
    static float intensity = 4.0f;
    intensity += step;
    intensity = glm::clamp(intensity, 0.0f, 10.0f);
    // std::cout << "intensity: " << intensity << '\n';
    ltcShaderPtr->use();
    ltcShaderPtr->setFloat("areaLight.intensity", intensity);
    glUseProgram(0);
}

void switchTwoSided(bool doSwitch) {
    static bool twoSided = true;
    if (doSwitch)
        twoSided = !twoSided;
    // std::cout << "twoSided: " << std::boolalpha << twoSided << '\n';
    ltcShaderPtr->use();
    ltcShaderPtr->setFloat("areaLight.twoSided", twoSided);
    glUseProgram(0);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    //   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Window   *window  = SDL_CreateWindow("8-guest/2022/7-area_lights/1-area_light", SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL);
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

    // LUT textures
    LTC_matrices mLTC;
    mLTC.mat1 = loadMTexture();
    mLTC.mat2 = loadLUTTexture();

    // SHADERS
    Shader shaderLTC("7.area_light.vs", "7.area_light.fs", nullptr, nullptr, nullptr);
    ltcShaderPtr = &shaderLTC;
    Shader shaderLightPlane("7.light_plane.vs", "7.light_plane.fs", nullptr, nullptr, nullptr);

    // TEXTURES
    unsigned int concreteTexture = loadTexture("../../../../resources/textures/concreteTexture.png", true);

    // SHADER CONFIGURATION
    shaderLTC.use();
    shaderLTC.setVec3("areaLight.points[0]", areaLightVertices[0].position);
    shaderLTC.setVec3("areaLight.points[1]", areaLightVertices[1].position);
    shaderLTC.setVec3("areaLight.points[2]", areaLightVertices[4].position);
    shaderLTC.setVec3("areaLight.points[3]", areaLightVertices[5].position);
    shaderLTC.setVec3("areaLight.color", LIGHT_COLOR);
    shaderLTC.setInt("LTC1", 0);
    shaderLTC.setInt("LTC2", 1);
    shaderLTC.setInt("material.diffuse", 2);
    incrementRoughness(0.0f);
    incrementLightIntensity(0.0f);
    switchTwoSided(false);
    glUseProgram(0);

    shaderLightPlane.use();
    {
        glm::mat4 model(1.0f);
        shaderLightPlane.setMat4("model", model);
    }
    shaderLightPlane.setVec3("lightColor", LIGHT_COLOR);
    glUseProgram(0);

    // 3D OBJECTS
    configureMockupData();
    areaLightTranslate = glm::vec3(0.0f, 0.0f, 0.0f);

    static unsigned short wireframe = 0;

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
                float sensitivity = 0.9f;
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

        //-------------------------------------------------------------------------------------------------------------

        if (keys[SDL_SCANCODE_R]) {
            if (keys[SDL_SCANCODE_LSHIFT]) {
                incrementRoughness(0.01f);
            } else {
                incrementRoughness(-0.01f);
            }
        }

        if (keys[SDL_SCANCODE_I]) {
            if (keys[SDL_SCANCODE_LSHIFT]) {
                incrementLightIntensity(0.025f);
            } else {
                incrementLightIntensity(-0.025f);
            }
        }

        if (keys[SDL_SCANCODE_LEFT]) {
            areaLightTranslate.z += 0.01f;
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
            areaLightTranslate.z -= 0.01f;
        }
        if (keys[SDL_SCANCODE_UP]) {
            areaLightTranslate.y += 0.01f;
        }
        if (keys[SDL_SCANCODE_DOWN]) {
            areaLightTranslate.y -= 0.01f;
        }

        if (keys[SDL_SCANCODE_B]) {
            switchTwoSided(true);
        }

        if (keys[SDL_SCANCODE_SPACE]) {
            if (wireframe == 0) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                wireframe = 1;
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                wireframe = 0;
            }
        }

        //
        if (!run) {
            break;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderLTC.use();
        glm::mat4 model(1.0f);
        glm::mat3 normalMatrix = glm::mat3(model);
        shaderLTC.setMat4("model", model);
        shaderLTC.setMat3("normalMatrix", normalMatrix);
        glm::mat4 view = camera.GetViewMatrix();
        shaderLTC.setMat4("view", view);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shaderLTC.setMat4("projection", projection);
        shaderLTC.setVec3("viewPosition", camera.Position);
        shaderLTC.setVec3("areaLightTranslate", areaLightTranslate);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mLTC.mat1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mLTC.mat2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, concreteTexture);
        renderPlane();
        glUseProgram(0);

        shaderLightPlane.use();
        model = glm::translate(model, areaLightTranslate);
        shaderLightPlane.setMat4("model", model);
        shaderLightPlane.setMat4("view", view);
        shaderLightPlane.setMat4("projection", projection);
        renderAreaLight();
        glUseProgram(0);

        currentTime = SDL_GetTicks();
        SDL_Delay(17);
        SDL_GL_SwapWindow(window);
    }

    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &planeVBO);
    glDeleteVertexArrays(1, &areaLightVAO);
    glDeleteBuffers(1, &areaLightVBO);

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const *path, bool gammaCorrection) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int            width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum internalFormat;
        GLenum dataFormat;
        if (nrComponents == 1) {
            internalFormat = dataFormat = GL_RED;
        } else if (nrComponents == 3) {
            internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
            dataFormat     = GL_RGB;
        } else if (nrComponents == 4) {
            internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
            dataFormat     = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
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
