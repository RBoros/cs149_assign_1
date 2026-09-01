#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist{ /* table entry: */
    char names[];
    char *name;
    int count;
};
//COLLISSSSSIOOOOOOOOOOOOOOOOOOOOOOOOOOOOON
#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */
char* nameList[101];
int nameCount = 0;

/* This is the hash function: form hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {

    struct nlist *np = hashtab[hash(s)];
    if (np != NULL) {
        return np;
    }
    return NULL; /* not found */
}

/* insert: put (name, count) in hashtab */
void insert(char *name) {
    struct nlist *np = lookup(name);

    if (np == NULL) {
        np = malloc(sizeof(*np));
        if (np == NULL) {
            fprintf(stderr, "Allocation failed\n");
            exit(1);
        }
        np->name = name;
        np->count = 1;
        hashtab[hash(name)] = np;

        nameList[nameCount++] = strdup(name);
    } else {
        hashtab[hash(name)]->count++;
    }
}

void printNames(){
    for(int i = 0; i < nameCount; i++){
        printf("%s: %d\n", nameList[i], hashtab[hash(nameList[i])]->count);
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;

    if(argc == 1) {
        fp = stdin;
    }else if(argc == 2) {
        fp = fopen(argv[1], "r");
        if(fp == NULL) {
            printf("cannot open file\n");
            exit(1);
        }
    }

    char buffer[31];
    int lineNum = 1;

    while(fgets(buffer, sizeof(buffer), fp) != NULL) {
        //printf("%s", buffer);
        //printf("%llu\n", strlen(buffer));
        if(strlen(buffer) <= 1) {
            fprintf(stderr, "Warning - Line %d is empty.\n", lineNum);
        }else {
            //printf("%s", buffer);

            if (buffer[strlen(buffer) - 1] == '\n') {
                buffer[strlen(buffer) - 1] = '\0';
            }
            char *trueLine = strdup(buffer);
            insert(trueLine);
        }
        lineNum++;
    }

    //printNames();
    if(fp != stdin) {
        fclose(fp);
    }

    return 0;
}






