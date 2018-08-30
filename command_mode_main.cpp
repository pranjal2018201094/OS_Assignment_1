#include <stdio.h>
#include <iostream>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <bits/stdc++.h>

using namespace std;
# include "custom_command_1.cpp"

int command_mode_main()
{
	static struct termios term, oterm;
    //non c mode enter
    tcgetattr(0, &oterm);
    // memcpy(&term, &oterm, sizeof(term));
    // term.c_lflag &= ~(ICANON | ECHO);
    term=oterm;
    term.c_lflag &= ~ICANON; 
    term.c_lflag &= ~ECHO;
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term);
    // tcsetattr(0, TCSANOW, &oterm);
    fflush(stdout);

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
		    /*cout<<endl;
		    for(int j=0;j<stream.size();j++)
		    {
		    	cout<<stream[j]<<endl;
		    }*/
		    custom_command(stream);
		    for(int i=0;i<200;i++)
		    {
		    	buffer[i]='\0';
		    }
		    
    	}
    	else if(c==27)
    	{
    		tcsetattr(0, TCSANOW, &oterm);
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