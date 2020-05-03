#pragma once
#include "../Logic/Header.h"
#include "../Logic/Converting.h"
using namespace sf;
using namespace std;

class Label {
private:
	Text text, textShadow;
	Font font;
	Color col;
	float x, y;
	Text getText();
	Text getShadow();
public:
	Label(string st = "\0", float x_in = 0, float y_in = 0, int size = 36, Color col_in = Color::White, Color colShadow_in = Color::Blue);
	void changePos(float dx, float dy);
	void setPos(int x_in = 0, int y_in = -1);
	Vector2i getPos();
	void outHere(RenderWindow& window);
	void setText(string st);

};