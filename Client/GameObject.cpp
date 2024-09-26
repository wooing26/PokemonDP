#include "pch.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::BeginPlay()
{
	Super::BeginPlay();
}

void GameObject::Tick()
{
	Super::Tick();

	switch (_state)
	{
	case ObjectState::Idle:
		TickIdle();
		break;
	case ObjectState::Move:
		TickMove();
		break;
	case ObjectState::Run:
		TickRun();
		break;
	case ObjectState::Battle:
		TickBattle();
		break;
	}
}

void GameObject::Render(HDC hdc)
{
	Super::Render(hdc);
}

void GameObject::SetState(ObjectState state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void GameObject::SetDir(Dir dir)
{
	_dir = dir;
	UpdateAnimation();
}

void GameObject::SetCellPos(Vec2Int cellPos, bool teleport)
{
	_cellPos = cellPos;

	Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();
	_destPos = scene->ConverPos(cellPos);

	if (teleport)
		_pos = _destPos;
}
