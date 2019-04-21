// Yanchen Guo
// CS4280 P1
#ifndef TESTSCANNER_H
#define TESTSCANNER_H

#include<string>
#include<iostream>
#include"scanner.h"
#include "token.h"
#include "node.h"
#include<fstream>
using namespace std;

node *block();
node *var();
void printTree(node *p,int level);
node *parser(FILE *fp);
node *expr();
node *stat();
node *mstat();
#endif
