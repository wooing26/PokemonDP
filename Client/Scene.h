#pragma once

class Actor;
class UI;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void	Init() abstract;
	virtual void	Update() abstract;
	virtual void	Render(HDC hdc) abstract;

	virtual void	AddActor(Actor* actor);
	virtual void	RemoveActor(Actor* actor);

	void			AddUI(UI* ui);
	void			RemoveUI(UI* ui);

	void			SetMainScreenSize(Vec2Int screenSize) { _mainScreenSize = screenSize; }
	const Vec2Int&	GetMainScreenSize() { return _mainScreenSize; }

	void			SetTouchScreenSize(Vec2Int screenSize) { _touchScreenSize = screenSize; }
	const Vec2Int&	GetTouchScreenSize() { return _touchScreenSize; }

	void			SetMapSize(Vec2 mapSize) { _mapSize = mapSize; }
	Vec2			GetMapSize() { return _mapSize; }

private:
	std::vector<Actor*>		_actors[LAYER_MAXCOUNT];
	std::vector<UI*>		_uis;

	Vec2Int					_mainScreenSize = {MainSizeX * 3, MainSizeY * 3};
	Vec2Int					_touchScreenSize = {TouchSizeX * 2, TouchSizeY * 2};
	Vec2					_mapSize = {};
};

