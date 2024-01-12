#include <glad/glad.h>

#include <iostream>

#include "Resources/ResourceManager.hpp"
#include "Render/ShaderProgram.hpp"
#include "Render/Texture2D.hpp"
#include "Render/Sprite.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Render/AnimatedSprite.hpp"
#include "Game/Game.hpp"
#include "Physics/PhysicsEngine.hpp"
#include "System/KeyState.hpp"
#include "System/Keys.hpp"

#include <GLFW/glfw3.h>

std::unique_ptr<Game> game = std::make_unique<Game>();

glm::uvec2 window_size(64 * 3 * 6, 64 * 3 * 4 - 64);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    window_size.x = width;
    window_size.y = height;
    game->set_window_size(window_size);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
    KeyState::set_key_state(static_cast<Keys>(key), action);
}



int main(const int argc, const char** argv)
{
#pragma region INIT_OPNEGL_AND_GLFW
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* pWindow = glfwCreateWindow(window_size.x, window_size.y, "Adventure Time", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
#pragma endregion


    glClearColor(1, 1, 0, 1);
    

    ResourceManager::init(argv[0]);
    PhysicsEngine::init();
    game->init(window_size);

    glfwSwapInterval(1);


    unsigned int delta;
    float t1 = static_cast<float>(glfwGetTime());
    while (!glfwWindowShouldClose(pWindow))
    {   
        glClear(GL_COLOR_BUFFER_BIT);

        float t2 = static_cast<float>(glfwGetTime());
        delta = static_cast<unsigned int>((t2 - t1) * 1000);
        t1 = static_cast<float>(glfwGetTime());



        game->update(delta);
        PhysicsEngine::update(delta);
        game->render();




        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}