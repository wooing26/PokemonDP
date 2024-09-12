#pragma once
#include "UI.h"

class Sprite;

enum class TextStyle
{
	OverworldText,
	BattleText
};

class TextBox : public UI
{
	using Super = UI;
public:
	TextBox();
	virtual ~TextBox() override;

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	void			SetTextStyle(TextStyle textStyle) { _textStyle = textStyle; }

	void			SetText(std::wstring text) { _currentText = text; }
	void			SetTextZip(const std::vector<std::wstring>& texts) { _texts = texts; }
	void			SetNextText();

private:
	Sprite*						_textBox = nullptr;
	std::wstring				_currentText = L"";
	std::vector<std::wstring>	_texts = {};
	int32						_textIdx = 0;

	RECT						_rect = {};
	float						_sumTime = 0.f;
	int32						_idx = 0;
	int32						_enterCount = 0;

	TextStyle					_textStyle = TextStyle::OverworldText;
};

