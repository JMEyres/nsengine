#pragma once
#include "Component.h"
#include "Entity.h"
#include <rend/rend.h>
#include <sys/string.h>

namespace nsengine
{
	struct Camera;
	struct Gui : Component
	{
		void onDisplay();
		void setPath(sys::string _path);
		void setText(sys::string _text);
		void enableAsTimer(bool toggle);
	private:
		sys::string path = "./Resources/Fonts/Comic.png";
		sys::string text = "2D/OrthoGraphic";
		float frameTimer;
		bool timer;
	};
}