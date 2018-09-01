#include <string.h>
#include <bits/stdc++.h>
#include <dirent.h> 
#include <stdio.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
using namespace std;
#include "disp_dir.h"
//#include "main.h"

vector<struct dirent *> disp_dir(int scroll_up,int scroll_down) 
{
	DIR *d;
	char show_path[200];
	int size;
	vector<struct dirent *>v;
	struct dirent *dir;
	struct stat st;
	d = opendir(".");
	cout<<"\033[2J\033[1;1H";
	getcwd(show_path, sizeof(show_path));
	if (d)
	 	{
			int i=1;
			
			while ((dir = readdir(d)) != NULL)
			{	
				v.push_back(dir);

				if(i<=scroll_down&&i>=scroll_up)
				{
					//printf("%4d\t",i);
					
					
					if(strlen(dir->d_name)>15)
					{
						for(int j=0;j<13;j++)
						{
						printf("%c",dir->d_name[j]);
						}
						printf("..");
					}
					else
					{
						printf("%-15s",dir->d_name);
					}
					//cout<<"\t";
					stat(dir->d_name, &st);
					size = st.st_size;
					if(size>1024*1024)
					{
						size=size/1024/1024;
						printf(" %-5dMB ", size);
					}
					else if(size>1024)
					{
						size=size/1024;
						printf(" %-5dKB ", size);
					}
					else
					{
						printf(" %-6dB ", size);	
					}

					struct passwd *pw = getpwuid(st.st_uid);
				    struct group  *gr = getgrgid(st.st_gid);
				    if(strlen(pw->pw_name)>8)
					{
						for(int j=0;j<6;j++)
						{
						printf("%c",pw->pw_name[j]);
						}
						printf("..");
					}
					else
					{
						printf("%-8s",pw->pw_name);
					}
					if(strlen(gr->gr_name)>8)
					{
						for(int j=0;j<6;j++)
						{
						printf("%c",gr->gr_name[j]);
						}
						printf("..");
					}
					else
					{
						printf("%-8s",gr->gr_name);
					}
				    
					printf( (S_ISDIR(st.st_mode)) ? "d" : "-");
					printf( (st.st_mode & S_IRUSR) ? "r" : "-");
					printf( (st.st_mode & S_IWUSR) ? "w" : "-");
					printf( (st.st_mode & S_IXUSR) ? "x" : "-");
					printf( (st.st_mode & S_IRGRP) ? "r" : "-");
					printf( (st.st_mode & S_IWGRP) ? "w" : "-");
					printf( (st.st_mode & S_IXGRP) ? "x" : "-");
					printf( (st.st_mode & S_IROTH) ? "r" : "-");
					printf( (st.st_mode & S_IWOTH) ? "w" : "-");
					printf( (st.st_mode & S_IXOTH) ? "x" : "-");
					printf("  ");
					
					//time Display
					long int tim=(st.st_mtime);
					cout<<ctime(&tim);
				}
				//q++;
				i++;

		    }
	       	closedir(d);
		}
		cout<<show_path;
		cout<<"\033[22;1H";
        cout<<"WELCOME TO NORMAL MODE";
	return v;
}