#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "UI.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	for (const std::vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			SAFE_DELETE(actor);
	
	_actors->clear();

	for (std::shared_ptr<UI>& ui : _uis)
		ui = nullptr;

	_uis.clear();
}

void Scene::Init()
{
	for (const std::vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->BeginPlay();

	for (std::shared_ptr<UI>& ui : _uis)
		ui->BeginPlay();
}

void Scene::Update()
{
	for (const std::vector<Actor*> actors : _actors)
		for (Actor* actor : actors)
			actor->Tick();

	for (std::shared_ptr<UI>& ui : _uis)
		if (ui != NULL)
			ui->Tick();
}

void Scene::Render(HDC hdc)
{
	for (const std::vector<Actor*>& actors : _actors)
		for (Actor* actor : actors)
			actor->Render(hdc);

	for (std::shared_ptr<UI>& ui : _uis)
		ui->Render(hdc);
}

void Scene::AddActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	_actors[actor->GetLayer()].push_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	std::vector<Actor*>& v = _actors[actor->GetLayer()];
	v.erase(std::remove(v.begin(), v.end(), actor), v.end());
}

void Scene::AddUI(std::shared_ptr<UI> ui)
{
	if (ui == nullptr)
		return;

	_uis.push_back(ui);
}

void Scene::RemoveUI(std::shared_ptr<UI> ui)
{
	if (ui == nullptr)
		return;

	_uis.erase(std::remove(_uis.begin(), _uis.end(), ui), _uis.end());
}

Vec2 Scene::ConverPos(Vec2Int cellPos)
{
	Vec2 ret = {};

	Vec2Int size = { 32, 32 };

	ret.x = cellPos.x * size.x + (size.x / 2);
	ret.y = cellPos.y * size.y + (size.y / 2);

	return ret;
}
