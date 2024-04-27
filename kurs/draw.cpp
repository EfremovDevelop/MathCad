#include "draw.h"

stack <dataa> st_value;
stack <dataa> st_operation;
dataa item;

bool check_value(char a) {
	if (a >= '0' && a <= 9)
		return 1;
	else return 0;
}

bool check = true;

bool Maths(stack <dataa>& st_value, stack <dataa>& st_operation, dataa& item) {
	float a, b, c;
	a = st_value.top().value;
	st_value.pop();
	switch (st_operation.top().type) {
	case '+':
		b = st_value.top().value;
		st_value.pop();
		c = a + b;
		item.type = '0';
		item.value = c;
		st_value.push(item); //Результат операции кладется обратно в стек с числами
		st_operation.pop();
		break;

	case '-':
		b = st_value.top().value;
		st_value.pop();
		c = b - a;
		item.type = '0';
		item.value = c;
		st_value.push(item);
		st_operation.pop();
		break;

	case '*':
		b = st_value.top().value;
		st_value.pop();
		c = a * b;
		item.type = '0';
		item.value = c;
		st_value.push(item);
		st_operation.pop();
		break;

	case '/':
		b = st_value.top().value;
		st_value.pop();

			c = (b / a);
			item.type = '0';
			item.value = c;
			st_value.push(item);
			st_operation.pop();

		break;
	case '^':
		b = st_value.top().value;

		st_value.pop();
		c = pow(b, a);
		item.type = '0';
		item.value = c;
		st_value.push(item);
		st_operation.pop();
		break;
	case 's':
		c = sin(a);
		item.type = '0';
		item.value = c;
		st_value.push(item);
		st_operation.pop();
		break;
	case 'c':
		c = cos(a);
		item.type = '0';
		item.value = c;
		st_value.push(item);
		st_operation.pop();
		break;
	case 't':
		if (cos(a) != 0) {
			c = sin(a) / cos(a);
			item.type = '0';
			item.value = c;
			st_value.push(item);
			st_operation.pop();
		}
		else {
			st_operation.pop();
			break;
		}
		break;
	case 'g':
		c = cos(a) / sin(a);
		item.type = '0';
		item.value = c;
		st_value.push(item);
		st_operation.pop();
		break;
	case 'a':
		c = abs(a);
		item.type = '0';
		item.value = c;
		st_value.push(item);
		st_operation.pop();
		break;
	default:
		check = false;
		break;
	}
	return true;
}

int priority(char a) {
	if (a == '+')
		return 1;
	else if (a == '-')
		return 1;
	else if (a == '*')
		return 2;
	else if (a == '/')
		return 2;
	else if (a == '^')
		return 3;
	else return 0;
}

void point(HDC dc, int x, int y) {
	SetPixel(dc, x, y, 0x000000FF);
	SetPixel(dc, x + 1, y + 1, 0x000000FF);
	SetPixel(dc, x, y + 1, 0x000000FF);
	SetPixel(dc, x + 1, y, 0x000000FF);
}

float parser(string arif) {
	bool flag = 1;
	for (int i = 0; i < arif.size(); i++) {
		if (i < arif.size() - 2 && arif[i] == 's' && 
			arif[i + 1] == 'i' && arif[i + 2] == 'n') {
			item.type = 's';
			item.value = 0;
			st_operation.push(item);
			i += 2;
			continue;
		}
		if (i < arif.size() - 2 && arif[i] == 'c' && 
			arif[i + 1] == 'o' && arif[i + 2] == 's') {
			item.type = 'c';
			item.value = 0;
			st_operation.push(item);
			i += 2;
			continue;
		}
		if (i < arif.size() - 2 && arif[i] == 't' &&
			arif[i + 1] == 'g') {
			item.type = 't';
			item.value = 0;
			st_operation.push(item);
			i += 1;
			continue;
		}
		if (i < arif.size() - 2 && arif[i] == 'c' && 
			arif[i + 1] == 't' && arif[i + 2] == 'g') {
			item.type = 'g';
			item.value = 0;
			st_operation.push(item);
			i += 2;
			continue;
		}
		if (i < arif.size() - 2 && arif[i] == 'a' && 
			arif[i + 1] == 'b' && arif[i + 2] == 's') {
			item.type = 'a';
			item.value = 0;
			st_operation.push(item);
			i += 2;
			continue;
		}
		if (arif[i] == 'p') {
			item.type = '0';
			item.value = 3.14;
			st_value.push(item);
	
			continue;
		}
		if (arif[i] == '^') {
			item.type = '^';
			item.value = 0;
			st_operation.push(item);
			continue;
		}
		if ((arif[i] >= '0' && arif[i] <= '9') || 
			arif[i] == '-' && flag == 1) // проверка на число
		{
			string val;
			val = arif[i];
			int k = 0;
			if (i < arif.size()) {
				int j = i + 1;
				while ((arif[j] >= '0' && arif[j] <= '9') ||
					arif[j] == '.') {
					val += arif[j];
					j += 1;
					k += 1;
				}
			}
			item.type = '0';
			item.value = stof(val);
			st_value.push(item);
			i += k;
			flag = false;
			continue;
		}
		if (arif[i] == '+' || arif[i] == '-' || arif[i] == '*' ||
			arif[i] == '/') {
			if (st_operation.size() == 0) {
				item.type = arif[i];
				item.value = 0;
				st_operation.push(item);
				continue;
			}
			if (st_operation.size() != 0 && priority(arif[i]) >
				priority(st_operation.top().type)) {
				item.type = arif[i];
				item.value = 0;
				st_operation.push(item);
				continue;
			}
			if (st_operation.size() != 0 && priority(arif[i]) <=
				priority(st_operation.top().type)) {
				if (Maths(st_value, st_operation, item) == false) {
					check = false;
					break;
				}
				else {
					item.type = arif[i];
					item.value = 0;
					st_operation.push(item);
					continue;
				}
			}
		}

		if (arif[i] == '(') {
			flag = 1;
			item.type = arif[i];
			item.value = 0;
			st_operation.push(item);
			continue;
		}
		if (arif[i] == ')') {
			while (st_operation.top().type != '(') {
				if (Maths(st_value, st_operation, item) == false) {
					check = false;
					break;
				}
				else continue;
			}
			st_operation.pop();
			continue;
		}

		else { //Если прочитан какой-то странный символ
			check = false;
			//return 0;
		}
	}

	while (st_operation.size() != 0) {
		if (Maths(st_value, st_operation, item) == false) { //Если функция вернет "false", то прекращаем работу
			check = false;
			break;
		}
		else { //Если все хорошо, выдаем ответ
			continue;

		}
	}
	return st_value.top().value;

}

int convert(float x_users, float max_x_user, int max_x_coord) {
	int x_coord = max_x_coord * x_users / max_x_user;
	return x_coord;
}

void prim(string vir, int a, int b, vector<float>& x_c,
	vector<float>& y_c, int Width, int Height, int max_x_user) {
	float p = max_x_user * 0.03/20;
	x_c.clear();
	y_c.clear();
	string val;
	for (float x = a; x < b; x += p) {
		val = to_string(x);
		if (x < 0) {
			string vir_minus;
			for (int i = 0; i < vir.size(); i++) {
				if (vir[i] == 'x')
					vir_minus += "(x)";
				else vir_minus += vir[i];
			}
			vir_minus = regex_replace(vir_minus, regex("x"), val);
			x_c.push_back(x);
			y_c.push_back(parser(vir_minus));
			vir_minus = regex_replace(vir_minus, regex(val), "x");
		}
		else {
			vir = regex_replace(vir, regex("x"), val);
			x_c.push_back(x);
			y_c.push_back(parser(vir));
			vir = regex_replace(vir, regex(val), "x");
		}
	}
}

void prim2(string vir, int a, int b, 
	vector<float>& x_c, vector<float>& y_c) {
	float p = 0.01;
	x_c.clear();
	y_c.clear();
	string val;
	for (float x = a; x < b; x += p) {
		//string val;
		val = to_string(x);
		if (x < 0) {
			string vir_minus;
			for (int i = 0; i < vir.size(); i++) {
				if (vir[i] == 'x')
					vir_minus += "(x)";
				else vir_minus += vir[i];
			}
			vir_minus = regex_replace(vir_minus, regex("x"), val);
			x_c.push_back(x);
			y_c.push_back(parser(vir_minus));
			vir_minus = regex_replace(vir_minus, regex(val), "x");
		}
		else {
			vir = regex_replace(vir, regex("x"), val);
			x_c.push_back(x);
			y_c.push_back(parser(vir));
			vir = regex_replace(vir, regex(val), "x");
		}
	}
}

void Draw_x(HDC dc, int Width, int Height) {
	MoveToEx(dc, 0, Height / 2, NULL);
	LineTo(dc, Width, Height / 2);
}
void Draw_y(HDC dc, int Width, int Height) {
	MoveToEx(dc, Width / 2, 0, NULL);
	LineTo(dc, Width / 2, Height);
}

float convert_point(float x_coord,
	float max_x_user, int max_x_coord) {
	float x_user = x_coord * max_x_user / max_x_coord;
	return x_user;
}

void func(HDC dc, int Width, int Height, float max_x_user,
	string arif, vector<float>& x_c, vector<float>& y_c) {
	MoveToEx(dc, convert(x_c[0], max_x_user, Width) + Width / 2, 
		convert(y_c[0], max_x_user, Height) + Height / 2, NULL);
	for (int i = 0; i < x_c.size(); i++) {
		LineTo(dc, convert(x_c[i], max_x_user, Width) + Width / 2, 
			convert(- y_c[i], max_x_user, Height) + Height / 2);
	}
	x_c.clear();
	y_c.clear();
}

void division(HDC dc, int Width, int Height, 
	float max_x_user, float delenia, float size_delenia) {
	for (float x = -max_x_user; x < max_x_user; x += size_delenia) {
		MoveToEx(dc, convert(x, max_x_user,Width), Height / 2 + 
			convert(delenia, max_x_user, Height), NULL);
		LineTo(dc, convert(x, max_x_user, Width), Height / 2 - 
			convert(delenia, max_x_user, Height));
	}
	for (float y = -max_x_user; y < max_x_user; y += size_delenia) {
		MoveToEx(dc, Width / 2 + convert(delenia, max_x_user, Width),
			convert(y, max_x_user, Height), NULL);
		LineTo(dc, Width / 2 - convert(delenia, max_x_user, Width),
			convert(y, max_x_user, Height));
	}
}

void pixel(HDC dc, int Width, int Height, 
	float max_x_user,vector<float> xcoord, vector<float> ycoord) {

	for (int i = 0; i < xcoord.size(); i++) {
		RoundRect(dc, xcoord[i] - 3, ycoord[i] + 3, 
			xcoord[i] + 3, ycoord[i] - 3, 5, 5);
	}
}

void delete_point(vector<float>& xcoord, vector<float>& ycoord) {
	if (xcoord.size() != 0) {
		xcoord.pop_back();
		ycoord.pop_back();
	}
}

void figure(HDC dc, vector<float> xcoord, vector<float> ycoord) {
	if (xcoord.size() >= 2) {
		MoveToEx(dc, xcoord[0], ycoord[0], NULL);
		for (int i = 0; i < xcoord.size(); i++) {
			LineTo(dc, xcoord[i], ycoord[i]);
		}
		MoveToEx(dc, xcoord[xcoord.size() - 1],
			ycoord[ycoord.size() - 1], NULL);
		LineTo(dc, xcoord[0], ycoord[0]);
	}
}

void draw_figure(HDC dc, int Width, int Height, float max_x_user, 
	vector<float> xcoord_point, vector<float> ycoord_point,
	vector<float> x_pix, vector<float> y_pix) {
	
	if (xcoord_point.size() >= 1) {
		MoveToEx(dc, convert(xcoord_point[0], max_x_user, Width) + Width / 2, 
			convert(-ycoord_point[0], max_x_user, Height) + Height / 2, NULL);
		for (int i = 0; i < xcoord_point.size(); i++) {
			LineTo(dc, convert(xcoord_point[i], max_x_user, Width) + Width / 2, 
				convert(-ycoord_point[i], max_x_user, Height) + Height / 2);
			RoundRect(dc, convert(xcoord_point[i], max_x_user, Width) + Width / 2 - 3, 
				convert(-ycoord_point[i], max_x_user, Height) + Height / 2 + 3,
				convert(xcoord_point[i], max_x_user, Width) + Width / 2 + 3,
				convert(-ycoord_point[i], max_x_user, Height) + Height / 2 - 3, 5, 5);
		}
		if (xcoord_point.size() >= 3) {
			MoveToEx(dc,convert( xcoord_point[xcoord_point.size() - 1], 
				max_x_user, Width) + Width/2, 
				convert(-ycoord_point[ycoord_point.size() - 1],
					max_x_user,Height) + Height/2, NULL);
			LineTo(dc, convert(xcoord_point[0], max_x_user, Width) + Width / 2,
				convert(-ycoord_point[0], max_x_user, Height) + Height / 2);
		}
	}

}

float s(vector <float> x, vector <float> y) {
	float sum = 0;
	x.push_back(x[0]);
	y.push_back(y[0]);
	for (int i = 0; i < x.size() - 1; i++) {
		sum += x[i] * y[i + 1] - y[i] * x[i + 1];
	}
	return 0.5 * abs(sum);
}

void draw_int(HDC dc, vector <float>& x_int, 
	vector<float>& y_int, int max_x_user, int Width, int Height) {
	
	if (x_int.size() > 0) {

		for (int i = 0; i < x_int.size(); i++) {
			MoveToEx(dc, convert(x_int[i], max_x_user, Width) + 
				Width / 2, Height / 2, NULL);
			LineTo(dc, convert(x_int[i], max_x_user, Width) + Width / 2,
				convert(-y_int[i], max_x_user, Height) + Height / 2);
		}
	}
	x_int.clear();
	y_int.clear();
}

float integrall(string vir,int a, int b, vector <float> &x_int, vector <float> &y_int) {

	float S = 0;
	for (int i = 1; i < x_int.size()-1; i++) {
		S += abs(x_int[i] - x_int[i - 1]) * y_int[i];
	}
	return round(S*100)/100;
	S = 0;
}


