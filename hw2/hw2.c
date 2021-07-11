/* Name: Alyssa Frost
BlazerId: frost7
Project #: 3
To compile: gcc hw2.c
To run: ./a.out

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
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <dirent.h>   //file type and file name , getting members?
#include <sys/stat.h> //size in bytes, file type

typedef void printer(char *, struct stat *, struct dirent *, int); //int is for level depth, char * is for the path name

void indentation_printer(char *pathname, struct stat *stat, struct dirent *dirent, int depth) //pathname needs to be built somewhere else
{
    for (int index = 0; index < depth; index++)
    {
        printf("    ");
    }
}

void filename_printer(char *pathname, struct stat *stat, struct dirent *dirent, int depth)
{
    printf("%s", dirent->d_name);
}

void symlink_name_printer(char *pathname, struct stat *stat, struct dirent *dirent, int depth) //SYMLINK requires magic
{
    if (S_ISLNK(stat->st_mode)) // st_size = /* total size, in bytes */
    {
        int string_size = stat->st_size + 1;                             //bytes + null terminator
        char *string_buff = malloc(string_size);                         //mallocs the string size
        int symlink_size = readlink(pathname, string_buff, string_size); //uses readlink for symlink
        free(string_buff);
    }
}

void file_size_printer(char *pathname, struct stat *stat, struct dirent *dirent, int depth)
{
    printf("%d", stat->st_size);
}

typedef bool filter(char *, struct stat *, struct dirent *);
// arg for level
// what current dir so we can open it
//

int main(int argc, char **argv)
{
    // https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
    // getopt used with the cases for each flag

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

    char *current = ".";
    if (optind < argc)
    {
        current = argv[optind];
    }

    int filter_array_size = 0;
    if (min_file_size > 0) // s flag provided (size)
    {
        filter_array_size++;
    }

    if (substring != NULL) // f flag provided (substring)
    {
        filter_array_size++;
    }

    filter **filter_array = malloc((sizeof *filter_array) * filter_array_size);

    int filter_index = 0; // genuinely populates the array with function pointers
    if (min_file_size > 0)
    {
        filter_index++;
    }

    int printer_array_size = 3; // Possibility of three "printers" with addition arg S (4)
    if (should_print_file_size)
    {
        printer_array_size++;
    }

    printer **printer_array = malloc((sizeof *printer_array) * printer_array_size);

    int printer_index = 0;
    if (should_print_file_size) // S flag
    {
        printer_index++;
    }

    // Also, insert the other 3 printers that always are inserted symlink, name, indent

    // one for symlink name(s)
    // one for normal file name
    // one for indentation
    // one for S (size) check

    // where we call the recursive directory function

    free(filter_array);
    free(printer_array);
}

// Devise how a directory is going to be listed and the files within it. Start at pathname or some function called for each file or dir
// S option functionality
//build a path -> have something for default casing
// TODO: loop through everything in directory -- OK either current dir or specified dir in arg
// print maybe the files based on stupif fucking flags -- the things you print depend on the given flag
// S - size, if no S just name, s filtering based on min size and f for str match
// edge case : symbolic link would print two names
//
// loop thru sub directories (not for f, no looping for f if it matches the string (dirs))
//
//
