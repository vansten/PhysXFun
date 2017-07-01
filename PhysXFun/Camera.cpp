#include "Camera.h"

#include "Input.h"
#include "Engine.h"
#include "Cube.h"
#include "BoxCollider.h"
#include "AudioClip.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& rotation, const CameraSettings& settings) : Actor(), _settings(settings)
{
	_transform.SetPosition(position);
	_transform.SetRotation(glm::quat(rotation));
	UpdateViewMatrix();
	UpdateProjectionMatrix();

	_spawned = false;

	_box = Memory::GetInstance()->Allocate<Cube>(sizeof(Cube), "Cube", __FILE__, __LINE__, 0.5f, Engine::GetInstance()->GetResourceManager().GetShader("screenTriangleVS.glsl", "screenTriangleFS.glsl"), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	_box->Initialize();

	_clip = Engine::GetInstance()->GetResourceManager().GetAudioClip("test.wav");

	_lastMousePos = Input::GetMousePosition();
}

Camera::~Camera()
{
	_box->Shutdown();
	Memory::GetInstance()->Deallocate<Cube>(_box);
	_box = nullptr;
}

void Camera::Update(GLfloat deltaTime)
{
	Actor::Update(deltaTime);

	float speed = 1.0f + (Input::GetKey(GLFW_KEY_LEFT_SHIFT) ? 2.0f : 0.0f);
	float horizontal = Input::GetKey(GLFW_KEY_A) ? -1.0f : (Input::GetKey(GLFW_KEY_D) ? 1.0f : 0.0f);
	float vertical = Input::GetKey(GLFW_KEY_S) ? -1.0f : (Input::GetKey(GLFW_KEY_W) ? 1.0f : 0.0f);
	glm::vec3 translation = (_transform.GetForward() * vertical + _transform.GetRight() * horizontal) * speed * deltaTime;
	translation.y = 0.0f;
	_transform.Translate(translation);

	glm::vec2 currentMousePos = Input::GetMousePosition();
	glm::vec2 delta = currentMousePos - _lastMousePos;
	_lastMousePos = currentMousePos;

	_transform.Rotate(delta.y * deltaTime, -delta.x * deltaTime, 0.0f);

	if(!_spawned)
	{
		if(Input::GetMouseButton(GLFW_MOUSE_BUTTON_1))
		{
			_spawned = true;
			Actor* a = Engine::SpawnActor(_transform.GetPosition() + _transform.GetForward() * 2.0f);
			if(a != nullptr)
			{
				a->SetMesh(*_box);
				BoxCollider* bc = NewObject(BoxCollider, this, false, glm::vec3(_box->GetSize()));
				a->AddCollider(bc);
				DynamicPhysicalBody* pb = a->CreateDynamicRigidbody();
				pb->AddForce(_transform.GetForward() * 100.0f);
				AudioSource* as = a->AddAudioSource(_clip);
				as->Play(false);
			}
		}
	}
	else
	{
		_spawned = Input::GetMouseButton(GLFW_MOUSE_BUTTON_1);
	}

	UpdateViewMatrix();
}
