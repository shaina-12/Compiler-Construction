#include <iostream>
#include <string>
#include <vector>
using namespace std;
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
void getAlphaBeta(char start,string g2,vector<string> &alpha,vector<string> &beta){
    vector <string> prod = splitStrings(g2,'|');
    for(int i=0;i<prod.size();i++){
        if(prod[i].at(0) == start){
            alpha.push_back(prod[i].substr(1));
        }
        else{
            beta.push_back(prod[i]);
        }
    }
}
int main(){
    // assumption - the the grammar should not be ambiguous in nature
    string grammar[3] = {"E->E+T|T","T->T*F|F","F->(E)|id"};
    vector <string> finGrammar;
    for(int i=0;i<3;i++){
        string g1 = grammar[i].substr(0,1);
        string g2 = grammar[i].substr(3);
        vector <string> alpha;
        vector <string> beta;
        //cout<<grammar[0].at(0)<<endl;
        getAlphaBeta(grammar[i].at(0),g2,alpha,beta);
        if(alpha.size()!=0){
            string b = g1 + "->";
            string a = g1 + "\'" + "->";
            for(int i=0;i<beta.size();i++){
                if(i!=beta.size()-1){
                    b += beta[i] + g1 + "\'" + "|";
                }
                else{
                    b += beta[i] + g1 + "\'";
                }
                //cout<<"beta "<<beta[i]<<endl;
            }
            finGrammar.push_back(b);
            for(int i=0;i<alpha.size();i++){
                if(i!=alpha.size()-1){
                    a += alpha[i] + g1 + "\'" + "|";
                }   
                else{
                    a += alpha[i] + g1 + "\'" + "|" + "episolon";
                }
                //cout<<"alpha "<<alpha[i]<<endl;
            }
            finGrammar.push_back(a);
        }
        else{
            finGrammar.push_back(grammar[i]);
        }
    }
    cout<<"The grammar without left recursion is: ";
    for(int i=0;i<finGrammar.size();i++){
        cout<<finGrammar[i]<<endl;
    }
}
