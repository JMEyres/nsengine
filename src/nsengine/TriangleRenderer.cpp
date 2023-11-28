#include "TriangleRenderer.h"
#include "Resources.h"
#include "Texture.h"

namespace nsengine
{
	void TriangleRenderer::onInitialize()
	{
		mesh.load(rend::TRIANGLE_MESH);
		shader.load(rend::TEXTURE_SHADER);

		shader.attribute("a_Position", *mesh.positions()); // set to mesh points

		shader.uniform("u_Color", rend::vec4(0.5f, 1.0f, 0.0f, 1.0f)); // choose colour
	}

	void TriangleRenderer::onDisplay()
	{
		shader.uniform("u_Projection", rend::perspective( // set perspective
			rend::radians(45.0f), 1.0f, 0.1f, 100.0f));
		
		shader.uniform("u_Model", getEntity()->getTransform()->Model());
		glActiveTexture(GL_TEXTURE0); // activate texture at index 0
		glBindTexture(GL_TEXTURE_2D, getEntity()->getEnvironment()->getCore()->getResources()->load<Texture>("../src/Resources/Textures/canosprite.png")->id); // load texture
		shader.uniform("u_Texture", 0); // assign uniform to index 0
		shader.attribute("a_TexCoord", *mesh.texcoords()); // have to pass it back in becuase it doesnt have indexes to where it should be
		shader.render();
	}
}