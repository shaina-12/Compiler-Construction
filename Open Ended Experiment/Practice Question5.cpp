// check whether a string belongs to E-> E+ E / E*E / id
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <climits>
#include <process.h>
using namespace std;
vector <string> prod = {"E->TR","R->+TR","R->#","T->FY","Y->*FY","Y->#","F->i"};
vector <char> term = {'+','*','i'};
vector <char> tabRow = {'+','*','i','$'};
vector <char> nonterm = {'E','R','T','Y','F'};
int parsingTable[5][4] = {{INT_MAX,INT_MAX,0,INT_MAX},
                           {1,INT_MAX,INT_MAX,2},
                           {INT_MAX,INT_MAX,3,INT_MAX},
                           {5,4,INT_MAX,5},
                           {INT_MAX,INT_MAX,6,INT_MAX}};
bool check(char ch){
    for(int i=0;i<term.size();i++){
        if(term.at(i)==ch){
            return true;
        }
    }
    return false;
}
int main(){
    string input;
    cout<<"Enter the string: ";
    cin>>input;
    for(int i=0;i<input.length();i++){
        //cout<<input[i]<<endl;
        if(!check(input[i])){
            //cout<<"Error"<<endl;
            cout<<"The given string does not belong to the grammar";
            exit(0);
        }
    }
    stack <char> s;
    input = input +"$";
    s.push('$');
    s.push(nonterm.at(0));
    int itr=0;
    //flag = 0
    while(s.top()!='$'){
        char a = input[itr];
        char X = s.top();
        int t = find(tabRow.begin(),tabRow.end(),a) - tabRow.begin();
        int nt = find(nonterm.begin(),nonterm.end(),X) - nonterm.begin();
        if(!isupper(X) && X==a){
            s.pop();
            itr++;
        }
        else if(!isupper(X) && X!=a){
            //flag = 1;
            break;
        }
        else if(parsingTable[nt][t] == INT_MAX){
            //flag = 1;
            break;
        }
        else{
            int ind = parsingTable[nt][t];
            string pro = prod[ind].substr(3);
            s.pop();
            for(int i=pro.length()-1;i>=0;i--){
                if(pro[i]!='#'){
                    s.push(pro[i]);
                }
            }
        }
    }
    if(s.size()==1){
        cout<<"The given string belongs to the grammar";
    }
    else{
        cout<<"The given string does not belong to the grammar";
    }
}