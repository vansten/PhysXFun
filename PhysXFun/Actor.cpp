#include "Actor.h"

#include "Camera.h"
#include "Collider.h"

Actor::Actor() : _mesh(nullptr), _physicalBody(nullptr), _audioSource(nullptr)
{

}						   

Actor::Actor(const Actor& actor) : _transform(actor._transform), _mesh(actor._mesh)
{

}

Actor::~Actor()
{

}

void Actor::Shutdown()
{
	auto& it = _colliders.begin();
	for(; it != _colliders.end(); ++it)
	{
		Memory::GetInstance()->Deallocate<Collider>((*it));
	}
	_colliders.clear();

	if(_mesh)
	{
		_mesh->Shutdown();
		Memory::GetInstance()->Deallocate<Mesh>(_mesh);
		_mesh = nullptr;
	}

	if(_physicalBody != nullptr)
	{
		Memory::GetInstance()->Deallocate<PhysicalBody>(_physicalBody);
		_physicalBody = nullptr;
	}

	if(_audioSource != nullptr)
	{
		Memory::GetInstance()->Deallocate<AudioSource>(_audioSource);
		_audioSource = nullptr;
	}
}

void Actor::Update(GLfloat deltaTime)
{

}

void Actor::PreSimulate()
{
	if(_physicalBody)
	{
		_physicalBody->PreSimulation();
	}
}

void Actor::PostSimulate()
{
	if(_physicalBody)
	{
		_physicalBody->PostSimulation();
	}
}

void Actor::Render(const Camera& camera, Graphics* graphics)
{
	if(_mesh)
	{
		_mesh->Render(camera, _transform.GetModelToWorldMatrix(), graphics);
	}
}

void Actor::SetTransform(const Transform& transform)
{
	_transform = transform;
}

StaticPhysicalBody* Actor::CreateStaticRigidbody()
{
	if(_physicalBody != nullptr)
	{
		Memory::GetInstance()->Deallocate<PhysicalBody>(_physicalBody);
		_physicalBody = nullptr;
	}

	_physicalBody = NewObject(StaticPhysicalBody, this);
	return reinterpret_cast<StaticPhysicalBody*>(_physicalBody);
}

DynamicPhysicalBody* Actor::CreateDynamicRigidbody()
{
	if(_physicalBody != nullptr)
	{
		Memory::GetInstance()->Deallocate<PhysicalBody>(_physicalBody);
		_physicalBody = nullptr;
	}


	_physicalBody = NewObject(DynamicPhysicalBody, this);
	return reinterpret_cast<DynamicPhysicalBody*>(_physicalBody);
}
