#ifndef CONVERTING
#define CONVERTING
#include "../Logic/Header.h"
using namespace sf;
using namespace std;
class Converting {
public:
	int getASCI(Uint32 in_st, bool isCaps);
	Text string2text(string st);
	string int2string(int number);
};
#endif