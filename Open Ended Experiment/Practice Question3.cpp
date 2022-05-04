//  Infix to postfix 
//a+b*(c^d-e)^(f+g*h)-i
#include <iostream>
#include <stack>
#include <string>
using namespace std;
bool checkPths(string pths){
    stack<char> s;
    //bool b = true;
    if(pths[0]==']' || pths[0]==')' || pths[0]=='}'){
        return false;
    }
    else{
        for(int i=0;i<pths.size();i++){
            if(pths[i]=='[' || pths[i]=='(' || pths[i]=='{'){
                s.push(pths[i]);
            }
            else if(pths[i]==']'){
                if(s.top()=='['){
                    s.pop();
                }
                else{
                    return false;
                }
            }
            else if(pths[i]=='}'){
                if(s.top()=='{'){
                    s.pop();
                }
                else{
                    return false;
                }
            }
            else if(pths[i]==')'){
                if(s.top()=='('){
                    s.pop();
                }
                else{
                    return false;
                }
            }
            else{
                continue;
            }
        }
        if(s.size()==0){
            return true;
        }
        else{
            return false;
        }
    }
}
bool checkOps(string expr){
    bool b = true;
    for(int i=0;i<expr.length()-2;i+=2){
        if(((expr[i]>='a' && expr[i]<='z')||(expr[i]>='A' && expr[i]<='Z')||
            (expr[i]>='0' && expr[i]<='9')) && 
            (expr[i+1]=='+'||expr[i+1]=='-'||expr[i+1]=='*'||expr[i+1]=='/'||expr[i+1]=='^') &&
            ((expr[i+2]>='a' && expr[i+2]<='z')||
            (expr[i+2]>='A' && expr[i+2]<='Z')||(expr[i+2]>='0' && expr[i+2]<='9'))){
                b = true;
        }
        else{
            b=false;
            break;
        }
    }
    return b;
}
bool checkExpr(string inExp){
    string pths="", expr="";
    for(int i=0;i<inExp.size();i++){
        if(inExp[i]=='(' || inExp[i]==')' || inExp[i]=='[' ||
            inExp[i]==']' || inExp[i]=='}'|| inExp[i]=='{'){
            pths += inExp[i];
        }
        else{
            expr += inExp[i];
        }
    }
    // Checking of Parenthesis and Expression Ordering
    if(checkPths(pths) && checkOps(expr)){
        return true;
    }
    else{
        return false;
    }
}
int prec(char c){
    if(c=='^'){
        return 3;
    }
    else if(c=='*'||c=='/'){
        return 2;
    }
    else if(c=='+'||c=='-'){
        return 1;
    }
    else{
        return -1;
    }
}
string infixToPostfix(string inExp){
    stack <char> s;
    string expr="";
    for(int i=0;i<inExp.length();i++){
        char c = inExp[i];
        //Operands
        if((c>='a' && c<='z')||(c>='A' && c<='Z')||(c>='0' && c<='9')){
            expr+=c;
        }
        //Parenthesis
        else if(c=='('||c=='['||c=='{'){
            s.push(c);
        }
        else if(c==')'){
            while(!s.empty() && s.top()!='('){
                expr+=s.top();
                s.pop();
            }
            s.pop();
        }
        else if(c==']'){
            while(!s.empty() && s.top()!='['){
                expr+=s.top();
                s.pop();
            }
            s.pop();
        }
        else if(c=='}'){
            while(!s.empty() && s.top()!='{'){
                expr+=s.top();
                s.pop();
            }
            s.pop();
        }
        //Operators
        else{
            while(!s.empty() && prec(inExp[i])<=prec(s.top())){
                if(c=='^' && s.top()=='^'){
                    break;
                }
                else{
                    expr+=s.top();
                    s.pop();
                }
            }
            s.push(inExp[i]);
        }
    }
    while(!s.empty()){
        expr += s.top();
        s.pop();
    }
    return expr;
}
int main()
{
    string inExp;
    while(1){
        cout<<"Enter the infix expression: ";
        cin>>inExp;
        // Checking of Infix Expression
        if(checkExpr(inExp)){
            break;
        }
        else{
            cout<<"Enter the correct infix expression."<<endl;
        }
    }
    //Conversion of Infix to Postfix
    string postExp = infixToPostfix(inExp);
    cout<<"The postfix expression is: "<<postExp<<endl;
    return 0;
}