#pragma once

#include "PhysicalBody.h"

class StaticPhysicalBody : public PhysicalBody
{
protected:
	PxRigidStatic* _physxActor;

public:
	StaticPhysicalBody(Actor* owner);
	~StaticPhysicalBody();

	virtual void PreSimulation();
	virtual void PostSimulation();

	virtual void OnTrigger(PhysicalBody* other);
	virtual void OnContact(PhysicalBody* other);

	virtual void SetKinematic(bool kinematic)
	{
		//Do nothing since static rigidboby doesn't have rigidbody flags
	}
};

