#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

/* table entry:
 * Each struct has a table of names just in case of collisions.
 */
struct nlist{
    int nCount;            // total names
    int nCapacity;
    int* counts;  //counts for each name in same struct
    char** names;

};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */
char* nameList[101];
int nameCount = 0;

/* This is the hash function: form hash value for string s */
unsigned hash(char *temp) {
    unsigned hashval;
    for (hashval = 0; *temp != '\0'; temp++) {
        hashval = *temp + 31 * hashval;
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
    char* temp = name;
    struct nlist *np = lookup(temp);
    const int hVal = hash(name);

    if (np == NULL) {
        np = malloc(sizeof(*np));
        if (np == NULL) {
            fprintf(stderr, "Allocation failed\n");
            exit(1);
        }

        np->nCount = 1;
        np->nCapacity = 4;
        np->names = malloc(np->nCapacity * sizeof(char*));
        np->names[0] = strdup(name);
        np->counts = malloc(np->nCapacity * sizeof(int));
        np->counts[0] = 1;
        hashtab[hVal] = np;

        nameList[nameCount++] = strdup(name);

    } else {
        int found = 0;
        for(int i = 0; i < np->nCount; i++){
            //printf("yes: %s\n",np->names[i]);
            if(strcmp(np->names[i], name) == 0) {
                found = 1;
                //printf("yes\n");
                hashtab[hVal]->counts[i]++;
                break;
            }
        }
        if(found == 0) {
            if(hashtab[hVal]->nCount == hashtab[hVal]->nCapacity) {
                hashtab[hVal]->nCapacity *=2;
                hashtab[hVal]->names = realloc(hashtab[hVal]->names, hashtab[hVal]->nCapacity * sizeof(char*));
                hashtab[hVal]->counts = realloc(hashtab[hVal]->counts, hashtab[hVal]->nCapacity * sizeof(int));

            }
            hashtab[hVal]->names[hashtab[hVal]->nCount] = strdup(name);
            hashtab[hVal]->counts[hashtab[hVal]->nCount] = 1;

            //printf("%s: %d\n", hashtab[hVal]->names[hashtab[hVal]->nCount], hashtab[hVal]->counts[hashtab[hVal]->nCount]);
            hashtab[hVal]->nCount++;

            nameList[nameCount++] = strdup(name);
        }
    }
}

void printNames(){
    for(int i = 0; i < nameCount; i++) {
        struct nlist *np = lookup(nameList[i]);
        for(int j = 0; j < np->nCount; j++) {
            if(strcmp(np->names[j], nameList[i]) == 0) {
                printf("%s: %d\n", nameList[i], np->counts[j]);
                break;
            }
        }
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
        if(strlen(buffer) <= 1) {
            fprintf(stderr, "Warning - Line %d is empty.\n", lineNum);
        }else {
            if (buffer[strlen(buffer) - 1] == '\n') {
                buffer[strlen(buffer) - 1] = '\0';
            }
            char *trueLine = strdup(buffer);

            insert(trueLine);
        }
        lineNum++;
    }

    printNames();
    if(fp != stdin) {
        fclose(fp);
    }

    return 0;
}
