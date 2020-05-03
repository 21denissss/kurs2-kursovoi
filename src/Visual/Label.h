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

class Label {
private:
	Text text, textShadow;
	Font font;
	Color col;
	float x, y;
	Text getText()
	{
		return text;
	}
	Text getShadow()
	{
		return textShadow;
	}
public:
	Label(string st = "\0", float x_in = 0, float y_in = 0, int size = 36, Color col_in = Color::White, Color colShadow_in = Color::Blue);
	void changePos(float dx, float dy);
	void setPos(int x_in = 0, int y_in = -1);
	Vector2i getPos();
	void outHere(RenderWindow& window)
	{
		window.draw(getShadow());
		window.draw(getText());
	}
	void setText(string st)
	{
		text.setString(st);
		textShadow.setString(st);
	}

};