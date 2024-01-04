#include "Input.h"

namespace nsengine
{
	int Input::isKeyHeld(int key)
	{
		for (size_t ki = 0; ki < keys.size(); ++ki)
		{
			if (key == keys.at(ki))
			{
				//std::cout << "keyHeld: " << key << std::endl;
				return key;
			}
			else
			{
				return 0;
			}
		}
	}

	int Input::isKeyPressed(int key)
	{
		for (size_t ki = 0; ki < pressedKeys.size(); ++ki)
		{
			if (key == pressedKeys.at(ki))
			{
				//std::cout << "keyPressed: " << key << std::endl;
				return key;
			}
			else
			{
				return 0;
			}
		}
	}

	int Input::isKeyReleased(int key)
	{
		for (size_t ki = 0; ki < releasedKeys.size(); ++ki)
		{
			if (key == releasedKeys.at(ki))
			{
				//std::cout << "keyReleased: " << key << std::endl;
				return key;
			}
			else
			{
				return 0;
			}
		}
	}

	void Input::clearInput()
	{
		pressedKeys.clear();
		releasedKeys.clear();
	}
}