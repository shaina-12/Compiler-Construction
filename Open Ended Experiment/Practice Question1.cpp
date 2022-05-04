//  Removal of comments, extra blank spaces and Token counting
#include <iostream>
#include <fstream>
#include <regex>
#include <process.h>
using namespace std;
int main(){
    ifstream fin;
    ofstream fout;
    string text, remove;
    int tokens = 0, count = 0;
    bool flag = false;
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
        int n = text.size()-1;
        if((text[0]=='\"' || text[0]=='\'')||(text[n]=='\"' || text[n]=='\'')){
            if(flag==false){
                flag=true;
            }
            else{
                flag=false;
            }
        }
        if(flag==true){
            count++;
        }
        //cout<<tokens<<" "<<text<<endl;
        text="";
    }
    fin.close();
    fout.close();
    cout<<"No of tokens present in the file are: "<<tokens-count<<endl;
}
