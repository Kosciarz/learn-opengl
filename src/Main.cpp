#include "Engine.hpp"

#include <exception>
#include <print>

int main() {
    try {
        learn::Engine engine;
        engine.run();
    } catch (const std::exception& e) {
        std::println(stderr, "Error: {}", e.what());
    }
}
