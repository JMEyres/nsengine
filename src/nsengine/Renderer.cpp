#include "Renderer.h"
#include "Resources.h"
#include "Texture.h"
#include "Model.h"
#include "Entity.h"

namespace nsengine
{
	void Renderer::onInitialize()
	{
		//model.load("../src/Resources/Models/curuthers.obj");
	}

	void Renderer::onDisplay()
	{
		modelShader.projection(rend::perspective(rend::radians(45.0f), 1.0f, 0.1f, 100.0f));

		modelShader.model(rend::translate(rend::mat4(1.0f), rend::vec3(0, 0, -10)));
		modelShader.model(model);
		modelShader.render();
	}
}