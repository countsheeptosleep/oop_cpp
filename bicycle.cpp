// ____________________________________________________
// ____________���������� ������� �������______________
// ____________________________________________________

#include <windows.h>
#include "bicycle.h"
#include <cmath>
#include <string>

extern HDC hdc;  // �������� ����������


// ---------------- ��������������� ������� -----------


// �������� �����
COLORREF invert_colour(COLORREF colour_to_invert) {


	// ���������� ��������������� ����:
	return RGB(255 - GetRValue(colour_to_invert), 255 - GetGValue(colour_to_invert), 255 - GetBValue(colour_to_invert));


}  // ����� ����� "�������� �����"


// ------------------------- ������� ------------------

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)  // ������ ��� ����������� ������� ������


// ----------------- ���������� ���������� -------------

const int gl_drag_sleep_time = 30;  // ����� ��� ����� ���� ����������
const int gl_drag_sleep_time_one_step = 15;  // ����� ��� ����� ���� ���������� � ������ "1 ���"

const int gl_min_bike_size = 15;  // ����������� ������ ����������

const int gl_max_bike_size = 100;  // ������������ ������ ����������

// �����:

const COLORREF colour_black RGB(0, 0, 0);
const COLORREF colour_red RGB(255, 0, 0);
const COLORREF colour_green RGB(0, 255, 0);
const COLORREF colour_blue RGB(0, 0, 255);
const COLORREF colour_white RGB(255, 255, 255);

// ����� � ������������ � �� �����:

const COLORREF colour_default_base = colour_blue;  // �� ��������� �������� ���� �������� 
const COLORREF colour_default_base2 = colour_black;  // �� ��������� ������ �������� ���� �������� 
const COLORREF colour_default_backgroung = colour_white;  // �� ��������� ���� ���� 
const COLORREF colour_inverted_default_backgroung = invert_colour(colour_default_backgroung);  // ��������������� ���� ���� �� ���������


// -----------------------------------------------------
// -- 1. ���������� ������� �������� ������ Location ---
// -----------------------------------------------------


// ����������� �������� ������
Location::Location(int InitX, int InitY)
{


	X = InitX;  // ������������� �������� �������� �������� ������

	Y = InitY;  // ������������� �������� �������� �������� ������


} // ����� ����� "����������� �������� ������"


// ���������� �������� ������
Location::~Location()
{


	// ������ ����


} // ����� ����� "���������� �������� ������"


// ��������� �������� �������� �������� ������
int Location::GetX()
{


	return X;  // ���������� �������� �������� ������


} // ����� ����� "��������� �������� �������� �������� ������"


// ��������� �������� �������� �������� ������
int Location::GetY()
{


	return Y;  // ���������� �������� �������� ������


} // ����� ����� "��������� �������� �������� �������� ������"


// ��������� �������� �������� �������� ������
void Location::SetX(int NewX)
{


	X = NewX;  // ������������� ����� �������� �������� �������� ������


} // ����� ����� "��������� �������� �������� �������� ������"


// ��������� �������� �������� �������� ������
void Location::SetY(int NewY)
{


	Y = NewY;  // ������������� ����� �������� �������� �������� ������


} // ����� ����� "��������� �������� �������� �������� ������"


// -----------------------------------------------------
// --------- 2. ���������� ������� ������ Point --------
// -----------------------------------------------------


// ����������� ������ �����
Point::Point(int InitX, int InitY) : Location(InitX, InitY)
{


	Visible = false;  // ��� �������� ����� �� �����, ������������� ���� ��������� �� False


} // ����� ����� "����������� ������ Point"


// ���������� ������ �����
Point::~Point()
{


	// ������ ����


} // ����� ����� "���������� ������ Point"


// ��������� �������� ��������� �����
bool Point::GetVisible() {


	return Visible;  // ���������� �������� ���� ���������


} // ����� ����� "��������� �������� ��������� �����"


// ��������� �������� ��������� �����
void Point::SetVisible(bool NewVisible)
{


	if (Visible != NewVisible) {  // ���� ����� �������� ���� ��������� �� ����� ��������

		Visible = NewVisible;  // ������������� � ���� ��������� ����� ��������

		if (Visible) {  // ���� ����� ������ ���� �����

			Show();  // ���������� �����

		} // if

		else {  // ���� ����� ������ ���� ������

			Hide();  // �������� �����

		} // else

	} // ����� ����� "���� ����� �������� ���� ��������� �� ����� ��������"


} // ����� ����� "��������� �������� ��������� �����"


// �������� ����� �� ������
void Point::Show()
{


	Visible = true;  // ����� ���������� �����

	Draw();  // ������ ����� �������� �����


} // ����� ����� "�������� ����� �� ������"


// �������� ����� �� ������, ���� ��� �� ��������
void Point::GetShowed() {

	if (!Visible) Show();  // ���������� ����� �� ������, ���� ��� ��� �� �����

}  // ����� ����� "�������� ����� �� ������, ���� ��� �� ��������"


// ������ ����� � ������
void Point::Hide()
{


	Visible = false;  // ����� ���������� �� �����

	Draw();  // ������ ����� ����� ���� 


} // ����� ����� "������ ����� � ������"


// ������ ����� � ������, ���� ��� �� ������
void Point::GetHidden() {

	if (Visible) Hide();  // ���� ����� �����, �� ������� ��

}  // ����� ����� "������ ����� � ������, ���� ��� �� ������"


// �������� �����
void Point::Draw() {


	// ���� �����:
	COLORREF colour;

	// ������������� ���� �����:
	if (Visible) colour = colour_default_base;
	else colour = colour_default_backgroung;


	// ������ �����:

	SetPixel(hdc, X, Y, colour);
	SetPixel(hdc, X + 1, Y, colour);
	SetPixel(hdc, X, Y + 1, colour);
	SetPixel(hdc, X + 1, Y + 1, colour);


}  // ����� ����� "�������� �����"


// ����������� ����� �� ������
void Point::MoveTo(int NewX, int NewY)
{


	if (Visible) {  // ���� ����� ������ ����� �� ������

		Hide();  // ������ �����

		// ��������� ���������� �����:

		X = NewX;  // ����� ��������

		Y = NewY;  // ����� ��������

		Show();  // �������� ����� �� ����� �����������

	}  // if

	else {  // ���� ����� ������ �� ����� �� ������

		// ��������� ���������� �����:

		X = NewX;  // ����� ��������

		Y = NewY;  // ����� ��������

	} // else


} // ����� ����� "����������� ����� �� ������"


// ���������� �����
void Point::Drag(int Step)
{


	if (!Visible) Show();  // �������, ��� ��� ������ ����������� ��������� �����, ������ � �������

	int FigX, FigY;  // ����� ���������� �����, ���������� � ���� ����������

	// ����� ��������� ����� ���������� ����� ��������� �����������:

	FigX = GetX();  // ��������� ��������

	FigY = GetY();  // ��������� ��������


	// ����������� ���� ����������:
	while (1) {

		if (KEY_DOWN(VK_ESCAPE)) {  // ���� ������ ������� 27 ("Esc")

			break;  // ����� �� ������������ ����� ����������

		}  // if

		if (KEY_DOWN(VK_LEFT)) {  // ���� ������ ������� 37 ("������� �����")

			FigX = FigX - Step;  // ����� �������� ����� ������ ������� �������� �� ��� ����������

		}  // if

		if (KEY_DOWN(VK_RIGHT)) {  // ���� ������ ������� 39 ("������� ������")

			FigX = FigX + Step;  // ����� �������� ����� ������ ������� �������� �� ��� ����������

		}  // if

		if (KEY_DOWN(VK_DOWN)) {  // ���� ������ ������� 40 ("������� ����")

			FigY = FigY + Step;  // ����� �������� ����� ������ ������� �������� �� ��� ����������

		}  // if

		if (KEY_DOWN(VK_UP)) {  // ���� ������ ������� 38 ("������� �����")

			FigY = FigY - Step;   // ����� �������� ����� ������ ������� �������� �� ��� ����������

		}  // if

		MoveTo(FigX, FigY);  // ���������� ����� �� ����� �����������

		Sleep(gl_drag_sleep_time);  // ����� ������������ ���� ���������� ���������� ����� ������������� �����

	} // ����� ����� "����������� ���� ����������"


} // ����� ����� "���������� �����"


// ------------------------------------------------------
// --------- 3. ���������� ������� ������ Bicycle -------
// ------------------------------------------------------


// ����������� ������ ���������� 
Bicycle::Bicycle(int InitX, int InitY, int InitSize, int InitDirection) : Point(InitX, InitY)
{


	size = InitSize;  // ������������� ������ ����������

	direction = InitDirection;  // ������������� ����������� ���������� (0 - �����, 1 - ������)


} // ����� ����� "����������� ������ ����������"


// ���������� ������ ����������
Bicycle::~Bicycle() {


	// ������ ����


}  // ����� ����� "���������� ������ ����������"


// ��������� ������� ����������
int Bicycle::GetSize() {


	return size; // ���������� ������ ����������


} // ����� ����� "��������� ������� ����������"


// ��������� �������� ������� ����������
void Bicycle::SetSize(int NewSize) { // ��������� �������� ���� Size


	bool was_visible = Visible;  // ��� ������� ��� ������� ���������

	GetHidden();  // � ����� ������ ��������� �� ������ ���� ����� ��� ��������� ��� ���������

	size = NewSize;  // ������������� ����� ������ ����������

	if (size < gl_min_bike_size) size = gl_min_bike_size;  // �� ������ ������� ������ ������� ������� ����������

	if (size > gl_max_bike_size) size = gl_max_bike_size;  // �� ������ ������� ������� ������� ������� ����������

	if (was_visible) Show();  // ���������� ���������, ���� ���������� �� ��� �����


} // SetSize()


// ��������� �������� ����������� ����������
int Bicycle::GetDirection() {


	return direction;  // ���������� ����������� ����������


}  // ����� ����� "��������� �������� ����������� ����������"


// ��������� �������� ����������� ����������
void Bicycle::SetDirection(int NewDirection) {


	bool was_visible = Visible;  // ��� ������� ��� ������� ���������

	GetHidden();  // � ����� ������ ��������� �� ������ ���� ����� ��� ��������� ��� ���������

	direction = NewDirection;  // ������������� ����� ����������� ����������

	if (was_visible) Show();  // ���������� ���������, ���� ���������� �� ��� �����


}  // ����� ����� "��������� �������� ����������� ����������"


// ��������� ���������
void Bicycle::Rotate() {


	bool was_visible = Visible;  // ��� ������� ��� ������� ���������

	GetHidden();  // � ����� ������ ��������� �� ������ ���� ����� ��� ��������� ��� ���������

	direction = 1 - direction;  // ������������� ����� ����������� ����������

	if (was_visible) Show();  // ���������� ���������, ���� ���������� �� ��� �����


} // ����� ����� "��������� ���������"


// ��������� ������ ����������
void Bicycle::Expand(int DeltaSize) {


	bool was_visible = Visible;  // ��� ������� ��� ������� ���������

	GetHidden();  // � ����� ������ ��������� �� ������ ���� ����� ��� ��������� ��� ���������

	SetSize(size + DeltaSize);

	if (was_visible) Show();  // ���������� ���������, ���� ���������� �� ��� �����


}  // ����� ����� "��������� ������ ����������"


// ��������� ������ ����������
void Bicycle::Reduce(int DeltaSize) {


	Expand(-DeltaSize);  // �������� ������� ���������� � ������������� ����������


}  // ����� ����� "��������� ������ ����������"


// �������� ���������
void Bicycle::Draw() {


	COLORREF colour;  // ���� ����������


	// ������������� ����:
	if (Visible) colour = colour_default_base;
	else colour = colour_default_backgroung;


	// ������� �����:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, colour);

	SelectObject(hdc, hPen1); // ������ ����� ��������


	// -- ��������� ���������� --
	// 
	// () ���� ��������� ����� � �������������� �� (X,Y) �� (X + 3*size, Y + 1.5*size)
	// () ��������������� ����� ����������: (X + 1.5*size, Y + size)
	// () ������� ����� - size
	// () ����� ���������� - size
	// () ������ ���������� ����� � ������ �� ���������������� ������ - �� 1,5 size
	// () ������ ���������� ��� ��������������� ������� - 1 size
	// () ������� ���������� ��� ��������������� ������� - 0,5 size


	// ������� ����������:

	int center_x, center_y; // ����� ���������� (��������������� �����, �� ��������������)

	int left_wheel_center_x, left_wheel_center_y,  // ������ ����� ����������
		right_wheel_center_x, right_wheel_center_y;


	// ������� �������:

	int l = size;  // ������ ����������� �������

	int r = l * 0.5;  // ������ �����

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // ������� ����� ���������� � ������������ �� ������ � ������� ����� �������

	// ���������� ����������:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- ������ ������ ���������� ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

	// �������� ����������� �������:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x + l - r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x - l + r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	}  // else 


	// --------- ������ ���� ���������� ----------


	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- ������ ������ ���������� ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);


}  // ����� ����� "�������� ���������"


// ��� ���������� � �����������, ����� �� ���� � ����� �����:
void Bicycle::WhenRide(int NewX, int NewY) {


	// ���� ��������� ������ � �������, ��������������� ��� �������� �����������, �� ��������� ������ �����������:
	if ((NewX > X && direction == 0) || (NewX < X && direction == 1)) {

		Rotate();  // ������� ����������

	}  // if

}  // ����� ����� "��� ���������� � �����������, ����� �� ���� � ����� �����"


// ��������� �� ������ ���� � ����� �����
void Bicycle::RideTo(int NewX, int NewY) {


	WhenRide(NewX, NewY);  // ��� ���������� � �����������, ����� �� ���� � ����� �����

	MoveTo(NewX, NewY);  // ���������� ��������� � ����� �����


}  // ����� ����� "��������� �� ������ ���� � ����� �����"


// ���������� ����������� 
void Bicycle::BikeRiding(int Step) // ������������� ���� ��� ����������, �. �. ���������� � ��������� � ������ �������
{


	if (!Visible) Show();  // �������, ��� ��� ������ ������ �� ��������� ����������, ������ ��� �������

	int FigX, FigY;  // ����� ���������� �����, ���������� � ���� ����

	// ����� ��������� ����� ���������� ����� ��������� �����������:

	FigX = GetX();  // ��������� ��������

	FigY = GetY();  // ��������� ��������


	// ����������� ���� ���� �� ����������:
	while (1) {

		if (KEY_DOWN(VK_ESCAPE)) {  // ���� ������ ������� 27 ("Esc")

			break;  // ����� �� ������������ ����� ����

		}  // if

		if (KEY_DOWN(VK_LEFT)) {  // ���� ������ ������� 37 ("������� �����")

			FigX = FigX - Step;  // ����� �������� ����� ������ ������� �������� �� ��� ����

		}  // if

		if (KEY_DOWN(VK_RIGHT)) {  // ���� ������ ������� 39 ("������� ������")

			FigX = FigX + Step;  // ����� �������� ����� ������ ������� �������� �� ��� ����

		}  // if

		if (KEY_DOWN(VK_DOWN)) {  // ���� ������ ������� 40 ("������� ����")

			FigY = FigY + Step;  // ����� �������� ����� ������ ������� �������� �� ��� ����

		}  // if

		if (KEY_DOWN(VK_UP)) {  // ���� ������ ������� 38 ("������� �����")

			FigY = FigY - Step;   // ����� �������� ����� ������ ������� �������� �� ��� ����

		}  // if

		RideTo(FigX, FigY);  // ��������� ���� �� ����� �����������

		Sleep(gl_drag_sleep_time);  // ����� ������������ ���� ���� ���������� ����� ������������� �����

	} // ����� ����� "����������� ���� ����"


}  // ����� ����� "���������� �����������"

// ���������� ����������� �� 1 ���
void Bicycle::BikeRideOneStep(int Step) {


	if (!Visible) Show();  // �������, ��� ��� ������ ������ �� ��������� ����������, ������ ��� �������

	int FigX, FigY;  // ����� ���������� �����, ���������� � ���� ����

	// ����� ��������� ����� ���������� ����� ��������� �����������:

	FigX = GetX();  // ��������� ��������

	FigY = GetY();  // ��������� ��������

	while (true) {  // ���� �� 1-��� �������

		if (KEY_DOWN(VK_LEFT)) {  // ���� ������ ������� 37 ("������� �����")

			FigX = FigX - Step;  // ����� �������� ����� ������ ������� �������� �� ��� ����

			break;

		}  // if

		if (KEY_DOWN(VK_RIGHT)) {  // ���� ������ ������� 39 ("������� ������")

			FigX = FigX + Step;  // ����� �������� ����� ������ ������� �������� �� ��� ����

			break;

		}  // if

		if (KEY_DOWN(VK_DOWN)) {  // ���� ������ ������� 40 ("������� ����")

			FigY = FigY + Step;  // ����� �������� ����� ������ ������� �������� �� ��� ����

			break;

		}  // if

		if (KEY_DOWN(VK_UP)) {  // ���� ������ ������� 38 ("������� �����")

			FigY = FigY - Step;   // ����� �������� ����� ������ ������� �������� �� ��� ����

			break;

		}  // if

	}  // while 


	RideTo(FigX, FigY);  // ��������� ���� �� ����� �����������

	Sleep(gl_drag_sleep_time_one_step);  // ����� ������������ ���� ���� ���������� ����� ������������� �����

} // ����� ����� "���������� ����������� �� 1 ���"


// -------------------------------------------------------------
// --------- 4 ���������� ������� ������ ColouredBicycle -------
// -------------------------------------------------------------


// ����������� �������� ����������
ColouredBicycle::ColouredBicycle(int InitX, int InitY, int InitSize, int InitDirection, COLORREF InitColour) : Bicycle(InitX, InitY, InitSize, InitDirection)
{


	colour = InitColour;  // ������������� ���� ����������


}  // ����� ����� "����������� �������� ����������"


// ���������� �������� ����������
ColouredBicycle::~ColouredBicycle() {


	// ������ ����


}  // ����� ����� "���������� �������� ����������"


// �������� ���� ����������
COLORREF ColouredBicycle::GetColour() {


	return colour;  // ���������� ���� ����������


}  // ����� ����� "�������� ���� ����������"


// ���������� ����� ���� ����������
void ColouredBicycle::SetColour(COLORREF NewColour) {


	bool was_visible = Visible;  // ��� ������� ��� ������� ���������

	GetHidden();  // � ����� ������ ��������� �� ������ ���� ����� ��� ��������� ��� ���������

	colour = NewColour;  // ������������� ����� ���� ����������

	if (was_visible) Show();  // ���������� ���������, ���� ���������� �� ��� �����


}  // ����� ����� "���������� ����� ���� ����������"


// �������� ������� ���������
void ColouredBicycle::Draw() {


	// �������� ���� ����������:
	COLORREF real_colour;

	// ���� ��������� �������, �������� ��� ���� - ��� ���� ����:
	if (!Visible) real_colour = colour_default_backgroung;
	else real_colour = colour;

	// ������� �����:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, real_colour);

	SelectObject(hdc, hPen1); // ������ ����� ��������


	// -- ��������� ���������� --
	// 
	// () ���� ��������� ����� � �������������� �� (X,Y) �� (X + 3*size, Y + 1.5*size)
	// () ��������������� ����� ����������: (X + 1.5*size, Y + size)
	// () ������� ����� - size
	// () ����� ���������� - size
	// () ������ ���������� ����� � ������ �� ���������������� ������ - �� 1,5 size
	// () ������ ���������� ��� ��������������� ������� - 1 size
	// () ������� ���������� ��� ��������������� ������� - 0,5 size


	// ������� ����������:

	int center_x, center_y; // ����� ���������� (��������������� �����, �� ��������������)

	int left_wheel_center_x, left_wheel_center_y,  // ������ ����� ����������
		right_wheel_center_x, right_wheel_center_y;


	// ������� �������:

	int l = size;  // ������ ����������� �������

	int r = l * 0.5;  // ������ �����

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // ������� ����� ���������� � ������������ �� ������ � ������� ����� �������

	// ���������� ����������:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- ������ ������ ���������� ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

	// �������� ����������� �������:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x + l - r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x - l + r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	}  // else 


	// --------- ������ ���� ���������� ----------


	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- ������ ������ ���������� ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);


}  // ����� ����� "�������� ������� ���������"


// -------------------------------------------------------------
// -------- 5 ���������� ������� ������ TestBicycle ------
// -------------------------------------------------------------


// ����������� TestBicycle
TestBicycle::TestBicycle(int InitX, int InitY, int InitSize, int InitDirection) : Bicycle(InitX, InitY, InitSize, InitDirection) {


	// ������ ����


} // ����� ����� "����������� TestBicycle"


// ���������� TestBicycle
TestBicycle::~TestBicycle() {


	// ������ ����


}  // ����� ����� "���������� TestBicycle"


// �������� TestBicycle
void TestBicycle::Draw() {


	// �������� ���� ����������:
	COLORREF real_colour;


	if (!Visible) real_colour = colour_default_backgroung;  // ���� ��������� �������, �������� ��� ���� - ��� ���� ����
	else real_colour = colour_inverted_default_backgroung;  // ����� - ��������������� ���� ����


	// ������� �����:
	HPEN hPen1 = CreatePen(PS_DASH, 1, real_colour);

	SelectObject(hdc, hPen1); // ������ ����� ��������


	// -- ��������� ���������� --
	// 
	// () ���� ��������� ����� � �������������� �� (X,Y) �� (X + 3*size, Y + 1.5*size)
	// () ��������������� ����� ����������: (X + 1.5*size, Y + size)
	// () ������� ����� - size
	// () ����� ���������� - size
	// () ������ ���������� ����� � ������ �� ���������������� ������ - �� 1,5 size
	// () ������ ���������� ��� ��������������� ������� - 1 size
	// () ������� ���������� ��� ��������������� ������� - 0,5 size


	// ������� ����������:

	int center_x, center_y; // ����� ���������� (��������������� �����, �� ��������������)

	int left_wheel_center_x, left_wheel_center_y,  // ������ ����� ����������
		right_wheel_center_x, right_wheel_center_y;


	// ������� �������:

	int l = size;  // ������ ����������� �������

	int r = l * 0.5;  // ������ �����

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // ������� ����� ���������� � ������������ �� ������ � ������� ����� �������

	// ���������� ����������:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- ������ ������ ���������� ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

	// �������� ����������� �������:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x + l - r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x - l + r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	}  // else 


	// --------- ������ ���� ���������� ----------


	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- ������ ������ ���������� ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);


}  // ����� ����� "�������� TestBicycle"


// ---------------------------------------------------------------------
// -------- 6 ���������� ������� ������ BicycleWithSpinningWheels ------
// ---------------------------------------------------------------------


// ����������� ���������� � ��������� �������� ����� ��� ��������
BicycleWithSpinningWheels::BicycleWithSpinningWheels(int InitX, int InitY, int InitSize, int InitDirection, COLORREF InitColour) : ColouredBicycle(InitX, InitY, InitSize, InitDirection, InitColour) {


	SpinPhase = 0;  // ������������� ��������� ���� �������� �����


}  // ����� ����� "����������� ���������� � ��������� �������� ����� ��� ��������"


// ���������� ���������� � ���������� ����� ��� ��������
BicycleWithSpinningWheels::~BicycleWithSpinningWheels() {


	// ������ ����


}  // ����� ����� "���������� ���������� � ���������� ����� ��� ��������"


// �������� ���� �������� �����
int BicycleWithSpinningWheels::GetSpinPhase() {


	return SpinPhase;


}  // ����� ����� "�������� ���� �������� �����"


// ���������� ���� �������� �����
void BicycleWithSpinningWheels::SetSpinPhase(float NewSpinPhase) {


	bool was_visible = Visible;  // ��� ������� ��� ������� ���������

	GetHidden();  // � ����� ������ ��������� �� ������ ���� ����� ��� ��������� ��� ���������

	SpinPhase = NewSpinPhase;  // ������������� ����� ���� �������� �����

	if (SpinPhase > 6.28) SpinPhase = 0;  // ������� ����

	if (was_visible) Show();  // ���������� ���������, ���� ���������� �� ��� �����


} // ����� ����� "���������� ���� �������� �����"


// ��� ���������� � �����������, ����� �� ���� � ����� �����
void BicycleWithSpinningWheels::WhenRide(int NewX, int NewY) {

	// ���� ��������� ������ � �������, ��������������� ��� �������� �����������, �� ��������� ������ �����������:
	if ((NewX > X && direction == 0) || (NewX < X && direction == 1)) {

		Rotate();  // ������� ����������

	}  // if

	// ���� ���������� ����������� ��� ��������:
	float L = sqrt(
		pow((NewX - X), 2) +
		pow((NewY - Y), 2));

	// ������ ����� ����������:
	float R = size / 2;

	// ���� ��������� ���� ������:
	if (direction == 1) {

		// ������������� ����� ���� �������� ������ (������ ��������������, ����� ��������� ������ ������� L):
		SetSpinPhase(SpinPhase - L / R);

	}
	else {  // ��������� ���� �����

		// ������������� ����� ���� �������� ������ (������ ��������������, ����� ��������� ������ ������� L):
		SetSpinPhase(SpinPhase + L / R);

	}

}  // ����� ����� "��� ���������� � �����������, ����� �� ���� � ����� �����"


// �������� ��������� � ��������� �������� �����
void BicycleWithSpinningWheels::Draw() {


	// �������� ���� ����������:
	COLORREF real_colour;

	// ���� ��������� �������, �������� ��� ���� - ��� ���� ����:
	if (!Visible) real_colour = colour_default_backgroung;
	else real_colour = colour;


	// ������� �����:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, real_colour);

	SelectObject(hdc, hPen1); // ������ ����� ��������


	// -- ��������� ���������� --
	// 
	// () ���� ��������� ����� � �������������� �� (X,Y) �� (X + 3*size, Y + 1.5*size)
	// () ��������������� ����� ����������: (X + 1.5*size, Y + size)
	// () ������� ����� - size
	// () ����� ���������� - size
	// () ������ ���������� ����� � ������ �� ���������������� ������ - �� 1,5 size
	// () ������ ���������� ��� ��������������� ������� - 1 size
	// () ������� ���������� ��� ��������������� ������� - 0,5 size


	// ������� ����������:

	int center_x, center_y; // ����� ���������� (��������������� �����, �� ��������������)

	int left_wheel_center_x, left_wheel_center_y,  // ������ ����� ����������
		right_wheel_center_x, right_wheel_center_y;


	// ������� �������:

	int l = size;  // ������ ����������� �������

	int r = l * 0.5;  // ������ �����

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // ������� ����� ���������� � ������������ �� ������ � ������� ����� �������

	// ���������� ����������:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- ������ ������ ���������� ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

	// �������� ����������� �������:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x + l - r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x - l + r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	}  // else 


	// --------- ������ ���� ���������� ----------


	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- ������ ������ ���������� ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);

	// -------------- ������ ����� ����� -----------

	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase), left_wheel_center_y - r * sin(SpinPhase));
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase + 1.57), left_wheel_center_y - r * sin(SpinPhase + 1.57));
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase + 3.14), left_wheel_center_y - r * sin(SpinPhase - 3.14));
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase - 1.57), left_wheel_center_y - r * sin(SpinPhase - 1.57));

	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase), right_wheel_center_y - r * sin(SpinPhase));
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase + 1.57), right_wheel_center_y - r * sin(SpinPhase + 1.57));
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase + 3.14), right_wheel_center_y - r * sin(SpinPhase - 3.14));
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase - 1.57), right_wheel_center_y - r * sin(SpinPhase - 1.57));

}  // ����� ����� "�������� ��������� � ��������� �������� �����"


// ---------------------------------------------------------------------
// ----------------- 7 ���������� ������� ������ Man -------------------
// ---------------------------------------------------------------------


// ���������� ��������
Man::Man(int InitX, int InitY, int InitSize, std::string InitName) : Point(InitX, InitY) {

	name = InitName;  // ��������� ���
	IsAlive = true;  // �� ������ ������� ���
	size = InitSize;  // ��������� ������

} // ����� ����� "���������� ��������"


// ���������� �������� 
Man::~Man() {


	// ������ ����


} // ����� ����� "���������� ��������" 


// ������, ��� �� �������
bool Man::GetIsAlive() {


	return IsAlive;  // ���������� ������ ����� ��������


}  // ����� ����� "������, ��� �� �������"


// ����� ��� ���������� ��������
void Man::SetIsAlive(bool NewIsAlive) {


	bool was_visible = Visible;  // ��� ������� ��� ������� �������

	GetHidden();  // � ����� ������ ������� �� ������ ���� ����� ��� ��������� ��� ���������

	IsAlive = NewIsAlive;  // ������������� ������ ����� ��������

	if (was_visible) Show();  // ���������� ��������, ���� ���������� �� ��� �����


}  // ����� ����� "����� ��� ���������� ��������"


// ��������� ������� ��������
int Man::GetSize() {


	return size; // ���������� ������ ��������


} // ����� ����� "��������� ������� ��������"


// ��������� �������� ������� ��������
void Man::SetSize(int NewSize) { // ��������� �������� ���� Size


	bool was_visible = Visible;  // ��� ������� ��� ������� ���������

	GetHidden();  // � ����� ������ ��������� �� ������ ���� ����� ��� ��������� ��� ���������

	size = NewSize;  // ������������� ����� ������ ��������

	if (size < gl_min_bike_size) size = gl_min_bike_size;  // �� ������ ������� ������ ������� ������� ��������

	if (size > gl_max_bike_size) size = gl_max_bike_size;  // �� ������ ������� ������� ������� ������� ��������

	if (was_visible) Show();  // ���������� ���������, ���� ���������� �� ��� �����


} // SetSize()


// �������� ���
string Man::GetName() {

	return name;

}


// ������ ��������
void Man::Draw() {


	COLORREF colour;  // ���� ��������


	// ������������� ����:
	if (Visible) colour = colour_default_base2;
	else colour = colour_default_backgroung;


	// ������� �����:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, colour);

	SelectObject(hdc, hPen1); // ������ ����� ��������

	if (IsAlive) {  // ���� ���, ������ ���������

		// -- ��������� �������� --
		// 
		// () ���� ������� ����� � �������������� �� (X,Y) �� (X + size, Y + 2.87*size)
		// () ��� �������� - (X + size/2, Y + 2 * size)
		// () ����� �������� - (X + size/2, Y + size)
		// () ������� ������ - size
		// () ����� ��� � ��� - size


		// ������� ����������:

		int groin_x, groin_y;  // ���

		int shoulders_x, shoulders_y;  // �����


		// ������� �������:

		int l = size;  // ����� �����������

		int d = size;  // ������� ������

		// ���������� ����������:

		groin_x = X + l / 2;
		groin_y = Y + 2 * l;

		shoulders_x = X + l / 2;
		shoulders_y = Y + l;

		// --------- ������ �������� ----------

		MoveToEx(hdc, groin_x, groin_y, NULL);  // ���������� ���� � ���

		LineTo(hdc, groin_x - l / 2, groin_y + (l / 2) * 1.7);  // ����� ����

		MoveToEx(hdc, groin_x, groin_y, NULL);  // ���������� ���� � ���

		LineTo(hdc, groin_x + l / 2, groin_y + (l / 2) * 1.7);  // ������ ����

		MoveToEx(hdc, groin_x, groin_y, NULL);  // ���������� ���� � ���

		LineTo(hdc, shoulders_x, shoulders_y);  // �����

		LineTo(hdc, shoulders_x - l / 2, shoulders_y + (l / 2) * 1.7);  // ����� ����

		MoveToEx(hdc, shoulders_x, shoulders_y, NULL);  // ���������� ���� � ������

		LineTo(hdc, shoulders_x + l / 2, shoulders_y + (l / 2) * 1.7);  // ������ ����

		Ellipse(hdc, shoulders_x - l / 2, shoulders_y - l, shoulders_x + l / 2, shoulders_y);

	}
	else {  // ���� ������� �� ���, ������ ���������

		// -- ��������� ������ --
		// 
		// () ��� ������� ����� � �������������� �� (X,Y) �� (X + size, Y + 2.87*size)
		// () ������ �������� ����� - 1.5*size
		// () ������ ������ - 2*size
		// () ����� - 0.87*size
		// () ������ ������� ����� - 0.5*size

		int h = 1.5 * size;
		int H = 2 * size;
		int HH = 2.87 * size;
		int w = size;

		// �������� �����
		MoveToEx(hdc, X, Y + HH - h, NULL);
		LineTo(hdc, X, Y + HH);
		LineTo(hdc, X + w, Y + HH);
		LineTo(hdc, X + w, Y + HH - h);
		LineTo(hdc, X + 0.75 * w, Y + HH - H);
		LineTo(hdc, X + 0.25 * w, Y + HH - H);
		LineTo(hdc, X, Y + HH - h);

		// �����
		MoveToEx(hdc, X + 0.5 * w, Y + HH - H, NULL);
		LineTo(hdc, X + 0.5 * w, Y);
		MoveToEx(hdc, X + 0.3 * w, Y + (HH - H) / 3, NULL);
		LineTo(hdc, X + 0.7 * w, Y + (HH - H) / 3);
	}


} // ����� ����� "������ ��������"


// ---------------------------------------------------------------------
// ----------------- 8 ���������� ������� ������ Male ------------------
// ---------------------------------------------------------------------


// ���������� �������
Male::Male(int InitX, int InitY, int InitSize, std::string InitName) : Man(InitX, InitY, InitSize, InitName) {


	// ������ ����


} // ����� ����� "����������� �������"


// ���������� ������� 
Male::~Male() {


	// ������ ����


} // ����� ����� "���������� �������"


// ������ �������
void Male::Draw() {


	COLORREF colour;  // ���� ��������


	// ������������� ����:
	if (Visible) colour = colour_default_base2;
	else colour = colour_default_backgroung;


	// ������� �����:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, colour);

	SelectObject(hdc, hPen1); // ������ ����� ��������

	if (IsAlive) {  // ���� ���, ������ ���������

		// -- ��������� �������� --
		// 
		// () ���� ������� ����� � �������������� �� (X,Y) �� (X + size, Y + 2.87*size)
		// () ��� �������� - (X + size/2, Y + 2 * size)
		// () ����� �������� - (X + size/2, Y + size)
		// () ������� ������ - size
		// () ����� ��� � ��� - size


		// ������� ����������:

		int groin_x, groin_y;  // ���

		int shoulders_x, shoulders_y;  // �����


		// ������� �������:

		int l = size;  // ����� �����������

		int d = size;  // ������� ������

		// ���������� ����������:

		groin_x = X + l / 2;
		groin_y = Y + 2 * l;

		shoulders_x = X + l / 2;
		shoulders_y = Y + l;

		// --------- ������ �������� ----------

		MoveToEx(hdc, groin_x, groin_y, NULL);  // ���������� ���� � ���

		LineTo(hdc, groin_x - l / 2, groin_y + (l / 2) * 1.7);  // ����� ����

		MoveToEx(hdc, groin_x, groin_y, NULL);  // ���������� ���� � ���

		LineTo(hdc, groin_x + l / 2, groin_y + (l / 2) * 1.7);  // ������ ����

		MoveToEx(hdc, groin_x, groin_y, NULL);  // ���������� ���� � ���

		LineTo(hdc, shoulders_x, shoulders_y);  // �����

		LineTo(hdc, shoulders_x - l / 2, shoulders_y + (l / 2) * 1.7);  // ����� ����

		MoveToEx(hdc, shoulders_x, shoulders_y, NULL);  // ���������� ���� � ������

		LineTo(hdc, shoulders_x + l / 2, shoulders_y + (l / 2) * 1.7);  // ������ ����

		Ellipse(hdc, shoulders_x - l / 2, shoulders_y - l, shoulders_x + l / 2, shoulders_y);

		// --------- ������ ������� ����� ---------

		int beard_size = size / 4;  // ������ ������

		// ������ ������
		Pie(hdc, shoulders_x - beard_size, shoulders_y - beard_size, shoulders_x + beard_size, shoulders_y + beard_size, shoulders_x - beard_size, shoulders_y - beard_size, shoulders_x + beard_size, shoulders_y - beard_size);

		// ������ �������� ����  // �� ������ ����� ������� �� ������� ������
		Arc(hdc, shoulders_x - beard_size, shoulders_y - 2 * beard_size, shoulders_x + beard_size, shoulders_y + 2 * beard_size, shoulders_x + beard_size, shoulders_y - beard_size, shoulders_x - beard_size, shoulders_y - beard_size);

	}
	else {  // ���� ������� �� ���, ������ ���������

		// -- ��������� ������ --
		// 
		// () ��� ������� ����� � �������������� �� (X,Y) �� (X + size, Y + 2.87*size)
		// () ������ �������� ����� - 1.5*size
		// () ������ ������ - 2*size
		// () ����� - 0.87*size
		// () ������ ������� ����� - 0.5*size

		int h = 1.5 * size;
		int H = 2 * size;
		int HH = 2.87 * size;
		int w = size;

		// �������� �����
		MoveToEx(hdc, X, Y + HH - h, NULL);
		LineTo(hdc, X, Y + HH);
		LineTo(hdc, X + w, Y + HH);
		LineTo(hdc, X + w, Y + HH - h);
		LineTo(hdc, X + 0.75 * w, Y + HH - H);
		LineTo(hdc, X + 0.25 * w, Y + HH - H);
		LineTo(hdc, X, Y + HH - h);

		// �����
		MoveToEx(hdc, X + 0.5 * w, Y + HH - H, NULL);
		LineTo(hdc, X + 0.5 * w, Y);
		MoveToEx(hdc, X + 0.3 * w, Y + (HH - H) / 3, NULL);
		LineTo(hdc, X + 0.7 * w, Y + (HH - H) / 3);
	}


}  // ����� ����� "������ �������"


// -----------------------------------------------------------------------
// ----------------- 9 ���������� ������� ������ Female ------------------
// -----------------------------------------------------------------------


// ���������� �������
Female::Female(int InitX, int InitY, int InitSize, std::string InitName) : Man(InitX, InitY, InitSize, InitName) {


	// ������ ����


} // ����� ����� "����������� �������"  


// ���������� �������
Female::~Female() {


	// ������ ����


} // ����� ����� "���������� �������" 


// ������ �������
void Female::Draw() {



	COLORREF colour;  // ���� ��������


	// ������������� ����:
	if (Visible) colour = colour_default_base2;
	else colour = colour_default_backgroung;


	// ������� �����:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, colour);

	SelectObject(hdc, hPen1); // ������ ����� ��������

	if (IsAlive) {  // ���� ���, ������ ���������

		// -- ��������� �������� --
		// 
		// () ���� ������� ����� � �������������� �� (X,Y) �� (X + size, Y + 2.87*size)
		// () ��� �������� - (X + size/2, Y + 2 * size)
		// () ����� �������� - (X + size/2, Y + size)
		// () ������� ������ - size
		// () ����� ��� � ��� - size


		// ������� ����������:

		int groin_x, groin_y;  // ���

		int shoulders_x, shoulders_y;  // �����


		// ������� �������:

		int l = size;  // ����� �����������

		int d = size;  // ������� ������

		// ���������� ����������:

		groin_x = X + l / 2;
		groin_y = Y + 2 * l;

		shoulders_x = X + l / 2;
		shoulders_y = Y + l;

		// --------- ������ �������� ----------

		MoveToEx(hdc, groin_x, groin_y, NULL);  // ���������� ���� � ���

		LineTo(hdc, groin_x - l / 2, groin_y + (l / 2) * 1.7);  // ����� ����

		MoveToEx(hdc, groin_x, groin_y, NULL);  // ���������� ���� � ���

		LineTo(hdc, groin_x + l / 2, groin_y + (l / 2) * 1.7);  // ������ ����

		MoveToEx(hdc, groin_x, groin_y, NULL);  // ���������� ���� � ���

		LineTo(hdc, shoulders_x, shoulders_y);  // �����

		// --------- ������ ������� ����� ---------

		int breast_size = size / 4;  // ������ ����

		// ������ ���

		Ellipse(hdc, shoulders_x - breast_size, shoulders_y + breast_size / 2, shoulders_x + breast_size, shoulders_y + 1.5 * breast_size);

		// ----- ����� ������ ������� ����� -------

		// ����� ����
		Arc(hdc, shoulders_x - l / 2, shoulders_y, shoulders_x + l / 2, shoulders_y + l, shoulders_x, shoulders_y, shoulders_x - l / 2, shoulders_y + (l / 2) * 1.7);

		// ������ ����
		Arc(hdc, shoulders_x - l / 2, shoulders_y, shoulders_x + l / 2, shoulders_y + l, shoulders_x + l / 2, shoulders_y + (l / 2) * 1.7, shoulders_x, shoulders_y);

		// ������
		Ellipse(hdc, shoulders_x - l / 2, shoulders_y - l, shoulders_x + l / 2, shoulders_y);



	}
	else {  // ���� ������� �� ���, ������ ���������

		// -- ��������� ������ --
		// 
		// () ��� ������� ����� � �������������� �� (X,Y) �� (X + size, Y + 2.87*size)
		// () ������ �������� ����� - 1.5*size
		// () ������ ������ - 2*size
		// () ����� - 0.87*size
		// () ������ ������� ����� - 0.5*size

		int h = 1.5 * size;
		int H = 2 * size;
		int HH = 2.87 * size;
		int w = size;

		// �������� �����
		MoveToEx(hdc, X, Y + HH - h, NULL);
		LineTo(hdc, X, Y + HH);
		LineTo(hdc, X + w, Y + HH);
		LineTo(hdc, X + w, Y + HH - h);
		LineTo(hdc, X + 0.75 * w, Y + HH - H);
		LineTo(hdc, X + 0.25 * w, Y + HH - H);
		LineTo(hdc, X, Y + HH - h);

		// �����
		MoveToEx(hdc, X + 0.5 * w, Y + HH - H, NULL);
		LineTo(hdc, X + 0.5 * w, Y);
		MoveToEx(hdc, X + 0.3 * w, Y + (HH - H) / 3, NULL);
		LineTo(hdc, X + 0.7 * w, Y + (HH - H) / 3);
	}



} // ����� ����� "������ �������"


// ------------------------------------------------------------------------
// ----------------- 10 ���������� ������� ������ Tricycle ----------------
// ------------------------------------------------------------------------


// ����������� ������������� ����������
Tricycle::Tricycle(int InitX, int InitY, int InitSize, int InitDirection) : Bicycle(InitX, InitY, InitSize, InitDirection)
{


	// ������ ����


}  // ����� ����� "����������� ������������� ����������"


 // ���������� ������������� ����������
Tricycle::~Tricycle() {


	// ������ ����


} // ����� ����� "���������� ������������� ����������"


// �������� ������������ ���������
void Tricycle::Draw() {


	COLORREF colour;  // ���� ����������


	// ������������� ����:
	if (Visible) colour = colour_default_base;
	else colour = colour_default_backgroung;


	// ������� �����:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, colour);

	SelectObject(hdc, hPen1); // ������ ����� ��������


	// -- ��������� ���������� --
	// 
	// () ���� ��������� ����� � �������������� �� (X,Y) �� (X + 3*size, Y + 1.5*size)
	// () ��������������� ����� ����������: (X + 1.5*size, Y + size)
	// () ������� ����� - size
	// () ����� ���������� - size
	// () ������ ���������� ����� � ������ �� ���������������� ������ - �� 1,5 size
	// () ������ ���������� ��� ��������������� ������� - 1 size
	// () ������� ���������� ��� ��������������� ������� - 0,5 size


	// ������� ����������:

	int center_x, center_y; // ����� ���������� (��������������� �����, �� ��������������)

	int left_wheel_center_x, left_wheel_center_y,  // ������ ����� ����������
		right_wheel_center_x, right_wheel_center_y;


	// ������� �������:

	int l = size;  // ������ ����������� �������

	int r = l * 0.5;  // ������ �����

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // ������� ����� ���������� � ������������ �� ������ � ������� ����� �������

	// ���������� ����������:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- ������ ������ ���������� ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

	// �������� ����������� �������:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x + l - r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x - l + r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	}  // else 


	// --------- ������ ���� ���������� ----------


	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- ������ ������ ���������� ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (center_x - 0.5 * l), center_y - 0.5 * l, center_x + 0.5 * l, center_y + 0.5 * l);

} // ����� ����� "�������� ������������ ���������"



// ------------------------------------------------------------------------------
// ----------------- 11 ���������� ������� ������ ColouredTricycle --------------
// ------------------------------------------------------------------------------


// ����������� �������� ������������� ����������
ColouredTricycle::ColouredTricycle(int InitX, int InitY, int InitSize, int InitDirection, COLORREF InitColour) : Tricycle(InitX, InitY, InitSize, InitDirection) {


	colour = InitColour;  // ������������� ���� ����������


} // ����� ����� "����������� �������� ������������� ����������"


// ���������� �������� ������������� ����������
ColouredTricycle::~ColouredTricycle() {


	// ������ ����


}  // ����� ����� "���������� �������� ������������� ����������"


// �������� ���� ������������� ����������
COLORREF ColouredTricycle::GetColour() {


	return colour;  // ���������� ���� ����������


}  // ����� ����� "�������� ���� ������������� ����������"


// ���������� ����� ���� ������������� ����������
void ColouredTricycle::SetColour(COLORREF NewColour) {

	bool was_visible = Visible;  // ��� ������� ��� ������� ���������

	GetHidden();  // � ����� ������ ��������� �� ������ ���� ����� ��� ��������� ��� ���������

	colour = NewColour;  // ������������� ����� ���� ����������

	if (was_visible) Show();  // ���������� ���������, ���� ���������� �� ��� �����

}  // ����� ����� "���������� ����� ���� ������������� ����������"


// �������� ������� ������������ ���������
void ColouredTricycle::Draw() {


	// �������� ���� ����������:
	COLORREF real_colour;

	// ���� ��������� �������, �������� ��� ���� - ��� ���� ����:
	if (!Visible) real_colour = colour_default_backgroung;
	else real_colour = colour;

	// ������� �����:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, real_colour);

	SelectObject(hdc, hPen1); // ������ ����� ��������


	// -- ��������� ���������� --
	// 
	// () ���� ��������� ����� � �������������� �� (X,Y) �� (X + 3*size, Y + 1.5*size)
	// () ��������������� ����� ����������: (X + 1.5*size, Y + size)
	// () ������� ����� - size
	// () ����� ���������� - size
	// () ������ ���������� ����� � ������ �� ���������������� ������ - �� 1,5 size
	// () ������ ���������� ��� ��������������� ������� - 1 size
	// () ������� ���������� ��� ��������������� ������� - 0,5 size


	// ������� ����������:

	int center_x, center_y; // ����� ���������� (��������������� �����, �� ��������������)

	int left_wheel_center_x, left_wheel_center_y,  // ������ ����� ����������
		right_wheel_center_x, right_wheel_center_y;


	// ������� �������:

	int l = size;  // ������ ����������� �������

	int r = l * 0.5;  // ������ �����

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // ������� ����� ���������� � ������������ �� ������ � ������� ����� �������

	// ���������� ����������:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- ������ ������ ���������� ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

	// �������� ����������� �������:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x + l - r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x - l + r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	}  // else 


	// --------- ������ ���� ���������� ----------


	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- ������ ������ ���������� ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (center_x - 0.5 * l), center_y - 0.5 * l, center_x + 0.5 * l, center_y + 0.5 * l);

} // ����� ����� "�������� ������� ������������ ���������"



// -----------------------------------------------------------------------------------
// ----------------- 12 ���������� ������� ������ TricycleWithSpinningWheels ---------
// -----------------------------------------------------------------------------------


// ����������� ������������� ���������� � ��������� �������� ����� ��� ��������
TricycleWithSpinningWheels::TricycleWithSpinningWheels(int InitX, int InitY, int InitSize, int InitDirection, COLORREF InitColour) : ColouredTricycle(InitX, InitY, InitSize, InitDirection, InitColour) {


	SpinPhase = 0;  // ������������� ��������� ���� �������� �����


}  // ����� ����� "����������� ������������� ���������� � ��������� �������� ����� ��� ���������"


// ���������� ������������� ���������� � ��������� �������� ����� ��� ��������
TricycleWithSpinningWheels::~TricycleWithSpinningWheels() {


	// ������ ����


}  // ����� ����� "���������� ������������� ���������� � ��������� �������� ����� ��� ��������"


// �������� ���� �������� �����
int TricycleWithSpinningWheels::GetSpinPhase() {


	return SpinPhase;


}  // ����� ����� "�������� ���� �������� �����"


// ���������� ���� �������� �����
void TricycleWithSpinningWheels::SetSpinPhase(float NewSpinPhase) {


	bool was_visible = Visible;  // ��� ������� ��� ������� ���������

	GetHidden();  // � ����� ������ ��������� �� ������ ���� ����� ��� ��������� ��� ���������

	SpinPhase = NewSpinPhase;  // ������������� ����� ���� �������� �����

	if (SpinPhase > 6.28) SpinPhase = 0;  // ������� ����

	if (was_visible) Show();  // ���������� ���������, ���� ���������� �� ��� �����


} // ����� ����� "���������� ���� �������� �����"


// ��� ���������� � ������������ �����������, ����� �� ���� � ����� �����
void TricycleWithSpinningWheels::WhenRide(int NewX, int NewY) {

	// ���� ��������� ������ � �������, ��������������� ��� �������� �����������, �� ��������� ������ �����������:
	if ((NewX > X && direction == 0) || (NewX < X && direction == 1)) {

		Rotate();  // ������� ����������

	}  // if

	// ���� ���������� ����������� ��� ��������:
	float L = sqrt(
		pow((NewX - X), 2) +
		pow((NewY - Y), 2));

	// ������ ����� ����������:
	float R = size / 2;

	// ���� ��������� ���� ������:
	if (direction == 1) {

		// ������������� ����� ���� �������� ������ (������ ��������������, ����� ��������� ������ ������� L):
		SetSpinPhase(SpinPhase - L / R);

	}
	else {  // ��������� ���� �����

		// ������������� ����� ���� �������� ������ (������ ��������������, ����� ��������� ������ ������� L):
		SetSpinPhase(SpinPhase + L / R);

	}

}  // ����� ����� "��� ���������� � ������������ �����������, ����� �� ���� � ����� �����"


// �������� ������������ ��������� � ��������� �������� �����
void TricycleWithSpinningWheels::Draw() {


	// �������� ���� ����������:
	COLORREF real_colour;

	// ���� ��������� �������, �������� ��� ���� - ��� ���� ����:
	if (!Visible) real_colour = colour_default_backgroung;
	else real_colour = colour;

	// ������� �����:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, real_colour);

	SelectObject(hdc, hPen1); // ������ ����� ��������


	// -- ��������� ���������� --
	// 
	// () ���� ��������� ����� � �������������� �� (X,Y) �� (X + 3*size, Y + 1.5*size)
	// () ��������������� ����� ����������: (X + 1.5*size, Y + size)
	// () ������� ����� - size
	// () ����� ���������� - size
	// () ������ ���������� ����� � ������ �� ���������������� ������ - �� 1,5 size
	// () ������ ���������� ��� ��������������� ������� - 1 size
	// () ������� ���������� ��� ��������������� ������� - 0,5 size


	// ������� ����������:

	int center_x, center_y; // ����� ���������� (��������������� �����, �� ��������������)

	int left_wheel_center_x, left_wheel_center_y,  // ������ ����� ����������
		right_wheel_center_x, right_wheel_center_y;


	// ������� �������:

	int l = size;  // ������ ����������� �������

	int r = l * 0.5;  // ������ �����

	int wheel_cos = r / sqrt(pow((l * 1.7 / 2), 2) + pow(2, r));  // ������� ����� ���������� � ������������ �� ������ � ������� ����� �������

	// ���������� ����������:

	center_x = X + 1.5 * l;
	center_y = Y + l;

	left_wheel_center_x = center_x - l;
	left_wheel_center_y = center_y;

	right_wheel_center_x = center_x + l;
	right_wheel_center_y = center_y;

	// --------- ������ ������ ���������� ----------

	MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

	// �������� ����������� �������:
	LineTo(hdc, center_x + l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x - l / 2, center_y - (l / 2) * 1.7);
	LineTo(hdc, center_x, center_y);

	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x + l - r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ��������������� �����

		LineTo(hdc, center_x - l + r, center_y);  // � ������� ������ ����������� �� ������

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ������ ���� ����������

		LineTo(hdc, center_x - l + r * wheel_cos, center_y - r * wheel_cos);  // � ������� ������ ����������� �� ������� ����� ����������

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � �������� ���� ����������

		LineTo(hdc, center_x + l - r * wheel_cos, center_y - r * wheel_cos);  // � ��������� ������ ����������� �� ��������� ����� ����������

	}  // else 


	// --------- ������ ���� ���������� ----------


	// ���� ��������� ���� �����:
	if (direction == 0) {

		MoveToEx(hdc, center_x - l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x - l / 2 - l / 8, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 - l / 3, center_y - (l / 2) * 1.7 - l / 8);
		LineTo(hdc, center_x - l / 2 + l / 12, center_y - (l / 2) * 1.7 - l / 8);

	} // if

	else {  // ���� ��������� ���� �����:

		MoveToEx(hdc, center_x + l / 2, center_y - (l / 2) * 1.7, NULL);  // ���������� ���� � ���� ����������

		// ��������������� ������ ����:
		LineTo(hdc, center_x + l / 2 + l / 8, center_y - l);
		LineTo(hdc, center_x + l / 2 + l / 3, center_y - l);
		LineTo(hdc, center_x + l / 2 - l / 12, center_y - l);

	}  // else 


	// ---------- ������ ������ ���������� ---------

	Ellipse(hdc, (left_wheel_center_x - 0.5 * l), left_wheel_center_y - 0.5 * l, left_wheel_center_x + 0.5 * l, left_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (right_wheel_center_x - 0.5 * l), right_wheel_center_y - 0.5 * l, right_wheel_center_x + 0.5 * l, right_wheel_center_y + 0.5 * l);
	Ellipse(hdc, (center_x - 0.5 * l), center_y - 0.5 * l, center_x + 0.5 * l, center_y + 0.5 * l);

	// -------------- ������ ����� ����� -----------

	// 1-�� ������
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase), left_wheel_center_y - r * sin(SpinPhase));
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase + 1.57), left_wheel_center_y - r * sin(SpinPhase + 1.57));
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase + 3.14), left_wheel_center_y - r * sin(SpinPhase - 3.14));
	MoveToEx(hdc, left_wheel_center_x, left_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, left_wheel_center_x + r * cos(SpinPhase - 1.57), left_wheel_center_y - r * sin(SpinPhase - 1.57));

	// 2-� ������
	MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, center_x + r * cos(SpinPhase), left_wheel_center_y - r * sin(SpinPhase));
	MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, center_x + r * cos(SpinPhase + 1.57), left_wheel_center_y - r * sin(SpinPhase + 1.57));
	MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, center_x + r * cos(SpinPhase + 3.14), left_wheel_center_y - r * sin(SpinPhase - 3.14));
	MoveToEx(hdc, center_x, center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, center_x + r * cos(SpinPhase - 1.57), left_wheel_center_y - r * sin(SpinPhase - 1.57));

	// 3-� ������
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase), right_wheel_center_y - r * sin(SpinPhase));
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase + 1.57), right_wheel_center_y - r * sin(SpinPhase + 1.57));
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase + 3.14), right_wheel_center_y - r * sin(SpinPhase - 3.14));
	MoveToEx(hdc, right_wheel_center_x, right_wheel_center_y, NULL);  // ���������� ���� � ������ ������
	LineTo(hdc, right_wheel_center_x + r * cos(SpinPhase - 1.57), right_wheel_center_y - r * sin(SpinPhase - 1.57));

} // ����� ����� "�������� ������������ ��������� � ��������� �������� �����"



// -----------------------------------------------------------------------------------
// --------------------------- 13 ���������� ������� ������ Button -------------------
// ------------------------------------------------------------------------------------


// ����������� ������
Button::Button(int InitX, int InitY, int InitRadius, COLORREF InitColour) : Point(InitX, InitY) {

	colour = InitColour;
	Visible = true;
	IsActivated = false;
	radius = InitRadius;  // ������������� ������
	Draw();


} // end of ����������� ������

Button::~Button() {}  // ���������� ������

// �������� ������
void Button::Draw() {

	// ���� ������:
	COLORREF real_colour;

	// ������������� ���� ������:
	if (Visible) real_colour = colour;
	else colour = colour_default_backgroung;

	// ������� �����:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, real_colour);

	SelectObject(hdc, hPen1); // ������ ����� ��������

	// ������ ������:

	Ellipse(hdc, X, Y, X + radius, Y + radius);

}

// �������� �������
int Button::GetSize() {

	return radius;

}


// ������ ������������ �� ������
bool Button::GetIsActivated() {

	return IsActivated;

}


// ���������� ���������������� ������
void Button::SetIsActivated(bool NewIsActivated) {

	IsActivated = NewIsActivated;

}



// -----------------------------------------------------------------------------------
// ------------------------ 13 ���������� ������� ������ Tombstone -------------------
// -----------------------------------------------------------------------------------



// ���������� ������
Tombstone::Tombstone(int InitX, int InitY, int InitSize, std::string InitName) : Point(InitX, InitY) {

	size = InitSize;
	name = InitName;

}

// ���������� ������
Tombstone::Tombstone(Man man) : Point(man.GetX(), man.GetY()) {

	size = man.GetSize();
	name = man.GetName();
	Visible = man.GetVisible();

}

// ���������� ������ 
Tombstone::~Tombstone() {}

// ��������� ������� ������
int Tombstone::GetSize() {

	return size;

}


// ��������� �������� ������� ������
void Tombstone::SetSize(int NewSize) {

	size = NewSize;

}


// ������ ������
void Tombstone::Draw() {


	COLORREF colour;  // ���� ��������


	// ������������� ����:
	if (Visible) colour = colour_default_base2;
	else colour = colour_default_backgroung;


	// ������� �����:
	HPEN hPen1 = CreatePen(PS_SOLID, 1, colour);

	SelectObject(hdc, hPen1); // ������ ����� ��������

	// -- ��������� ������ --
	// 
	// () ��� ������� ����� � �������������� �� (X,Y) �� (X + size, Y + 2.87*size)
	// () ������ �������� ����� - 1.5*size
	// () ������ ������ - 2*size
	// () ����� - 0.87*size
	// () ������ ������� ����� - 0.5*size

	int h = 1.5 * size;
	int H = 2 * size;
	int HH = 2.87 * size;
	int w = size;

	// �������� �����
	MoveToEx(hdc, X, Y + HH - h, NULL);
	LineTo(hdc, X, Y + HH);
	LineTo(hdc, X + w, Y + HH);
	LineTo(hdc, X + w, Y + HH - h);
	LineTo(hdc, X + 0.75 * w, Y + HH - H);
	LineTo(hdc, X + 0.25 * w, Y + HH - H);
	LineTo(hdc, X, Y + HH - h);

	// �����
	MoveToEx(hdc, X + 0.5 * w, Y + HH - H, NULL);
	LineTo(hdc, X + 0.5 * w, Y);
	MoveToEx(hdc, X + 0.3 * w, Y + (HH - H) / 3, NULL);
	LineTo(hdc, X + 0.7 * w, Y + (HH - H) / 3);

}