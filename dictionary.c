// Implements a dictionary's functionality
// Use linked-list based hash table

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

// globally declare hash table made up of pointers to singly-linked list
sllist *hashtable[HASHTABLE_SIZE] = { NULL };
// globally declare the hashvalue variable, a buffer to copy word, and a traverse pointer
unsigned long hashvalue;
char wordcpy[LENGTH + 1];
sllist *traverse;
unsigned int wordcount;
int cmp;
//int collisions;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // make a copy of the read-only word
    strcpy(wordcpy, word);
    // convert any uppercase letters to lowercase
    for (int i = 0; wordcpy[i] != '\0'; i++)
    {
        wordcpy[i] = tolower(wordcpy[i]);
    }

    // insert the word into the hash function to calculate its hash value
    hashvalue = hash((unsigned char *)wordcpy);
    // go to the location in the hash table corresponded to its hash value, if the pointer at the node is NULL, return false
    if (hashtable[hashvalue] == NULL)
    {
        return false;
    }
    // if the word in the first node matches the word being searched, return true.
    else if ((cmp = strcmp(hashtable[hashvalue] -> str, wordcpy)) == 0)
    {
        return true;
    }
    // if the word at the node is alphabetically less than the word being searched, if the next pointer is null, return false
    else if (cmp < 0 || hashtable[hashvalue] -> next == NULL)
    {
        return false;
    }
    // otherwise, linearly search along the linked list
    else
    {
        // make the traverse pointer point to the next node
        traverse = hashtable[hashvalue] -> next;
        while (true)
        {
            // if the word at the node matches the word being searched, return true
            if ((cmp = strcmp(traverse -> str, wordcpy)) == 0)
            {
                return true;
            }
            // if the word at the node is alphabetically less than the word being searched, if the next pointer is null, return false
            else if (cmp < 0 || traverse -> next == NULL)
            {
                return false;
            }
            // otherwise, make the traverse pointer point to the next node, and repeat the while loop
            else
            {
                traverse = traverse -> next;
            }
        }
    }
}

// Loads dictionary into memory, returning true if successful else false
// implement hash table using hash function for english words
bool load(const char *dictionary)
{
    // open the dictionary file, and check for error
    FILE *dictptr = fopen(dictionary, "r");
    if (dictptr == NULL)
    {
        printf("Could not open dictionary\n");
        return false;
    }

    // create a buffer to store word, and a pointer for new nodes
    unsigned char word[LENGTH + 1];
    sllist *newnode;

    // read each word and save them into the buffer
    while (fscanf(dictptr, "%s", word) != EOF)
    {
        // increment word counter
        wordcount++;
        // apply hash function to the word, make a copy the pointer in the hash table to a new pointer "traverse"
        hashvalue = hash(word);

        // if the pointer is NULL, calloc (malloc and zero initialize) a new node pointed by the pointer in hash table
        if (hashtable[hashvalue] == NULL)
        {
            hashtable[hashvalue] = calloc(1, sizeof(sllist));
            // check if memory ran out
            if (hashtable[hashvalue] == NULL)
            {
                fclose(dictptr);
                printf("Memory allocation failed\n");
                return false;
            }
        }

        // otherwise, insert a new node as the first node of the linked list pointed to by the hash table
        else
        {
            //collisions++;
            // malloc a new node pointed by a new pointer
            newnode = malloc(sizeof(sllist));
            // check if memory ran out
            if (newnode == NULL)
            {
                fclose(dictptr);
                printf("Memory allocation failed\n");
                return false;
            }
            // make the new node's next pointer to point to the node pointed by the pointer in the hash table
            newnode -> next = hashtable[hashvalue];
            // move the pointer in the hash table to point to the new node
            hashtable[hashvalue] = newnode;
        }
        // add the word in the new node
        strcpy(hashtable[hashvalue] -> str, (const char *) word);
    }
    fclose(dictptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;

    /* COUNT WORDS BY ITERATING THROUGH THE HASH TABLE
    // initialize word counter
    unsigned int wordcount = 0;
    // iterate over each element of the hash table
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // if the pointer at this index is NULL, do nothing
        if (hashtable[i] == NULL);
        // if there is only one node, increment the counter by one
        else if (hashtable[i] -> next == NULL)
        {
            wordcount++;
        }
        // otherwise, walk through the nodes in the linked list until the pointer is null
        else
        {
            // count the first two nodes
            wordcount += 2;
            // make the traverse pointer equal to the pointer in the second node
            traverse = hashtable[i] -> next -> next;
            // as long as the pointer in the node is not NULL, increment counter, make the traverse pointer equal to the pointer in the next node
            while (traverse != NULL)
            {
                wordcount++;
                traverse = traverse -> next;
            }
        }
    }
    return wordcount;
    */
}

// Unloads dictionary from memory, returning true if successful else false
// delete all nodes from each linked list
bool unload(void)
{
    // iterate over the hash table
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // if the pointer at this index is NULL, do nothing
        if (hashtable[i] == NULL);
        // if there is only one node, free the pointer at the hash table
        else if (hashtable[i] -> next == NULL)
        {
            free(hashtable[i]);
        }
        // otherwise, pass the pointer at the second node to the delsllist function, then delete the first two nodes
        else
        {
            delsllist(hashtable[i] -> next -> next);
            free(hashtable[i] -> next);
            free(hashtable[i]);
        }
    }
    //printf("Number of collisons: %i", collisions);

    // success
    return true;
}

// hash function djb2 by Dan Bernstein (source url: http://www.cse.yorku.ca/~oz/hash.html)
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % HASHTABLE_SIZE;
}

// delete a singly-linked list
void delsllist(sllist *ptr)
{
    // if a current pointer is null, stop
    if (ptr == NULL);
    // otherwise, delete the rest of the list, and free the current node
    else
    {
        delsllist(ptr -> next);
        free(ptr);
    }
}