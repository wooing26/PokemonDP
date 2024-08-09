#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "BattleScene.h"

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	if (_scene)
		_scene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)
		_scene->Render(hdc);
}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType)
		return;

	Scene* newScene = nullptr;
	switch (sceneType)
	{
	case SceneType::DevScene:
		break;
	case SceneType::EditScene:
		break;
	case SceneType::BattleScene:
		newScene = new BattleScene();
		break;
	}

	SAFE_DELETE(_scene);

	_scene = newScene;
	_sceneType = sceneType;

	newScene->Init();
}
