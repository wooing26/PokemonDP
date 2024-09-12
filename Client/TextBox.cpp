#include "pch.h"
#include "TextBox.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Sprite.h"

TextBox::TextBox()
{
}

TextBox::~TextBox()
{
}

void TextBox::BeginPlay()
{
	Super::BeginPlay();
	_textBox = GET_SINGLE(ResourceManager)->GetSprite(L"TextBox");

	_rect =
	{
		(int32)_pos.x - _size.x / 2 + 50,
		(int32)_pos.y - _size.y / 2 + 20,
		(int32)_pos.x + _size.x / 2 - 100,
		(int32)_pos.y + _size.y / 2 - 20,
	};
}

void TextBox::Tick()
{
	Super::Tick();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_idx < _texts[_textIdx].size())
	{
		_sumTime += deltaTime;
		if (_sumTime > 0.1f)
		{
			_currentText += _texts[_textIdx][_idx];
			if (_texts[_textIdx][_idx] == '\n')
			{
				_enterCount++;
				if (_enterCount == 2)
				{
					_currentText = _currentText.substr(_currentText.find('\n') + 1);
					_enterCount--;
				}
			}
			_idx++;
			_sumTime = 0.f;
		}
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Enter))
	{
		SetNextText();
	}
}

void TextBox::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_textBox == nullptr)
		return;

	::TransparentBlt(hdc,
		_pos.x - _size.x / 2,
		_pos.y - _size.y / 2,
		_size.x,
		_size.y,
		_textBox->GetDC(),
		_textBox->GetPos().x,
		_textBox->GetPos().y,
		_textBox->GetSize().x,
		_textBox->GetSize().y,
		_textBox->GetTransparent());

	Utils::DrawTextRect(hdc, _rect, _currentText);
}

void TextBox::SetNextText()
{
	if (_textIdx == _texts.size() - 1)
		return;

	_textIdx++;
	_currentText = L"";
	_idx = 0;
	_enterCount = 0;
}
