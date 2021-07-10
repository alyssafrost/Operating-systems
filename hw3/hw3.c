
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
