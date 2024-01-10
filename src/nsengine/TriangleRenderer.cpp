#include "TriangleRenderer.h"
#include "Resources.h"
#include "Texture.h"
#include "Camera.h"

namespace nsengine
{
	void TriangleRenderer::onInitialize()
	{
		mesh.load(rend::TRIANGLE_MESH);
		shader.load(rend::TEXTURE_SHADER);

		shader.attribute("a_Position", *mesh.positions()); // set to mesh points

		shader.uniform("u_Color", rend::vec4(0.5f, 1.0f, 0.0f, 1.0f)); // choose colour
		id = getEntity()->getEnvironment()->getCore()->getResources()->load<Texture>("/Textures/canosprite.png")->id;
	}

	void TriangleRenderer::onDisplay()
	{
		std::shared_ptr<Camera> cam = getEntity()->getEnvironment()->getCamera(0);

		shader.uniform("u_Projection",cam->projMatrix);
		
		shader.uniform("u_Model", getEntity()->getTransform()->Model());
		glActiveTexture(GL_TEXTURE0); // activate texture at index 0
		glBindTexture(GL_TEXTURE_2D, id); // load texture
		shader.uniform("u_Texture", 0); // assign uniform to index 0
		shader.attribute("a_TexCoord", *mesh.texcoords()); // have to pass it back in becuase it doesnt have indexes to where it should be
		shader.render();
	}
}