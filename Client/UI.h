#pragma once

class UI
{
public:
	UI();
	virtual ~UI();

	virtual void	BeginPlay();
	virtual void	Tick();
	virtual void	Render(HDC hdc);

	void			SetPos(Vec2 pos) { _pos = pos; }
	Vec2			GetPos() { return _pos; }

	void			SetSize(Vec2Int size) { _size = size; }
	Vec2Int			GetSize() { return _size; }

	RECT			GetRect();
	bool			IsMouseInRect();

protected:
	Vec2		_pos = { 400, 300 };
	Vec2Int		_size = {300, 143};
};

