// Yanchen Guo
// CS4280 P1
#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;
// enumeration for different tokens, will be used as indexes for the tokenName array under testScanner.cpp
enum tokenType{ID_tk,NUM_tk,OP_tk, DEL_tk,INT_tk, BEGIN_tk, END_tk, LOOP_tk, VOID_tk, RETURN_tk, READ_tk, OUTPUT_tk, PROGRAM_tk, IFF_tk, THEN_tk, LET_tk,EOF_tk,ERR_tk};

// token struct that stores the tokenID, the tokenInstance, and the lineNum
struct token{
	tokenType tokenID;
	string tokenInstance;
	int lineNum;
};


#endif
