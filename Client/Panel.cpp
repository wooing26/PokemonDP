#include "pch.h"
#include "Panel.h"

Panel::Panel()
{
}

Panel::~Panel()
{
	for (std::shared_ptr<UI>& child : _children)
		child = nullptr;

	_children.clear();
}

void Panel::BeginPlay()
{
	Super::BeginPlay();

	for (const std::shared_ptr<UI>& child : _children)
		child->BeginPlay();
}

void Panel::Tick()
{
	Super::Tick();

	for (std::shared_ptr<UI> child : _children)
	{
		child->Tick();
	}
		
}

void Panel::Render(HDC hdc)
{
	Super::Render(hdc);

	for (const std::shared_ptr<UI>& child : _children)
		child->Render(hdc);
}

void Panel::AddChild(std::shared_ptr<UI> ui)
{
	if (ui == nullptr)
		return;

	_children.push_back(ui);
}

bool Panel::RemoveChild(std::shared_ptr<UI> ui)
{
	auto findIt = std::find(_children.begin(), _children.end(), ui);
	if (findIt == _children.end())
		return false;

	findIt->reset();
	_children.erase(findIt);
	return true;
}

std::shared_ptr<UI> Panel::GetChild(int32 index)
{
	if (index >= _children.size())
		return nullptr;

	return _children[index];
}

