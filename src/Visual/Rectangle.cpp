#include "Rectangle.h"


void Rectangle::setSize(Vector2i size)
{
	this->size = size;
}

bool Rectangle::select(Vector2i mouse, Color color )
{
	if ((mouse.x > coord.x && mouse.x < coord.x + size.x) && (mouse.y > coord.y && mouse.y < coord.y + size.y)) {
		if (shadowRect.getFillColor() == Color::Black)
			shadowRect.setFillColor(color);
		return true;
	}
	else {
		if (shadowRect.getFillColor() == color)
			shadowRect.setFillColor(Color::Black);
		return false;
	}
}

void Rectangle::click()
{
	Music music;
	music.openFromFile("resources/music/click.ogg");
	music.setVolume(100);
	music.play();
}

Rectangle::Rectangle(int x, int y, int weight, int height)
{
	color = Color::Black;
	setPosition(Vector2i(x, y));
	setSize(Vector2i(weight, height));
	rect.setSize(Vector2f(weight - 4, height - 4));
	shadowRect.setSize(Vector2f(weight, height));
	shadowRect.setFillColor(color);
}

Vector2i Rectangle::getPosition()
{
	return coord;
}

void Rectangle::setPosition(Vector2i coord)
{
	this->coord = coord;
	shadowRect.setPosition(coord.x, coord.y);
	rect.setPosition(coord.x + 2, coord.y + 2);
}

void Rectangle::OutHere(RenderWindow& window)
{
	window.draw(shadowRect);
	window.draw(rect);
}

Vector2i Rectangle::getSize()
{
	return size;
}

bool Rectangle::onClick(Vector2i mouse, Color col_in)
{
	if (select(mouse, col_in) && Mouse::isButtonPressed(Mouse::Left)) {
		while (Mouse::isButtonPressed(Mouse::Left));
		click();
		return true;
	}
	else
		return false;
}