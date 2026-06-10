#include "Engine.hpp"

int main() {
    learn::Engine engine;

    while (!glfwWindowShouldClose(engine.window())) {
        glfwSwapBuffers(engine.window());
        glfwPollEvents();
    }
}
