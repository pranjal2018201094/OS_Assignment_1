#include <iostream>
#include <string.h>
#include <sstream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <sys/types.h>


#include "disp_dir.cpp"

using namespace std;

int main ()
{
    front :
    cout<<"$";
    string line,temp;
    //char rnm[6],xt[4];
    getline(cin, line);
    //cin>>line;
    //cout<<line;
    vector<string>stream;
    stringstream check(line);
    while(getline(check,temp,' '))
    {
        stream.push_back(temp);
    }

    /*for(int i=0;i<stream.size();i++)
    {
        cout<<stream[i]<<endl;
    }*/
    
    if(stream[0]=="rename") //this should be fine because you inputted to line and are comparing to line
    {
        //cout<<"rename_chala"<<endl;

        if (rename(stream[1].c_str(),stream[2].c_str()) == 0)
        {
            printf("File renamed successfully.\n");
        }
        else
        {
            printf("Unable to rename files. Please check files exist and you have permissions to modify files.\n");
        }

        goto front;//never do this
    }
    else if(stream[0]=="exit") //what if they entered one of the other commands?
    {
        //cout<<"exit_chala";
        goto xyz;
        //return 0;
    }
    else if(stream[0]=="goto") //what if they entered one of the other commands?
    {
        chdir(stream[1].c_str());
        disp_dir();
    }
    else
    {
        cout<<"wrong command"<<endl;
        goto front; //never do this
    }

    xyz : cin.ignore(unsigned(-1), '\n'); //never do this, instead use: system("PAUSE > NULL");;
    return 0;
}