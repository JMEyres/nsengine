#include "Input.h"

namespace nsengine
{
	bool Input::IsKeyHeld(int key) // checks if key is being held
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

	bool Input::IsKeyPressed(int key) // checks if key is pressed that frame
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

	bool Input::IsKeyReleased(int key) // checks if key is released that frame
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