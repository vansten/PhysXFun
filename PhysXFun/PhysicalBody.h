#pragma once

#include "Physics.h"

class Actor;

class PhysicalBody
{
protected:
	Actor* _owner;

public:
	PhysicalBody(Actor* owner);
	~PhysicalBody();

	virtual void PreSimulation() = 0;
	virtual void PostSimulation() = 0;

	virtual void OnTrigger(PhysicalBody* other) = 0;
	virtual void OnContact(PhysicalBody* other) = 0;

	virtual void SetKinematic(bool kinematic) = 0;

	inline Actor* GetOwner() const
	{
		return _owner;
	}
};

