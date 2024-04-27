#define IDB_Button2 2
#define IDB_Button1 1
#define IDB_Button3 3
#define IDB_Button4 4
#define IDB_Button5 5
#define WIN32_LEAN_AND_MEAN

#include "draw.h"

using namespace std;

int convert(int x_users, int max_x_user, int max_x_coord) {
	int x_coord = max_x_coord * x_users / max_x_user;
	return x_coord;
}

void Menu(HWND hwnd) {
	HMENU hmenu = CreateMenu();
	AppendMenu(hmenu, MF_POPUP, 2, L"Draw func");
	SetMenu(hwnd, hmenu);
}

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
PAINTSTRUCT ps;
RECT Rect;
HDC hCmpDC;
HBITMAP hBmp;
HDC dc;

int __stdcall WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	MSG msg;

	// Create window
	ZeroMemory(&wc, sizeof WNDCLASS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"CMyWnd";
	RegisterClass(&wc);
	HWND hWnd = CreateWindowA("CMyWnd", "Mathcad", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 0, 800, 600, NULL, NULL, hInstance, NULL);
	dc = GetDC(hWnd);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0) > 0) {	// while not WM_QUIT (0) nor some error (-1)
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

// Message processing function
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool	Move = 1;
	static int	Phase = 0, Width, Height;

	struct Coord
	{
		float x, y;
	};

	static vector<Coord> coord_x_c;
	 //TCHAR  IntSize[10] = {0};
	 TCHAR ARIF[100] = { 0 };
	 TCHAR x_point[50] = { 0 };
	 TCHAR y_point[50] = { 0 };

	 static HWND hBtn , hBtn_size;
	 HINSTANCE hInst;
	 static HWND hEdt1; // дескрипторы полей редактирования
	 static HWND hEdt2; //дескрипторы полей редактирования
	 static HWND label;
	 static HWND label2;
	 static HWND hEdit_point_x;
	 static HWND hEdit_point_y;
	 static HWND label_point_x;
	 static HWND label_point_y;
	 static HWND btn_points;
	 static HWND btn_s;

	 static HWND label_a;
	 static HWND label_b;
	 static HWND hEdit_integral_a;
	 static HWND hEdit_integral_b;
	 static HWND btn_integral;

	 static vector <float> x_c;
	 static vector <float> y_c;

	 static int x, y; //координаты

	 static float a, b;
	 static vector <float> x_int;
	 static vector <float> y_int;

	 static vector<float> xcoord; 
	 static vector<float> ycoord;

	 static vector<float> xcoord_point;
	 static vector<float> ycoord_point;

	 static vector<float> x_pix;
	 static vector<float> y_pix;


	static int size = 10;
	static string arif = "x";
	static float x_points;
	static float y_points;

	switch (message)
	{	
	case WM_CREATE:

		hInst = ((LPCREATESTRUCT)lParam)->hInstance; // дескриптор приложения
	// Создаем и показываем первое поле редактирования
		label_a = CreateWindowEx(0, TEXT("Static"), TEXT("a"), WS_CHILD | 
			WS_VISIBLE, 10, 180, 10, 20, hWnd, 0, 0, 0);
		hEdit_integral_a = CreateWindow(L"Edit", NULL, WS_EX_CLIENTEDGE | 
			WS_BORDER | WS_CHILD | WS_VISIBLE,  20, 180, 50, 20, hWnd, NULL, hInst, 0);
		ShowWindow(hEdit_integral_a, SW_SHOWNORMAL);
		// -------------------------------- integral b
		label_b = CreateWindowEx(0, TEXT("Static"), TEXT("b"), WS_CHILD | 
			WS_VISIBLE, 70, 180, 10, 20, hWnd, 0, 0, 0);
		hEdit_integral_b = CreateWindow(L"Edit", NULL, WS_EX_CLIENTEDGE |
			WS_BORDER | WS_CHILD | WS_VISIBLE, 80, 180, 50, 20, hWnd, NULL, hInst, 0);
		ShowWindow(hEdit_integral_b, SW_SHOWNORMAL);
		// -------------------------------- button integral
		btn_points = CreateWindow(L"button", L"Интеграл",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 195, 100, 20, hWnd, (HMENU)IDB_Button5, hInst, NULL);
		ShowWindow(btn_points, SW_SHOWNORMAL);
		// --------------------------------
		label = CreateWindowEx(0, TEXT("Static"), TEXT("y="), WS_CHILD | 
			WS_VISIBLE, 10, 10, 20, 24, hWnd, 0, 0, 0);

		label_point_x = CreateWindowEx(0, TEXT("Static"), TEXT("x="), WS_CHILD |
			WS_VISIBLE, 10, 110, 20, 24, hWnd, 0, 0, 0);
		label_point_y = CreateWindowEx(0, TEXT("Static"), TEXT("y="), WS_CHILD | 
			WS_VISIBLE, 80, 110, 20, 24, hWnd, 0, 0, 0);


		hEdit_point_x = CreateWindow(L"Edit", NULL, WS_EX_CLIENTEDGE | 
			WS_BORDER | WS_CHILD | WS_VISIBLE, 30, 110, 50, 20, hWnd, NULL, hInst, 0);
		ShowWindow(hEdit_point_x, SW_SHOWNORMAL);
		hEdit_point_y = CreateWindow(L"Edit", NULL, WS_EX_CLIENTEDGE |
			WS_BORDER | WS_CHILD | WS_VISIBLE, 100, 110, 50, 20, hWnd, NULL, hInst, 0);
		ShowWindow(hEdit_point_y, SW_SHOWNORMAL);

		btn_points = CreateWindow(L"button", L"Точка",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 130, 100, 30, hWnd, (HMENU)IDB_Button3, hInst, NULL);
		ShowWindow(btn_points, SW_SHOWNORMAL);

		btn_s = CreateWindow(L"button", L"Площадь фигуры",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 160, 150, 20, hWnd, (HMENU)IDB_Button4, hInst, NULL);
		ShowWindow(btn_s, SW_SHOWNORMAL);

		hEdt1 = CreateWindow(L"Edit", NULL, WS_EX_CLIENTEDGE | WS_BORDER |
			WS_CHILD | WS_VISIBLE, 30, 10, 150, 20, hWnd, NULL, hInst, 0);
		ShowWindow(hEdt1, SW_SHOWNORMAL);
		// Создаем и показываем кнопку
		label2 = CreateWindowEx(0, TEXT("Static"), TEXT("size="), WS_CHILD |
			WS_VISIBLE, 10, 60, 50, 24, hWnd, 0, 0, 0);

		hEdt2 = CreateWindow(L"edit", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 50, 60, 50, 20,
			hWnd, 0, hInst, NULL);
		ShowWindow(hEdt2, SW_SHOWNORMAL);

		hBtn = CreateWindow(L"button", L"функция",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 30, 100, 20, hWnd, (HMENU)IDB_Button2, hInst, NULL);
		ShowWindow(hBtn, SW_SHOWNORMAL);

		hBtn_size = CreateWindow(L"button", L"размер",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 80, 100, 20, hWnd, (HMENU) IDB_Button1, hInst, NULL);
		ShowWindow(hBtn, SW_SHOWNORMAL);



	case WM_PAINT:  
		GetClientRect(hWnd, &Rect);
		dc = BeginPaint(hWnd, &ps);
		
		// Создание теневого контекста для двойной буферизации
		hCmpDC = CreateCompatibleDC(dc);
		hBmp = CreateCompatibleBitmap(dc, Rect.right - Rect.left,
			Rect.bottom - Rect.top);
		SelectObject(hCmpDC, hBmp);
		
		// Закраска фоновым цветом
		LOGBRUSH br;
		br.lbStyle = BS_SOLID;
		br.lbColor = /*0xEECCCC*/RGB(180, 251, 250);
		HBRUSH brush;
		brush = CreateBrushIndirect(&br);
		FillRect(hCmpDC, &Rect, brush);
		DeleteObject(brush);
		
		// Здесь рисуем на контексте hCmpDC
		Draw_x(hCmpDC, Width, Height);
		Draw_y(hCmpDC, Width, Height);	
		prim(arif, -size * 2, size * 2,x_c, y_c, Width, Height, size*2);
		func(hCmpDC,  Width, Height, size*2,arif, x_c, y_c);
		division(hCmpDC, Width, Height, size*2, 0.1, 1);
		draw_int(hCmpDC, x_int, y_int, size*2, Width, Height);		
		pixel(hCmpDC,Width,Height,size*2, xcoord, ycoord);
		draw_figure(hCmpDC, Width, Height, size * 2, 
			xcoord_point, ycoord_point, x_pix, y_pix);
		// Копируем изображение из теневого контекста на экран
		SetStretchBltMode(dc, COLORONCOLOR);
		BitBlt(dc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
			hCmpDC, 0, 0, SRCCOPY);
		
		// Удаляем ненужные системные объекты
		DeleteDC(hCmpDC);
		DeleteObject(hBmp);
		hCmpDC = NULL;
		
		EndPaint(hWnd, &ps);
		
		
		break;

	case WM_SIZE:
		Width = LOWORD(lParam),
			Height = HIWORD(lParam);
		break;
	
	case WM_COMMAND:  // сообщение о команде
		
		if (wParam == IDB_Button1)   // если нажали на кнопку
		{
			
			int cTextLength; // text length
			cTextLength = GetWindowTextLength(hEdt2);// get text length
			wchar_t* textS = new wchar_t[cTextLength + 1]; //dynamically allocate buffer
			// get text from an edit and store it into a buffer variable
			GetWindowText(hEdt2, textS, cTextLength + 1);
			// display the message
			int hsize = _wtoi(textS);
			//int n = WideToInt(textS);
			size = hsize;
			//MessageBox(NULL, textS, textS, MB_OKCANCEL | MB_ICONEXCLAMATION);
			delete[] textS; // free the allocated memory
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
		}

		if (wParam == IDB_Button2)   // если нажали на кнопку
		{
			
			int cTextLength; // text length
			cTextLength = GetWindowTextLength(hEdt1);// get text length
			wchar_t* textS = new wchar_t[cTextLength + 1]; //dynamically allocate buffer

			GetWindowText(hEdt1, textS, cTextLength + 1);
			arif.clear();
			for (int i = 0; i < cTextLength + 1; i++) {
				arif += textS[i];
			}
			
			//MessageBox(NULL, textS, textS, MB_OKCANCEL | MB_ICONEXCLAMATION);
			delete[] textS; // free the allocated memory
			x_c.clear();
			y_c.clear();
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
		}

		if (wParam == IDB_Button3) {
			int cTextLength; // text length
			int x_size;
			cTextLength = GetWindowTextLength(hEdit_point_x);// get text length
			wchar_t* textS = new wchar_t[cTextLength + 1]; //dynamically allocate buffer
			// get text from an edit and store it into a buffer variable
			GetWindowText(hEdit_point_x, textS, cTextLength + 1);
			// display the message
			x_size = _wtoi(textS);
			//int n = WideToInt(textS);
			x_points = x_size;
			//MessageBox(NULL, textS, textS, MB_OKCANCEL | MB_ICONEXCLAMATION);
			delete[] textS; // free the allocated memory

			int cTextLength2;
			cTextLength2 = GetWindowTextLength(hEdit_point_y);// get text length
			wchar_t* textS2 = new wchar_t[cTextLength2 + 1]; //dynamically allocate buffer
			// get text from an edit and store it into a buffer variable
			GetWindowText(hEdit_point_y, textS2, cTextLength2 + 1);
			// display the message
			int y_size = _wtoi(textS2);
			//int n = WideToInt(textS);
			y_points = y_size;
	
			ycoord_point.push_back(y_points);
			xcoord_point.push_back(x_points);
			
			//MessageBox(NULL, textS, textS, MB_OKCANCEL | MB_ICONEXCLAMATION);
			delete[] textS2; // free the allocated memory

			float rx = convert(x_points, size * 2, Width);
			float ry = convert(y_points, size * 2, Height);

			x_pix.push_back(rx);
			y_pix.push_back(ry);

			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
		}

		if (wParam == IDB_Button4) {
			if (xcoord_point.size() >= 3) {
				float pl;
				pl = s(xcoord_point, ycoord_point);
				wstring str = std::to_wstring(pl);
				const wchar_t* wstr = str.c_str();
				MessageBox(NULL, wstr, L"Площадь", MB_OKCANCEL | MB_ICONEXCLAMATION);
			}
			else MessageBox(NULL, NULL, L"Ошибка", MB_OKCANCEL | MB_ICONEXCLAMATION);

		}

		if (wParam == IDB_Button5) {

			int cTextLength; // text length
			float x_size;
			cTextLength = GetWindowTextLength(hEdit_integral_a);// get text length
			wchar_t* textS = new wchar_t[cTextLength + 1]; //dynamically allocate buffer
			// get text from an edit and store it into a buffer variable
			GetWindowText(hEdit_integral_a, textS, cTextLength + 1);
			// display the message

			x_size = _wtoi(textS);
			//int n = WideToInt(textS);
			a = x_size;
			//MessageBox(NULL, textS, textS, MB_OKCANCEL | MB_ICONEXCLAMATION);
			delete[] textS; // free the allocated memory

			int cTextLength2;
			cTextLength2 = GetWindowTextLength(hEdit_integral_b);// get text length
			wchar_t* textS2 = new wchar_t[cTextLength2 + 1]; //dynamically allocate buffer
			// get text from an edit and store it into a buffer variable
			GetWindowText(hEdit_integral_b, textS2, cTextLength2 + 1);
			// display the message
			float y_size = _wtoi(textS2);
			//int n = WideToInt(textS);
			b = y_size;

			//MessageBox(NULL, textS, textS, MB_OKCANCEL | MB_ICONEXCLAMATION);
			delete[] textS2; // free the allocated memory
			
			if (a < b) {
				prim2(arif, a, b, x_int, y_int);
				if (x_int.size() > 0) {

				float pl;
				pl = integrall(arif, a, b, x_int, y_int);
				wstring str = std::to_wstring(pl);
				const wchar_t* wstr = str.c_str();
				MessageBox(NULL, wstr, L"Интеграл", MB_OKCANCEL | MB_ICONEXCLAMATION);
	
				}
				else MessageBox(NULL, L"Нет графика\nВведите функцию",
					L"Ошибка", MB_OKCANCEL | MB_ICONEXCLAMATION);
			}
			else {
				MessageBox(NULL, L"a должно быть меньше чем b", 
					L"Ошибка", MB_OKCANCEL | MB_ICONEXCLAMATION);
			}


			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);

		}

		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);

	case WM_RBUTTONDOWN:
		
		delete_point(xcoord_point, ycoord_point);
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}