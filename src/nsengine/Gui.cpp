#include "Gui.h"
#include "Camera.h"
#include <iostream>

namespace nsengine
{
	void Gui::setPath(sys::string _path)
	{
		sys::string fullPath = "./Resources" + _path;
		path = fullPath;
	}

	void Gui::setText(sys::string _text)
	{
		text = _text;
	}

	void Gui::enableAsTimer(bool _toggle)
	{
		timer = _toggle;
	}

	void Gui::onDisplay()
	{
		if(timer)
		{
			float dt = getCore()->getDeltaTime();
			frameTimer += dt;

			setText(sys::to_string(frameTimer));
		}

		rend::Font font(path);
		rend::TextShader textShader;
		textShader.projection(rend::ortho(0.0f, 1152.0f, 864.0f, 0.0f, -0.1f, 1000.0f));
		textShader.model(rend::translate(rend::mat4(1.0f), rend::vec3(100, 100, 0)));
		textShader.text(text);
		textShader.font(font);
		textShader.render();
	}

}