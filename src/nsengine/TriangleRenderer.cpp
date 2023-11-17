#include "TriangleRenderer.h"

namespace nsengine
{
	void TriangleRenderer::onInitialize()
	{
		mesh.load(rend::TRIANGLE_MESH);
		shader.load(rend::COLOR_SHADER);

		shader.attribute("a_Position", *mesh.positions()); // set to mesh points

		shader.uniform("u_Color", rend::vec4(0.5f, 1.0f, 0.0f, 1.0f)); // choose colour
	}

	void TriangleRenderer::onDisplay()
	{
		shader.uniform("u_Projection", rend::perspective( // set perspective
			rend::radians(45.0f), 1.0f, 0.1f, 100.0f));
		
		shader.uniform("u_Model", getEntity()->getTransform()->Model());

		shader.render();
	}
}