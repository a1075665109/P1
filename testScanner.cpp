// Yanchen Guo
// CS4280 P1

#include<string>
#include<iostream>
#include "testScanner.h"

string tokenName[]={"Identifier token","Number token","Operator token","Delimiter token","INT token","Begin token", "End token", "Loop token","Void token", "Return token", "Read token", "Output token", "Program token", "IFF token", "Then token", "Let token", "EOF token", "Error token"};

void testScanner(FILE *fp){
	//string a = "hello";
	//cout << a[0];
	int lookahead;
	int lineNum =1;
	while((lookahead = fgetc(fp))!= EOF){
		ungetc(lookahead,fp);
		token t = scanner(fp,lineNum);
		if(t.tokenID != ERR_tk) {
            		cout << "Line Num: " << t.lineNum << "  Token ID: " << tokenName[t.tokenID] << ",  Token Instance: \"" << t.tokenInstance << "\"\n\n";	
		} else {
            		cout << "Line Num: " << t.lineNum << ",  Token ID: " << tokenName[t.tokenID] << ",  Token Instance: \"" << t.tokenInstance << "\"\n\n";	
		}
	
    	}
	//cout << "hello";
	fclose(fp);
	return;
}
