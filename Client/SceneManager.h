#pragma once

class Scene;

class SceneManager
{
	DECLARE_SINGLE(SceneManager)
public:
	void		Init();
	void		Update();
	void		Render(HDC hdc);

	void		Clear();

public:
	void		ChangeScene(SceneType sceneType);
	Scene*		GetCurrentScene() { return _scene; }
	SceneType	GetSceneType() { return _sceneType; }

private:
	Scene*		_scene;
	SceneType	_sceneType = SceneType::None;

public:
	void		SetCameraPos(Vec2 pos) { _cameraPos = pos; }
	Vec2		GetCameraPos() { return _cameraPos; }

private:
	Vec2		_cameraPos = {GWinSizeX / 2, GWinSizeY / 2};
};

