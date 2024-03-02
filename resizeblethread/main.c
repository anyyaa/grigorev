#include <windows.h>
#include "draw.h"
#include "koch.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

POINT startPoint = { 0 };
POINT endPoint = { 0 };
BOOL isDrawing = FALSE;
BOOL isLineFixed = FALSE;
int clickCount = 0;
int downArrowCount = 0; 
HDC hdcMem = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"ResizableThread";
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        L"ResizableThread",
        L"Resizable Thread",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_RBUTTONDOWN:
        
        clickCount++;
        if (clickCount % 2 == 0) {
            isDrawing = FALSE;
            isLineFixed = TRUE;
            downArrowCount = 0; 
            InvalidateRect(hwnd, NULL, TRUE); 
        }
        if (clickCount % 2 == 1) {
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
            endPoint = startPoint;
            isDrawing = TRUE;
            isLineFixed = FALSE;
            InvalidateRect(hwnd, NULL, TRUE); 
        }
        break;

    case WM_MOUSEMOVE:
        if (isDrawing && !isLineFixed) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hwnd, NULL, TRUE); 
        }
        break;

    case WM_KEYDOWN:
        if (wParam == VK_UP) {
            downArrowCount++;
           
            InvalidateRect(hwnd, NULL, TRUE); 
        }
        else if (wParam == VK_DOWN && downArrowCount > 0) {
            downArrowCount--;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        hdcMem = BeginPaint(hwnd, &ps);
        ClearDrawingArea(hwnd);
        if (isDrawing) {
            DrawFixedLine(hdcMem, startPoint, endPoint);
        }
        else {
            if (isLineFixed) { 
                DrawFixedLine(hdcMem, startPoint, endPoint);
                DrawKochCurve(hdcMem, startPoint, endPoint, downArrowCount);
            }
        }
        EndPaint(hwnd, &ps);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}
