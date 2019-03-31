// Yanchen Guo
// CS4280 P1
#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
using namespace std;

token scanner(FILE *fp, int &lineNum);

#endif
