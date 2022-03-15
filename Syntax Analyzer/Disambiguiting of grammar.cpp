// In this program we are dismabiguiting the operator grammar having binary operators.
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
using namespace std;
map<char,int> pre = {{'-',1},{'+',1},{'/',2},{'*',2},{'^',3}}; // 1 - lowest and 3 - highest
map<char,char> asso = {{'+','L'},{'-','L'},{'*','L'},{'/','L'},{'^','R'}};
string grammarGen(string s, vector<string> grp, string num1, string num2){
    string s1 = "" + s;
    if(num1=="0"){
        s1 += "->";
    }
    else{
        s1 += num1 + "->";
    }
    for(int i=0;i<grp.size();i++){
        char a = grp[i].at(1);
        if(num1 == "0"){
            if(asso[a] == 'L'){
                s1 += s + a + s + num2;
            }
            else{
                s1 += s + num2 + a + s;
            }
        }
        else{
            if(asso[a] == 'L'){
                s1 += s + num1 + a + s + num2;
            }
            else{
                s1 += s + num2 + a + s + num1;
            }
        }
        if(i!=grp.size()-1){
            s1 += "|";
        }
    }
    return s1;
}
vector<string> splitStrings(string str, char dl)
{
    string word = "";
    int num = 0;
    str = str + dl;
    int l = str.size();
    vector<string> substr_list;
    for (int i = 0; i < l; i++) {
        if (str[i] != dl)
            word = word + str[i];
 
        else {
            if ((int)word.size() != 0)
                substr_list.push_back(word);
            word = "";
        }
    }
    return substr_list;
}
int main(){
    // assumption -  here we are taking the grammar containing the operators +, -, *, / and ^.
    string grammar = "E->E*E|E+E|E^E|(E)|id";
    char g = grammar.at(0);
    string gm = grammar.substr(3);
    vector<string> spl = splitStrings(gm,'|');
    vector<string> ambi;
    vector<string> nonambi;
    for(int i=0;i<spl.size();i++){
        int ctr = 0;
        for(int j=0;j<spl[i].size();j++){
            if(spl[i].at(j)==g){
                ctr++;
            }
        }
        if(ctr>1){
            ambi.push_back(spl[i]);
        }
        else{
            nonambi.push_back(spl[i]);
        }
    }
    if(ambi.size()!=0){
        vector<string> fin;
        vector<string> grp1;
        vector<string> grp2;
        vector<string> grp3;
        for(int i=0;i<ambi.size();i++){
            char a = ambi[i].at(1);
            if(pre[a] == 1){
                grp1.push_back(ambi[i]);
            }
            else if(pre[a] == 2){
                grp2.push_back(ambi[i]);
            }
            else{
                grp3.push_back(ambi[i]);
            }
        } 
        string s = grammar.substr(0,1);
        if(grp1.size()!=0){
            string s1 = grammarGen(s,grp1,"0","1");
            fin.push_back(s1);
        }
        if(grp2.size()!=0){
            string s1 = grammarGen(s,grp2,"1","2");
            fin.push_back(s1);
        }
        if(grp3.size()!=0){
            string s1 = grammarGen(s,grp3,"2","3");
            fin.push_back(s1);
        }
        string s2 = grammar.substr(0,1) + "3->";
        for(int i=0;i<nonambi.size();i++){
            if(i!=nonambi.size()-1){
                s2 += nonambi[i] + "|";
            }
            else{
                s2 += nonambi[i];
            }
        }
        fin.push_back(s2);
        cout<<"The grammar is ambiguous."<<endl;
        cout<<"The non ambigous grammar is: "<<endl;
        for(int i=0;i<fin.size();i++){
            cout<<fin[i]<<endl;
        }
    }
    else{
        cout<<"The grammar is non ambiguous in nature"<<endl;
    }
}