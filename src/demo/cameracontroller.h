#include <nsengine/nsengine.h>
using namespace nsengine;

struct CameraController : Component
{
	void OnTick()
	{
		float dt = GetCore()->GetDeltaTime();

		if (GetCore()->GetInput()->IsKeyHeld(KEY_TAB))
			follow = !follow;

		if (follow)
			GetEntity()->GetComponent<Camera>()->Follow();
		else
		{
			if (GetCore()->GetInput()->IsKeyHeld(KEY_RIGHT))
				GetEntity()->GetTransform()->Rotate(0, -angle * dt, 0);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_LEFT))
				GetEntity()->GetTransform()->Rotate(0, angle * dt, 0);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_DOWN))
				GetEntity()->GetTransform()->Rotate(angle * dt, 0, 0);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_UP))
				GetEntity()->GetTransform()->Rotate(-angle * dt, 0, 0);

			// Move
			if (GetCore()->GetInput()->IsKeyHeld(KEY_J))
				GetEntity()->GetTransform()->Move(-speed * dt, 0, 0);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_L))
				GetEntity()->GetTransform()->Move(speed * dt, 0, 0);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_K))
				GetEntity()->GetTransform()->Move(0, 0, speed * dt);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_I))
				GetEntity()->GetTransform()->Move(0, 0, -speed * dt);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_O))
				GetEntity()->GetTransform()->Move(0, speed * dt, 0);
			if (GetCore()->GetInput()->IsKeyHeld(KEY_U))
				GetEntity()->GetTransform()->Move(0, -speed * dt, 0);
		}
	}
private:

	bool follow = true;
	float angle = 90.0f;
	float speed = 5.0f;
};