#include "koch.h"
#include <math.h>
#include <windows.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void DrawKochCurve(HDC hdc, POINT pointStart, POINT pointEnd, int n) {
    if (n == 0) {
        MoveToEx(hdc, pointStart.x, pointStart.y, NULL);
        LineTo(hdc, pointEnd.x, pointEnd.y);
    }
    else {
        double angle = M_PI / 3.0; 
        int deltaX = pointEnd.x - pointStart.x;
        int deltaY = pointEnd.y - pointStart.y;

        
        int x3 = pointStart.x + deltaX / 3;
        int y3 = pointStart.y + deltaY / 3;
        POINT point3 = { x3, y3 };

        int x4 = (int)(0.5 * (pointStart.x + pointEnd.x) + sqrt(3) * (pointStart.y - pointEnd.y) / 6);
        int y4 = (int)(0.5 * (pointStart.y + pointEnd.y) + sqrt(3) * (pointEnd.x - pointStart.x) / 6);
        POINT point4 = { x4, y4 };

        int x5 = pointStart.x + 2 * deltaX / 3;
        int y5 = pointStart.y + 2 * deltaY / 3;
        POINT point5 = { x5, y5 };


        
        DrawKochCurve(hdc, pointStart, point3, n - 1);
        DrawKochCurve(hdc, point3, point4, n - 1);
        DrawKochCurve(hdc, point4, point5, n - 1);
        DrawKochCurve(hdc, point5, pointEnd, n - 1);
    }
}
