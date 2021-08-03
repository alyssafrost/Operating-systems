/*
Name: Alyssa Frost
BlazerId: frost7
Project #: 3
To compile: make tree
To run: ./tree
*/

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

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <dirent.h>   //file type and file name , getting members?
#include <sys/stat.h> //size in bytes, file type
#include <sys/wait.h>

typedef void printer(char *, struct stat *, struct dirent *, int, char *command); //int is for level depth, char * is for the path name

void indentation_printer(char *pathname, struct stat *stat, struct dirent *dirent, int depth, char *command) //pathname needs to be built somewhere else
{
    for (int index = 0; index < depth; index++)
    {
        printf("    ");
    }
}

void filename_printer(char *pathname, struct stat *stat, struct dirent *dirent, int depth, char *command)
{
    printf("%s", dirent->d_name);
}

void symlink_name_printer(char *pathname, struct stat *stat, struct dirent *dirent, int depth, char *command) //SYMLINK requires magic
{
    if (S_ISLNK(stat->st_mode)) // st_size = /* total size, in bytes */
    {
        int string_size = stat->st_size + 1;                             //bytes + null terminator
        char *string_buff = malloc(string_size);                         //mallocs the string size
        int symlink_size = readlink(pathname, string_buff, string_size); //uses readlink for symlink
        printf("%s", string_buff);
        free(string_buff);
    }
}

void file_size_printer(char *pathname, struct stat *stat, struct dirent *dirent, int depth, char *command)
{
    printf("%d", stat->st_size);
}

void command_printer(char *pathname, struct stat *stat, struct dirent *dirent, int depth, char *command)
{
    int process_id = fork();
    if (process_id == 0)
    {
        int token_index = 0;
        char *args[100]; //nullify
        //populate arg array with tokens, hey get rid of 10 later
        char *token = strtok(command, " ");
        while (token != NULL)
        {
            args[token_index] = token;
            token = strtok(NULL, " ");
            token_index++;
        };
        args[token_index] = pathname;
        args[token_index + 1] = NULL;
        execvp(args[0], args);
        // this is the child, execute
    }
    else
    {
        int status;
        waitpid(0, &status, 0);
    }
    // this is the parent, go from here should work? proly not
    //exec
    // call fork, ;
}

typedef bool filter(char *, struct stat *, struct dirent *, int, char *); // int is minimum file size in bytes, char * x2 is for the substring "-f"

//filter for -s flag
bool filter_file_size(char *pathname, struct stat *stat, struct dirent *dirent, int min_file_size, char *substring)
{
    if (min_file_size <= stat->st_size)
    {
        return true;
    }
    return false;
}

bool filter_string_pattern(char *pathname, struct stat *stat, struct dirent *dirent, int min_file_size, char *substring)
{
    char *found_substring = strstr(pathname, substring);
    if (found_substring)
    {
        return true;
    }
    return false;
}

// Recursive function for traversing the tree

void tree_traversal(char *current_dir, filter **filter_array, printer **printer_array, int min_file_size, char *substring, int current_depth, int filter_length, int printer_length, char *command)
{
    DIR *open_dir = opendir(current_dir);
    struct dirent *dir_entry;
    char *relative_path = malloc(sizeof *relative_path * PATH_MAX);

    while (dir_entry = readdir(open_dir)) // loop over dir contents
    {
        //construct relative path for each thing in the dir
        strcpy(relative_path, current_dir);
        strcat(relative_path, "/");
        strcat(relative_path, dir_entry->d_name);
        //
        struct stat stat;
        lstat(relative_path, &stat);

        bool should_print = true;

        for (int index = 0; index < filter_length; index++)
        {
            if (!(*filter_array[index])(relative_path, &stat, dir_entry, min_file_size, substring))
            {
                should_print = false;
                break;
            }
        }

        if (should_print)
        {
            for (int index = 0; index < printer_length; index++)
            {
                (*printer_array[index])(relative_path, &stat, dir_entry, current_depth, command);
                printf(" ");
            }

            printf("\n");
        }

        //

        if ((S_ISDIR(stat.st_mode) || S_ISLNK(stat.st_mode)) &&
            (!(strcmp(dir_entry->d_name, ".") == 0)) &&
            (!(strcmp(dir_entry->d_name, "..") == 0)))
        {
            tree_traversal(relative_path, filter_array, printer_array, min_file_size, substring, current_depth + 1, filter_length, printer_length, command);
        }
    }
    free(relative_path);
    closedir(open_dir);
}

int main(int argc, char **argv)
{
    // https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
    // getopt used with the cases for each flag

    bool should_print_file_size = 0;
    int min_file_size = 0; // use optarg str-atoi-int
    char *substring = NULL;
    char *command = NULL;
    // pointer for unix command
    int c;

    opterr = 0;

    while ((c = getopt(argc, argv, "Ss:f:e:")) != -1)
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
        case 'e':
            command = optarg;
            break;
            // unix command in " " - executed for each file-- fork/exe/wait
        default:
            printf("Please only use S, s, f, or e arguments.");
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
        filter_array[filter_index] = filter_file_size;
        filter_index++;
    }

    if (substring != NULL)
    {
        filter_array[filter_index] = filter_string_pattern;
        filter_index++;
    }

    int printer_array_size = 4; // Possibility of four "printers" with addition arg S (4)
    if (should_print_file_size)
    {
        printer_array_size++;
    }

    printer **printer_array = malloc((sizeof *printer_array) * printer_array_size);

    int printer_index = 0;

    printer_array[printer_index] = indentation_printer;
    printer_index++;

    printer_array[printer_index] = filename_printer;
    printer_index++;

    printer_array[printer_index] = symlink_name_printer;
    printer_index++;

    printer_array[printer_index] = command_printer;
    printer_index++;

    if (should_print_file_size) // S flag
    {
        printer_array[printer_index] = file_size_printer;
        printer_index++;
    }

    // where we call the recursive directory function
    tree_traversal(current, filter_array, printer_array, min_file_size, substring, 0, filter_array_size, printer_array_size, command);

    free(filter_array);
    free(printer_array);
}
