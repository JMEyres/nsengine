#include "Renderer.h"
#include "Resources.h"
#include "Texture.h"
#include "Model.h"
#include "Entity.h"
#include "Camera.h"

#include <filesystem>

namespace nsengine
{
	void Renderer::SetPath(std::string _path)
	{
		path = _path;
	}

	void Renderer::OnInitialize()
	{
		model = GetCore()->GetResources()->Load<Model>(path)->GetModel();
	}

	void Renderer::OnDisplay()
	{		
		std::shared_ptr<Camera> cam = GetEntity()->GetEnvironment()->GetCamera(0);
		modelShader.projection(cam->GetProj());
		modelShader.view(cam->GetView());

		modelShader.model(GetEntity()->GetTransform()->Model());
		modelShader.model(*model);
		modelShader.render();
	}
}