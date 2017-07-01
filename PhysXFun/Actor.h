#pragma once

#include "Transform.h"
#include "Mesh.h"
#include "DynamicPhysicalBody.h"
#include "StaticPhysicalBody.h"
#include "Memory.h"
#include "AudioSource.h"

#define STRING(T) #T

class Collider;

class Actor
{
protected:
	Transform _transform;
	Mesh* _mesh;
	PhysicalBody* _physicalBody;
	AudioSource* _audioSource;
	std::vector<Collider*> _colliders;

public:
	Actor();
	Actor(const Actor& actor);
	virtual ~Actor();

	void Shutdown();

	virtual void Update(GLfloat deltaTime);
	void PreSimulate();
	void PostSimulate();
	void Render(const class Camera& camera, Graphics* graphics);

	template<typename T>
	void SetMesh(const T& mesh)
	{
		if(_mesh != nullptr)
		{
			_mesh->Shutdown();
			Memory::GetInstance()->Deallocate<Mesh>(_mesh);
			_mesh = nullptr;
		}

		_mesh = NewObject(T, mesh);
	}

	void SetTransform(const Transform& transform);

	StaticPhysicalBody* CreateStaticRigidbody();
	DynamicPhysicalBody* CreateDynamicRigidbody();
	
	inline void AddCollider(Collider* col)
	{
		_colliders.push_back(col);
	}

	inline AudioSource* AddAudioSource(AudioClip* clip)
	{
		if(_audioSource)
		{
			Memory::GetInstance()->Deallocate<AudioSource>(_audioSource);
			_audioSource = nullptr;
		}

		_audioSource = NewObject(AudioSource, clip);
		_audioSource->SetOwner(this);
		return _audioSource;
	}

	inline const std::vector<Collider*>& GetColliders() const
	{
		return _colliders;
	}

	inline Transform& GetTransform()
	{
		return _transform;
	}

	inline Mesh* GetMesh() const
	{
		return _mesh;
	}
};

