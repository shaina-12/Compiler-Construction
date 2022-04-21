#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <fstream>
#include <regex>
using namespace std;
int itr = 0;
void infixToPostfix(vector<string> inExp,vector<string> &postExp){
    stack <string> s;
    for(int i=0;i<inExp.size();i++){
        if(inExp[i].compare("(")==0){
            s.push(inExp[i]);
        }
        else if(inExp[i].compare(")")==0){
            while(!s.empty() && s.top().compare("(")!=0){
                postExp.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else if(inExp[i].compare("^")==0){
            if(s.empty()){
                s.push(inExp[i]);
            }
            else 
            {
                string a = s.top();
                if(a.compare("^")==0){
                    postExp.push_back(a);
                    s.pop();
                    while(!s.empty()){
                        string b = s.top();
                        if(b.compare("^")==0||b.compare("*")==0||b.compare("/")==0){
                            postExp.push_back(b);
                            s.pop();
                        }
                        else{
                            break;
                        }
                    }
                s.push(inExp[i]);
                }
                else{
                    s.push(inExp[i]);
                }
            }   
        }
        else if(inExp[i].compare("*")==0){
            if(s.empty()){                    
                s.push(inExp[i]);
            }
            else{
                string a = s.top();
                if(a.compare("^")==0||a .compare("*")==0||a.compare("/")==0){
                while(!s.empty()){
                    string b = s.top();                    
                    if (b.compare("^")==0||b.compare("*")==0||b.compare("/")==0){
                        postExp.push_back(b);
                        s.pop();
                    }
                    else{
                        break;
                    }
                }
                s.push(inExp[i]);
                }     
                else{
                    s.push(inExp[i]);
                }
            }
        }
        else if(inExp[i].compare("/")==0){
            if(s.empty()){
                s.push(inExp[i]);
            }
            else{
                string a = s.top();
                if(a.compare("^")==0||a.compare("*")==0||a.compare("/")==0){
                while(!s.empty()){
                    string b = s.top();
                    if(b.compare("^")==0||b.compare("*")==0||b.compare("/")==0){
                        string b = s.top();
                        postExp.push_back(b);
                        s.pop();
                    }
                    else{
                        break;
                    }
                }
                 s.push(inExp[i]);
                }
                else{
                     s.push(inExp[i]);
                }
            }
        }
        else if(inExp[i].compare("+")==0){
            if(s.empty()){
                s.push(inExp[i]);
            }
            else{
                string a = s.top();
                if(a.compare("^")==0||a.compare("*")==0||a.compare("/")==0||a.compare("+")==0||a.compare("-")==0){
                while(!s.empty()){
                    string b = s.top();
                    if(b.compare("^")==0||b.compare("*")==0||b.compare("/")==0||b.compare("+")==0||b.compare("-")==0){
                        string b = s.top();
                        postExp.push_back(b);
                        s.pop();
                    }
                    else{
                        break;
                    }
                }
                 s.push(inExp[i]);
                }
                else{
                    s.push(inExp[i]);
                }
            }
        }
        else if(inExp[i].compare("-")==0){
            if(s.empty()){
                s.push(inExp[i]);
            }
            else{
                string a = s.top();
                if(a.compare("^")==0||a.compare("*")==0||a.compare("/")==0||a.compare("+")==0||a.compare("-")==0){
                while(!s.empty()){
                    string b = s.top();
                    if(b.compare("^")==0||b.compare("*")==0||b.compare("/")==0||b.compare("+")==0||b.compare("-")==0){
                        string b = s.top();
                        postExp.push_back(b);
                        s.pop();
                    }
                    else{
                        break;
                    }
                }
                 s.push(inExp[i]);
                }
                else{
                    s.push(inExp[i]);
                }
            }
        }
        else{
            postExp.push_back(inExp[i]);
        }
    }
    while(!s.empty()){
        postExp.push_back(s.top());
        s.pop();
    }
}
void TACGenerate(vector <string> output, vector <string> &code)
{
    //vector <string> v;
    regex r("[0-9]+");
    stack <string> s;
    //int len=strlen(output);
    //puts(output);
    for(int i=0;i<output.size();i++)
    {
        if(regex_match(output[i],r) || output[i].at(0) == '_' || (output[i].at(0)>='A' && output[i].at(0) <='Z') || (output[i].at(0)>='a' && output[i].at(0)<='z'))
        {
            s.push(output[i]);
        }
        else
        {
            string a= s.top();
            //printf("%d ",a);
            s.pop();
            string b= s.top();
            //printf("%d ",b);
            s.pop();
            string c;
            if(output[i].compare("+")==0)
            {
                code.push_back("temp" + to_string(itr) + " = " + b + " + " + a);
            }
            else 
            {
                code.push_back("temp" + to_string(itr) + " = " + b + " * " + a);
            }
            s.push("temp"+to_string(itr));
            itr++;
        }
    }
    string a = s.top();
    s.pop();
    code.push_back("final = "+a);
}
int main(){
    vector <string> inExp = {"a","*","b","+","c"};
    vector <string> postExp;
    vector <string> code;
    infixToPostfix(inExp,postExp);
    for(int i=0;i<postExp.size();i++){
        cout<<postExp[i]<<" ";
    }
    cout<<endl;
    TACGenerate(postExp,code);
    for(int i=0;i<code.size();i++){
        cout<<code[i]<<endl;;
    }
    cout<<endl;
}
