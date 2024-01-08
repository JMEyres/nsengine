#include "Input.h"

namespace nsengine
{
	bool Input::isKeyHeld(int key)
	{
		for (size_t ki = 0; ki < keys.size(); ++ki)
		{
			if (key == keys.at(ki))
			{
				return true;
			}
		}
		return false;
	}

	bool Input::isKeyPressed(int key)
	{
		for (size_t ki = 0; ki < pressedKeys.size(); ++ki)
		{
			if (key == pressedKeys.at(ki))
			{
				return true;
			}
		}
		return false;
	}

	bool Input::isKeyReleased(int key)
	{
		for (size_t ki = 0; ki < releasedKeys.size(); ++ki)
		{
			if (key == releasedKeys.at(ki))
			{
				return true;
			}
		}
		return false;
	}

	void Input::clearInput()
	{
		pressedKeys.clear();
		releasedKeys.clear();
	}
}