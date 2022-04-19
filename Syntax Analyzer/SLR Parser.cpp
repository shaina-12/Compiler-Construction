#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <stack>
//#include <typeinfo>
using namespace std;
vector<vector<string>> Action = {{"S3","S4","@","@","@","@","@","@","S8","S7","@"},
    {"@","@","@","@","@","@","S9","@","@","@","@"},
     {"@","@","@","@","@","@","@","S10","@","@","@"},
    {"@","@","R4","R4","@","R4","R4","R4","@","@","@"},
    {"@","@","R5","R5","@","R5","R5","@","@","@","@"},
    {"@","@","@","@","@","@","R2","@","@","@","@"},
    {"@","@","@","@","@","@","R3","@","@","@","@"},
    {"@","@","@","@","S11","@","@","@","@","@","@"},
    {"@","@","@","@","S12","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@","@","Accept"},
    {"S3","S4","@","@","S16","@","@","@","@","@","@"},
    {"S3","@","@","@","@","@","@","@","@","@","@"},
    {"S3","S4","@","@","@","@","@","@","@","@","@"},
    {"@","@","S21","@","@","@","R1","@","@","@","@"},
    {"@","@","R7","S22","@","R7","R7","@","@","@","@"},
    {"@","@","R9","R9","@","R9","R9","@","@","@","@"},
    {"S3","S4","@","@","S16","@","@","@","@","@","@"},
    {"@","@","R11","R11","@","R11","R11","@","@","@","@"},                  
    {"@","@","@","@","@","S24","@","@","@","@","@"},
    {"@","@","@","@","@","S25","@","@","@","@","@"},
    {"@","@","@","@","@","S26","@","@","@","@","@"},
    {"S3","S4","@","@","S16","@","@","@","@","@","@"},
    {"S3","S4","@","@","S16","@","@","@","@","@","@"},
    {"@","@","S21","@","@","S29","@","@","@","@","@"},
    {"@","@","@","@","@","@","R12","@","@","@","@"},
    {"@","@","@","@","@","@","R13","@","@","@","@"},
    {"@","@","@","@","@","@","R14","@","@","@","@"},
    {"@","@","R6","S22","@","R6","R6","@","@","@","@"},
    {"@","@","R8","R8","@","R8","R8","@","@","@","@"},
    {"@","@","R10","R10","@","R10","R10","@","@","@","@"},
    {"@","@","R15","R15","@","R15","R15","@","@","@","@"}};
vector<vector<string>> Goto = {{"@","1","2","@","@","@","@","5","6"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","17","30","13","14","15","@","@"},
    {"@","@","18","@","@","@","@","@","@"},
    {"@","@","19","20","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","17","30","23","14","15","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","17","30","@","27","15","@","@"},
    {"@","@","17","30","@","@","28","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"},
    {"@","@","@","@","@","@","@","@","@"}};
vector <string> term = {"id","num","+","*","(",")",";","=","print","read","$"};
vector <string> nonterm = {"S","A","V","C","E","T","F","R","O"};
vector <vector<string>> prod = {{"S","->","A",";"},
                                {"A","->","V","=","E"},
                                {"A","->","R"},
                                {"A","->","O"},
                                {"V","->","id"},
                                {"C","->","num"},
                                {"E","->","E","+","T"},
                                {"E","->","T"},
                                {"T","->","T","*","F"},
                                {"T","->","F"},
                                {"F","->","(","E",")"},
                                {"F","->","V"},
                                {"R","->","read","(","V",")"},
                                {"O","->","print","(","V",")"},
                                {"O","->","print","(","C",")"},
                                {"F","->","C"}};
int main(){
    ofstream fout;
    ifstream fin;
    string text,remove;
    vector <string> input;
    int tokens=0;
    fout.open("result.txt", ios::trunc | ios::out );
    if(!fout) cout<<"File creation failed";
    fin.open("code.txt", ios::in);
    while(!fin.eof()){
        fin>>text;
        if((text[0]=='/' && text[1]=='*') || regex_match(text,regex("(//)(.*)"))){
            if(text[1]=='*') getline(fin,remove,'/');
            else getline(fin,remove);
//            cout<<"removed : "<<remove<<endl;
            continue;
        }
        if(text=="") continue;         //empty lines
//        cout<<text<<endl;
        fout<<text<<" ";
        //category(text, keywords, relOp, identifiers);
        tokens++;
        input.push_back(text);
        //fout<<text<<" ";
        //category(text, keywords, relOp, identifiers);
        //tokens++;
        text="";
    }
    fin.close();
//    fout<<endl<<"Tokens: "<<tokens;
    fout.close();
//    cout<<endl<<"Number of tokens in the file : "<<tokens<<endl;
//    cout<<endl<<"Keywords: "<<keywords<<endl;
//    cout<<"Relational Operators: "<<relOp<<endl;
//    cout<<"Identifiers: "<<identifiers<<endl<<endl;
    input.push_back("$");
    vector<string> stack;
    stack.push_back("0");
    int itr = 0;
    /*
    for(int i=0;i<input.size();i++){
        cout<<input[i]<<" ";
    }*/
    while(1){
        int state = stoi(stack[stack.size()-1]);
        string a = input[itr];
        //cout<<itr<<" "<<input[itr]<<" ";
        int sym = find(term.begin(),term.end(),a) - term.begin();
        //cout<<state<<" "<<sym<<" "<<a<<" "<<Action[state][sym]<<endl;
        /*
        if(itr==4){
            break;
        }*/
        if(Action[state][sym].at(0) == 'S'){
            stack.push_back(a);
            stack.push_back(Action[state][sym].substr(1));
            itr++;
            /*
            if(itr==5){
                break;
            }*/
        }
        else if(Action[state][sym].at(0) == 'R'){
            stack.pop_back();
            int pro = stoi(Action[state][sym].substr(1));
            //cout<<pro<<endl;
            string lhs = prod[pro].at(0);
            //string rhs = prod[pro].substr(3);
            /*
            for(int i=0;i<=rhs.length()-1;i++){
                //cout<<rhs;
                stack.pop_back();
            }*/
            int i=0;
            int n = prod[pro].size()-2;
            //cout<<n<<endl;
            if(n==1){
                stack.pop_back();
            }
            else{
                while(i<((2*n)-1)){
                    stack.pop_back();
                    i++;
                }
            }
            /*
            if(itr==4){
                break;
            }*/
            //for(int i=0;i<rhs.length()-1)
            //cout<<lhs<<" "<<rhs<<endl;
            //cout<<lhs;
            stack.push_back(lhs);
            //cout<<typeid().name()<<endl;
            string b = stack.at(stack.size()-2);
            //cout<<b<<endl;
            //cout<<lhs;
            int s = stoi(b);
            int sy = find(nonterm.begin(),nonterm.end(),lhs) - nonterm.begin();
            stack.push_back(Goto[s][sy]);
            //cout<<stack.at(stack.size()-1);
            //break;
        }
        else if(Action[state][sym].compare("Accept")==0){
            cout<<"The string has been parsed successfully."<<endl;
            break;
        }
        else{
            cout<<"Error!!!"<<endl;
            cout<<"The string could not be parsed successfully,"<<endl;
            break;
        }
    }
}
