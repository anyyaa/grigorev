#include "draw.h"

void ClearDrawingArea(HWND hwnd) {
    HDC hdc = GetDC(hwnd);
    RECT rc;
    GetClientRect(hwnd, &rc);
    FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
    ReleaseDC(hwnd, hdc);
}

void DrawFixedLine(HDC hdc, POINT p1, POINT p2) {
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // Красное перо
    SelectObject(hdc, hPen);
    MoveToEx(hdc, p1.x, p1.y, NULL);
    LineTo(hdc, p2.x, p2.y);
    DeleteObject(hPen);
}
