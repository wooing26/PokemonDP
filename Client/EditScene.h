#pragma once
#include "Scene.h"

class EditScene : public Scene
{
	using Super = Scene;
public:
	EditScene();
	virtual ~EditScene();

	virtual void	Init() override;
	virtual void	Update() override;
	virtual void	Render(HDC hdc) override;

	virtual void	AddActor(Actor* actor) override;
	virtual void	RemoveActor(Actor* actor) override;

	void			ChangeBattle();
	void			ChangeTilemap();

private:
	SceneType		_sceneType = SceneType::EditScene;
};

