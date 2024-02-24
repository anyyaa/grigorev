#include <windows.h>
#include  <WindowsX.h>

#define MAX_TRAIL_POINTS 16
#define MAX_DISTANCE 200
#define real_radius 20
typedef struct
{
    int x;
    int y;
} TrailPoint;

TrailPoint trailPoints[MAX_TRAIL_POINTS];
int trailIndex = 0;
int trailCount = 0;


void check_distance(x, y) {
    for (int i = 0; i < trailCount; i++)
    {
        int distance = abs(trailPoints[i].x - x) + abs(trailPoints[i].y - y);
        if (distance > MAX_DISTANCE)
        {
            for (int j = i; j < trailCount - 1; j++)
            {
                trailPoints[j] = trailPoints[j + 1];
            }
            trailCount--;
            i--;
        }
    }
}

void make_trail(x, y) {
    TrailPoint newPoint = { x, y };
    if (trailCount < MAX_TRAIL_POINTS) {
        trailPoints[trailIndex] = newPoint;
        trailCount++;
    }
    else {
        for (int i = 0; i < MAX_TRAIL_POINTS - 1; i++) {
            trailPoints[i] = trailPoints[i + 1];
        }
        trailPoints[MAX_TRAIL_POINTS - 1] = newPoint;
    }
    trailIndex = (trailIndex + 1) % MAX_TRAIL_POINTS;
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("MovingBall");
    HWND         hwnd;
    MSG          msg;
    WNDCLASS     wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;
    
    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"),
            szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, TEXT("Moving Ball"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);
    DeleteObject(hBrush);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int cxClient, cyClient;
    static int x, y;
    static int dx, dy;    

    switch (message)
    {
    case WM_CREATE:
    {   
        x = 200;
        y = 200;
        dx = 5;
        dy = 5;
        return 0;
    }
    case WM_SIZE:
    {
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        return 0;

    }    
   
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC         hdc;
        HBRUSH      hBrush, hBrush1;
        hdc = BeginPaint(hwnd, &ps);
        hBrush = CreateSolidBrush(RGB(255, 20, 147));
        hBrush1 = CreateSolidBrush(RGB(255, 192, 203));
        SelectObject(hdc, hBrush);
        Ellipse(hdc, x - real_radius, y - real_radius, x + real_radius, y + real_radius);
        check_distance(x, y);
        SelectObject(hdc, hBrush1);
        int start = 0;
        int end = trailCount / 4;
        int delta = trailCount / 4;
        int rad = 9;
        
        if (trailCount == MAX_TRAIL_POINTS) {
            for (int j = 0; j < 4; j++) {
                for (int i = start; i < end; i++)
                {
                    Ellipse(hdc, trailPoints[i].x - rad, trailPoints[i].y - rad, 
                        trailPoints[i].x + rad, trailPoints[i].y + rad);
                }
                start = start + delta;
                end = end + delta;
                rad += 3;
            }
        }
        else {
            for (int i = 0; i < trailCount; i++)
            {
                Ellipse(hdc, trailPoints[i].x - 16, trailPoints[i].y - 16, 
                    trailPoints[i].x + 16, trailPoints[i].y + 16);
            }
        
        }

        
        DeleteObject(hBrush);
        DeleteObject(hBrush1);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_KEYDOWN:
    {   
        switch (wParam)
        {
        case VK_LEFT:
            x -= 10;
            if (x - real_radius>0)
            make_trail(x + real_radius, y);
            break;

        case VK_RIGHT:
            x += 10;
            if (x + real_radius < cxClient)
            make_trail(x - real_radius, y);
            break;

        case VK_UP:
            y -= 10;
            if (y - real_radius > 0)
            make_trail(x, y + real_radius);
            break;

        case VK_DOWN:
            y += 10;
            if (y + real_radius < cyClient)
            make_trail(x, y - real_radius);
            break;
        }
        if (x - real_radius < 0)
            x = real_radius;
        if (x + real_radius > cxClient)
            x = cxClient - real_radius;
        if (y - real_radius < 0)
            y = real_radius;
        if (y + real_radius > cyClient)
            y = cyClient - real_radius;
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    }
    case WM_DESTROY:
        KillTimer(hwnd, 10);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
