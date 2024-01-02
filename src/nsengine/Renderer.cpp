#include "Renderer.h"
#include "Resources.h"
#include "Texture.h"
#include "Model.h"
#include "Entity.h"
#include<filesystem>

namespace nsengine
{
	void Renderer::onInitialize()
	{
		model = getEntity()->getEnvironment()->getCore()->getResources()->load<Model>("../src/Resources/Models/curuthers.obj")->model;
	}

	void Renderer::onDisplay()
	{		
		modelShader.projection(rend::perspective(rend::radians(45.0f), 1.0f, 0.1f, 100.0f));

		modelShader.model(getEntity()->getTransform()->Model());
		modelShader.model(*model);
		modelShader.render();
	}
}