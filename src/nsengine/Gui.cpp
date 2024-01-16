#include "Gui.h"
#include "Camera.h"
#include <iostream>

namespace nsengine
{
	void Gui::SetPath(sys::string _path)
	{
		sys::string fullPath = "./Resources" + _path;
		path = fullPath;
	}

	void Gui::SetText(sys::string _text)
	{
		text = _text;
	}

	void Gui::EnableAsTimer(bool _toggle)
	{
		timer = _toggle;
	}

	void Gui::SetTimer(float _value)
	{
		frameTimer = _value;
	}

	float Gui::GetTimer()
	{
		return frameTimer;
	}

	void Gui::SetPosition(rend::vec3 _pos)
	{
		position = _pos;
	}

	void Gui::SetResolution(float _width, float _height)
	{
		resW = _width;
		resH = _height;
	}

	void Gui::OnDisplay()
	{
		if(timer) // if set to be a timer
		{
			float dt = GetCore()->GetDeltaTime();
			frameTimer += dt;
			sys::string timer = sys::to_string(frameTimer);
			SetText(timer);
		}

		rend::Font font(path);
		rend::TextShader textShader;
		textShader.projection(rend::ortho(0.0f, resW, resH, 0.0f, -0.1f, 1000.0f)); // bounds of gui
		textShader.model(rend::translate(rend::mat4(1.0f), rend::vec3(position.x, position.y, position.z))); // set position of text
		textShader.text(text); // set text
		textShader.font(font); // set font
		textShader.render();
	}

}