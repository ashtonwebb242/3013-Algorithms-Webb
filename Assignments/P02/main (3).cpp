/**************************************************************************************
*                    
*  Author:           Ashton Webb
*  Email:            ashtonwebb46@gmail.com 
*  Label:            P02
*  Title:            Linear Dictionary Lookup
*  Course:           CMPS 3013
*  Semester:         Spring 2022
* 
* Description:
*    Allows the user type in a tring of letters a letter at a time, then searches a 
*      dictionary of words for possible matches. 
*
* Files: 
*      main.cpp
*      tempcolor.hpp
*      timer.hpp
*      dictionary.txt
*      
* 
**************************************************************************************/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"

using namespace std;

// Node for our linked list
struct wordNode
{
    string word;    // data value (could be a lot more values)
    wordNode *next; // we always need a "link" in a linked list

    wordNode(string x)
    { // cunstructor to make adding values easy
        word = x;
        next = NULL;
    }
};

// Linked list of nodes of type string to store dictionary
class WordList
{
private:
    wordNode *head; // base pointer of list

public:
    /**
     * @brief Default Constructor
     *
     * Creates a new Linked List object.
     *
     * @param void
     * @return void
     */
    WordList()
    {
        head = NULL; // NULL = zeros
                     // and zeros imply empty
    }

    /**
     * @brief Overloaded Constructor
     *
     * Creates a new Linked List object from
     * an array of values.
     *
     * @param int* A - array of values
     * @param int size - size of array
     *
     * @return void
     */
    WordList(vector<string> words)
    {
        head = NULL; // NULL = zeros
                     // and zeros imply empty

        for (int i = words.size() - 1; i >= 0; i--)
        {
            pushFront(words[i]);
        }
    }

    /**
     * @brief pushFront adds given word at front of linked list
     *
     * @param word word to add to linkedlist
     */
    void pushFront(string x)
    {
        wordNode *tempPtr = new wordNode(x); // create a new node and
                                             // add data to it

        if (!head)
        { // `!head` implies empty list
          // So does `head == NULL`

            head = tempPtr; // `head = tempPtr` places addrress of
                            // tempPtr in head (points head to tempPtr)
        }
        else
        {                         // list not empty
            tempPtr->next = head; // point tempPtr's next to what head points to
            head = tempPtr;       // now point head to tempPtr
        }
    }

    /**
     * @brief pushRear adds given word to end of linkedlist
     *
     * @param word word to add to linkedlist
     */
    void pushRear(string word)
    {
        wordNode *tempPtr = new wordNode(word);

        if (!head)
        {
            head = tempPtr;
        }
        else
        {
            wordNode *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = tempPtr;
        }
    }

    /**
     * @brief findMatches finds the words starting with a particular word
     *
     * @param word word to search in linkedlist
     * @return vector<string> words that match the criteria
     */
    vector<string> findMatches(string word)
    {
        vector<string> matches;
        // iterate over linked list
        wordNode *temp = head;
        while (temp != NULL)
        {
            // find if current word in linked list starts with given word
            if (temp->word.rfind(word, 0) != string::npos)
            {
                // if match found, add it to matches
                matches.push_back(temp->word);
            }
            // go to next node
            temp = temp->next;
        }
        return matches;
    }

    /** @brief Destructor
     *
     * @return void
     */
    ~WordList()
    {
        wordNode *temp = head;
        while (temp != NULL)
        {
            wordNode *temp2 = temp;
            temp = temp->next;
            delete temp2;
        }
    }
};

/**
 * Description:
 *      Given a file_name, returns number of lines in the file.
 * Params:
 *      string file_name - file to get the line count
 *
 * Returns:
 *      int - line count
 */
int CountLines(string file_name)
{
    ifstream inFile(file_name);
    return count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n');
}

/**
 * Description:
 *      Loads a file of strings (words, names, whatever) reading them in
 *      with one word per line. So words must be delimited by newlines '\n'
 * Params:
 *      string file_name - file to get the line count
 *
 * Returns:
 *      int - vector of words
 */
vector<string> LoadWords(string file_name)
{
    ifstream fin;                            // file to get words names
    int count = (CountLines(file_name) + 1); // get size of input file
    vector<string> array(count);             // allocate vector of correct size

    fin.open(file_name); // open file for reading

    // knowing the size of the file lets us treat
    // it like an array without using .push_back(value)
    for (int i = 0; i < count; i++)
    {
        fin >> array[i]; // read in animals
        for (auto &c : array[i])
        {                   // c++ 11 style loop
            c = tolower(c); // lowercase the word
        }
    }

    return array;
}

int main()
{
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    vector<string> words;   // vector of dictionary words
    vector<string> matches; // any matches found in vector of words
    int loc;                // location of substring to change its color

    Timer T;   // create a timer
    T.Start(); // start it

    // read words from file
    words = LoadWords("dictionary.txt");
    // create a linked list of words
    WordList list(words);

    T.End(); // end the current timer

    // get time in seconds using nanoseconds as T.Seconds() will return 0
    double seconds = T.NanoSeconds() / (1e9);
    // print out how long it took to load the animals file
    cout << "It took " << seconds << " seconds to load words in linkedlist" << endl;

    cout << "Start typing for word suggestions. Type capital Z to quit." << endl
         << endl;

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z')
    {
        T.Start(); // start it
        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127)
        {
            if (word.size() > 0)
            {
                word = word.substr(0, word.size() - 1);
            }
        }
        else
        {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k))
            {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97)
            {
                k += 32;
            }
            word += k; // append char to word
        }

        // Find any animals in the array that partially match
        // our substr word
        matches = list.findMatches(word);
        if ((int)k != 32)
        { // if k is not a space print it
            T.End();
            cout << termcolor::blue;
            cout << word << endl;

            seconds = T.NanoSeconds() / (1e9);
            cout << termcolor::magenta;
            cout << matches.size() << " words found in " << seconds << " seconds" << endl;
            // This prints out first 10 matches found n dictionary
            // matched characters in green color and rest in red color
            for (int i = 0; i < matches.size() && i < 10; i++)
            {
                for (int j = 0; j < matches[i].size(); j++)
                {
                    // green if matched charcter
                    if (j < word.size())
                    {
                        cout << termcolor::green;
                    }
                    else // else red character
                    {
                        cout << termcolor::red;
                    }
                    cout << matches[i][j];
                }
                cout << " ";
            }
            cout << termcolor::reset << endl
                 << endl;
        }
    }
    return 0;
}
