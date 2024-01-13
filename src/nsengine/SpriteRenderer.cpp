#include "SpriteRenderer.h"
#include "Resources.h"

namespace nsengine
{
	void SpriteRenderer::onInitialize()
	{
		mesh.load(rend::QUAD_MESH);
		shader.load(rend::PLANE_SHADER);

		shader.attribute("a_Position", *mesh.positions()); // set to mesh points

		shader.uniform("u_Color", rend::vec4(0.5f, 1.0f, 0.0f, 1.0f)); // choose colour
		currentID = getEntity()->getEnvironment()->getCore()->getResources()->load<Texture>("/Textures/SpriteAnim/_1.png")->id;
	}

	void SpriteRenderer::onDisplay()
	{
		std::shared_ptr<Camera> cam = getEntity()->getEnvironment()->getCamera(0);

		shader.uniform("u_Projection", cam->projMatrix);
		shader.uniform("u_View", cam->viewMatrix);

		shader.uniform("u_Model", getEntity()->getTransform()->Model());
		glActiveTexture(GL_TEXTURE0); // activate texture at index 0
		glBindTexture(GL_TEXTURE_2D, currentID); // load texture
		shader.uniform("u_Texture", 0); // assign uniform to index 0
		shader.attribute("a_TexCoord", *mesh.texcoords()); // have to pass it back in becuase it doesnt have indexes to where it should be
		shader.render();
	}

	void SpriteRenderer::onTick()
	{
		float dt = getCore()->getDeltaTime();
		frameTimer += dt;

		frameCount = frameTimer;

		currentID = frameCount;
		if (frameCount == ids.size())
		{
			frameCount = 1;
			frameTimer = 1;
		}
	}

	void SpriteRenderer::Animate(std::vector<std::shared_ptr<Texture>> sprites)
	{
		animate = true;
		animTextures = sprites;
		for (size_t i = 0; i < animTextures.size(); ++i)
		{
			ids.push_back(animTextures.at(i)->id);
		}
	}
}