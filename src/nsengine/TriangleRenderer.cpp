#include "TriangleRenderer.h"
#include "Resources.h"
#include "Texture.h"
#include "Camera.h"

namespace nsengine
{
	void TriangleRenderer::OnInitialize() // Init Triangle with texture and shaders
	{
		mesh.load(rend::TRIANGLE_MESH);
		shader.load(rend::TEXTURE_SHADER);

		shader.attribute("a_Position", *mesh.positions()); // set to mesh points

		shader.uniform("u_Color", rend::vec4(0.5f, 1.0f, 0.0f, 1.0f)); // choose colour
		id = GetCore()->GetResources()->Load<Texture>("/Textures/canosprite.png")->GetID(); // Load default sprite
	}

	void TriangleRenderer::OnDisplay()
	{
		std::shared_ptr<Camera> cam = GetEntity()->GetEnvironment()->GetCamera(0); // get main cam

		shader.uniform("u_Projection",cam->GetProj());
		
		shader.uniform("u_Model", GetEntity()->GetTransform()->Model());
		glActiveTexture(GL_TEXTURE0); // activate texture at index 0
		glBindTexture(GL_TEXTURE_2D, id); // load texture
		shader.uniform("u_Texture", 0); // assign uniform to index 0
		shader.attribute("a_TexCoord", *mesh.texcoords()); // have to pass it back in becuase it doesnt have indexes to where it should be
		shader.render();
	}
}