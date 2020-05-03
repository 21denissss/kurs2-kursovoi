#include "Button.h"


Button::Button(string st, float x_in, float y_in, int w, int h, Color col_in, Color colShadow_in) {
	font.loadFromFile("resources/comic.ttf");
	x = x_in;
	y = y_in;
	col = col_in;
	weight = w;
	height = h;
	text.setFont(font);
	text.setPosition(x, y);
	text.setString(st);
	text.setCharacterSize(36);
	text.setFillColor(col_in);
	textShadow.setFont(font);
	textShadow.setPosition(x - 1, y);
	textShadow.setString(st);
	textShadow.setCharacterSize(36);
	textShadow.setFillColor(colShadow_in);
}
bool Button::select(Vector2i mouse, Color col_in)
{
	if ((mouse.x > x && mouse.x < x + weight) && (mouse.y > y && mouse.y < y + height)) {
		text.setFillColor(col_in);
		textShadow.setFillColor(Color::Black);
		return true;
	}
	else {
		text.setFillColor(col);
		textShadow.setFillColor(Color::Blue);
		return false;
	}
}
bool Button::onClick(Vector2i mouse, Color col_in )
{
	if (select(mouse, col_in) && Mouse::isButtonPressed(Mouse::Left)) {
		while (select(mouse, col_in) && Mouse::isButtonPressed(Mouse::Left));
		Music music;
		music.openFromFile("resources/music/click.ogg");
		music.setVolume(100);
		music.play();
		Sleep(music.getDuration().asMilliseconds());
		return true;
	}
	else
		return false;
}