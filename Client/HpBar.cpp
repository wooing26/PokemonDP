#include "pch.h"
#include "HpBar.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Sprite.h"
#include "Pokemon.h"

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
	_standardHp = _pokemon->GetStat().hp;		// HP Bar 변환을 위한 기준 HP

	// 내 포켓몬인지 확인
	if (_isMine)
	{
		// Status Bar Sprite 받고, 위치, 크기 조정
		_statusBar = GET_SINGLE(ResourceManager)->GetSprite(L"My_HP_Male");
		_size = _statusBar->GetSize() * _ratio;
		_pos = Vec2(MainSizeX - _size.x, MainSizeY * 2 / 3);

		// 내 포켓몬만 경험치 표시
		_expBar = GET_SINGLE(ResourceManager)->GetSprite(L"EXPBar");
	}
	else
	{
		_statusBar = GET_SINGLE(ResourceManager)->GetSprite(L"Enemy_HP_Male");
		_size = _statusBar->GetSize() * _ratio;
		_pos = Vec2(0, MainSizeY * 1 / 5);
	}
}

void HpBar::Tick()
{
	Super::Tick();

	int32 maxHp = _pokemon->GetStat().hp;
	int32 hp = _pokemon->GetHp();
	int32 exp = _pokemon->GetExp();
	int32 maxExp = _pokemon->GetMaxExp();

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Left))
	{
		if (hp > 0)
			_pokemon->AddHp(-100);

		if (exp > 0)
			_pokemon->AddExp(-100);
	}
	else if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Right))
	{
		if (hp < maxHp)
			_pokemon->AddHp(100);

		if (exp < maxExp)
			_pokemon->AddExp(100);
	}


	// hp 크기에 따른 hp 바 선택 및 기준 hp 변경
	
	if (hp > maxHp / 2)
	{
		_standardHp = maxHp;
		_currentHpBar = _hpBar[2];
	}
	else if (hp > maxHp / 4)
	{
		_standardHp = maxHp / 2;
		_currentHpBar = _hpBar[1];
	}
	else
	{
		_standardHp = maxHp / 4;
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
		int32 hp = _pokemon->GetHp();
		Vec2Int size = _currentHpBar->GetSize();
		::AlphaBlend(hdc,
			_pos.x + _size.x * 31 / 60,
			_pos.y + _size.y * 19 / 41,
			size.x * _ratio * hp / _standardHp,
			size.y * _ratio,
			_currentHpBar->GetDC(),
			_currentHpBar->GetPos().x,
			_currentHpBar->GetPos().y,
			size.x * hp / _standardHp,
			size.y,
			bf);

		// HP 표시
		std::wstring hp_string = std::to_wstring(hp);
		size = _numbers[0]->GetSize();
		for (int32 i = 0; i < hp_string.size(); i++)
		{
			::AlphaBlend(hdc,
				_pos.x + _size.x * 47 / 60 + size.x * _ratio * (-i - 2),
				_pos.y + _size.y * 6 / 9,
				size.x * _ratio,
				size.y * _ratio,
				_numbers[hp_string[hp_string.size() - 1 - i] - L'0']->GetDC(),
				_numbers[hp_string[hp_string.size() - 1 - i] - L'0']->GetPos().x,
				_numbers[hp_string[hp_string.size() - 1 - i] - L'0']->GetPos().y,
				size.x,
				size.y,
				bf);
		}

		// Max HP 표시
		std::wstring maxHp = std::to_wstring(_pokemon->GetStat().hp);
		size = _numbers[0]->GetSize();
		for (int32 i = 0; i < maxHp.size(); i++)
		{
			::AlphaBlend(hdc,
				_pos.x + _size.x * 47 / 60 + size.x * _ratio * i,
				_pos.y + _size.y * 6 / 9,
				size.x * _ratio,
				size.y * _ratio,
				_numbers[maxHp[i] - L'0']->GetDC(),
				_numbers[maxHp[i] - L'0']->GetPos().x,
				_numbers[maxHp[i] - L'0']->GetPos().y,
				size.x,
				size.y,
				bf);
		}

		// EXP Bar
		size = _expBar->GetSize();
		int32 exp = _pokemon->GetExp();
		::AlphaBlend(hdc,
			_pos.x + _size.x * 29 / 120,
			_pos.y + _size.y - size.y * _ratio,
			size.x * _ratio * _pokemon->GetExp() / _pokemon->GetMaxExp(),
			size.y * _ratio,
			_expBar->GetDC(),
			_expBar->GetPos().x,
			_expBar->GetPos().y,
			size.x * _pokemon->GetExp() / _pokemon->GetMaxExp(),
			size.y,
			bf);

		// Level
		std::wstring level = std::to_wstring(_pokemon->GetLevel());
		size = _numbers[0]->GetSize();
		for (int32 i = 0; i < level.size(); i++)
		{
			::AlphaBlend(hdc,
				_pos.x + _size.x * 47 / 60 + size.x * _ratio * i,
				_pos.y + _size.y * 8 / 41,
				size.x * _ratio,
				size.y * _ratio,
				_numbers[level[i] - L'0']->GetDC(),
				_numbers[level[i] - L'0']->GetPos().x,
				_numbers[level[i] - L'0']->GetPos().y,
				size.x,
				size.y,
				bf);
		}

		// Name
		Utils::DrawTextSize(hdc,
			{
				(int32)_pos.x + _size.x * 2 / 15, 
				(int32)_pos.y + _size.y * 2 / 13
			}, 
			40, _pokemon->GetName());
	}
	else
	{
		// 상대편 포켓몬 렌더링
		// HP Bar
		int32 hp = _pokemon->GetHp();
		Vec2Int size = _currentHpBar->GetSize();
		::AlphaBlend(hdc,
			_pos.x + _size.x * 281 / 672,
			_pos.y + _size.y * 19 / 30,
			size.x * _ratio * hp / _standardHp,
			size.y * _ratio,
			_currentHpBar->GetDC(),
			_currentHpBar->GetPos().x,
			_currentHpBar->GetPos().y,
			size.x * hp / _standardHp,
			size.y,
			bf);

		// Level
		std::wstring level = std::to_wstring(_pokemon->GetLevel());
		size = _numbers[0]->GetSize();
		for (int32 i = 0; i < level.size(); i++)
		{
			::AlphaBlend(hdc,
				_pos.x + _size.x * 41/ 60 + size.x * _ratio * i,
				_pos.y + _size.y * 4 / 15,
				size.x * _ratio,
				size.y * _ratio,
				_numbers[level[i] - L'0']->GetDC(),
				_numbers[level[i] - L'0']->GetPos().x,
				_numbers[level[i] - L'0']->GetPos().y,
				size.x,
				size.y,
				bf);
		}

		// Name
		Utils::DrawTextSize(hdc,
			{
				(int32)_pos.x + _size.x * 1 / 20,
				(int32)_pos.y + _size.y * 2 / 13
			},
			40, _pokemon->GetName());
	}
}

void HpBar::SetPokemon(Pokemon* pokemon)
{
	if (pokemon == nullptr)
		return;

	_pokemon = pokemon;
}
