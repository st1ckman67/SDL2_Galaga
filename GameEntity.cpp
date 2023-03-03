#include "GameEntity.h"

GameEntity::GameEntity(float x, float y)
{
	mPos.x = x;
	mPos.y = y;

	mRotation = 0.0f;

	mActive = true;
	
	mParent = NULL;
}

GameEntity::~GameEntity()
{
	mParent = NULL;
}

void GameEntity::Pos(Vector2 pos)
{
	mPos = pos;
}

Vector2 GameEntity::Pos(SPACE space)
{
	if (space == local || mParent == NULL)
		return mPos;

	return mParent->Pos(world) + RotateVector(mPos, mParent->Rotation(local));
}

void GameEntity::Rotation(float r)
{
	mRotation = r;

	if (mRotation > 360.0f)
	{
		int mul = mRotation / 360;
		mRotation -= 360.0f * mul;
	}

	if (mRotation < 0.0f)
	{
		int mul = (mRotation / 360) - 1;
		mRotation -= 360.0f * mul;
	}
}

float GameEntity::Rotation(SPACE space)
{
	if (space == local || mParent == NULL)
		return mRotation;

	return mParent->Rotation(world) + mRotation;
}

void GameEntity::Active(bool active)
{
	mActive = active;
}

bool GameEntity::Active()
{
	return mActive;
}

void GameEntity::Parent(GameEntity* parent)
{
	mPos = Pos(world) - parent->Pos(world);

	mParent = parent;
}

GameEntity* GameEntity::Parent()
{
	return mParent;
}

void GameEntity::Update()
{

}

void GameEntity::Render()
{

}

