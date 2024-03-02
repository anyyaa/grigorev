#pragma once
#ifndef DRAW_H
#define DRAW_H

#include <windows.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void ClearDrawingArea(HWND hwnd);
void DrawFixedLine(HDC hdc);

#endif
