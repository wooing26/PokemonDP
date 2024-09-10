#pragma once
#include "UI.h"

class Panel : public UI
{
	using Super = UI;
public:
	Panel();
	virtual ~Panel() override;

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	void			AddChild(std::shared_ptr<UI> ui);
	bool			RemoveChild(std::shared_ptr<UI> ui);

private:
	std::vector<std::shared_ptr<UI>>	_children;
};

