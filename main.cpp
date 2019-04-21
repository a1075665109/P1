// Yanchen Guo
// cs4280 p1
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <unistd.h>

#include "node.h"
#include "token.h"
#include "scanner.h"
#include "testScanner.h"
using namespace std;
int main(int argc, char*argv[]){
	string filename;
	FILE *fp;
	//if there is no redirect
	if(isatty(STDIN_FILENO)){
		//if no argument provided
		if(argc==1){	
			string tempInput;
			ofstream wfile;
			filename = "input.txt";
			wfile.open(filename.c_str());
			while (cin>>tempInput){
				wfile <<tempInput<<"\n";
			}
			wfile.close();	
			fp = fopen(filename.c_str(),"r");	
		//if an argument file is provided, check for empty and non-exist file 	
		}else if(argc==2){
			// customize file extension
			string ogfn = argv[1];
			filename = ogfn +".input1";
			ifstream rfile;
			rfile.open(filename.c_str());
			// Check file validity and report errors msg.
			if(rfile && !(rfile.peek()==std::ifstream::traits_type::eof())){
				rfile.close();
			}else if(!rfile){
				cout <<"Error! The file does not exist\n";
				return 0;
			}else{
				cout <<"Error! The file is empty \n";
				return 0;
			}
			fp=fopen(filename.c_str(),"r");
		}
	// files redirected
	}else{
		// write file to another temp file then set the file pointer to temp file.
		string input; 
	ofstream write;
		write.open("input.txt");
		while(getline(cin,input)){
			write<<input<<"\n";
		}
		write.close();
		filename="input.txt";
		fp=fopen(filename.c_str(),"r");
	}
	cout << "\n";
	// call testScanner with the appropriate file pointer	
	node *root = parser(fp);
	printTree(root,0);
	fclose(fp);
	return 0;
}

