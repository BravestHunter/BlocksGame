#include "glfw_convert.hpp"


KeyboardKeyState ConvertFromGlfwKeyState(int state)
{
	switch (state)
	{
	case GLFW_RELEASE:
		return KeyboardKeyState::RELEASED;

	case GLFW_PRESS:
	case GLFW_REPEAT:
		return KeyboardKeyState::PRESSED;

	default:
		return KeyboardKeyState::UNKNOWN;
	}
}

int ConvertToGlfwKeyState(KeyboardKeyState state)
{
	switch (state)
	{
	case KeyboardKeyState::RELEASED:
		return GLFW_RELEASE;

	case KeyboardKeyState::PRESSED:
		return GLFW_PRESS;

	case KeyboardKeyState::UNKNOWN:
	default:
		return -1;
	}
}


KeyboardKey ConvertFromGlfwKeyboardKey(int key)
{
	switch (key)
	{
	case GLFW_KEY_A:
		return KeyboardKey::A;

	case GLFW_KEY_B:
		return KeyboardKey::B;

	case GLFW_KEY_C:
		return KeyboardKey::C;

	case GLFW_KEY_D:
		return KeyboardKey::D;

	case GLFW_KEY_E:
		return KeyboardKey::E;

	case GLFW_KEY_F:
		return KeyboardKey::F;

	case GLFW_KEY_G:
		return KeyboardKey::G;

	case GLFW_KEY_H:
		return KeyboardKey::H;

	case GLFW_KEY_I:
		return KeyboardKey::I;

	case GLFW_KEY_J:
		return KeyboardKey::J;

	case GLFW_KEY_K:
		return KeyboardKey::K;

	case GLFW_KEY_L:
		return KeyboardKey::L;

	case GLFW_KEY_M:
		return KeyboardKey::M;

	case GLFW_KEY_N:
		return KeyboardKey::N;

	case GLFW_KEY_O:
		return KeyboardKey::O;

	case GLFW_KEY_P:
		return KeyboardKey::P;

	case GLFW_KEY_Q:
		return KeyboardKey::Q;

	case GLFW_KEY_R:
		return KeyboardKey::R;

	case GLFW_KEY_S:
		return KeyboardKey::S;

	case GLFW_KEY_T:
		return KeyboardKey::T;

	case GLFW_KEY_U:
		return KeyboardKey::U;

	case GLFW_KEY_V:
		return KeyboardKey::V;

	case GLFW_KEY_W:
		return KeyboardKey::W;

	case GLFW_KEY_X:
		return KeyboardKey::X;

	case GLFW_KEY_Y:
		return KeyboardKey::Y;

	case GLFW_KEY_Z:
		return KeyboardKey::Z;

	case GLFW_KEY_UNKNOWN:
	default:
		return KeyboardKey::UNKNOWN;
	}

	return KeyboardKey::ESCAPE;
}

int ConvertToGlfwKeyboardKey(KeyboardKey key)
{
	switch (key)
	{
	case KeyboardKey::A:
		return GLFW_KEY_A;

	case KeyboardKey::B:
		return GLFW_KEY_B;

	case KeyboardKey::C:
		return GLFW_KEY_C;

	case KeyboardKey::D:
		return GLFW_KEY_D;

	case KeyboardKey::E:
		return GLFW_KEY_E;

	case KeyboardKey::F:
		return GLFW_KEY_F;

	case KeyboardKey::G:
		return GLFW_KEY_G;

	case KeyboardKey::H:
		return GLFW_KEY_H;

	case KeyboardKey::I:
		return GLFW_KEY_I;

	case KeyboardKey::J:
		return GLFW_KEY_J;

	case KeyboardKey::K:
		return GLFW_KEY_K;

	case KeyboardKey::L:
		return GLFW_KEY_L;

	case KeyboardKey::M:
		return GLFW_KEY_M;

	case KeyboardKey::N:
		return GLFW_KEY_N;

	case KeyboardKey::O:
		return GLFW_KEY_O;

	case KeyboardKey::P:
		return GLFW_KEY_P;

	case KeyboardKey::Q:
		return GLFW_KEY_Q;

	case KeyboardKey::R:
		return GLFW_KEY_R;

	case KeyboardKey::S:
		return GLFW_KEY_S;

	case KeyboardKey::T:
		return GLFW_KEY_T;

	case KeyboardKey::U:
		return GLFW_KEY_U;

	case KeyboardKey::V:
		return GLFW_KEY_V;

	case KeyboardKey::W:
		return GLFW_KEY_W;

	case KeyboardKey::X:
		return GLFW_KEY_X;

	case KeyboardKey::Y:
		return GLFW_KEY_Y;

	case KeyboardKey::Z:
		return GLFW_KEY_Z;

	case KeyboardKey::ESCAPE:
		return GLFW_KEY_ESCAPE;

	case KeyboardKey::UNKNOWN:
	default:
		return GLFW_KEY_UNKNOWN;
	}
}
