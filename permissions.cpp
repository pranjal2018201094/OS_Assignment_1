#include<iostream>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

int permissions(int mode_v)
{
	//char a[9];
	printf( (S_ISDIR(mode_v)) ? "d" : "-");
	printf( (mode_v & S_IRUSR) ? "r" : "-");
	printf( (mode_v & S_IWUSR) ? "w" : "-");
	printf( (mode_v & S_IXUSR) ? "x" : "-");
	printf( (mode_v & S_IRGRP) ? "r" : "-");
	printf( (mode_v & S_IWGRP) ? "w" : "-");
	printf( (mode_v & S_IXGRP) ? "x" : "-");
	printf( (mode_v & S_IROTH) ? "r" : "-");
	printf( (mode_v & S_IWOTH) ? "w" : "-");
	printf( (mode_v & S_IXOTH) ? "x" : "-");
	printf("\t");
	return 0;
}
int time_conv(long int lin_tim)
{
	cout<<ctime(&lin_tim);
	return 0;
}
