#include "Renderer.h"
#include "Resources.h"
#include "Texture.h"
#include "Model.h"
#include "Entity.h"
#include "Camera.h"

#include <filesystem>

namespace nsengine
{
	void Renderer::onInitialize()
	{
		model = getCore()->getResources()->load<Model>(path)->model;
	}

	void Renderer::onDisplay()
	{		
		std::shared_ptr<Camera> cam = getEntity()->getEnvironment()->getCamera(0);
		modelShader.projection(cam->projMatrix);
		modelShader.view(cam->viewMatrix);

		modelShader.model(getEntity()->getTransform()->Model());
		modelShader.model(*model);
		
		modelShader.render();
	}
}