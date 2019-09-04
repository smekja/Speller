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

// Represents a trie
node *root;
node *ptr;

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
    FILE *file = fopen(dictionary, "r");
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
        for (int i = 0, position = 0; i < strlen(word); i++)
        {
            // Checking if the character is apostrophe
            if (word[i] == '\'')
            {
                // Assigning position in the trie
                position = word[i] - 13;
            }

            // Checking if the character is alphabetical
            if (isalpha(word[i]) != 0)
            {
                // Assigning position in the trie
                position = word[i] - 97;
            }

            // Checking if children is NULL, meaning not used yet
            if (ptr->children[position] == NULL)
            {
                // Making a new node
                node n* = malloc(sizeof(node));

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

                // Assigning a pointer to the new node at the children position
                ptr->children[position] = n;

                // Updating root with the first letter, but only with the first
                if (i == 0)
                {
                    root = ptr;
                }

                // Marking the end of the word
                if (i == strlen(word) - 1)
                {
                    ptr->is_word = true;
                }

                // Changing pointer so that it points at the new node
                else
                {
                     ptr = n;
                }

            }

            // If children is not NULL
            else
            {
                // Marking the end of the word
                if (i == strlen(word) - 1)
                {
                    ptr->is_word = true;
                }

                // Moving to the next node, if it is not the end of the word
                else
                {
                ptr = ptr->children[position];
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
    // TODO
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    fclose(file);
    return false;
}

