#include "pch.h"
#include "HpBar.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Sprite.h"

HpBar::HpBar()
{
}

HpBar::~HpBar()
{
	int32 a = 3;
}

void HpBar::BeginPlay()
{
	Super::BeginPlay();
	
	// 번호 Sprite
	for (int32 i = 0; i < 10; i++)
	{
		_numbers[i] = GET_SINGLE(ResourceManager)->GetSprite(std::to_wstring(i));
	}
	
	// HP Bar 종류별 Sprite
	_hpBar[0] = GET_SINGLE(ResourceManager)->GetSprite(L"LowHPBar");
	_hpBar[1] = GET_SINGLE(ResourceManager)->GetSprite(L"MiddleHPBar");
	_hpBar[2] = GET_SINGLE(ResourceManager)->GetSprite(L"HighHPBar");

	_currentHpBar = _hpBar[2];
	_standardHp = _status.maxHp;		// HP Bar 변환을 위한 기준 HP

	// 내 포켓몬인지 확인
	if (_isMine)
	{
		// Status Bar Sprite 받고, 위치, 크기 조정
		_statusBar = GET_SINGLE(ResourceManager)->GetSprite(L"My_HP_Male");
		_size = _statusBar->GetSize() * _ratio;
		_pos = Vec2(MainSizeX - _size.x, MainSizeY * 2 / 3);

		// 내 포켓몬만 경험치 표시
		_expBar = GET_SINGLE(ResourceManager)->GetSprite(L"EXPBar");
		_status.exp = 0;
	}
	else
	{
		_statusBar = GET_SINGLE(ResourceManager)->GetSprite(L"Other_HP_Male");
		_size = _statusBar->GetSize() * _ratio;
		_pos = Vec2(0, MainSizeY * 1 / 5);
	}
}

void HpBar::Tick()
{
	Super::Tick();

	if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::Left))
	{
		if (_status.hp >= 0)
			_status.hp--;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::Right))
	{
		if (_status.hp <= _status.maxHp)
			_status.hp++;
	}


	if (_status.exp <= _status.maxExp)
		_status.exp++;

	// hp 크기에 따른 hp 바 선택 및 기준 hp 변경
	if (_status.hp > _status.maxHp / 2)
	{
		_standardHp = _status.maxHp;
		_currentHpBar = _hpBar[2];
	}
	else if (_status.hp > _status.maxHp / 4)
	{
		_standardHp = _status.maxHp / 2;
		_currentHpBar = _hpBar[1];
	}
	else
	{
		_standardHp = _status.maxHp / 4;
		_currentHpBar = _hpBar[0];
	}
	
}

void HpBar::Render(HDC hdc)
{
	Super::Render(hdc);

	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 255;	// 0(투명) ~ 255(불투명)
	bf.AlphaFormat = AC_SRC_ALPHA;

	// Status Bar
	::AlphaBlend(hdc,
		_pos.x,
		_pos.y,
		_size.x,
		_size.y,
		_statusBar->GetDC(),
		_statusBar->GetPos().x,
		_statusBar->GetPos().y,
		_statusBar->GetSize().x,
		_statusBar->GetSize().y,
		bf);
	
	// 내 포켓몬 렌더링
	if (_isMine)
	{
		// HP Bar
		Vec2Int size = _currentHpBar->GetSize() * _ratio;
		::AlphaBlend(hdc,
			_pos.x + _size.x * 31 / 60,
			_pos.y + _size.y * 19 / 41,
			size.x * _status.hp / _standardHp,
			size.y,
			_currentHpBar->GetDC(),
			_currentHpBar->GetPos().x,
			_currentHpBar->GetPos().y,
			_currentHpBar->GetSize().x * _status.hp / _standardHp,
			_currentHpBar->GetSize().y,
			bf);

		// EXP Bar
		size = _expBar->GetSize() * _ratio;
		::AlphaBlend(hdc,
			_pos.x + _size.x * 23 / (24 * _ratio),
			_pos.y + _size.y - size.y,
			size.x * _status.exp / _status.maxExp,
			size.y,
			_expBar->GetDC(),
			_expBar->GetPos().x,
			_expBar->GetPos().y,
			_expBar->GetSize().x * _status.exp / _status.maxExp,
			_expBar->GetSize().y,
			bf);
	}
	else
	{
		// 상대편 포켓몬 렌더링
		// HP Bar
		Vec2Int size = _currentHpBar->GetSize() * _ratio;
		::AlphaBlend(hdc,
			_pos.x + _size.x * 3 / 7 - 5,
			_pos.y + _size.y * 6 / 10 + 4,
			size.x * _status.hp / _standardHp,
			size.y,
			_currentHpBar->GetDC(),
			_currentHpBar->GetPos().x,
			_currentHpBar->GetPos().y,
			_currentHpBar->GetSize().x * _status.hp / _standardHp,
			_currentHpBar->GetSize().y,
			bf);
	}
}
