#include "pch.h"
#include "FlipbookActor.h"
#include "Flipbook.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Texture.h"

FlipbookActor::FlipbookActor()
{
}

FlipbookActor::~FlipbookActor()
{
}

void FlipbookActor::BeginPlay()
{
	Super::BeginPlay();
}

void FlipbookActor::Tick()
{
	Super::Tick();

	if (_flipbook == nullptr)
		return;

	const FlipbookInfo& info = _flipbook->GetInfo();
	if (info.loop == false && _idx == info.end)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_sumTime += deltaTime;

	int32 frameCount = (info.end - info.start + 1);
	float delta = info.duration / frameCount;

	if (_sumTime >= delta)
	{
		_sumTime = 0.f;
		_idx = (_idx + 1) % frameCount;
	}
}

void FlipbookActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_flipbook == nullptr)
		return;

	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
	const FlipbookInfo& info = _flipbook->GetInfo();

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;	// 0(투명) ~ 255(불투명)
	bf.AlphaFormat = AC_SRC_ALPHA;

	::AlphaBlend(hdc,
		_pos.x - _size.x / 2,
		_pos.y - _size.y / 2,
		_size.x,
		_size.y,
		info.texture->GetDC(),
		(info.start + _idx) * info.size.x,
		info.line * info.size.y,
		info.size.x,
		info.size.y,
		bf);
}

void FlipbookActor::SetFlipbook(Flipbook* flipbook)
{
	if (flipbook == nullptr)
		return;

	_flipbook = flipbook;
	Vec2Int size = flipbook->GetInfo().size;
	SetSize(size * _sizeRatio);
}

void FlipbookActor::Reset()
{
	_sumTime = 0.f;
	_idx = 0;
}
