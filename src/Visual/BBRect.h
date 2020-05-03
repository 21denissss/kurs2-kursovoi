#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <GL/glut.h>
#include <sstream>
#include <iostream>
#include <locale>
#include <string.h>
#include <windows.h>
#include "Rectangle.h"
#include "src/Logic/Converting.h"

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

