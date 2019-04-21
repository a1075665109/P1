#ifndef NODE_H
#define NODE_H

#include <string>
#include "scanner.h"
#include "token.h"

using namespace std;

struct node{
	string label;
	node *child1, *child2, *child3, *child4, *child5;
	token token_t;

};

#endif
