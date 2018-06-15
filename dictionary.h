// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
#define NUM_WORDS 143091
#define HASHTABLE_SIZE 300007 // ideally ~ 1.3 times number of words, and is a prime number

// declare struct for singly-linked list, where each node consists of a string of max length = 45 + 1, and a pointer to the next node
typedef struct sllist
{
    char str[LENGTH + 1];
    struct sllist *next;
} sllist;

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
unsigned long hash(unsigned char *str);
void delsllist(sllist *ptr);

#endif // DICTIONARY_H
