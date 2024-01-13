#include "Gui.h"
#include "Camera.h"

namespace nsengine
{
	void Gui::onDisplay()
	{
		rend::Font font("C:/Users/joshu/Github/nsengine/build/Resources/Fonts/comic.png");
		rend::TextShader textShader;
		textShader.projection(rend::ortho(0.0f, 1152.0f, 864.0f, 0.0f, -0.1f, 1000.0f));
		textShader.model(rend::translate(rend::mat4(1.0f), rend::vec3(100, 100, 0)));
		textShader.text("2D/Othrographic");
		textShader.font(font);
		textShader.render();
	}

}