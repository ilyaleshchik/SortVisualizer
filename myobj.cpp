#include "myobj.h"
#include <random>
#include <ctime>
using namespace std;
myObj::myObj() {
	nHeight = 0;

	nVal = rand() % 500 + 100;
}

myObj::myObj(int _nHeight, int _nVal) {
	nHeight = _nHeight;
	nVal = _nVal;
}
