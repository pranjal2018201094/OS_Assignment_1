#include <stdio.h>
#include <iostream>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <bits/stdc++.h>
#include <string>
#include <fcntl.h>
#include <stdlib.h>
using namespace std;
#include "commandModeDisp.h"
#include "command_mode_main.h"

int custom_command(vector<string>stream);
int renamer(string old_name,string new_name);
int create_f_d(string stream0,string stream1,string stream2);
int cp_mv(vector<string>v);


int command_mode_main(string root)
{
    //cout<<"$";
    TOP :
    char c,buffer[500]="";
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
            goto TOP;
            /*for(int i=0;i<stream.size();i++)
            {
                cout<<stream[i];
            }*/
		    /*i=0;
		    while(buffer[i]!='\0')
		    {
		    	buffer[i]='';
		    	i++;
		    }
            //buffer[500]="";
		    i=i-1;*/
    	}
    	else if(c==27)
    	{
    		break;
    	}
    	else if(c==127)
    	{
    		/*i=i-1;
    		buffer[i]=' ';
    		cout<<buffer[i];
    		buffer[i]='\0';
    		cout<<"\033[1D";
    		//break;*/
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
        // cout<<stream[1];
        // cout<<stream[2];
        renamer(stream[1],stream[2]);
        return 0;
    }
    else if(stream[0]=="goto") 
    {
        //cout<<stream[1][0];
        chdir(stream[1].c_str());
        commandModeDisp();
        cout<<"\033[22;1H";
        cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
        cout<<"\033[24;1H";
        return 0;
    }
    else if(stream[0]=="create_dir"||stream[0]=="create_file")
    {
        create_f_d(stream[0],stream[1],stream[2]);
    }
    else if(stream[0]=="copy"||stream[0]=="move")
    {
        cp_mv(stream);
    }
    else
    {
        //cout<<"\033[2J\033[1;1H";
        commandModeDisp();
        cout<<"\033[22;1H";
        cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
        cout<<"wrong command"<<endl;
        cout<<"\033[24;1H";
        return 0;
        
    }

    return 0;
}


int renamer(string old_name,string new_name)
{

    if (rename(old_name.c_str(),new_name.c_str()) == 0)
    {
        commandModeDisp();
        cout<<"\033[22;1H";
        cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
        cout<<"Successfully Done !!!"<<endl;
        cout<<"\033[24;1H";
    }
    else
    {
        cout<<"\033[2J\033[1;1H";
        commandModeDisp();
        cout<<"\033[22;1H";
        cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
        cout<<"Incorrect File Name"<<endl;
        cout<<"\033[24;1H";
    }
    
    return 0;
}


int create_f_d(string stream0,string stream1,string stream2)
{
	
	 if(stream0=="create_dir") 
    {
     
		chdir(stream2.c_str());
        if(mkdir(stream1.c_str(),S_IRWXU | S_IRWXG | S_IRWXO))
        {
            cout<<"\033[2J\033[1;1H";
            commandModeDisp();
            cout<<"\033[22;1H";
            cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
            cout<<"successfully created"<<endl;
            cout<<"\033[24;1H";
        }
        else
        {
            cout<<"\033[2J\033[1;1H";
            commandModeDisp();
            cout<<"\033[22;1H";
            cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
            cout<<"Incorrect path"<<endl;
            cout<<"\033[24;1H"; 
        }
    }
    else if(stream0=="create_file")
    {
        chdir(stream2.c_str());
        FILE *file_pointer; 
        if(file_pointer = fopen(stream1.c_str(), "w+b"))
        {
            cout<<"\033[2J\033[1;1H";
            commandModeDisp();
            cout<<"\033[22;1H";
            cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
            cout<<"File is successfully created"<<endl;
            cout<<"\033[24;1H";
        }
        else
        {
            cout<<"\033[2J\033[1;1H";
            commandModeDisp();
            cout<<"\033[22;1H";
            cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
            cout<<"Incorrect Path"<<endl;
            cout<<"\033[24;1H";
        }
        fclose(file_pointer); 
        
        return 0;
        
    }
    else
    {
        cout<<"\033[2J\033[1;1H";
        commandModeDisp();
        cout<<"\033[22;1H";
        cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
        cout<<"Incorrect Command"<<endl;
        cout<<"\033[24;1H";   
    }
    return 0;
    
}


int cp_mv(vector<string>v)
{
    if(v[0]=="copy")
    {
        
        int in, out,max;
        int nread;
        char old_path[256];
        getcwd(old_path, sizeof(old_path));
        max=v.size();

        for(int i=1;i<max-1;i++)
        {

            char block[1024];
            chdir(old_path);
            in = open(v[i].c_str(), O_RDONLY);
            chdir(v[max-1].c_str());
            out = open(v[i].c_str(), O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
            while((nread = read(in,block,sizeof(block))) > 0)
            write(out,block,nread);
            cout<<i;
        }

        cout<<"\033[2J\033[1;1H";
        commandModeDisp();
        cout<<"\033[22;1H";
        cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
        cout<<"successfully copied"<<endl;
        cout<<"\033[24;1H";

    }
    /*else if(v[0].c_str()=="move")
    {
        chdir(stream2.c_str());
        FILE *file_pointer; 
        if(file_pointer = fopen(stream1.c_str(), "w+b"))
        {
            cout<<"\033[2J\033[1;1H";
            commandModeDisp();
            cout<<"\033[22;1H";
            cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
            cout<<"File is successfully created"<<endl;
            cout<<"\033[24;1H";
        }
        else
        {
            cout<<"\033[2J\033[1;1H";
            commandModeDisp();
            cout<<"\033[22;1H";
            cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
            cout<<"Incorrect Path"<<endl;
            cout<<"\033[24;1H";
        }
        fclose(file_pointer); 
        
        return 0;
        
    }*/
    else
    {
        cout<<"\033[2J\033[1;1H";
        commandModeDisp();
        cout<<"\033[22;1H";
        cout<<"WELCOME TO COMMAND MODE :: PRESS ESC TO GO TO NORMAL MODE"<<endl;
        cout<<"Incorrect Command"<<"cp_mv copy"<<endl;
        cout<<"\033[24;1H";   
    }
    return 0;
    
}