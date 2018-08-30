#include<iostream>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <bits/stdc++.h>
#include<string>
#include<vector>
using namespace std;
#ifndef INC_MAIN_H
#define INC_MAIN_H

void commandModeDisp();
int command_mode_main();
int custom_command(vector<string>stream);
int renamer(string old_name,string new_name);
int create_f_d(string stream0,string stream1,string stream2);
vector<struct dirent *> disp_dir(int scroll_up,int scroll_down);
int normal_mode();


#endif  /*INC_MODULE1_H*/

