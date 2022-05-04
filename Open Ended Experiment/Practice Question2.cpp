// To token categorisation
// Assumption - The language does not support strings
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <process.h>
using namespace std;
void categorize(string token, int &key, int &relop, int &arithop, int &obj, int &iden){
    // Keywords
    string keywords[32] = {"auto","break","case","char","const","continue","default","do",
                        "double","else","enum","extern","for","float","goto","if",
                        "int","long","register","return","short","signed","sizeof","static",
                        "struct","switch","typedef","union","unsigned","void","volatile","while"};
    // predefined identifier
    string objects[7] = {"cout","cin","endl","main","using","namespace","std"}; 
    // relational operators
    string relOps[6] = {">","<",">=","<=","==","!="};
    // arithmatic operators
    string arithOps[6] = {"+","-","*","/","%","="};
    for(int i=0;i<32;i++){
        if(token.compare(keywords[i])==0){
            cout<<token<<" is a keyword."<<endl;
            key++;
            return;
        }
    }
    for(int i=0;i<7;i++){
        if(token.compare(objects[i])==0){
            cout<<token<<" is a predefined identifier."<<endl;
            obj++;
            return;
        }
    }
    for(int i=0;i<6;i++){
        if(token.compare(relOps[i])==0){
            cout<<token<<" is a relational operator."<<endl;
            relop++;
            return;
        }
    }
    for(int i=0;i<6;i++){
        if(token.compare(arithOps[i])==0){
            cout<<token<<" is an arithmatic operator."<<endl;
            arithop++;
            return;
        }
    }
    if(token[0]=='_'||(token[0]>='A' && token[0]<='Z') || (token[0]>='a' && token[0]<='z')){
        cout<<token<<" is an identifier."<<endl;
        iden++;
        return;
    }
}
int main(){
    ifstream fin;
    ofstream fout;
    string text, remove;
    int tokens = 0, keywords = 0, identifiers = 0, relop = 0, arithop = 0, objects = 0;
    // Resultant File
    fout.open("tokens.txt",ios::trunc|ios::out);
    if(!fout){
        cout<<"The file could not be created."<<endl;
        exit(0);
    }
    // Input File
    fin.open("code.txt",ios::in);
    while(!fin.eof()){
        fin>>text;
        // removal of preprocessor directives
        if(text[0]=='#'){
            getline(fin,remove);
            continue;
        }
        // removal of comments
        if((text[0]=='/' && text[1]=='*') || regex_match(text,regex("(//)(.*)"))){
            if(text[1]=='*'){
                getline(fin,remove,'/');
            }
            else{
                getline(fin,remove);
            }
            continue;
        }
        // removal of extra blank spaces
        if(text==""){
            continue;
        }
        fout<<text<<" ";
        // token counting
        tokens++;
        // categorization of tokens
        categorize(text,keywords,relop,arithop,objects,identifiers);
        text="";
    }
    fin.close();
    fout.close();
    //cout<<"No of tokens present in the file are: "<<tokens<<endl;
    cout<<"No of keywords present in the file are: "<<keywords<<endl;
    cout<<"No of identifiers present in the file are: "<<identifiers<<endl;
    cout<<"No of predefined identifiers present in the file are: "<<objects<<endl;
    cout<<"No of relational operators present in the file are: "<<relop<<endl;
    cout<<"No of arithmatic operators present in the file are: "<<arithop<<endl;
}
