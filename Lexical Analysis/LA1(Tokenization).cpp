#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
    fstream file,file1;
    string words,filename,filename1;
    filename = "My First Program.txt";
    filename1 = "newfile.txt";
    file.open(filename,ios::in);
    file1.open(filename1,ios::out);
    while(file){
        getline(file,words);
        string str = words;
        //cout<<str<<endl;
        if(str.compare("\n")!=0){
            string s = "";
            for(int i=0;i<str.size();i++){
                if(str[i]=='#'){
                    break;
                }
                else if(str[i]=='/' && (str[i+1]=='/' || str[i+1]=='*')){
                    break;
                }
                else if(str[i]=='*' && str[i+1]=='/'){
                    s="";
                    break;
                }
                else{
                    s=s+str[i];
                }
            }
            //cout<<s<<" "<<s.compare("")<<endl;
            if(s.compare("") != 0 && s.compare("") != 4){
                file1<<s<<endl;
               //cout<<file1.tellg()<<endl;
            }
        }
    }
    file.close();
    file1.close();
    string filename2 = "final.txt";
    fstream file2;
    file1.open(filename1.c_str(),ios::in);
    file2.open(filename2,ios::out);
    string word;
    while(file1>>word){
        string str1 = word;
        //cout<<str1<<endl;
        string str2 = "";
        int i=0;
        int flag = 0;
        for(;i<str1.size();){
            if((str1[i]=='<' && str1[i+1]=='<')){
                file2<<str2<<" ";
                string str3 = "<<";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }// Author: Shaina Mehta
            else if(str1[i]=='>' && str1[i+1]=='>'){
                file2<<str2<<" ";
                string str3 = ">>";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='=' && str1[i+1]=='='){
                file2<<str2<<" ";
                string str3 = "==";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='>' && str1[i+1]=='='){
                file2<<str2<<" ";
                string str3 = ">=";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='<' && str1[i+1]=='='){
                file2<<str2<<" ";
                string str3 = "<=";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='<' && str1[i+1]=='>'){
                file2<<str2<<" ";
                string str3 = "<>";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='+' && str1[i+1]=='='){
                file2<<str2<<" ";
                string str3 = "+=";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='-' && str1[i+1]=='='){
                file2<<str2<<" ";
                string str3 = "-=";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='*' && str1[i+1]=='='){
                file2<<str2<<" ";
                string str3 = "*=";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='/' && str1[i+1]=='='){
                file2<<str2<<" ";
                string str3 = "/=";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='%' && str1[i+1]=='='){
                file2<<str2<<" ";
                string str3 = "%=";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='+' && str1[i+1]=='+'){
                file2<<str2<<" ";
                string str3 = "++";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='-' && str1[i+1]=='-'){
                file2<<str2<<" ";
                string str3 = "--";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='|' && str1[i+1]=='|'){
                file2<<str2<<" ";
                string str3 = "||";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]=='&' && str1[i+1]=='&'){
                file2<<str2<<" ";
                string str3 = "&&";
                file2<<str3<<" ";
                i+=2;
                str2="";
                flag = 1;
                //count +=2;
            }
            else if(str1[i]==','||str1[i]==';'||str1[i]=='('||str1[i]==')'||str1[i]=='+'||str1[i]=='-'
                ||str1[i]=='*'||str1[i]=='/'||str1[i]=='%'||str1[i]=='='||str1[i]=='>'||str1[i]=='<'
                ||str1[i]=='!'||str1[i]=='&'||str1[i]=='|'||str1[i]=='^'){
                    file2<<str2<<" ";
                    file2<<str1[i]<<" ";
                    str2="";
                    flag = 1;
                    //count += 2;
                    i++;
            }
            else{
                str2=str2+str1[i];
                //cout<<str1[i]<<" ";
                i++;
            }
        }
        if(flag==0){
            file2<<str1<<" ";
            //count++;
        }
        else{
            file2<<str2<<" ";
            //count++;
        }
    }
    //cout<<count<<endl;
    file1.close();
    file2.close();
    file2.open(filename2.c_str(),ios::in);
    int count = 0;
    int count1 = 0;
    bool flag = false;
    //bool flag2 = false;
    string newword;
    while(file2>>newword){
        string s1 = newword;
        int n = s1.size()-1;
        count1++;
        if((s1[0]=='\"' || s1[0]=='\'')||(s1[n]=='\"' || s1[n]=='\'')){
            if(flag==false){
                flag=true;
            }
            else{
                flag=false;
                //if(s1.size()==1){
                    //count++;
                //}
            }
        }
        if(flag==true){
            count++;
        }
    }
    file2.close();
    cout<<"No of tokens are: "<<count1-count<<endl;
    return 0;
}
