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

	void			SetMainScreenSize(Vec2Int screenSize) { _mainScreenSize = screenSize; }
	const Vec2Int&	GetMainScreenSize() { return _mainScreenSize; }

	void			SetTouchScreenSize(Vec2Int screenSize) { _touchScreenSize = screenSize; }
	const Vec2Int&	GetTouchScreenSize() { return _touchScreenSize; }


private:
	vector<Actor*>	_actors[LAYER_MAXCOUNT];
	vector<UI*>		_uis;

	Vec2Int			_mainScreenSize = {MainSizeX * 3, MainSizeY * 3};
	Vec2Int			_touchScreenSize = {TouchSizeX * 2, TouchSizeY * 2};
};

