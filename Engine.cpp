#include "Processing.h"
#include <iostream>
#include <string>
#define BACKGROUND_VALUE __BACKGROUND__COLOR__.r, __BACKGROUND__COLOR__.g, __BACKGROUND__COLOR__.b, Processing::MaxColorValue

// static const char* vertex_shader_text =
// "#version 110\n"
// "attribute vec3 vCol;\n"
// "attribute vec2 vPos;\n"
// "varying vec3 color;\n"
// "void main()\n"
// "{\n"
// "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
// "    color = vCol;\n"
// "}\n";

// static const char* fragment_shader_text =
// "#version 110\n"
// "varying vec3 color;\n"
// "void main()\n"
// "{\n"
// "    gl_FragColor = vec4(color, 1.0);\n"
// "}\n";

static void error_callback(int error, const char *description)
{
    fputs(description, stderr);
}
static void print(std::string c)
{
    //std::cout<<c<<std::endl;
}
// void Processing::run()
// {
//     glfwSetErrorCallback(error_callback);
//     if (!glfwInit())
//         exit(EXIT_FAILURE);
//     window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);

//     if (!window)
//     {
//         glfwTerminate();
//         exit(EXIT_FAILURE);
//     }

//     glfwMakeContextCurrent(window);
//     glfwSetWindowUserPointer(window, this);

//     glfwSetKeyCallback(window, [](GLFWwindow *window_, int key, int scancode, int action, int mods) {
//         ((Processing *)glfwGetWindowUserPointer(window_))->onKeyEvent(key, scancode, action, mods);
//     });

//     glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window_, int w, int h) {
//         Processing *p = ((Processing *)glfwGetWindowUserPointer(window_));
//         //float scw,sch;
//         glfwGetFramebufferSize(window_, &p->width, &p->height);
//         //glfwGetWindowContentScale(window, &scw, &sch);
//         p->onResize(p->width, p->height);
//     });

//     glfwSetCursorPosCallback(window, [](GLFWwindow *window_, double x, double y) {
//         ((Processing *)glfwGetWindowUserPointer(window_))->onMouseMove(x, y);
//     });

//     setup();
//     glfwSwapInterval(1);
//     while (!glfwWindowShouldClose(window))
//     {
//         float ratio;
//         glfwGetFramebufferSize(window, &width, &height);

//         ratio = width / (float) height;

//         glViewport(0, 0, width, height);
//         glClear(GL_COLOR_BUFFER_BIT);
//         glMatrixMode(GL_PROJECTION);
//         glLoadIdentity();
//         glOrtho(0,width,height,0, 1.f, -1.f);
//         glMatrixMode(GL_MODELVIEW);
//         glLoadIdentity();

//         draw();

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }
//     glfwDestroyWindow(window);
//     glfwTerminate();
//     //exit(EXIT_SUCCESS);
// }

void Processing::run()
{
    //GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(width, height, "L", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    //glfwSetKeyCallback(window, key_callback);
    float ratio;
    glLineWidth(1);
    setup();
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, [](GLFWwindow *window_, int key, int scancode, int action, int mods) {
        ((Processing *)glfwGetWindowUserPointer(window_))->onKeyEvent(key, scancode, action, mods);
    });

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window_, int w, int h) {
        Processing *p = ((Processing *)glfwGetWindowUserPointer(window_));
        float scw, sch;
        glfwGetFramebufferSize(window_, &p->width, &p->height);
        glfwGetWindowContentScale(window_, &scw, &sch);
        p->width *= scw;
        p->height *= sch;
        p->onResize(p->width, p->height);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow *window_, double x, double y) {
        auto p = ((Processing *)glfwGetWindowUserPointer(window_));
        auto me = MouseEvent();
        me.x = x;
        me.y = y;
        me.dx = x - p->mouseX;
        me.dy = y - p->mouseY;
        p->mouseX = x;
        p->mouseY = y;
        p->onMouseMove(me);
    });

    // glfwSetMouseButtonCallback(window, [](GLFWwindow *window_, int button, int mode, int bits) {
    //     if (mode == GLFW_PRESS)
    //         ((Processing *)glfwGetWindowUserPointer(window_))->mousePressed();
    // });
    while (!glfwWindowShouldClose(window))
    {
        //glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}