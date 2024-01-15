#include "Input.h"

namespace nsengine
{
	bool Input::IsKeyHeld(int key)
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

	bool Input::IsKeyPressed(int key)
	{
		for (size_t ki = 0; ki < pressedKeys.size(); ++ki)
		{
			if (key == pressedKeys.at(ki))
			{
				//std::cout << key << std::endl;
				return true;
			}
		}
		return false;
	}

	bool Input::IsKeyReleased(int key)
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

	void Input::ClearInput()
	{
		pressedKeys.clear();
		releasedKeys.clear();
	}

	int Input::GetMouseX()
	{
		return mouseX;
	}

	int Input::GetMouseY()
	{
		return mouseY;
	}
}