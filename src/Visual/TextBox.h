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
#include "src/Logic/Converting.h"

using namespace sf;
using namespace std;

extern bool isCaps;

class TextBox {
private:
	Text text;
	Font font;
	Color col;
	bool isReleased;
	RectangleShape BOX;
	bool select;
	int x, y, weight, height;
	bool inBox(Vector2i mouse)
	{
		if ((mouse.x > x && mouse.x < x + weight) && (mouse.y > y && mouse.y < y + height)) {
			return true;
		}
		else {
			return false;
		}
	}
public:
	TextBox(float x_in = 0, float y_in = 0, int w = 110, int h = 50, Color col_in = Color::Black);
	
	bool getSelect(Event event, Vector2i mouse);
	bool is_empty();
	void editTextInt(Event event);
	void editTextString(Event event);
	int getInt();
	string getString()
	{
		return text.getString();
	}
	void outHere(RenderWindow& window)
	{
		window.draw(BOX);
		window.draw(text);
	}
};

