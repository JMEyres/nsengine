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
		float angle = 0;
		angle += 0.25f;

		getEntity()->getComponent<Transform>()->Rotate(rend::vec3(0.0f, angle, 0.0f));

		shader.uniform("u_Projection", rend::perspective( // set perspective
			rend::radians(45.0f), 1.0f, 0.1f, 100.0f));

		//shader.uniform("u_Model", rend::translate( // set position
			//rend::mat4(1.0f), rend::vec3(0.0f, 0.0f, -5.0f)));
		
		shader.uniform("u_Model", getEntity()->getComponent<Transform>()->Model());

		shader.render();
	}
}