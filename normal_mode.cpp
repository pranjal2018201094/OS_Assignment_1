#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <bits/stdc++.h>
using namespace std;

#include "command_mode_main.h"
#include "disp_dir.h"
#include "normal_mode.h"
//#include "command_mode_main.cpp"

int normal_mode()
{
    int c;
	int position=0;


    char cwd[256],root[256];

    stack<string>stack_backward;
    stack<string>stack_forward;
	
    struct dirent *dir;
    struct stat st;

    getcwd(root, sizeof(root));

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

    int scroll_up=1,scroll_down=10,cursor=1,flag=0;
    
    FOREVER : vector <struct dirent *> dir_cur(disp_dir(scroll_up,scroll_down));
   
    if(flag==1)
    {
        printf("\033[%d;1H",cursor);
        flag=0;
    }
    else
    {
        printf("\033[1;1H");
        flag=0;
    }

    while (1) 
    {
    
        c = getchar();
            
        if (c == 27 ) 
        {
            c=getchar();

            if(c == '[')
            {
                c=getchar();

                if(c==65)
                {
                    flag=1;
                    
                    if(position>0)
                    {
                        position--;
                        printf("\033[1A");
                    	
                    	if(cursor<=1)
	                    {
	                        if(scroll_up>1)
	                        {
	                            scroll_down--;
	                            scroll_up--;
	                        }
	                        goto FOREVER;
	                    }
	                    else
	                    {
	                        cursor--;
	                    }
                    }
            
                }
                else if(c==66)
                {
                    flag=1;

                    if(position<dir_cur.size()-1)
                    {
                        position++;
                        printf("\033[1B");

                    	if(cursor>=10)
	                    {
	                        if(scroll_up<11)
	                        {
	                            scroll_down++;
	                            scroll_up++;
	                        }
	                        goto FOREVER;
	                    }
	                    else
	                    {
	                        cursor++;
	                    }
                    }
	            
                }
                else if (c==67)
                {
                   if(!stack_forward.empty())
                    {
                        getcwd(cwd, sizeof(cwd));
                        stack_backward.push(cwd);

                        string top =stack_forward.top();
                        chdir(top.c_str());
                        stack_forward.pop();
                        
                        position=0;
		                scroll_up=1;
		                scroll_down=10;
		                cursor=1;
                        
                        goto FOREVER;
                    }
                    else
                    {
                       
                    }
                    
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

                        position=0;
		                scroll_up=1;
		                scroll_down=10;
		                cursor=1;

                        goto FOREVER;
                    }
                    else
                    {
                        
                    }
                    
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
                scroll_up=1;
                scroll_down=10;
                cursor=1;
                
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
        }
        else if(c=='h'||c=='H')
        {
        	for(int k=0;k<stack_forward.size();k++)
            {
                stack_forward.pop();
            }

            getcwd(cwd, sizeof(cwd));
            
            stack_backward.push(cwd);

            chdir(root);
            
            position=0;
            scroll_up=1;
            scroll_down=10;
            cursor=1;
            
            goto FOREVER;
            //break;
        }
        else if(c==127)
        {
        	for(int k=0;k<stack_forward.size();k++)
            {
                stack_forward.pop();
            }

            getcwd(cwd, sizeof(cwd));
            
            stack_backward.push(cwd);

            chdir("..");
            
            position=0;
            scroll_up=1;
            scroll_down=10;
            cursor=1;
            
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
            //tcsetattr(0, TCSANOW, &oterm);
            cout<<"\033[36;1H";
            cout<<"WELCOME TO COMMAND MODE :: ENTER EXIT TO GO TO NORMAL MODE";
            cout<<"\033[40;1H";
            command_mode_main();
            printf("\033[1;1H");
            //break;
            goto FOREVER;
        }

    }
    
    return 0;
}


