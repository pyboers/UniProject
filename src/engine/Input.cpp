//
// Created by Pierre-Yves Boers on 02/04/2018.
//
#include "Input.h"
#include "Engine.h"


Input::Input() {
	memset(pressed, 0, MAX_INPUT);
	memset(down, 0, MAX_INPUT);
	memset(released, 0, MAX_INPUT);
}

void Input::clear() {
	memset(pressed, 0, MAX_INPUT);
	memset(released, 0, MAX_INPUT);

	down[MOUSE_WHEEL_UP] = 0; //Wheel can't be held
	down[MOUSE_WHEEL_DOWN] = 0;

	m_dx = 0;
	m_dy = 0;
}

bool Input::isPressed(Input::_Input input) const {
	return pressed[input];
}

bool Input::isDown(Input::_Input input) const {
	return down[input];
}

bool Input::isReleased(Input::_Input input) const {
	return released[input];
}

int Input::getMouseX() const {
	return m_x;
}

int Input::getMouseY() const {
	return m_y;
}

int Input::getMouseDX() const {
	return m_dx;
}

int Input::getMouseDY() const {
	return m_dy;
}

void Input::update(SDL_Event event) {
	clear();
	while (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_KEYDOWN
				   && event.key.repeat == 0) {

			down[event.key.keysym.scancode] = true;
			pressed[event.key.keysym.scancode] = true;
		} else if (event.type == SDL_KEYUP) {
			down[event.key.keysym.scancode] = false;
			released[event.key.keysym.scancode] = true;
		} else if (event.type == SDL_MOUSEMOTION) {
			m_dx = event.motion.xrel;
			m_dy = event.motion.yrel;
			m_x = event.motion.x;
			m_y = Engine::getEngine().getWindowHeight() - event.motion.y - 1;
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			_Input mInput;
			mInput = static_cast<_Input>(event.button.button + KEY_LAST);
			down[mInput] = true;
			pressed[mInput] = true;
		} else if (event.type == SDL_MOUSEBUTTONUP) {
			_Input mInput;
			mInput = static_cast<_Input>(event.button.button + KEY_LAST);

			down[mInput] = false;
			released[mInput] = true;
		}
	}
}


