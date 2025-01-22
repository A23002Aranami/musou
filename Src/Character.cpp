#include "Character.h"
#include "Animator.h"

Character::Character()
{
	animator = new Animator;
}

Character::~Character()
{
}

void Character::SetMesh(TCHAR* file)
{
	mesh = new CFbxMesh();
	mesh->Load(file);
}

void Character::Update()
{
}
