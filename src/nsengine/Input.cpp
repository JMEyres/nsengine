#include "Input.h"
#include<iostream>

namespace nsengine
{
	int Input::isKeyHeld(int key)
	{
		for (size_t ki = 0; ki < keys.size(); ++ki)
		{
			if (key == keys.at(ki))
			{
				std::cout << key << std::endl;
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
		return 0;
	}

	int Input::isKeyReleased(int key)
	{
		return 0;
	}

}