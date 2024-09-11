#pragma once

class Texture;

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void	BeginPlay();
	virtual void	Tick();
	virtual void	Render(HDC hdc);

	void			SetPos(Vec2 pos) { _pos = pos; }
	Vec2			GetPos() { return _pos; }

	void			SetLayer(LAYER_TYPE layer) { _layer = layer; }
	LAYER_TYPE		GetLayer() { return _layer; }

	void			SetSize(Vec2Int size) { _size = size; }
	Vec2Int			GetSize() { return _size; }

protected:
	Vec2		_pos = {0, 0};
	Vec2		_destPos = { 0, 0 };
	LAYER_TYPE	_layer = LAYER_OBJECT;

	Vec2Int		_size = {};
};

