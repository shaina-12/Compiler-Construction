#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <stack>
using namespace std;
vector <string> prod= {"E->TR","R->+TR","R->#","T->FY","Y->*FY","Y->#","F->(E)","F->i"};
vector <vector<char>> firsts = {{'(','i'},{'+','#'},{'(','i'},{'*','#'},{'(','i'}};
vector <vector<char>> follow = {{'$',')'},{'$',')'},{'$',')','+'},{'$',')','+'},{'$',')','+','*'}};
vector <char> term = {'i','+','*','(',')','$'};
vector <char> nonterm = {'E','R','T','Y','F'};
// '@' represents the error in the predictive parsing table
int parsingTable[5][6] = {{INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX},
                            {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX},
                            {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX},
                            {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX},
                            {INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX}};
vector<char> calFirst(string rhs){
    vector <char> v;
    //cout<<rhs.at(0)<<endl;
    if(!isupper(rhs.at(0)) || rhs.at(0)=='#'){
        //cout<<rhs.at(0)<<endl;
        v.push_back(rhs.at(0));
        return v;
    }
    char b = rhs.at(0);
    auto i = find(nonterm.begin(),nonterm.end(),b);
    int in = i - nonterm.begin();
    vector <char> f = firsts[in];
    if(find(f.begin(),f.end(),'#')==f.end()){
        for(int j=0;j<f.size();j++){
            if(find(v.begin(),v.end(),f[j])==v.end()){
                v.push_back(f[j]);
            }
        }
        return v;
    }
    else{
        for(int i=1;i<rhs.size();i++){
            char a = rhs.at(i);
            auto it = find(nonterm.begin(),nonterm.end(),a);
            int ind = it - nonterm.begin();
            vector <char> fi = firsts[ind];
            // stopping at not finding of '#
            if(find(fi.begin(),fi.end(),'#')==fi.end()){
                for(int j=0;j<fi.size();j++){
                    // to avoid repeatation
                    if(find(v.begin(),v.end(),fi[j])==v.end()){
                        v.push_back(fi[j]);
                    }
                }
                break;
            }
            else{
                for(int j=0;j<fi.size();j++){
                    // to avoid repeatation
                    if(find(v.begin(),v.end(),fi[j])==v.end()){
                        // to eliminate repetation of '#'
                        if(i!=rhs.size()-1){
                            if(fi[j]!='#'){
                                v.push_back(fi[j]);
                            }
                        }
                        else{
                            v.push_back(fi[j]);  
                        }
                    }
                }
            }
        }
    }
    return v;
}
int main(){
    for(int i=0;i<prod.size();i++){
        int pno = i;
        char lhs = prod[i].at(0);
        //cout<<lhs<<" ";
        string rhs = prod[i].substr(3);
        //finding the index of lhs 
        auto nt = find(nonterm.begin(),nonterm.end(),lhs);
        int nind = nt - nonterm.begin();
        // cal the first of rhs
        vector<char> fir = calFirst(rhs);
        /*
        for(int k=0;k<fir.size();k++){
            cout<<fir[k]<<" ";
        }*/
        // checking for '#' in the first of alpha
        //cout<<fir.size()<<endl;
        if(find(fir.begin(),fir.end(),'#')==fir.end()){
            for(int j=0;j<fir.size();j++){
                char a = fir.at(j);
                //cout<<a<<endl;
                auto t = find(term.begin(),term.end(),a);
                int tind = t - term.begin();
                parsingTable[nind][tind] = pno;
            }
        }
        else{
            // '#' is present in first of alpha
            // cal the follow of lhs
            vector<char> fol = follow[nind];
            for(int j=0;j<fir.size();j++){
                char a = fir.at(j);
                if(a!='#'){
                    auto t = find(term.begin(),term.end(),a);
                    int tind = t - term.begin();
                    parsingTable[nind][tind] = pno;
                }
            }
            for(int j=0;j<fol.size();j++){
                char a = fol.at(j);
                auto t = find(term.begin(),term.end(),a);
                int tind = t - term.begin();
                parsingTable[nind][tind] = pno;
            }
        }
    }
    cout<<"The predictive parsing table is: "<<endl;
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            if(parsingTable[i][j]==INT_MAX){
                cout<<"@"<<" ";
            }
            else{
                cout<<parsingTable[i][j]<<" ";
            }
        }
        cout<<endl;
    }
    // parsing the string using predictive parsing table
    string input;
    cout<<"Enter the input string"<<endl;
    cin>>input;
    stack <char> s;
    s.push('$');
    s.push(nonterm[0]);
    int itr = 0;
    while(s.top()!='$'){
       //cout<<"Stack Top"<<" "<<s.top()<<endl;
        char a = input[itr];
        //cout<<"input"<<" "<<a<<endl;
        auto nt = find(nonterm.begin(),nonterm.end(),s.top());
        int nind = nt - nonterm.begin();
        auto t = find(term.begin(),term.end(),a);
        int tind = t - term.begin();
        if(!isupper(s.top()) && s.top()==a){
            s.pop();
            itr++;
        }
        else if(!isupper(s.top()) && s.top()!=a){
            cout<<"Error 1"<<endl;
            break;
        }
        else if(parsingTable[nind][tind]==INT_MAX){
            cout<<"Error 2"<<endl;
            break;
        }
        else{
            int b = parsingTable[nind][tind];
            string st = prod[b].substr(3);
            s.pop();
            for(int i=st.length()-1;i>=0;i--){
                if(st.at(0)!='#'){
                    s.push(st.at(i));
                }
            }
        }
    }
    if(s.size()==1){
        cout<<"The string has been parsed successfully by the parser."<<endl;
    }
    else{
        cout<<"The string has failed to parse by the parser."<<endl;
    }
}
