#pragma once
#include "Scene.h"

class BattleScene : public Scene
{
	using Super = Scene;
public:
	BattleScene();
	virtual ~BattleScene();

	virtual void	Init() override;
	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;

	virtual void	AddActor(Actor* actor) override;
	virtual void	RemoveActor(Actor* actor) override;

	void			LoadMap();
	void			LoadTouchScreen();
	void			LoadPlayer();
	void			LoadPokemon();


private:
	Vec2	_myPos = {0, (float)MainSizeY};
	Vec2	_enemyPos = {(float)(MainSizeX - 20), 10 * 3};
};

