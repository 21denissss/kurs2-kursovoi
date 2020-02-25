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
bool isCaps = false;

using namespace sf; 
using namespace std;
namespace Btn {
	int getASCI(Uint32 in_st)
	{
		if (in_st == -1 && isCaps)
			isCaps = false;
		else if (in_st == -1 && !isCaps)
			isCaps = true;
		if (in_st >= 0 && in_st < 25)
			if (!isCaps)
				in_st += 97;
			else
				in_st += 65;
		else
			if (in_st == 59)
				in_st = 8;
			else
				if (in_st > 25 && in_st < 37)
					in_st += 22;
				else
				in_st = -999;
		return in_st;
	}
	Text string2text(string st)
	{
		Text text;
		wstringstream ost;
		wstring q;
		wchar_t Mass[255];
		MultiByteToWideChar(0, 0, st.c_str(), -1, Mass, 255);
		ost << Mass;
		q = ost.str();
		text.setString(q);
		return text;
	}
	string int2string(int number)
	{
		string st;
		char ch;
		int TempOst, TempCel = number, i = 0;
		while (TempCel != 0)
		{
			TempOst = TempCel % 10;
			TempCel /= 10;
			ch = TempOst + '0';
			st = ch + st;
		}
		return st;
	}


	class Rectangle {
	private:
		RectangleShape rect,shadowRect;
		Text text;
		int num;
		Font font;
		Color col;
		int x_win, y_win;
		int x,y,weight,height;
	public:
		Rectangle(int x, int y, int weight, int height);
		int getNumber()
		{
			return num;
		}
		bool select(Vector2i mouse, Color col);
		Vector2i getPosition();
		Vector2i getWinPosition();
		void setPosition(Vector2i mouse);
		void OutHere(RenderWindow& window)
		{
			shadowRect.setPosition(x, y);
			rect.setPosition(x + 2, y + 2);
			if(num < 10)
				text.setPosition(-9 + x + weight / 2, -19 + y + height / 2);
			else
				text.setPosition(-16 + x + weight / 2, -19 + y + height / 2);
			window.draw(shadowRect);
			window.draw(rect);
			window.draw(text);
		}
		bool onClick(Vector2i mouse, Color col_in);
	};


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
		Label(string st, float x_in, float y_in, int size, Color col_in, Color colShadow_in);
		void changePos(float dx, float dy);
		void setPos(int x_in, int y_in);
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


	class Button {
	private:
		Text text, textShadow;
		Font font;
		Color col;
		int x, y, weight, height;
		bool select(Vector2i mouse, Color col_in);
		Text getText()
		{
			return text;
		}
		Text getShadow()
		{
			return textShadow;
		}
	public:
		Button(string st, float x_in, float y_in, int w, int h, Color col_in, Color colShadow_in);
		bool onClick(Vector2i mouse, Color col_in);
		void outHere(RenderWindow& window)
		{
			window.draw(getShadow());
			window.draw(getText());
		}
	};


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
		TextBox(float x_in, float y_in, int w, int h, Color col_in);
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
}










//TextBox
Btn::TextBox::TextBox(float x_in = 0, float y_in = 0, int w = 110, int h = 50, Color col_in = Color::Black) {
	font.loadFromFile("resources/comic.ttf");
	x = x_in;
	y = y_in;
	isReleased = false;
	col = col_in;
	weight = w;
	height = h;
	text.setString("");
	text.setFont(font);
	text.setPosition(x, y);
	text.setCharacterSize(36);
	text.setFillColor(col_in);
	BOX.setSize(Vector2f(w + 4, h + 2));
	BOX.setPosition(x - 2, y - 1);
	BOX.setFillColor(Color::White);
}
int Btn::TextBox::getInt()
{
	string temp = "0", st = text.getString();
	int result = 0;
	bool minus = false;
	if (st[0] == '-') {
		minus = true;
	}
	for (int i = 0; i < st.length(); i++) {
		if (st[i] >= 48 && st[i] <= 57) {
			temp += st[i];
		}
	}
	for (int i = 0; i < temp.length(); i++) {
		result += (temp[i] - 48) * pow(10, temp.length() - i - 1);
	}
	if (minus) result *= -1;
	return result;
}
void Btn::TextBox::editTextString(Event event)
{
	Uint32 in_st = event.text.unicode;
	in_st = getASCI(in_st);

	string st = text.getString();
	if (in_st == -999)
		return;
	if (in_st == 8) {
		if (st.length() != 1) {
			st.erase(st.length() - 2, 2);
			text.setString(st + "|");
		}

	}
	else
		if ((st[st.length() - 1] == '|') && st.length() <= 4) {
			st.erase(st.length() - 1, 1);
			st += in_st;
			text.setString(st + "|");
		}
}
void Btn::TextBox::editTextInt(Event event)
{
	Uint32 in_st = event.text.unicode;
	string st = text.getString();
	in_st = getASCI(in_st);
	cout << int(in_st) << endl;

	if (in_st == -999)
		return;
	if ((in_st >= 48 && in_st <= 57) || in_st == 8 || in_st == 45) {
		if (in_st == 45) {
			if (st.length() != 1) {
				st.erase(st.length() - 1, 1);
				text.setString(st + "-");
				text.setString(st + "|");
			}
		}
		if (in_st == 8) {
			if (st.length() != 1) {
				st.erase(st.length() - 2, 2);
				text.setString(st + "|");
			}

		}
		else
			if ((st[st.length() - 1] == '|') && st.length() <= 4) {
				st.erase(st.length() - 1, 1);
				st += in_st;
				text.setString(st + "|");
			}
	}
}
bool Btn::TextBox::getSelect(Event event, Vector2i mouse)
{
	if (event.type == Event::KeyReleased)
		isReleased = false;
	if (inBox(mouse) && Mouse::isButtonPressed(Mouse::Left)) {
		string st = text.getString();
		if (st[st.length() - 1] != '|') {
			text.setString(st + "|");
			select = true;
		}
	}
	if (!inBox(mouse) && Mouse::isButtonPressed(Mouse::Left))
	{
		string st = text.getString();
		if (st[st.length() - 1] == '|') {
			st.erase(st.length() - 1, 1);
			text.setString(st);
		}
		select = false;
	}
	if (!isReleased && (event.type == Event::KeyPressed)) {
		isReleased = true;
		return select;
	}
	else {
		return false;

	}
}
bool Btn::TextBox::is_empty()
{
	string st = text.getString();
	if (st.length() == 0) {
		return true;
	}
	else {
		if (st[0] != '|')
			return false;
		else
			return true;
	}
}
//Button
Btn::Button::Button(string st = "\0", float x_in = 0, float y_in = 0, int w = 200, int h = 50, Color col_in = Color::White, Color colShadow_in = Color::Blue) {
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
bool Btn::Button::select(Vector2i mouse, Color col_in = Color::Black)
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
bool Btn::Button::onClick(Vector2i mouse, Color col_in = Color::Black)
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
//Label
Btn::Label::Label(string st = "\0", float x_in = 0, float y_in = 0, int size = 36, Color col_in = Color::White, Color colShadow_in = Color::Blue) {
	font.loadFromFile("resources/comic.ttf");
	x = x_in;
	y = y_in;
	col = col_in;
	text = string2text(st);
	text.setFont(font);
	text.setPosition(x, y);
	text.setCharacterSize(size);
	text.setFillColor(col_in);
	textShadow = string2text(st);
	textShadow.setFont(font);
	textShadow.setPosition(x - 2, y - 1);
	textShadow.setCharacterSize(size);
	textShadow.setFillColor(colShadow_in);
}
void Btn::Label::changePos(float dx = 0, float dy = -1)
{
	x += dx;
	y += dy;
	text.setPosition(x, y);
	textShadow.setPosition(x, y);
}
void Btn::Label::setPos(int x_in, int y_in)
{
	x = x_in;
	y = y_in;
	text.setPosition(x, y);
	textShadow.setPosition(x, y);
}
Vector2i Btn::Label::getPos()
{
	Vector2i temp;
	temp.x = x;
	temp.y = y;
	return temp;
}
//Rectangle
Btn::Rectangle::Rectangle(int x = 650, int y = 300, int weight = 75, int height = 75)
{
	extern int number;
	num = number;
	col = Color::Black;
	if (number == 0)
		number = 16;
	x = x + weight * ((number - 1) % 4);
	y = y + height * ((number - 1) / 4);
	x_win = x;
	y_win = y;
	if (number == 16)
		number = 0;
	font.loadFromFile("resources/comic.ttf");
	rect.setSize(sf::Vector2f(weight - 4, height - 4));
	shadowRect.setSize(sf::Vector2f(weight, height));
	shadowRect.setFillColor(col);
	this->weight = weight;
	this->height = height;
	this->x = x;
	this->y = y;
	text = string2text(int2string(number));
	text.setFillColor(col);
	text.setFont(font);
	text.setCharacterSize(36);
	number++;
}
bool Btn::Rectangle::select(Vector2i mouse, Color col)
{
	if ((mouse.x > x && mouse.x < x + weight) && (mouse.y > y && mouse.y < y + height)) {
		text.setFillColor(col);
		return true;
	}
	else {
		text.setFillColor(this->col);
		return false;
	}
}
Vector2i Btn::Rectangle::getPosition()
{
	Vector2i vect;
	vect.x = x;
	vect.y = y;
	return vect;
}
Vector2i Btn::Rectangle::getWinPosition()
{
	Vector2i vect;
	vect.x = x_win;
	vect.y = y_win;
	return vect;
}
void Btn::Rectangle::setPosition(Vector2i mouse)
{
	x = mouse.x;
	y = mouse.y;
}
bool Btn::Rectangle::onClick(Vector2i mouse, Color col_in = Color::Yellow)
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