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
#define KEY_RETURN 13

namespace nsengine 
{
	/// @brief Class handling the input from keyboard and mouse
	struct Input
	{
		/// @brief Checks if specified key is being held
		/// @param key Key to check for
		/// @return True/False depending on if key is held
		bool IsKeyHeld(int key);

		/// @brief Checks if specified key has been pressed that frame
		/// @param key Key to check for
		/// @return True/False depending on if the key was presssed that frame
		bool IsKeyPressed(int key);

		/// @brief Checks if specified key was released that frame
		/// @param key Key to check for
		/// @return True/False depending on if the key was released that frame
		bool IsKeyReleased(int key);

		/// @brief Clear the list of held and pressed keys
		void ClearInput();

		/// @brief Gets the relative x position of the mouse
		/// @return Integer relative x position of the mouse
		int GetMouseX();

		/// @brief Gets the relative y position of the mouse
		/// @return Integer relative y position of the mouse
		int GetMouseY();
	private:
		friend struct Core;

		int mouseX, mouseY;
		std::vector<int> keys; // keys held down
		std::vector<int> pressedKeys; // keys pressed that frame
		std::vector<int> releasedKeys; // keys released that frame
	};
}