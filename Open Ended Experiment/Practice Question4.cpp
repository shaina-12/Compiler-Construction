// Postfix to infix
#include <iostream>
#include <string>
#include <stack>
using namespace std;
bool is_operand(char ch){
    if((ch>='a' && ch<='z')||(ch>='A' && ch<='Z')||(ch>='0' && ch<='9')){
        return true;
    }
    return false;
}
string postfixToInfix(string inp){
    string out;
    stack<string> s;
    for(int i=0;i<inp.length();i++){
        if(is_operand(inp[i])){
            string op(1,inp[i]);
            s.push(op);
        }
        else{
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.push("("+op2+inp[i]+op1+")");
        }
    }
    return s.top();
}
int main(){
    string postExp;
    cout<<"Enter the postfix expression: ";
    cin>>postExp;
    string inExp = postfixToInfix(postExp);
    cout<<"The infix expression is: "<<inExp<<endl;
    return 0;
}