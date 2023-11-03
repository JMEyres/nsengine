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
		float angle = 1.0f;

		float dt = getEntity()->getEnvironment()->getDeltaTime();
		//std::cout << dt << std::endl;
		

		getEntity()->getComponent<Transform>()->setRotation(rend::vec3(0.0f, angle * dt, 0.0f));
		getEntity()->getComponent<Transform>()->setPosition(rend::vec3(0.0f, 0.0f, -10.0f));
		getEntity()->getComponent<Transform>()->setScale(rend::vec3(5.0f, 5.0f, 1.0f));

		shader.uniform("u_Projection", rend::perspective( // set perspective
			rend::radians(45.0f), 1.0f, 0.1f, 100.0f));
		
		shader.uniform("u_Model", getEntity()->getComponent<Transform>()->Model());

		shader.render();
	}
}