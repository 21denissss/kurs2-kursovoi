#pragma once
#include "../Logic/Header.h"
#include "../Logic/Converting.h"
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
	bool inBox(Vector2i mouse);
public:
	TextBox(float x_in = 0, float y_in = 0, int w = 110, int h = 50, Color col_in = Color::Black);
	
	bool getSelect(Event event, Vector2i mouse);
	bool is_empty();
	void editTextInt(Event event);
	void editTextString(Event event);
	int getInt();
	string getString();
	void outHere(RenderWindow& window);
};

