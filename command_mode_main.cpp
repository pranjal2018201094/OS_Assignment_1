#include <stdio.h>
#include <iostream>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <bits/stdc++.h>

//#include<headerss.h>

using namespace std;
# include "commandModeDisp.cpp"
int custom_command(vector<string>stream);
int renamer(string old_name,string new_name);
int create_f_d(string stream0,string stream1,string stream2);

int command_mode_main()
{
    cout<<"$";

    char c,buffer[200];
    int i=0;
    while(1)
    {
    	
    	c=getchar();
    	if(c=='\n')
    	{
    		string temp;
    		vector<string>stream;
    		stringstream check(buffer);
    		while(getline(check,temp,' '))
		    {
		        stream.push_back(temp);
		    }
		    
		    custom_command(stream);
		    i=0;
		    while(buffer[i]!='\0')
		    {
		    	buffer[i]='\0';
		    	i++;
		    }
		    i=-1;
    	}
    	else if(c==27)
    	{
    		break;
    	}
    	else if(c=='\b')
    	{
    		/*i--;
    		
    		buffer[i]=' ';
    		cout<<buffer[i];
    		buffer[i-1]='\0';
    		cout<<printf("\033[1D");
    		//i--;
    		tcsetattr(0, TCSANOW, &oterm);
    		//cout<<"0x07f";*/
    		break;
    	}
    	else
    	{
    		buffer[i]=c;
    		cout<<c;
    	}
    	i++;
    }
    return 0;
}

int custom_command(vector<string>stream)
{
    
    if(stream[0]=="rename") 
    {
        renamer(stream[2],stream[1]);
        return 0;
    }
    else if(stream[0]=="goto") 
    {
        chdir(stream[1].c_str());
        commandModeDisp();
    }
    else if(stream[0]=="create_dir")
    {
        create_f_d(stream[0],stream[1],stream[2]);
    }
    else
    {
        cout<<"\033[2J\033[1;1H";
        commandModeDisp();
        cout<<"\033[36;1H";
        cout<<"WELCOME TO COMMAND MODE :: ENTER EXIT TO GO TO NORMAL MODE"<<endl;
        cout<<"wrong command"<<endl;
        cout<<"\033[40;1H";
        //cout<<"\033[1;1H";
        
    }

    return 0;
}


int renamer(string old_name,string new_name)
{

    if (rename(old_name.c_str(),new_name.c_str()) == 0)
    {
        commandModeDisp();
        cout<<"\033[36;1H";
        cout<<"WELCOME TO COMMAND MODE :: ENTER EXIT TO GO TO NORMAL MODE";
        cout<<"Successfully Done !!!"<<endl;
        cout<<"\033[40;1H";
        //cout<<"\033[37;1H";
    }
    else
    {
        cout<<"\033[2J\033[1;1H";
        commandModeDisp();
        cout<<"\033[36;1H";
        cout<<"WELCOME TO COMMAND MODE :: ENTER EXIT TO GO TO NORMAL MODE"<<endl;
        cout<<"Incorrect File Name"<<endl;
        cout<<"\033[40;1H";
    }
    
    return 0;
}
int create_f_d(string stream0,string stream1,string stream2)
{
	/*string line,temp;
    //char rnm[6],xt[4];
    getline(cin, line);
    
    vector<string>stream;
    stringstream check(line);
    while(getline(check,temp,' '))
    {
        stream.push_back(temp);
    }
*/
	 if(stream0=="create_dir") //this should be fine because you inputted to line and are comparing to line
    {
     
		chdir(stream2.c_str());
		mkdir(stream1.c_str(),S_IRWXU | S_IRWXG | S_IRWXO);   
		cout<<"successfully created";
        //goto front;
    }
    return 0;
}