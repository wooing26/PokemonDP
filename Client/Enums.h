#pragma once

enum class SceneType
{
	None,
	DevScene,
	EditScene,
	BattleScene
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_OBJECT,
	LAYER_EFFECT,
	LAYER_UI,

	LAYER_MAXCOUNT
};

enum Dir
{
	DIR_Up,
	DIR_Down,
	DIR_Left,
	DIR_Right
};

enum class ObjectState
{
	Idle,
	Move
};