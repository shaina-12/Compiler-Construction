# include <iostream>
# include <regex>
using namespace std;
int main(){
    regex r1("[0-1]*|0*1*");
    cout<<regex_match("0111111000000",r1);
    return 0;
}
