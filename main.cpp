#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <sys/types.h>

#include "normal_mode.h"
int main()
{
	normal_mode();
	return 0;
}