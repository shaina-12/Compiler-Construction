#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
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
void findProductions(char a, vector<pair<int,string>> &prod, vector<vector<string>> ref2){
    for(int i=0;i<ref2.size();i++){
        for(int j=0;j<ref2[i].size();j++){
            if(ref2[i][j].find(a)!=-1){
                pair<int,string> p;
                p.first = i;
                p.second = ref2[i][j];
                prod.push_back(p);
            }
        }
    }
}
vector <int> findAll(string str,char a){
    vector <int> index;
    for(int i=0;i<str.size();i++){
        if(str[i]==a){
            index.push_back(i);
        }
    }
    return index;
}
void calFirstFollow(char a,vector <char> &v,vector<vector<char>> firsts,vector<char> ref1){
    auto it = find(ref1.begin(), ref1.end(), a);
    int index = it - ref1.begin();
    for(int i=0;i<firsts[index].size();i++){
        v.push_back(firsts[index][i]);
    }
}
void calFollow(vector<char> ref1, vector<vector<string>> ref2, vector<vector<char>> &follow, vector<vector<char>> firsts){
    for(int i=0;i<ref1.size();i++){
        vector <char> c;
        c.push_back(ref1[i]);
        follow.push_back(c);
    }
    follow[0].push_back('$');
    for(int i=0;i<ref1.size();i++){
        char a = ref1[i];
        //cout<<a<<endl;
        vector<pair<int,string>> prod;
        findProductions(a,prod,ref2);
        for(int j=0;j<prod.size();j++){
            vector <int> index = findAll(prod[j].second,a);
            //cout<<"Index doodh liya hai "<<j<<endl;
            for(int l=0;l<index.size();l++){
                int ind = index[l];
                if(ind==prod[j].second.size()-1){
                    //cout<<"Rule 3 part 1"<<endl;
                    for(int k=1;k<follow[prod[j].first].size();k++){
                        char b = follow[prod[j].first][k];
                        if(find(follow[i].begin(),follow[i].end(),b)==follow[i].end()){
                            follow[i].push_back(b);
                        }
                    }
                }
                else{
                    //cout<<"Rule 2"<<endl;
                    string s = prod[j].second.substr(ind+1);
                    int flag=1;
                    for(int m=0;m<s.size();m++){
                        if(!isupper(s[m]) && s[m]!='#' && find(follow[i].begin(),follow[i].end(),s[m])==follow[i].end()){
                            follow[i].push_back(s[m]);
                            flag=0;
                            break;
                        }
                        else{
                            vector<char> v;
                            calFirstFollow(s[m],v,firsts,ref1);
                            if(find(v.begin(), v.end(),'#')==v.end()){
                                for(int k=0;k<v.size();k++){
                                    if(find(follow[i].begin(),follow[i].end(),v[k])==follow[i].end()){
                                        follow[i].push_back(v[k]);
                                    }
                                    //follow[i].push_back(v[k]);
                                }
                                flag=0;
                                break;
                            }
                            else{
                                //remove the # symbol
                                auto id = find(v.begin(), v.end(), '#');
                                int ind = id - v.begin();
                                v.erase(v.begin() + ind);
                                for(int k=0;k<v.size();k++){
                                    if(find(follow[i].begin(),follow[i].end(),v[k])==follow[i].end()){
                                        follow[i].push_back(v[k]);
                                    }
                                }
                            }
                        }
                    }
                    //add the follow of the left hand side if flag=1
                    if(flag==1){
                        //cout<<"Rule 3 part 2"<<endl;
                        for(int k=1;k<follow[prod[j].first].size();k++){
                            char b = follow[prod[j].first][k];
                            if(find(follow[i].begin(),follow[i].end(),b)==follow[i].end()){
                                        follow[i].push_back(b);
                            }
                        }
                    }
                }
            }
        }
        /*
        for(int j=0;j<prod.size();j++){
            cout<<prod[j].first<<" "<<prod[j].second<<endl;
        }
        */
       //cout<<"Yaar Bhai Ho Gaya"<<endl;
    }
}
void calFirstUtil(char a, vector<char> ref1, vector<vector<string>> ref2, vector<vector<char>> firsts, vector<char> &v){
    if(!isupper(a) || a=='#'){
        //cout<<a<<endl;
        v.push_back(a);
        return;
    }
    auto it = find(ref1.begin(),ref1.end(),a);
    int index = it - ref1.begin();
    for(int i=0;i<ref2[index].size();i++){
        char b = ref2[index][i].at(0);
        //cout<<"Shaina" << b<<endl;
        //v.push_back('$');
        calFirstUtil(b,ref1,ref2,firsts,v);
    }
}
void calFirst(vector<char> ref1, vector<vector<string>> ref2, vector<vector<char>> &firsts){
    for(int i=0;i<ref2.size();i++){
        vector<char> fi;
        for(int j=0;j<ref2[i].size();j++){
            if(ref2[i][j].compare("#")==0){
                fi.push_back('#');
            }
            else if(!(isupper(ref2[i][j].at(0)))){
                fi.push_back(ref2[i][j].at(0));
            }
            else{
                fi.push_back('$');
            }
        }
        firsts.push_back(fi);
    }
    for(int i=0;i<ref2.size();i++){
        for(int j=0;j<ref2[i].size();j++){
            char a = ref2[i][j].at(0);
            if(isupper(a)){
                auto it = find(firsts[i].begin(), firsts[i].end(), '$');
                int index = it - firsts[i].begin();
                firsts[i].erase(firsts[i].begin() + index);
                for(int k=0;k<ref2[i][j].size();k++){
                    char b = ref2[i][j].at(k);
                    vector <char> v;
                    //cout<<b<<endl;
                    calFirstUtil(b,ref1,ref2,firsts,v);
                    for(int l=0;l<v.size();l++){
                        auto id = find(firsts[i].begin(), firsts[i].end(), v[l]);
                        if(id==firsts[i].end() and v[l]!='#'){
                            firsts[i].push_back(v[l]);
                        }
                        if(k==ref2[i][j].size()-1 && v[l]=='#'){
                            firsts[i].push_back(v[l]);
                        }
                        //cout<<v[l]<<" ";
                    }
                    //cout<<endl;
                    auto i = find(v.begin(), v.end(), '#');
                    if(i==v.end()){
                        break;
                    }
                }
            }
        }
    }
}
int main(){
    //"T->FY","Y->*FY|#","F->(T)|i"
    //"S->AaAb|BbBa","A->#","B->#"
    //"E->TR","R->+TR|#", "T->FY","Y->*FY|#","F->(E)|i"
    string grammar[5] = {"E->TR","R->+TR|#", "T->FY","Y->*FY|#","F->(E)|i"};
    vector<vector<char>> firsts;
    vector<vector<char>> follow;
    vector <char> ref1;
    vector <vector<string>> ref2;
    for(int i=0;i<5;i++){
        char lhs = grammar[i].at(0);
        string rhs = grammar[i].substr(3);
        vector <string> parts = splitStrings(rhs,'|');
        ref1.push_back(lhs);
        ref2.push_back(parts);
    }
    calFirst(ref1,ref2,firsts);
    for(int i=0;i<firsts.size();i++){
        cout<<"First of "<<ref1[i]<<" ";
        for(int j=0;j<firsts[i].size();j++){
            cout<<firsts[i][j]<<" ";
        }
        cout<<endl;
    }
    calFollow(ref1,ref2,follow,firsts);
    for(int i=0;i<follow.size();i++){
        cout<<"Follow of "<<ref1[i]<<" ";
        for(int j=1;j<follow[i].size();j++){
            cout<<follow[i][j]<<" ";
        }
        cout<<endl;
    }
}
