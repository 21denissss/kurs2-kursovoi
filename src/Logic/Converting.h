#ifndef CONVERTING
#define CONVERTING
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
using namespace sf;
using namespace std;
class Converting {
public:
	int getASCI(Uint32 in_st, bool isCaps);
	Text string2text(string st);
	string int2string(int number);
};
#endif