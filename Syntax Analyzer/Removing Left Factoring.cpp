#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
string findCommonPrefixUtil(string s1, string s2){
    string result;
    int n1 = s1.length();
    int n2 = s2.length();
    for(int i=0,j=0;i<=n1-1&&j<=n2-1;i++,j++){
        if(s1[i]!=s2[j]){
            break;
        }
        result.push_back(s1[i]);
    }
    return result;
}
string findCommonPrefix(vector <string> alpha){
    string prefix = alpha[0];
    for(int i=1;i<alpha.size();i++){
        prefix = findCommonPrefixUtil(prefix,alpha[i]);
    }
    return prefix;
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
int main()
{
    //"S->iEtS|iEtSeS|a","E->b"
    //"S->abcA|abcAB|dB|dC|h","A->e","B->f","C->g"
    string Grammar[4]= {"S->abcA|abcAB|dB|dC|h","A->e","B->f","C->g"};
    vector <string> final;
    for(int i=0;i<4;i++){
        if(Grammar[i].size()==1){
            final.push_back(Grammar[i]);
        }
        else{
            unordered_map <char,vector<string>> similar;
            string lhs = Grammar[i].substr(0,1);
            string rhs = Grammar[i].substr(3);
            vector <string> parts = splitStrings(rhs,'|');
            for(int i=0;i<parts.size();i++){
                char a = parts[i].at(0);
                int ind = i;
                vector<string> s1;
                s1.push_back(parts[i]);
                for(int j=0;j<parts.size();j++){
                    char b = parts[j].at(0);
                    if(ind==j){
                        continue;
                    }
                    else{
                        if(a==b){
                            s1.push_back(parts[j]);
                        }
                    }
                }
                similar[a] = s1;
            }
            int itr = 1;
            for(auto x: similar){
                if(x.second.size()==1){
                    final.push_back(lhs+"->"+x.second[0]);
                }
                else{
                    vector <string> alpha;
                    for(int j=0;j<x.second.size();j++){
                        alpha.push_back(x.second[j]);
                    }
                    string s = findCommonPrefix(alpha);
                    final.push_back(lhs+"->"+s+lhs+(char)(itr+'0'));
                    int index = s.length()-1;
                    for(int j=0;j<alpha.size();j++){
                        if(alpha[j].length()-1 == index){
                            final.push_back(lhs+(char)(itr+'0')+"->episolon");
                        }
                        else{
                            final.push_back(lhs+(char)(itr+'0')+"->"+alpha[j].substr(index+1));
                        }
                    }
                    itr++;
                }
            }
        }
    }
    cout<<"The grammar without left factoring is: "<<endl;
    for(int i=0;i<final.size();i++){
        cout<<final[i]<<endl;
    }
    return 0;
}
