
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFSIZE 4096

// Takes filenames as command line arguments and concatenates the contents of the first file -> into the second file
// It should also be checking if the files have the same contents and throw an error if they do.
// After running the code, the first file should be modified such that it has the contents of itself, plus the second file. The second file doesn't get modified.
// APPROACH
// Using standard input stream, take in the files and their contents, targeting the second file -- copy the contents and use a check against the contents of file one before appending.
// if they are not the same contents (not equal) then append them into file one, and reprint as a modified file.

int main(int argc, char *argv[])
{
    int readFileDescriptor, writeFileDescriptor;
    long int n;
    char buf[BUFFSIZE];
    if (argc != 3)
    {
        printf("Usage: %s <source_filename> <destination_filename>\n", argv[0]);
        exit(-1);
    }
    readFileDescriptor = open(argv[2], O_RDONLY);
    writeFileDescriptor = open(argv[1], O_WRONLY | O_APPEND);
    if (readFileDescriptor == -1 || writeFileDescriptor == -1)
    {
        printf("Error with file open\n");
        exit(-1);
    }
    while ((n = read(readFileDescriptor, buf, BUFFSIZE)) > 0)
    {
        if (write(writeFileDescriptor, buf, n) != n)
        {
            printf("Error writing to output file\n");
            exit(-1);
        }
    }
    if (n < 0)
    {
        printf("Error reading input file\n");
        exit(-1);
    }
    close(readFileDescriptor);
    close(writeFileDescriptor);
    return 0;
}