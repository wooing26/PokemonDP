#pragma once

enum
{
	PokemonMaxCount = 251
};

class InfoManager
{
	DECLARE_SINGLE(InfoManager);

	~InfoManager();
public:
	void Init();
	void Clear();

private:
	

};

