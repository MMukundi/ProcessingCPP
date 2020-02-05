#include "Processing.h"
#include <iostream>
#include <string>
#define BACKGROUND_VALUE __BACKGROUND__COLOR__.r, __BACKGROUND__COLOR__.g, __BACKGROUND__COLOR__.b, Processing::MaxColorValue

static void error_callback(int error, const char *description)
{
    fputs(description, stderr);
}

void Processing::run()
{

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwSetErrorCallback(error_callback);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    float ratio;

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, [](GLFWwindow *window_, int key, int scancode, int action, int mods) {
        ((Processing *)glfwGetWindowUserPointer(window_))->onKeyEvent(key, scancode, action, mods);
    });

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window_, int w, int h) {
        Processing *p = ((Processing *)glfwGetWindowUserPointer(window_));
        glfwGetFramebufferSize(window_, &p->width, &p->height);
        // printf("(%f,%f)",scw,sch);
        // p->width *= scw;
        // p->height *= sch;
        p->onResize(p->width, p->height);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow *window_, double x, double y) {
        auto p = ((Processing *)glfwGetWindowUserPointer(window_));
        auto me = MouseEvent();
        float scw, sch;
        me.x = x;
        me.y = y;
        me.dx = x - p->mouseX;
        me.dy = y - p->mouseY;
        glfwGetWindowContentScale(window_, &scw, &sch);
        //printf("(%f,%f)",scw,sch);
        p->mouseX = x*scw;
        p->mouseY = y*sch;
        p->onMouseMove(me);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow *window_, int button, int mode, int bits) {
        if (mode == GLFW_PRESS)
            ((Processing *)glfwGetWindowUserPointer(window_))->mousePressed();
    });   

    glfwGetFramebufferSize(window, &width, &height);

    setup();


    while (!glfwWindowShouldClose(window))
    {

        ratio = width / (float)height;
        glViewport(0, 0, width, height);
        glClearColor(BACKGROUND_VALUE);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}