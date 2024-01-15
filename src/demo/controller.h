#include <nsengine/nsengine.h>

using namespace nsengine;

struct Controller : Component
{
	void OnTick()
	{
		std::shared_ptr<Camera> cam = GetEntity()->GetEnvironment()->GetCamera(0);
		float dt = GetCore()->GetDeltaTime();

		glm::vec2 oldMouse;

		glm::vec2 currentMouse = glm::vec2(GetCore()->GetInput()->GetMouseX(), GetCore()->GetInput()->GetMouseY());
		glm::vec2 mouseDelta = oldMouse - currentMouse;

		GetEntity()->GetTransform()->Rotate(0, mouseDelta.x * 0.1f, 0);

		oldMouse = currentMouse;

		if(finish)
		{
			glm::vec3 finishPos = finish->GetTransform()->GetPosition();
			glm::vec3 finishSize = finish->GetComponent<BoxCollider>()->GetSize();
			if (GetEntity()->GetComponent<BoxCollider>()->IsColliding(finishPos, finishSize) && !finished)
			{
				float finishTime = cam->GetEntity()->GetComponent<Gui>()->GetTimer();
				finished = true;
				cam->GetEntity()->GetComponent<Gui>()->EnableAsTimer(false);
				cam->GetEntity()->GetComponent<Gui>()->SetText("Finished - Press Enter to Restart");
				finish->GetComponent<AudioSource>()->Play();
			}
		}

		if (pickup)
		{
			glm::vec3 otherPos = pickup->GetTransform()->GetPosition();
			glm::vec3 otherSize = pickup->GetComponent<BoxCollider>()->GetSize();
			if (GetEntity()->GetComponent<BoxCollider>()->IsColliding(otherPos, otherSize))
			{
				pickup->GetComponent<AudioSource>()->Play();
				pickup->GetComponent<RigidBody>()->Disable();
				cam->GetEntity()->GetComponent<Gui>()->SetTimer(cam->GetEntity()->GetComponent<Gui>()->GetTimer() - 5);
			}
		}

		if (GetCore()->GetInput()->IsKeyHeld(KEY_W))
			GetEntity()->GetComponent<RigidBody>()->Move(0, 0, speed * dt);
		if (GetCore()->GetInput()->IsKeyHeld(KEY_A))
			GetEntity()->GetComponent<RigidBody>()->Move(speed * dt, 0, 0);
		if (GetCore()->GetInput()->IsKeyHeld(KEY_S))
			GetEntity()->GetComponent<RigidBody>()->Move(0, 0, -speed * dt);
		if (GetCore()->GetInput()->IsKeyHeld(KEY_D))
			GetEntity()->GetComponent<RigidBody>()->Move(-speed * dt, 0, 0);
		if (GetCore()->GetInput()->IsKeyReleased(KEY_SPACE))
		{
			GetEntity()->GetComponent<RigidBody>()->Move(0, 500, 0);
			GetEntity()->GetComponent<AudioSource>()->Play();
		}
		if (GetCore()->GetInput()->IsKeyPressed(KEY_RETURN))
		{
			finished = false;
			GetEntity()->GetComponent<RigidBody>()->SetPosition(0.0f, 5.0f, 0.0f);
			GetEntity()->GetTransform()->SetRotation(rend::vec3(0.0f, 90.0f, 0.0f));
			cam->GetEntity()->GetComponent<Gui>()->SetTimer(0);
			cam->GetEntity()->GetComponent<Gui>()->EnableAsTimer(true);
			pickup->GetComponent<RigidBody>()->Enable();

		}
		if (GetCore()->GetInput()->IsKeyPressed(KEY_ESCAPE))
			GetCore()->Stop();
	}

	std::shared_ptr<Entity> finish;
	std::shared_ptr<Entity> pickup;
private:
	float angle = 360.0f;
	float speed = 1000.0f;
	bool finished = false;
};