#include <Windows.h>

template <typename T>
void presentation(T& obj, int i);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIstance, PSTR szCmdLine, int iCmdShow)
{
	const char szAppName[] = "Hierarchy";
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		// в случае отсутстви€ регистрации класса:
		MessageBox(NULL, "Ќе получилось зарегистрировать класс!", "ќшибка", MB_OK);
		return NULL; // возвращаем, следовательно, выходим из WinMain
	}

	hwnd = CreateWindow(szAppName,
		"Hierarchy",
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT,
		NULL,
		900, 900,
		(HWND)NULL,
		NULL,
		HINSTANCE(hInstance),
		NULL);

	if (!hwnd)
	{
		MessageBox(NULL, "ƒа не открываетс€", "Error", MB_OK);
		return NULL;
	}

	ShowWindow(hwnd, SW_NORMAL);
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
	static HDC hdc;
	PAINTSTRUCT ps;
	static RECT rect;
	static int cxClient, cyClient, i = -1;
	HBRUSH hBrush;
	KFlag flag(KPoint(1, 3), 4, 7);
	KHalfEllipse Ellipse(KPoint(2, 0), 6, 8);
	KFlagFilled flagF( KPoint(0, 2), 
		 6, 8, 0, RGB(0, 200,0) );

	switch (message)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &rect);
		hdc = GetDC(hwnd);
		break;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		break;

	case WM_PAINT:
	{
		
		hdc = BeginPaint(hwnd, &ps);

		//set of context
		flag.setDC(hdc);
		Ellipse.setDC(hdc);
		flagF.setDC(hdc);
		
		// drawing of axes:
		MoveToEx(hdc, cxClient / 2, 0, NULL);
		LineTo(hdc, cxClient / 2, cyClient);
		MoveToEx(hdc, 0, cyClient / 2, NULL);
		LineTo(hdc, cxClient, cyClient / 2);

		// settings of logic units
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, cxClient, cyClient, NULL);
		SetViewportExtEx(hdc, cxClient / 2, -cyClient / 2, NULL);
		SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);
		
		/*flag.Draw();
		flag.Show();
		flag.Rotate(50);
		flag.Draw();
		flag.Show();
*/

		if (i == 15) { i = 0; }
		if (i < 5) {
			presentation(flag, i);
		}
		else
			if (i < 10) {
				presentation(Ellipse, i % 5);
			}
			else
				if (i < 15) {
					presentation(flagF, i % 10);
				}

		EndPaint(hwnd, &ps);
		break;
	}

	case WM_LBUTTONDOWN:
	{
		++i;
		InvalidateRect(hwnd, 0, TRUE);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		ReleaseDC(hwnd, hdc);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return NULL;
}

template <class T>
void presentation(T& obj, int i)
{
	switch (i)
	{
	case 0:
		obj.Draw();
		break;
	case 1:
		obj.Rotate(50);
		obj.Draw();
		break;
	case 2:
		obj.Rotate(50);
		obj.Explode(2);
		obj.Draw();
		break;
	case 3:
		obj.Rotate(50);
		obj.Explode(2);
		obj.Shift(1, 2);
		obj.Draw();
		break;
	case 4:
		obj.Rotate(50);
		obj.Explode(2);
		obj.Shift(1, 2);
		obj.Rotate(50);
		obj.Explode(-2);
		obj.Draw();
		break;
	default: break;

		
	}

}