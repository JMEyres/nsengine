#pragma once
#include <vector>
#include <SDL2/SDL.h>

namespace nsengine 
{
	struct Input
	{
		int isKeyHeld(int key);
		int isKeyPressed(int key);
		int isKeyReleased(int key);
	private:
		friend struct Core;

		std::vector<int> keys; // keys held down
		std::vector<int> pressedKeys; // keys pressed that frame
		std::vector<int> releasedKeys; // keys released that frame
	};
}