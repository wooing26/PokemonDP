#include "pch.h"
#include "CameraComponent.h"
#include "Actor.h"
#include "SceneManager.h"
#include "Scene.h"

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::BeginPlay()
{
}

void CameraComponent::TickComponent()
{
	if (_owner == nullptr)
		return;

	Vec2 pos = _owner->GetPos();

	switch (GET_SINGLE(SceneManager)->GetSceneType())
	{
	case SceneType::TileMapScene:
		{
			Scene* scene = GET_SINGLE(SceneManager)->GetCurrentScene();
			Vec2 mapSize = scene->GetMapSize();

			pos.x = std::clamp(pos.x, GWinSizeX / 2.f, mapSize.x - (GWinSizeX / 2.f));
			pos.y = std::clamp(pos.y, GWinSizeY / 2.f, mapSize.y - (GWinSizeY / 2.f));
		}
	case SceneType::BattleScene:
		{
			// TODO
		}
	case SceneType::DevScene:
	{
		// TODO
	}
	case SceneType::EditScene:
	{
		// TODO
	}
	}
	
	GET_SINGLE(SceneManager)->SetCameraPos(pos);
}

void CameraComponent::Render(HDC hdc)
{
}
