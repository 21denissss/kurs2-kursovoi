#include "TextBox.h"


TextBox::TextBox(float x_in, float y_in, int w, int h, Color col_in) {
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
int TextBox::getInt()
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
void TextBox::editTextString(Event event)
{
	Uint32 in_st = event.text.unicode;
	in_st = Converting().getASCI(in_st, isCaps);

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
void TextBox::editTextInt(Event event)
{
	Uint32 in_st = event.text.unicode;
	string st = text.getString();
	in_st = Converting().getASCI(in_st, isCaps);
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
bool TextBox::getSelect(Event event, Vector2i mouse)
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
bool TextBox::is_empty()
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