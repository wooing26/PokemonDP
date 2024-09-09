#include "pch.h"
#include "Panel.h"

Panel::Panel()
{
}

Panel::~Panel()
{
	for (std::shared_ptr<UI> child : _children)
		child = nullptr;

	_children.clear();
}

void Panel::BeginPlay()
{
	Super::BeginPlay();

	for (std::shared_ptr<UI> child : _children)
		child->BeginPlay();
}

void Panel::Tick()
{
	Super::Tick();

	for (std::shared_ptr<UI> child : _children)
	{
		if (child)
			child->Tick();
	}
		
}

void Panel::Render(HDC hdc)
{
	Super::Render(hdc);

	for (std::shared_ptr<UI> child : _children)
		child->Render(hdc);
}

void Panel::AddChild(UI* ui)
{
	if (ui == nullptr)
		return;

	_children.push_back(std::make_shared<UI>(ui));
}

bool Panel::RemoveChild(UI* ui)
{
	auto findIt = std::find(_children.begin(), _children.end(), ui);
	if (findIt == _children.end())
		return false;

	_children.erase(findIt);
	return true;
}
