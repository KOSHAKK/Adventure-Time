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



glm::vec2 window_size(640*2, 480*2);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    window_size.x = width;
    window_size.y = height;
    glViewport(0, 0, window_size.x, window_size.y);
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
    GLFWwindow* pWindow = glfwCreateWindow(window_size.x, window_size.y, "Simple Game", nullptr, nullptr);
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

    

    std::vector<std::string> sub_textures_names{
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10",
        "11",
        "12",
        "13",
        "14",
        "15",
        "16",
        "17",
        "18",
        "19",
        "20",
        "21",
        "22",
        "23",
        "24"
    };

    auto shader = ResourceManager::load_shader_program("default_shader", "res/Shaders/vs.vert", "res/Shaders/fs.frag");

    auto atlas = ResourceManager::load_texture_atlas("defaultAtlas", "res/Textures/Main Characters/Virtual Guy/DinoSprites - doux.png", sub_textures_names, 24, 24);

    ResourceManager::load_sprite("NewSpite", "default_shader", "defaultAtlas", 78, 58, "1");

    

    auto animatedSprite = ResourceManager::load_animated_sprite("zxc1", "defaultAtlas", "default_shader", 200, 200, "1");
    animatedSprite->set_position(glm::vec2(300, 300));
    std::vector<std::pair<std::string, uint64_t>> state;
    state.emplace_back(std::make_pair<std::string, uint64_t>("5", 100));
    state.emplace_back(std::make_pair<std::string, uint64_t>("6", 100));
    state.emplace_back(std::make_pair<std::string, uint64_t>("7", 100));
    state.emplace_back(std::make_pair<std::string, uint64_t>("8", 100));
    state.emplace_back(std::make_pair<std::string, uint64_t>("9", 100));
    state.emplace_back(std::make_pair<std::string, uint64_t>("10", 100));
    state.emplace_back(std::make_pair<std::string, uint64_t>("11", 100));


    animatedSprite->insertState("st", state);
    animatedSprite->setState("st");

   
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

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(window_size.x), 0.f, static_cast<float>(window_size.y), -100.f, 100.f);

    shader->use();
    shader->set_matrix4("projection", projectionMatrix);

    glfwSwapInterval(1);


    unsigned int delta;
    float t1 = glfwGetTime();
    while (!glfwWindowShouldClose(pWindow))
    {   
        glClear(GL_COLOR_BUFFER_BIT);

        float t2 = glfwGetTime();
        delta = static_cast<unsigned int>((t2 - t1) * 1000);
        t1 = glfwGetTime();

        //animatedSprite->set_position(glm::vec2(40 * cos(glfwGetTime()) + 200, 200));
        animatedSprite->update(delta);
        animatedSprite->render();




        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}