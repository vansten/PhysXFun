#pragma once

#include "PhysicalBody.h"

class DynamicPhysicalBody : public PhysicalBody
{
protected:
	PxRigidDynamic* _physxActor;

public:
	DynamicPhysicalBody(Actor* owner);
	~DynamicPhysicalBody();

	virtual void PreSimulation();
	virtual void PostSimulation();

	virtual void OnTrigger(PhysicalBody* other);
	virtual void OnContact(PhysicalBody* other);

	virtual void SetKinematic(bool kinematic)
	{
		if(_physxActor)
		{
			_physxActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, kinematic);
		}
	}

	void AddForce(const glm::vec3& force);
};

