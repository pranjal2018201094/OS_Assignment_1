#include <string.h>
#include <bits/stdc++.h>
#include <dirent.h> 
#include <stdio.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "permissions.cpp"
vector<struct dirent *> disp_dir() {
	DIR *d;
	int size;
	vector<struct dirent *>v;
	struct dirent *dir;
	struct stat st;
	d = opendir(".");
	cout<<"\033[2J\033[1;1H";
	if (d)
	 	{
			int i=1;
			
			//int index=10;
			//int p=scroll_down;    &&(scroll_down+10)>q
			//int q=0;
			while ((dir = readdir(d)) != NULL)
			{	
				//if(i>scroll_down)
				//{
					printf("%10d\t",i);
					
					v.push_back(dir);
					if(strlen(dir->d_name)>20)
					{
						for(int i=0;i<18;i++)
						{
						printf("%c",dir->d_name[i]);
						}
						printf("..");
					}
					else
					{
						printf("%20s",dir->d_name);
					}
					//cout<<"\t";
					stat(dir->d_name, &st);
					size = st.st_size;
					printf("%10d\t", size);
					permissions(st.st_mode);
					
					time_conv(st.st_mtime);
					

				//}
				//q++;
				i++;

		    }
	       	closedir(d);
		}
	//cout<<
	return v;
}






