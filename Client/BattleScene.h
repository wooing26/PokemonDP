#pragma once
#include "Scene.h"

class BattleScene : public Scene
{
	using Super = Scene;
public:
	BattleScene();
	virtual ~BattleScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void AddActor(Actor* actor) override;
	virtual void RemoveActor(Actor* actor) override;

private:
	Vec2	_myPos = {0, (float)MainSizeY * 3};
	Vec2	_enemyPos = {(float)(MainSizeX - 20) * 3, 10 * 3};
};

