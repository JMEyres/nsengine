#include "SpriteRenderer.h"
#include "Resources.h"
#include <iostream>

namespace nsengine
{
	void SpriteRenderer::OnInitialize() // Init with default values
	{
		mesh.load(rend::QUAD_MESH);
		shader.load(rend::PLANE_SHADER);

		shader.attribute("a_Position", *mesh.positions()); // set to mesh points

		shader.uniform("u_Color", rend::vec4(0.5f, 1.0f, 0.0f, 1.0f)); // choose colour
	}

	void SpriteRenderer::OnDisplay()
	{
		std::shared_ptr<Camera> cam = GetEntity()->GetEnvironment()->GetCamera(0);

		shader.uniform("u_Projection", cam->GetProj()); // Set to cam projection/view matrix so it is in view
		shader.uniform("u_View", cam->GetView());

		shader.uniform("u_Model", GetEntity()->GetTransform()->Model());
		glActiveTexture(GL_TEXTURE0); // activate texture at index 0
		glBindTexture(GL_TEXTURE_2D, currentID); // load texture
		shader.uniform("u_Texture", 0); // assign uniform to index 0
		shader.attribute("a_TexCoord", *mesh.texcoords()); // have to pass it back in becuase it doesnt have indexes to where it should be
		shader.depth_test(true);
		shader.render();
	}

	void SpriteRenderer::OnTick()
	{
		float dt = GetCore()->GetDeltaTime();
		frameTimer += dt;

		if (frameTimer >= 0.1f) // change this to change speed of animation
		{
			frameCount++;
			frameTimer = 0;
		}

		if (frameCount == ids.size()) // when it hits the last frame reset
		{
			frameCount = 0;
		}
		currentID = ids[frameCount];
	}

	void SpriteRenderer::Animate(std::vector<std::shared_ptr<Texture>> _animFrames) // Set sprite to animate
	{
		animate = true;
		animTextures = _animFrames;
		for (size_t i = 0; i < animTextures.size(); ++i)
		{
			ids.push_back(animTextures.at(i)->GetID()); // push frame ids to buffer
		} 

		frameCount = ids[0];
		frameTimer = ids[0];
	}
}