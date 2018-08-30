#include <stdio.h>
#include <bits/stdc++.h>
void renamer(string old_name,string new_name)
{

    if (rename(old_name.c_str(),new_name.c_str()) == 0)
    {
        //commandModeDisp();
        cout<<"\033[36;1H";
        cout<<"WELCOME TO COMMAND MODE :: ENTER EXIT TO GO TO NORMAL MODE";
        cout<<"Incorrect File Name"<<endl;
        cout<<"\033[40;1H";
        //cout<<"\033[37;1H";
    }
    else
    {
        cout<<"\033[2J\033[1;1H";
        //commandModeDisp();
        cout<<"\033[36;1H";
        cout<<"WELCOME TO COMMAND MODE :: ENTER EXIT TO GO TO NORMAL MODE"<<endl;
        cout<<"Incorrect File Name"<<endl;
        cout<<"\033[40;1H";
    }
}