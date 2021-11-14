#pragma once

#include "glfw_input.hpp"


KeyboardKeyState ConvertFromGlfwKeyState(int state);
int ConvertToGlfwKeyState(KeyboardKeyState state);

KeyboardKey ConvertFromGlfwKeyboardKey(int key);
int ConvertToGlfwKeyboardKey(KeyboardKey key);
