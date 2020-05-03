#include "BBRect.h"

bool BBRect::select(Vector2i mouse, Color color)
{
	if ((mouse.x > coord.x && mouse.x < coord.x + size.x) && (mouse.y > coord.y && mouse.y < coord.y + size.y)) {
		text.setFillColor(color);
		return true;
	}
	else {
		text.setFillColor(this->color);
		return false;
	}
}

BBRect::BBRect(int x, int y, int weight, int height) :num(NUMBER)
{
	if (NUMBER == 0)
		NUMBER = 16;
	x = x + weight * ((NUMBER - 1) % 4);
	y = y + height * ((NUMBER - 1) / 4);
	color = Color::Black;
	font.loadFromFile("resources/comic.ttf");
	win_coord = Vector2i(x, y);
	rect.setSize(Vector2f(weight - 4, height - 4));
	shadowRect.setSize(Vector2f(weight, height));
	shadowRect.setFillColor(color);
	text = Converting().string2text(Converting().int2string(num));
	setSize(Vector2i(weight, height));
	setPosition(Vector2i(x, y));
	text.setFillColor(color);
	text.setFont(font);
	text.setCharacterSize(36);
	if (NUMBER == 16)
		NUMBER = 0;
	NUMBER++;
}
void BBRect::swap(Rectangle & rect)
{
	Vector2i temp = rect.getPosition();
	rect.setPosition(this->getPosition());
	this->setPosition(temp);
}
bool BBRect::onClick(Vector2i mouse, Color col_in)
{
	if (select(mouse, col_in) && Mouse::isButtonPressed(Mouse::Left)) {
		while (Mouse::isButtonPressed(Mouse::Left));
		Music music;
		music.openFromFile("resources/music/click.ogg");
		music.setVolume(100);
		music.play();
		Sleep(125);
		return true;
	}
	else
		return false;
}
void BBRect::setPosition(Vector2i coord)
{
	this->coord = coord;
	shadowRect.setPosition(coord.x, coord.y);
	rect.setPosition(coord.x + 2, coord.y + 2);
	if (num < 10)
		text.setPosition(-9 + coord.x + size.x / 2, -19 + coord.y + size.y / 2);
	else
		text.setPosition(-16 + coord.x + size.x / 2, -19 + coord.y + size.y / 2);
}
Vector2i BBRect::getWinPosition()
{
	return win_coord;
}
void BBRect::OutHere(RenderWindow & window)
{
	window.draw(shadowRect);
	window.draw(rect);
	window.draw(text);
}