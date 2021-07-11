/* Name: Alyssa Frost
BlazerId: frost7
Project #: 3
To compile: <instructions for compiling the program>
To run: <instructions to run the program>*/

// Takes the directory name from where to start the file traversal as a cmd line argument and prints the file hierarchy, starting with the given one.
// IMPLEMENT: If the program is executed with no arguments, it should print the file hierarchy where it is executed. If no directories, in the current one, list the files by line.
// If there ARE other directories in the current one, list them line by line with tab identations.
/* like so:
            directory 1
                directory 2
                    directory 3
                    |
                    |
                    file 1
                    file 2
*/
// TODO: If a file is a symobolic link, make sure to display the name and in parenthesis the file name the link points to.
// TODO: Make it support the following: "-S" lists all files in the hierarchy and prints the file size next to the file name in parenthesis
//                                      "-s" is the file size in bytes, lists all files in the h. with file size greater than or = to the specified value
//                                      "-f" is the string pattern, lists files whose name or directory contains substring specified in the string pattern option
// Should support every option "flag" separetely, but also all strung together as in: -S, -s 1024, -f jpg, -S -s 1024, etc.
//

// make a main function and then add functionality

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <dirent.h>   //file type and file name , getting members?
#include <sys/stat.h> //size in bytes, file type
                      // page 128 for lstat

int main(int argc, char **argv)
{
    bool should_print_file_size = 0;
    int min_file_size = 0; // use optarg str-atoi-int
    char *substring = NULL;
    int c;

    opterr = 0;

    while ((c = getopt(argc, argv, "Ss:f:")) != -1)
    {
        switch (c)
        {
        case 'S':
            should_print_file_size = 1;
            break;
        case 's':
            min_file_size = atoi(optarg);
            break;
        case 'f':
            substring = optarg;
            break;
        default:
            printf("Please only use S, s, or f arguments.");
            return -1;
        }
    }

    // what arguments are provided, and what do they do
}