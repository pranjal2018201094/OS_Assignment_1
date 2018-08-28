#include<bits/stdc++.h>
#include <stdio.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h> 

using namespace std;

int main()
{
	string line,temp;
    //char rnm[6],xt[4];
    getline(cin, line);
    
    vector<string>stream;
    stringstream check(line);
    while(getline(check,temp,' '))
    {
        stream.push_back(temp);
    }

	 if(stream[0]=="create_dir") //this should be fine because you inputted to line and are comparing to line
    {
     
		chdir(stream[2].c_str());
		mkdir(stream[1].c_str(),S_IRWXU | S_IRWXG | S_IRWXO);   
		cout<<"successfully created";
        //goto front;
    }
    return 0;
}