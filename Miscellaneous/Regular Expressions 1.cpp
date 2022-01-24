# include <iostream>
# include <regex>
# include <string>
using namespace std;
int main(){
    regex r1("[0-1]*|0*1*");
    string s;
    cout<<"Enter the string: ";
    cin>>s;
    if(regex_match(s,r1)){
        cout<<"The string is accepted.";
    }
    else{
        cout<<"The string is rejected.";
    }
    return 0;
}
