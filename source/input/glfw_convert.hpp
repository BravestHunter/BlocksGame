#pragma once

#include <GLFW/glfw3.h>

#include "key_state.hpp"
#include "keyboard_key.hpp"


KeyState ConvertFromGlfwKeyState(int state);
int ConvertToGlfwKeyState(KeyState state);

KeyboardKey ConvertFromGlfwKeyboardKey(int key);
int ConvertToGlfwKeyboardKey(KeyboardKey key);
