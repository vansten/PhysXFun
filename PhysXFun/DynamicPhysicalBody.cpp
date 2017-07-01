#include "DynamicPhysicalBody.h"

#include "Engine.h"
#include "Cube.h"
#include "Collider.h"

DynamicPhysicalBody::DynamicPhysicalBody(Actor* owner) : PhysicalBody(owner), _physxActor(nullptr)
{
	_physxActor = Engine::GetInstance()->GetPhysics().CreateDynamicActor(owner->GetTransform().GetPhysxTransform());
	_physxActor->userData = this;

	auto& it = _owner->GetColliders().begin();
	auto& end = _owner->GetColliders().end();
	for(; it != end; ++it)
	{
		PxShape* shape = (*it)->GetShape();
		_physxActor->attachShape(*shape);
	}

	Engine::GetInstance()->GetPhysics().GetScene()->addActor(*_physxActor);
}

DynamicPhysicalBody::~DynamicPhysicalBody()
{
	if(_physxActor)
	{
		_physxActor->release();
		_physxActor = 0;
	}
}

void DynamicPhysicalBody::PreSimulation()
{
	if(_physxActor)
	{
		_physxActor->setGlobalPose(_owner->GetTransform().GetPhysxTransform());
	}
}

void DynamicPhysicalBody::PostSimulation()
{
	if(_physxActor)
	{
		_owner->GetTransform().SetPhysxTransform(_physxActor->getGlobalPose());
	}
}

void DynamicPhysicalBody::OnTrigger(PhysicalBody* other)
{
	printf("Dynamic physical body trigger\n");
}

void DynamicPhysicalBody::OnContact(PhysicalBody* other)
{
}

void DynamicPhysicalBody::AddForce(const glm::vec3& force)
{
	if(_physxActor != nullptr)
	{
		_physxActor->addForce(GLMVec3ToPxVec3(force));
	}
}
