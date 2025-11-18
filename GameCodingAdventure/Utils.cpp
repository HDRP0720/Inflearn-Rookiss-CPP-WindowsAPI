#include "pch.h"
#include "Utils.h"

void Utils::DrawText(HDC hdc, Pos pos, const wstring& str)
{
	int x = static_cast<int32>(pos.x);
	int y = static_cast<int32>(pos.y);
	::TextOut(hdc, x, y, str.c_str(), static_cast<int32>(str.size()));
}

void Utils::DrawRect(HDC hdc, Pos pos, int32 w, int32 h)
{
	int calcX = static_cast<int32>(pos.x - w / 2);
	int calcY = static_cast<int32>(pos.y - h / 2);
	int postX = static_cast<int32>(pos.x + w / 2);
	int postY = static_cast<int32>(pos.y + w / 2);

	::Rectangle(hdc, calcX, calcY, postX, postY);
}

void Utils::DrawCircle(HDC hdc, Pos pos, int32 radius)
{
	int calcX = static_cast<int32>(pos.x - radius);
	int calcY = static_cast<int32>(pos.y - radius);
	int postX = static_cast<int32>(pos.x + radius);
	int postY = static_cast<int32>(pos.y + radius);

	::Ellipse(hdc, calcX, calcY, postX, postY);
}

void Utils::DrawLine(HDC hdc, Pos from, Pos to)
{
	int fromX = static_cast<int32>(from.x);
	int fromY = static_cast<int32>(from.y);
	int toX = static_cast<int32>(to.x);
	int toY = static_cast<int32>(to.x);

	::MoveToEx(hdc, fromX, fromY, nullptr);
	::LineTo(hdc, toX, toY);
}
