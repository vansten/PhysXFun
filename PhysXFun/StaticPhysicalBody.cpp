#include "StaticPhysicalBody.h"

#include "Engine.h"
#include "Cube.h"
#include "Collider.h"

StaticPhysicalBody::StaticPhysicalBody(Actor* owner) : PhysicalBody(owner)
{
	_physxActor = Engine::GetInstance()->GetPhysics().CreateStaticActor(owner->GetTransform().GetPhysxTransform());
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

StaticPhysicalBody::~StaticPhysicalBody()
{
	if(_physxActor)
	{
		_physxActor->release();
		_physxActor = 0;
	}
}

void StaticPhysicalBody::PreSimulation()
{

}

void StaticPhysicalBody::PostSimulation()
{

}

void StaticPhysicalBody::OnTrigger(PhysicalBody* other)
{
	printf("StaticPhysicalBody onTrigger\n");
}

void StaticPhysicalBody::OnContact(PhysicalBody* other)
{

}
