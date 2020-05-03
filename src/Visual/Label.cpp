#include "Label.h"

Label::Label(string st, float x_in, float y_in, int size, Color col_in, Color colShadow_in) {
	font.loadFromFile("resources/comic.ttf");
	x = x_in;
	y = y_in;
	col = col_in;
	text = Converting().string2text(st);
	text.setFont(font);
	text.setPosition(x, y);
	text.setCharacterSize(size);
	text.setFillColor(col_in);
	textShadow = Converting().string2text(st);
	textShadow.setFont(font);
	textShadow.setPosition(x - 2, y - 1);
	textShadow.setCharacterSize(size);
	textShadow.setFillColor(colShadow_in);
}
void Label::changePos(float dx, float dy)
{
	x += dx;
	y += dy;
	text.setPosition(x, y);
	textShadow.setPosition(x, y);
}
void Label::setPos(int x_in, int y_in)
{
	x = x_in;
	y = y_in;
	text.setPosition(x, y);
	textShadow.setPosition(x, y);
}
Vector2i Label::getPos()
{
	Vector2i temp;
	temp.x = x;
	temp.y = y;
	return temp;
}