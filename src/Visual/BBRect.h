#pragma once
#include "Rectangle.h"
#include "../Logic/Header.h"
#include "../Logic/Converting.h"
extern int NUMBER;

using namespace sf;
using namespace std;
class BBRect :public Rectangle {
	Vector2i win_coord;
	Text text;
	const int num;
	Font font;
	bool select(Vector2i mouse, Color color = Color::Yellow);
public:
	BBRect(int x = 650, int y = 300, int weight = 75, int height = 75);
	void swap(Rectangle& rect);
	bool onClick(Vector2i mouse, Color col_in = Color::Yellow);
	void setPosition(Vector2i coord);
	Vector2i getWinPosition();
	void OutHere(RenderWindow& window);
};

