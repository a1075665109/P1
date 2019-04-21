// Yanchen Guo
// CS4280 P1

#include<string>
#include<iostream>
#include <stdlib.h>
#include "testScanner.h"

string tokenName[]={"Identifier token","Number token","Operator token","Delimiter token","INT token","Begin token", "End token", "Loop token","Void token", "Return token", "Read token", "Output token", "Program token", "IFF token", "Then token", "Let token", "EOF token", "Error token"};

FILE *fp;
token tk;
int lineNum =0;
int level =0;

node *getNode(string name){
	node *nodeptr = new node;
	nodeptr->label = name;
	return nodeptr;
}
node *RO(){
	node *p = getNode("<RO>");
	if(tk.tokenInstance =="<"){
		p->child1 = getNode("<");
		tk = scanner(fp, lineNum);
		return p;
	}if(tk.tokenInstance == ">"){
                p->child1 = getNode(">");
                tk = scanner(fp, lineNum);
                return p;
        }if(tk.tokenInstance == "="){
		tk = scanner(fp, lineNum);
		if(tk.tokenInstance == "<"){
			p->child1 = getNode("=<");
			tk = scanner(fp,lineNum);
			return p;
		}else if(tk.tokenInstance == ">"){
			p->child1 = getNode(">=");
			tk = scanner(fp,lineNum);
			return p;
		}else{
			return p;
		}
        }else{
		cout << "Error, expecting \"< > =\" token\n";
		exit (0);
	}
}
node *vars(){
	cout <<"vars\n";
	node *p = getNode("<vars>");
	if(tk.tokenID == BEGIN_tk){
		return p;
	}else if(tk.tokenID == INT_tk){
		p->child1 = getNode("INT");
		p->child1->token_t = tk;
		tk = scanner(fp,lineNum);
		if(tk.tokenID == ID_tk){
			p->child2 = getNode("Identifier");
			p->child2->token_t = tk;
			tk = scanner(fp,lineNum);
			if(tk.tokenID == NUM_tk){
				p->child3 = getNode("Integer");
				p->child3->token_t = tk;
				tk = scanner(fp,lineNum);
				p->child4 = vars();
				tk = scanner(fp,lineNum);
				return p;
			}else{
				cout<<"Error, expecting integer after declaring INT id\n";
				exit(0);
			}
		}else{
			cout <<"Error, expecting ID token\n";
			exit(0);
		}
	}else{
		cout << "Erorr, expecting INT token or Begin token to prove vars to be empty\n";
		exit(0);
	}
}

node *in(){
	node *p = getNode("<in>");
	if(tk.tokenID == READ_tk){
		tk = scanner(fp,lineNum);
		if(tk.tokenInstance == "["){
			tk = scanner(fp,lineNum);
			if(tk.tokenID == ID_tk){
				p->child1 = getNode("<id>");
				p->child1->token_t = tk;
				tk = scanner(fp, lineNum);
				if(tk.tokenInstance == "]"){
					tk=scanner(fp,lineNum);
					return p;
				}else{
					cout << "Error, expecting \"]\" token\n";
					exit(0);
				}
			}else {
				cout << "Error, expecting id token \n";
				exit(0);
			}
		}else{
			cout << "Eroor, expecting \"[\" token\n";
			exit(0);
		}
	}else{
		cout << "Error, expecting READ token \n";
		exit(0);
	}
	return p;
}

node*R(){
	node *p = getNode("<R>");
	if(tk.tokenInstance == "["){
		tk=scanner(fp,lineNum);
		p->child1 = expr();
		if(tk.tokenInstance == "]"){
			tk = scanner(fp,lineNum);
			return p;
		}
	}else if (tk.tokenID = ID_tk){
		p->child1 = getNode("Identifier");
		p->child1->token_t = tk;
		tk = scanner(fp,lineNum);
		return p;
	}else if (tk.tokenID = NUM_tk){
		p->child1 = getNode("Number");
		p->child1->token_t = tk;
		tk = scanner(fp, lineNum);
		return p;
	}else{
		cout<<"Error, expecting \"[, ID, NUM token\"\n";
		exit (0);
	}	
}

node *M(){
	node *p = getNode("<M>");
	if(tk.tokenInstance == "-"){
		p->child1 = getNode("-");
		tk = scanner(fp,lineNum);
		p->child2 = M();
		return p;
	}else if(tk.tokenInstance == "[" || tk.tokenID == ID_tk || tk.tokenID == NUM_tk){
		p->child1 = R();
		return p;
	}else{
		cout << "Error, expecting \"-, ID, NUM token\"\n";
		exit(0);
	}
}

node *N(){
	node *p = getNode("<N>");
	p->child1 = M();
	if(tk.tokenInstance == "/"){
		p->child2 = getNode("/");
		tk = scanner(fp,lineNum);
		p->child3 = N();
		return p;
	}else{
		return p;
	}
}

node *A(){
	node *p = getNode("<A>");
	p->child1 = N();
	if(tk.tokenInstance == "*"){
		p->child2 = getNode("*");
		tk = scanner(fp,lineNum);
		p->child3 = N();
	}else{
		return p;	
	}
}

node *expr(){
	node *p = getNode("<expr>");
	p->child1 = A();
	if(tk.tokenInstance == "+"){
		p->child2 = getNode ("+");
		tk = scanner(fp,lineNum);
		p->child3 = expr();
		return p;
	}else if(tk.tokenInstance =="-"){
		p->child2 = getNode("-");
		tk = scanner(fp,lineNum);
		p->child3 = expr();
		return p;
	}else if(tk.tokenInstance =="]" || 
		 tk.tokenInstance == "<" ||
		tk.tokenInstance == ">" ||
		tk.tokenInstance == "=" ||
		tk.tokenInstance == ":"){
		return p;
	}else{
		"Error, expecting token \"+ - ] < > = :\"\n";
		exit(0);
	}
}

node *out(){
	node *p = getNode("<out>");
	if(tk.tokenID == OUTPUT_tk){
		tk = scanner(fp,lineNum);
		if(tk.tokenInstance == "["){
			tk = scanner(fp,lineNum);
			p->child1 = expr();
			if(tk.tokenInstance == "]"){
				tk = scanner(fp,lineNum);
				return p;
			}else{
				cout << "Error, expecting \"]\" token\n";
				exit(0);
			}
		}else{
			cout << "Error, expecting \"[\" token\n";
			exit(0);
		}
	}else{
		cout << "Error, expecting OUTPUT token \n";
		exit (0);
	}
	return p;
}

node *iff(){
	node *p = getNode("IFF");
	tk = scanner(fp,lineNum);
	if(tk.tokenInstance == "["){
		tk = scanner(fp,lineNum);
		p->child1 = expr();
		p->child2 = RO();
		p->child3 = expr();
		if(tk.tokenInstance == "]"){
			tk = scanner(fp,lineNum);
			p->child4=stat();
			return p;
		}else{
			cout <<"Error, expecting \"]\" token\n";
			exit (0);
		}
	}else{
		cout <<"Error, expecting \"[\" token\n";
		exit(0);
	}
}

node *loop(){
	node *p = getNode("<loop>");
	tk = scanner(fp,lineNum);
	if(tk.tokenInstance == "["){
                tk = scanner(fp,lineNum);
                p->child1 = expr();
                p->child2 = RO();
                p->child3 = expr();
                if(tk.tokenInstance == "]"){
                        tk = scanner(fp,lineNum);
                        p->child4=stat();
                        return p;
                }else{
                        cout <<"Error, expecting \"]\" token\n";
                        exit (0);
                }
        }else{
                cout <<"Error, expecting \"[\" token\n";
                exit(0);
        }

}

node *assign(){
	node*p = getNode("<assign>");
	p->child1 = getNode("<id>");
	p->child1->token_t = tk;
	tk=scanner(fp,lineNum);
	if(tk.tokenInstance == "="){
		p->child2 = getNode("=");
		tk = scanner(fp,lineNum);
		p->child3 = expr();
		return p;
	}else{
		cout<<"Error, expecting \"=\" token\n";
		exit(0);
	}
	
}

node *stat(){
	node *p = getNode("<stat>");
	if(tk.tokenID == READ_tk){
		p->child1=in();
		return p;
	}else if(tk.tokenID == OUTPUT_tk){
		p->child1=out();
		return p;
	}else if(tk.tokenID == BEGIN_tk){
		p->child1=block();
		return p;
	}else if(tk.tokenID == IFF_tk){
		p->child1=iff();
		return p;
	}else if (tk.tokenID == LOOP_tk){
		p->child1=loop();
		return p;
	}else if (tk.tokenID == ID_tk){
		p->child1 = assign();
		return p;
	}else{
		cout << "Error, no matching tokens found (read, output, begin, iff, loop, id tokens)\n";
		exit(0);
	}
}

node *mStat(){
	node *p = getNode("<mStat>");
	if (tk.tokenID == END_tk){
		return p;
	}else{
		p->child1 = stat();
		if(tk.tokenInstance == ":"){
			tk = scanner(fp,lineNum);
			p->child2 = mStat();
			return p;
		}	
	}
}
node *stats(){
	node *p = getNode("<stats>");
	p->child1 = stat();
	if(tk.tokenInstance == ":"){
		tk = scanner(fp, lineNum);
		p->child2 = mStat();
	}else{
		cout << "Error, expecting : token\n";
		exit(0);
	}
}

node *block(){
	cout <<"block\n";
	node *p=getNode("<block>");
	if(tk.tokenID == BEGIN_tk){
		tk = scanner(fp,lineNum);
		p->child1=vars();
		p->child2 = stats();
		if(tk.tokenID == END_tk){
			tk = scanner(fp,lineNum);
			return p;
		}else{
			cout <<"Error, expecting END token\n";
			exit(0);
		}
	}else{
		cout<<"Error, expecting BEGIN token\n";
		exit(0);
	}
}

node *program(){
        node *p = getNode("<program>");
        tk = scanner (fp,lineNum);
        cout << "program\n";
	p->child2 = vars();
        p->child3 = block();
                return p;
}


node *parser(FILE *fp){
	node *tree;
	tk = scanner(fp, lineNum);
	tree = program();
	cout << "Parse success\n";
	return tree;

}

void printTree(node *root,int level){
	if(root == NULL){
		return;
	}else{
		for (int i=0; i<level; i++){
			cout <<"  ";
		}
		cout << root->label << "\t";
		token t = root->token_t;
		cout << tokenName[t.tokenID] << ": "<< t.tokenInstance << "\n";
		printTree(root->child1, level+1);
		printTree(root->child2, level+1);
		printTree(root->child3, level+1); 
		printTree(root->child3, level+1);
		printTree(root->child3, level+1);
	}
}
/*void testScanner(FILE *fp){
	//string a = "hello";
	//cout << a[0];
	int lookahead;
	int lineNum =1;
	while((lookahead = fgetc(fp))!= EOF){
		ungetc(lookahead,fp);
		token t = scanner(fp,lineNum);
		if(t.tokenID != ERR_tk) {
            		cout << "Line Num: "<< t.lineNum << "  Token ID: " << tokenName[t.tokenID] << ",  Token Instance: \"" << t.tokenInstance << "\"\n\n";	
		} else {
            		cout << "Line Num: " << t.lineNum << ",  Token ID: " << tokenName[t.tokenID] << ",  Token Instance: \"" << t.tokenInstance << "\"\n\n";	
		}
	
    	}
	//cout << "hello";
	fclose(fp);
	return 0;
}*/
