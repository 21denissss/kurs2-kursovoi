#pragma once
#include "../Logic/Header.h"

using namespace sf;
using namespace std;

class Button {
private:
	Text text, textShadow;
	Font font;
	Color col;
	int x, y, weight, height;
	bool select(Vector2i mouse, Color col_in = Color::Black);
	Text getText()
	{
		return text;
	}
	Text getShadow()
	{
		return textShadow;
	}
public:
	Button(string st = "\0", float x_in = 0, float y_in = 0, int w = 200, int h = 50, Color col_in = Color::White, Color colShadow_in = Color::Blue);
	bool onClick(Vector2i mouse, Color col_in = Color::Black);
	void outHere(RenderWindow& window)
	{
		window.draw(getShadow());
		window.draw(getText());
	}
};
