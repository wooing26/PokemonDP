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
	
	// ��ȣ Sprite
	for (int32 i = 0; i < 10; i++)
	{
		_numbers[i] = GET_SINGLE(ResourceManager)->GetSprite(std::to_wstring(i));
	}
	
	// HP Bar ������ Sprite
	_hpBar[0] = GET_SINGLE(ResourceManager)->GetSprite(L"LowHPBar");
	_hpBar[1] = GET_SINGLE(ResourceManager)->GetSprite(L"MiddleHPBar");
	_hpBar[2] = GET_SINGLE(ResourceManager)->GetSprite(L"HighHPBar");

	_currentHpBar = _hpBar[2];
	_standardHp = _status.maxHp;		// HP Bar ��ȯ�� ���� ���� HP

	// �� ���ϸ����� Ȯ��
	if (_isMine)
	{
		// Status Bar Sprite �ް�, ��ġ, ũ�� ����
		_statusBar = GET_SINGLE(ResourceManager)->GetSprite(L"My_HP_Male");
		_size = _statusBar->GetSize() * _ratio;
		_pos = Vec2(MainSizeX - _size.x, MainSizeY * 2 / 3);

		// �� ���ϸ� ����ġ ǥ��
		_expBar = GET_SINGLE(ResourceManager)->GetSprite(L"EXPBar");
		_status.exp = 0;
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

	if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::Left))
	{
		if (_status.hp > 0)
			_status.hp--;

		if (_status.exp > 0)
			_status.exp--;
	}
	else if (GET_SINGLE(InputManager)->GetButtonPress(KeyType::Right))
	{
		if (_status.hp < _status.maxHp)
			_status.hp++;

		if (_status.exp < _status.maxExp)
			_status.exp++;
	}


	// hp ũ�⿡ ���� hp �� ���� �� ���� hp ����
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
	bf.SourceConstantAlpha = 255;	// 0(����) ~ 255(������)
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
	
	// �� ���ϸ� ������
	if (_isMine)
	{
		// HP Bar
		Vec2Int size = _currentHpBar->GetSize();
		::AlphaBlend(hdc,
			_pos.x + _size.x * 31 / 60,
			_pos.y + _size.y * 19 / 41,
			size.x * _ratio * _status.hp / _standardHp,
			size.y * _ratio,
			_currentHpBar->GetDC(),
			_currentHpBar->GetPos().x,
			_currentHpBar->GetPos().y,
			size.x * _status.hp / _standardHp,
			size.y,
			bf);

		// HP ǥ��
		std::wstring hp = std::to_wstring(_status.hp);
		size = _numbers[0]->GetSize();
		for (int32 i = 0; i < hp.size(); i++)
		{
			::AlphaBlend(hdc,
				_pos.x + _size.x * 47 / 60 + size.x * _ratio * (-i - 2),
				_pos.y + _size.y * 6 / 9,
				size.x * _ratio,
				size.y * _ratio,
				_numbers[hp[hp.size() - 1 - i] - L'0']->GetDC(),
				_numbers[hp[hp.size() - 1 - i] - L'0']->GetPos().x,
				_numbers[hp[hp.size() - 1 - i] - L'0']->GetPos().y,
				size.x,
				size.y,
				bf);
		}

		// Max HP ǥ��
		std::wstring maxHp = std::to_wstring(_status.maxHp);
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
		::AlphaBlend(hdc,
			_pos.x + _size.x * 29 / 120,
			_pos.y + _size.y - size.y * _ratio,
			size.x * _ratio * _status.exp / _status.maxExp,
			size.y * _ratio,
			_expBar->GetDC(),
			_expBar->GetPos().x,
			_expBar->GetPos().y,
			size.x * _status.exp / _status.maxExp,
			size.y,
			bf);

		// Level
		std::wstring level = std::to_wstring(_status.level);
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
	}
	else
	{
		// ����� ���ϸ� ������
		// HP Bar
		Vec2Int size = _currentHpBar->GetSize();
		::AlphaBlend(hdc,
			_pos.x + _size.x * 281 / 672,
			_pos.y + _size.y * 19 / 30,
			size.x * _ratio * _status.hp / _standardHp,
			size.y * _ratio,
			_currentHpBar->GetDC(),
			_currentHpBar->GetPos().x,
			_currentHpBar->GetPos().y,
			size.x * _status.hp / _standardHp,
			size.y,
			bf);

		// Level
		std::wstring level = std::to_wstring(_status.level);
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
	}
}
