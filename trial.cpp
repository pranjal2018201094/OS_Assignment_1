#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <bits/stdc++.h>


#include "disp_dir.cpp"

int mode()
{
    int c,d,e;
	int position=0;
	
    struct dirent *dir;
    struct stat st;

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
    
    FOREVER : vector <struct dirent *> dir_cur(disp_dir());
    printf("\033[1;1H");

    while (1) {

        
    
    
    c = getchar();
        
        if (c == 27 ) 
        {
            c=getchar();

            if(c == '[')
            {
                c=getchar();

                if(c==65)
                {
                    printf("\033[1A");
                    position--;
                }
                else if(c==66)
                {
                    printf("\033[1B");
                        position++;
                }
                else if (c==67)
                {
                    //printf("\033[1C");
                }
                else if (c==68)
                {
                    //printf("\033[1D");
                }

            }

        }
        else if(c=='\n')
        {
            stat(dir_cur[position]->d_name, &st);
            //string file_name;
            //file_name=dir_cur[position]->d_name;
            //cout<<S_ISDIR(st.st_mode);
            //printf( (S_ISDIR(st.st_mode)) ? "d" : "-");
            if(S_ISDIR(st.st_mode))
            {
                chdir(dir_cur[position]->d_name);
                position=0;
                goto FOREVER;
            }
            else
            {
                pid_t pid;
                pid=fork();
                if(pid==0)
                {
                    execl("/usr/bin/xdg-open","xdg-open",dir_cur[position]->d_name,(char *)0);
                    exit(1);
                }

            }

            
            //cout<<"\033[2J\033[1;1H";
            //break;

        }
        else if(c=='h'||c=='H')
        {
            chdir("/home/");
            position=0;
            goto FOREVER;
            //break;
        }
        else if(c==127)
        {
            chdir("..");
            position=0;
            goto FOREVER;
            //break;

        } 
        else if (c=='q'||c=='Q')
        {
            tcsetattr(0, TCSANOW, &oterm);
            cout<<"\033[2J\033[1;1H";
            //printf("\033[1;1H");
            break;
        }

    }
    return 0;
}


