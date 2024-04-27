#include <Windows.h>
#include <iostream>
#include <windows.h>
#include <cmath>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <regex>
#include <stack>
using namespace std;
struct dataa {
	char type;
	float value;
};

struct func {
	vector <float> mas;
};
float integrall(string vir, int a, int b,
	vector <float>& x_int, vector <float>& y_int);
void draw_int(HDC dc, vector <float>& x_int, 
	vector<float>& y_int, int max_x_user, int Weidth, int Height);
float s(vector <float> x, vector <float> y);
float convert_point(float x_coord, 
	float max_x_user, int max_x_coord);
bool check_value(char a);
bool Maths(stack <dataa>& st_value, 
	stack <dataa>& st_operation, dataa& item);
int priority(char a);
float parser(string arif);
void prim(string vir, int a, int b, vector<float>& x_c, 
	vector<float>& y_c, int Width, int Height, int max_x_user);
void prim2(string vir, int a, int b, vector<float>& x_c, vector<float>& y_c);

void Draw_x(HDC hdc, int Width, int Height);
void Draw_y(HDC hdc, int Width, int Height);
void func(HDC dc, int Width, int Height, float max_x_user, 
	string arif, vector<float>& x_c, vector<float>& y_c);
void division(HDC dc, int Width, int Height, float max_x_user, 
	float delenia, float size_delenia);
void pixel(HDC dc, int Width, int Height, float max_x_user,
	vector<float> xcoord, vector<float> ycoord);
void delete_point(vector<float>& xcoord, vector<float>& ycoord);
void figure(HDC dc, vector<float> xcoord, vector<float> ycoord);
void draw_figure(HDC dc, int Width, int Height, float max_x_user,
	vector<float> xcoord_point, vector<float> ycoord_point, vector<float> x_pix, vector<float> y_pix);