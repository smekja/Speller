// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "dictionary.h"
#include <cs50.h>

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

void destroy(node *tmp);
// Represents a trie
node *root;
node *ptr;
FILE *file = NULL;
int position = 0, x = 0;
unsigned int counter = 0;



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // Initializing ptr
        ptr = root;

        // Going trough characters of the word
        for (int i = 0; i < strlen(word); i++)
        {
            // Getting position of the character
            get_position(word[i]);
            // Checking if children is NULL, meaning not used yet
            if (ptr->children[position] == NULL)
            {
                // Making a new node
                node *n = malloc(sizeof(node));

                // Checking if n is NULL
                if (!n)
                {
                return 1;
                }

                // Setting the new node´s children to zero
                for (int j = 0; j < N; j++)
                {
                    n->children[j] = NULL;
                }

                // Setting is_word to false
                n->is_word = false;

                ptr->children[position] = n;
                ptr = n;

                // Marking the end of the word
                if (i == strlen(word) - 1)
                {
                    ptr->is_word = true;
                    counter++;
                }
            }

            // If children is not NULL, meaning already used
            else
            {
                // Moving to the next node
                ptr = ptr->children[position];

                // Marking the end of the word
                if (i == strlen(word) - 1)
                {
                    ptr->is_word = true;
                    counter++;
                }
            }

        }

    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (counter > 0)
    {
        return counter;
    }

    else
    {
        return 0;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Initializing ptr
    ptr = root;
    // For every letter of the word
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        // Getting position of the character
        get_position(word[i]);

        // If NULL - word is not in dictionary = is misspelled
        if (ptr->children[position] == NULL)
        {
            return false;
        }

        // Moving to the next node
        else
        {
            ptr = ptr->children[position];
        }


        // Checking if the word is in dictionary
        if (i == length - 1)
        {
            if (ptr->is_word == true)
            {
                return true;
            }
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    destroy(root);
    return true;
}

// Gives character position in trie, case sensitive
int get_position(char index)
{
    // Checking if the character is apostrophe
    if (index == '\'')
    {
        // Assigning position in the trie
        position = index - 13;
        return position;
    }

    // Checking if the character is alphabetical
    else if (isalpha(index) != 0)
    {
        // Making sure it will be lower case output
        index = tolower(index);

        // Assigning position in the trie
        position = index - 'a';
        return position;
    }
    return 1;
}

void destroy(node *tmp)
{
     // Going through all the children nodes
    for (int i = 0, number = 0; i < N; i++)
    {
        // If children node is not NULL, destroy it (recursion)
        if (tmp->children[i] != NULL)
        {
            destroy(tmp->children[i]);
        }
    }

    // At this point all the children nodes should be NULL
    // Free current node
    free(tmp);
}

