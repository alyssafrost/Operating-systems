#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tokenize to delim on spaces
// -> returns null if nothing 
// strtok will show if complete 

// compare token to keyword list , increment if they match the number 
// argv used for [key, word, for, counting, in, sentence] 

int main(int argc, char *argv[]){

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    struct row {
        char keyword;
        int count;
    };

    int size = argc - 1;
    struct row keywords[size]; //array of rows 
    int i;
    for(i = 0; i < size + 1; i++){
        strcpy(&keywords[i].keyword, argv[i]);
        keywords[i].count = 0;
    };


    while ((read = getline(&line, &len, stdin)) > 0) {
        char *token = strtok(line, " ");
        while(token != NULL){
            for(i = 0; i < size + 1; i++){
                if(strcmp(token, &keywords[i].keyword) == 0){
                    keywords[i].count++;
                }
            };
            //printf("%s\n", token);
            token = strtok(NULL, " ");
        };
    };

    for(i = 1; i < size + 1; i++){
        printf("The keyword is %s, it appears %d times\n", &keywords[i].keyword, keywords[i].count);
    };

    free(line); 
    return 0;
}

  /* struct row {
    int id;
    char name;
  };

  struct row people[10];
  int size = sizeof people / sizeof people[0];

  int i;
  for (i = 0; i < size; i++){
    people[i].id = rand();
    strcpy(&people[i].name, "Charles");
    printf("%d | Name is %s, my id is %d\n", i, &people[i].name, people[i].id);
  } */

