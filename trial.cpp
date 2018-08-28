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
    int c;
	int position=0;
    int scroll_up=0,scroll_down=0,cursor=0;

    char cwd[256];

    stack<string>stack_backward;
    stack<string>stack_forward;
	
    struct dirent *dir;
    struct stat st;

//getcwd();

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
    /*if(scroll_down<=0)
    {
        printf("\033[1;1H");
    }*/
    printf("\033[1;1H");

    while (1) 
    {  
        /*if(cursor>20)
        {
            scroll_down++;
            position--;
            goto FOREVER;
        }

        if(position<0)
        {
            scroll_up++;
            position++;
            goto FOREVER;
            
        } */    
        //if(scroll_up)  
    
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
                    //scroll_down--;
                    //scroll_down--;
                }
                else if(c==66)
                {
                    printf("\033[1B");
                        position++;
                        cursor++;
                        //scroll_down++;
                        //scroll_down++;
                }
                else if (c==67)
                {
                   if(!stack_forward.empty())
                    {
                        //getcwd();
                        getcwd(cwd, sizeof(cwd));
                        stack_backward.push(cwd);

                        string top =stack_forward.top();
                        chdir(top.c_str());
                        stack_forward.pop();
                        goto FOREVER;
                    }
                    else
                    {
                        //stack_backward.push(dir_cur[position]->d_name);
                    }
                    //goto FOREVER;

                    //printf("\033[1C");
                }
                else if (c==68)
                {
                    if(!stack_backward.empty())
                    {
                         getcwd(cwd, sizeof(cwd));
                        stack_forward.push(cwd);
                        string top =stack_backward.top();
                        chdir(top.c_str());
                        stack_backward.pop();
                        goto FOREVER;
                    }
                    else
                    {
                        //stack_backward.push(dir_cur[position]->d_name);
                    }
                    //printf("\033[1D");
                    //goto FOREVER;
                }

            }

        }
        else if(c=='\n')
        {

            for(int k=0;k<stack_forward.size();k++)
            {
                stack_forward.pop();
            }

            getcwd(cwd, sizeof(cwd));
            
            stack_backward.push(cwd);

            
            stat(dir_cur[position]->d_name, &st);
            
            if(S_ISDIR(st.st_mode))
            {
                chdir(dir_cur[position]->d_name);
                position=0;
                goto FOREVER;
            }
            else
            {
                pid_t pro;
                pro=fork();
                if(pro==0)
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
        else if (c==58)
        {
            tcsetattr(0, TCSANOW, &oterm);
            cout<<"\033[40;1H";
            // //printf("\033[1;1H");
            break;
        }

    }
    
    
    
    
    return 0;
}


