#include <iostream>
#include <string.h>
#include <sstream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <sys/types.h>

#include "create_f_d.cpp"
//#include "commandModeDisp.cpp"
#include "rename.cpp"

using namespace std;

int custom_command(vector<string>stream)
{
    front :
    
    /*string line,temp;
    getline(cin, line);
    vector<string>stream;
    stringstream check(line);
    while(getline(check,temp,' '))
    {
        stream.push_back(temp);
    }*/
    
    if(stream[0]=="rename") 
    {
        renamer(stream[2],stream[1]);
    }
    else if(stream[0]=="goto") 
    {
        chdir(stream[1].c_str());
        //commandModeDisp();
    }
    else if(stream[0]=="create_dir")
    {
        create_f_d(stream[0],stream[1],stream[2]);
    }
    else
    {

        cout<<"\033[2J\033[1;1H";
        //commandModeDisp();
        cout<<"\033[36;1H";
        cout<<"WELCOME TO COMMAND MODE :: ENTER EXIT TO GO TO NORMAL MODE"<<endl;
        cout<<"wrong command"<<endl;
        cout<<"\033[40;1H";
        cout<<"\033[1;1H";
        
        goto front; 
    }

    xyz : cin.ignore(unsigned(-1), '\n'); //never do this, instead use: system("PAUSE > NULL");;
    return 0;
}