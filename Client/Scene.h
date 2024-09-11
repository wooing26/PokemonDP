#pragma once

class Actor;
class UI;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void			Init() abstract;
	virtual void			Update() abstract;
	virtual void			Render(HDC hdc) abstract;

	virtual void			AddActor(Actor* actor);
	virtual void			RemoveActor(Actor* actor);

	void					AddUI(std::shared_ptr<UI> ui);
	void					RemoveUI(std::shared_ptr<UI> ui);

	void					SetMainScreenSize(Vec2Int screenSize) { _mainScreenSize = screenSize; }
	const Vec2Int&			GetMainScreenSize() { return _mainScreenSize; }

	void					SetTouchScreenSize(Vec2Int screenSize) { _touchScreenSize = screenSize; }
	const Vec2Int&			GetTouchScreenSize() { return _touchScreenSize; }

	void					SetMapSize(Vec2 mapSize) { _mapSize = mapSize; }
	Vec2					GetMapSize() { return _mapSize; }

	void					SetSceneType(SceneType sceneType) { _sceneType = sceneType; }
	const SceneType&		GetSceneType() { return _sceneType; }

private:
	std::vector<Actor*>						_actors[LAYER_MAXCOUNT];
	std::vector<std::shared_ptr<UI>>		_uis;

	Vec2Int									_mainScreenSize = {MainSizeX, MainSizeY};
	Vec2Int									_touchScreenSize = {TouchSizeX, TouchSizeY};
	Vec2									_mapSize = {};

	SceneType								_sceneType = SceneType::None;
};

