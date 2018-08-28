#include <stdio.h>
#include <bits/stdc++.h>
void renamer(string old_name,string new_name)
{

    //char old_name[50], new_name[50];

    // Input old and new file name
    /*printf("Enter old file path: ");
    scanf("%s", old_name);

    printf("Enter new file path: ");
    scanf("%s", new_name);

*/
    // rename old file with new name
    if (rename(old_name, new_name )== 0)
    {
        printf("File renamed successfully.\n");
    }
    else
    {
        printf("Unable to rename files. Please check files exist and you have permissions to modify files.\n");
    }
}