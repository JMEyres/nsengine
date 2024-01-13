#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include <iostream>

#define KEY_Q 'q'
#define KEY_W 'w'
#define KEY_E 'e'
#define KEY_R 'r'
#define KEY_T 't'
#define KEY_Y 'y'
#define KEY_U 'u'
#define KEY_I 'i'
#define KEY_O 'o'
#define KEY_P 'p'
#define KEY_A 'a'
#define KEY_S 's'
#define KEY_D 'd'
#define KEY_F 'f'
#define KEY_G 'g'
#define KEY_H 'h'
#define KEY_J 'j'
#define KEY_K 'k'
#define KEY_L 'l'
#define KEY_Z 'z'
#define KEY_X 'x'
#define KEY_C 'c'
#define KEY_V 'v'
#define KEY_B 'b'
#define KEY_N 'n'
#define KEY_M 'm'
#define KEY_SPACE 32
#define KEY_RIGHT 1073741903
#define KEY_LEFT 1073741904
#define KEY_DOWN 1073741905
#define KEY_UP 1073741906
#define KEY_LSHIFT 1073742049
#define KEY_LCTRL 1073742048
#define KEY_ESCAPE 27
#define KEY_TAB 9

namespace nsengine 
{
	struct Input
	{
		bool isKeyHeld(int key);
		bool isKeyPressed(int key);
		bool isKeyReleased(int key);
		void clearInput();

		int mouseX, mouseY;
		int oldMousePosX, oldMousPosY;
	private:
		friend struct Core;

		std::vector<int> keys; // keys held down
		std::vector<int> pressedKeys; // keys pressed that frame
		std::vector<int> releasedKeys; // keys released that frame
	};
}