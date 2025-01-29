/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
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
#include "game.h"
#include "resource_manager.h"
//
#include <SDL3/SDL_keyboard.h>
#include <iostream>

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

// The Width of the screen
const unsigned int SCREEN_WIDTH  = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Window   *window  = SDL_CreateWindow("7-in_practice/3-2d_game/0-full_source", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_SetWindowMinimumSize(window, 200, 200);
    SDL_GL_MakeCurrent(window, context);
    glewExperimental = GL_TRUE;
    glewInit();
    SDL_Event event;
    bool      run = true;

    // glfwSetKeyCallback(window, key_callback);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize game
    // ---------------
    Breakout.Init();

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

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
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                run = false;
                break;
            }
        }

        auto keys = SDL_GetKeyboardState(nullptr);

        if (keys[SDL_SCANCODE_ESCAPE]) {
            run = false;
        }

        if (!run) {
            break;
        }

        // manage user input
        // -----------------
        // Breakout.ProcessInput(deltaTime);

        if (Breakout.State == GAME_MENU) {

            if (keys[SDL_SCANCODE_RETURN]) {
                Breakout.State = GAME_ACTIVE;
            }

            if (keys[SDL_SCANCODE_W]) {
                Breakout.Level = (Breakout.Level + 1) % 4;
            }

            if (keys[SDL_SCANCODE_S]) {
                if (Breakout.Level > 0) {
                    --Breakout.Level;
                } else {
                    Breakout.Level = 3;
                }
                // this->Level = (this->Level - 1) % 4;
            }
        }
        if (Breakout.State == GAME_ACTIVE) {
            float velocity = PLAYER_VELOCITY * deltaTime; //*delta;
            // move playerboard
            if (keys[SDL_SCANCODE_A]) {
                if (Breakout.Player->Position.x >= 0.0f) {
                    Breakout.Player->Position.x -= velocity;
                    if (Breakout.Ball->Stuck)
                        Breakout.Ball->Position.x -= velocity;
                }
            }
            if (keys[SDL_SCANCODE_D]) {
                if (Breakout.Player->Position.x <= Breakout.Width - Breakout.Player->Size.x) {
                    Breakout.Player->Position.x += velocity;
                    if (Breakout.Ball->Stuck)
                        Breakout.Ball->Position.x += velocity;
                }
            }
            if (keys[SDL_SCANCODE_SPACE]) {
                Breakout.Ball->Stuck = false;
            }
        }

        if (Breakout.State == GAME_WIN) {
        }

        // update game state
        // -----------------
        Breakout.Update(deltaTime);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render(delta);

        currentTime = SDL_GetTicks();
        SDL_Delay(17);
        SDL_GL_SwapWindow(window);
    }

    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    ResourceManager::Clear();

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            Breakout.Keys[key] = true;
        else if (action == GLFW_RELEASE) {
            Breakout.Keys[key]          = false;
            Breakout.KeysProcessed[key] = false;
        }
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}