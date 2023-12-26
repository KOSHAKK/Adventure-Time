#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Resources/ResourceManager.hpp"
#include "Render/ShaderProgram.hpp"
#include "Render/Texture2D.hpp"
#include "Render/Sprite.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Render/AnimatedSprite.hpp"


GLfloat point[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat texture_coords[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};



int g_windowSizeX = 640;
int g_windowSizeY = 480;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(const int argc, const char** argv)
{
    ResourceManager::init(argv[0]);
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Simple Game", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;


    glClearColor(1, 1, 0, 1);

    auto shader = ResourceManager::load_shader_program("default_shader", "res/Shaders/vs.vert", "res/Shaders/fs.frag");
    auto tex = ResourceManager::load_texture("tex", "res/Textures/Objects/Basic_Grass_Biom_things.png");




    std::vector<std::string> sub_textures_names{
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9"
    };

    std::vector<std::string> qwe{
        "6",
        "7",
        "8",
        "9"
    };


    auto atlas = ResourceManager::load_texture_atlas("defaultAtlas", "res/Textures/Objects/Basic_Grass_Biom_things.png", sub_textures_names, 16, 16);

    auto sp = ResourceManager::load_sprite("test_sprite", "default_shader", "defaultAtlas", 100, 100, "6");
    sp->set_position(glm::vec2(100, 100));
    sp->set_scale(glm::vec2(100, 100));


    auto zxc = Render::AnimatedSprite("defaultAtlas", qwe, "default_shader", 500, glm::vec2(100, 100), glm::vec2(100, 100));

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    GLuint texture_vbo = 0;
    glGenBuffers(1, &texture_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coords), texture_coords, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, texture_vbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    /* Loop until the user closes the window */

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(g_windowSizeX), 0.f, static_cast<float>(g_windowSizeY), -100.f, 100.f);

    shader->use();
    shader->set_matrix4("projection", projectionMatrix);

    glfwSwapInterval(1);

    float t;
    float t1 = glfwGetTime();
    while (!glfwWindowShouldClose(pWindow))
    {   
        glClear(GL_COLOR_BUFFER_BIT);

        float t2 = glfwGetTime();
        t = t2 - t1;
        t1 = glfwGetTime();
        //std::cout << static_cast<unsigned int>(t * 1000) << std::endl;


        
        sp->set_position(glm::vec2(100 * sin(glfwGetTime()) + 100, 100 * cos(glfwGetTime()) + 100));
        sp->set_rotate(360 * sin(glfwGetTime()));
        sp->render();

        zxc.update(static_cast<unsigned int>(t * 1000));
        zxc.render();
        zxc.set_position(glm::vec2(100 * sin(glfwGetTime()) + 100, 100 * -cos(glfwGetTime()) + 100));


        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}