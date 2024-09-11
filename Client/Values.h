#pragma once

const int32 MainScreenRatio = 4;
const int32 MainSizeX = 256 * MainScreenRatio;
const int32 MainSizeY = 144 * MainScreenRatio;

const int32 TouchScreenRatio = 2;
const int32 TouchSizeX = 256 * TouchScreenRatio;
const int32 TouchSizeY = 192 * TouchScreenRatio;

const int32 GWinSizeX = ::GetSystemMetrics(SM_CXSCREEN); 
const int32 GWinSizeY = ::GetSystemMetrics(SM_CYSCREEN);
/*const int32 GWinSizeX = MainSizeX + TouchSizeX;
const int32 GWinSizeY = MainSizeY + TouchSizeY;*/ 

const float PI = 3.1415926f;