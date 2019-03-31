// Yanchen Guo
// CS4280
#include<string>
#include<iostream>
#include<fstream>
#include<cstdio>
#include "token.h"
#include "scanner.h"

using namespace std;

// array corresponding to the fsa table.
// final state >= 1000 and <= 0 if error occurs.

struct opDel{
	int name;
	int value;
};

// 2d array based on fsa table
int fsaArray[5][22]={
  //    ws L D = > < : + - * / % . ( ) , { } ; [ ] eof
	{0,1,2,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,-99},
	{1000,1,1,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000},
	{1001,1001,2,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001},
	{1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002},
	{1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003,1003}
};


// an array used for indetifying key words within ID token
token kwLookup[15] ={
	{BEGIN_tk, "Begin", 0},
	{END_tk, "End", 0},
	{LOOP_tk,"Loop",0},
	{VOID_tk,"Void",0},
	{INT_tk,"INT",0},
	{RETURN_tk,"Return",0},
	{READ_tk,"Read",0},
	{OUTPUT_tk,"Output",0},
	{PROGRAM_tk,"Program",0},
	{IFF_tk,"IFF",0},
	{THEN_tk,"Then",0},
	{LET_tk,"Let",0}
};

//operator array used to match character with operator name and return operator value as state
opDel opDelArray[18]={
	{'=',3},
	{'>',3},
	{'<',3},
	{':',3},
	{'+',3},
	{'-',3},
	{'*',3},
	{'/',3},
	{'%',3},
	{'.',4},
	{'(',4},
	{')',4},
	{',',4},
	{'{',4},
	{'}',4},
	{';',4},
	{'[',4},
	{']',4}
};


//scanner driver, takes in a file pointer and the line number;
token scanner(FILE *fp, int &lineNum){
	
	// creating variables for different states
	int lookahead;
	int lookaheadState=0;
	int state=0;
	int nextState=0;
	// string instance to store the value gotten from the file pointer
	string instance;
	token t;

	// loop until final state is reached
	while(state>=0 && state<1000){
		//get the next character
		lookahead = fgetc(fp);
		// if the look ahead spots a back slash, continue until new line
		if(lookahead =='\\'){
			while (lookahead != '\n'){
				lookahead = fgetc(fp);
			}
			lineNum +=1;
			// look ahead to see if double comment.
			lookahead =fgetc(fp);
		}
		
		//for loop to identify if the value is a operator or  a delimiter
		for(int i =0; i < 18; i++){
			if(opDelArray[i].name == lookahead){
				lookaheadState = opDelArray[i].value;
				break;
			}
			// different states for alphabet and diget and EOF
			if (isalpha(lookahead)){
				lookaheadState = 1;
			}else if(isdigit(lookahead)){
				lookaheadState =2;
			}else if(isspace(lookahead)){
				lookaheadState = 0;
			}else if(lookahead == EOF){
				lookaheadState = 21;
			}else{
				lookaheadState =22;
			}
		}	
		// look in the fsaArray to see if has reached a final state, final state is greater or equal than 1000, or-99 for EOF
		nextState = fsaArray[state][lookaheadState];	
		if(nextState >=1000){
			
			// if the final state = 1000, stands for ID token
			if(nextState == 1000){
				// loop the keyword array with the instance stored to check if its a keyword token
				for(int i=0; i < 14; i++){
					if(kwLookup[i].tokenInstance==instance){
						t.tokenID = kwLookup[i].tokenID;
						t.tokenInstance = instance;
						t.lineNum = lineNum;
						if(lookahead == '\n')lineNum+=1;
						ungetc(lookahead,fp);
						return t;
					}

				}
				// if not a keyword token then check wheter if it start with a uppercase letter
				// if it does then its a ID token
				if(isupper(instance[0])){
				t.tokenID = ID_tk;
				t.tokenInstance = instance;
				t.lineNum = lineNum;
				if(lookahead == '\n')lineNum+=1;
				ungetc(lookahead,fp);
				return t;
				}else{
					cout<<"\"The identifier token must start with upper case letter\" \n";
					t.tokenID = ERR_tk;
					t.tokenInstance = instance;
					t.lineNum = lineNum;
					ungetc(lookahead,fp);
					return t;
				}
			// if the final state = 1001, stands for a number token
			}else if(nextState == 1001){
				t.tokenID = NUM_tk;
				t.tokenInstance = instance;
				t.lineNum = lineNum;	
				if(lookahead == '\n')lineNum+=1;
				ungetc(lookahead,fp);
				return t;		
			// if the final state = 1002, stands for a operator token
			}else if (nextState == 1002){
				t.tokenID = OP_tk;
				t.tokenInstance = instance;
				t.lineNum = lineNum;
				if(lookahead == '\n')lineNum+=1;
				ungetc(lookahead,fp);
				return t;
			// if the final state = 1003, stands for a delimiter token
			}else if (nextState == 1003){
				t.tokenID = DEL_tk;
				t.tokenInstance = instance;
				t.lineNum = lineNum;
				if(lookahead == '\n')lineNum+=1;
				ungetc(lookahead,fp);
				return t;
			}
		// if the nextState is -99, then its a EOF token
		}else if (nextState == -99){
				t.tokenID = EOF_tk;
				t.lineNum = lineNum;
				t.tokenInstance ="EOF";
				return t;
		// if the final state is not reached, then keep on looping and add the character gotten to the instance
		}else{
			char value = static_cast <char> (lookahead);	
			if(!isspace(value)){
				instance+= value;
			}
			state = nextState;	
		}
				
	}
}
