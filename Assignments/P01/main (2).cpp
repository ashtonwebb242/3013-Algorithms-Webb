/**************************************************************************************
*                    
*  Author:           Ashton Webb
*  Email:            ashtonwebb46@gmail.com 
*  Label:            P01
*  Title:            Resizing the Stack
*  Course:           CMPS 3013
*  Semester:         Spring 2022
* 
* Description:
*      This program has a resizable stack and reads in numbers from a file. Whether the number is even or odd
       decides whether or not numbers are pushed onto the stack or popped off
*

*      
* 
**************************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Writes header to output file
void write_headers(ofstream &);

void print_config_params(ofstream &output_file, double tooFullThreshold, double tooEmptyThreshold, double enlargeThreshold, double shrinkThreshold);

void print_other_data(ofstream &output_file, int processedCommands, int maxSize, int endSize, int timesResized);
/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack
{
private:
    int *A;   // pointer to array of int's
    int size; // current max stack size
    int minSize;
    int top; // top of stack
    int timesResized = 0;

    double tooFullThreshold;
    double tooEmptyThreshold;
    double enlargeThreshold;
    double shrinkThreshold;

    int maxSize;

    // top = number of items in the stack + 1
    // size = array size

    // size = 100
    // (top + 1) / size

public:
    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack()
    {
        size = 10;
        minSize = 10;
        maxSize = minSize;
        A = new int[size];
        top = -1;

        double tooFullThreshold = 1.0;
        double tooEmptyThreshold = 0.15;
        double enlargeThreshold = 2.0;
        double shrinkThreshold = 0.5;
    }

    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack(int s)
    {
        size = s;
        minSize = 10;
        maxSize = minSize;
        A = new int[s];
        top = -1;

        double tooFullThreshold = 1.0;
        double tooEmptyThreshold = 0.15;
        double enlargeThreshold = 2.0;
        double shrinkThreshold = 0.5;
    }

    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor to allow control over stack growing and shrinking
  * 
  * Params:
  *     - int tooFull, tooEmpty, enlarge, shrink
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack(double tooFull, double tooEmpty, double enlarge, double shrink)
    {
        size = 10;
        minSize = 10;
        maxSize = minSize;
        A = new int[size];
        top = -1;

        tooFullThreshold = tooFull;
        tooEmptyThreshold = tooEmpty;
        enlargeThreshold = enlarge;
        shrinkThreshold = shrink;
    }

    /**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
    bool Empty()
    {
        return (top <= -1);
    }

    /**
  * Public bool: Full
  * 
  * Description:
  *      Stack full?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
    bool Full()
    {
        return (top >= size - 1);
    }

    /**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Peek()
    {
        if (!Empty())
        {
            return A[top];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Pop()
    {
        if (!Empty())
        {
            int toReturn = A[top--];
            checkResize();
            return toReturn;
        }

        return -99; // some sentinel value
                    // not a good solution 
    }

    /**
  * Public void: Print
  * 
  * Description:
  *      Prints stack to standard out
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void Print()
    {
        for (int i = 0; i <= top; i++)
        {
            cout << A[i] << " ";
        }
        cout << endl;
    }

    /**
  * Public bool: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      [bool] ; success = true
  */
    bool Push(int x)
    {
        if (Full())
        {
            ContainerGrow();
        }
        if (!Full())
        {
            A[++top] = x;

            checkResize();
            return true;
        }

        return false;
    }

    /**
  * Public void: ContainerGrow
  * 
  * Description:
  *      Resizes the container for the stack by shriniking its capacity as per enlargeThreshold
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void ContainerGrow()
    {
        timesResized++;
        int newSize = size * enlargeThreshold; // double size of original
        int *B = new int[newSize];             // allocate new memory
        maxSize = max(maxSize, newSize);

        for (int i = 0; i <= top; i++)
        { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

        A = B; // reset array pointer
    }

    /**
  * Public void: ContainerShrink
  * 
  * Description:
  *      Resizes the container for the stack by shriniking its capacity as per shrinkThreshold
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void ContainerShrink()
    {
        timesResized++;
        int newSize = size - size * shrinkThreshold; // double size of original
        newSize = max(newSize, minSize);
        int *B = new int[newSize]; // allocate new memory

        for (int i = 0; i <= top; i++)
        { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size
        A = B;          // reset array pointer
    }

    /**
  * Public void: checkResize
  * 
  * Description:
  *      checks if stack's size is within the thresholds
  *      and calls the appropriate resize function
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void checkResize()
    {
        if (size * tooFullThreshold <= top + 1)
        {
            ContainerGrow();
        }
        else if (size * tooEmptyThreshold >= top + 1)
        {
            ContainerShrink();
        }
    }

    int getMaxSize()
    {
        return maxSize;
    }

    int getSize()
    {
        return size;
    }

    int getTimesResized()
    {
        return timesResized;
    }
};

// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char **argv)
{
    // put command line arguments in a vector
    vector<string> args(argv + 1, argv + argc);

    // set default values for command line params
    double tooFullThreshold = 1.0;
    double tooEmptyThreshold = 0.15;
    double enlargeThreshold = 2.0;
    double shrinkThreshold = 0.5;

    // if command line arguments are present
    if (args.size() == 4)
    {
        // p command line arguments
        tooFullThreshold = stod(args[0]);
        tooEmptyThreshold = stod(args[1]);
        enlargeThreshold = stod(args[2]);
        shrinkThreshold = stod(args[3]);

        // check for valid values
        if (tooFullThreshold < 0.0 || tooFullThreshold > 1.0)
        {
            cout << "Invalid value for tooFullThreshold: " << tooFullThreshold << endl;
            return 1;
        }
        if (tooEmptyThreshold < 0.0 || tooEmptyThreshold > 1.0)
        {
            cout << "Invalid value for tooEmptyThreshold: " << tooEmptyThreshold << endl;
            return 1;
        }
        if (enlargeThreshold <= 1.0)
        {
            cout << "Invalid value for enlargeThreshold: " << enlargeThreshold << endl;
            return 1;
        }
        double maxAllowedShrinkThreshold = 1.0 - tooEmptyThreshold;
        if (shrinkThreshold > maxAllowedShrinkThreshold)
        {
            cout << "Invalid value for shrinkThreshold: " << shrinkThreshold << endl;
            return 1;
        }
    }

    // create a new stack
    ArrayStack stack(tooFullThreshold, tooEmptyThreshold, enlargeThreshold, shrinkThreshold);
    int r = 0;

    string input_file("nums_test.dat");
    string output_file("nums_test_out.dat");

    // open and read file line by line till eof
    ifstream infile(input_file);
    ofstream outfile(output_file);

    string line;
    int commandsProcessed = 0;
    while (!infile.eof())
    {
        int num;
        infile >> num;

        // if num is even, push it to stack
        if (num % 2 == 0)
        {
            stack.Push(num);
        }
        else
        {
            int val = stack.Pop();
        }
        commandsProcessed++;
    }

    write_headers(outfile);
    print_config_params(outfile, tooFullThreshold, tooEmptyThreshold, enlargeThreshold, shrinkThreshold);
    print_other_data(outfile, commandsProcessed, stack.getMaxSize(), stack.getSize(), stack.getTimesResized());

    infile.close();
    outfile.close();
}

// Function: write_headers
// Input: ofstream &, output file
// Description: writes headers to output file
//        headers are: Name, Program Name and Column Headings
void write_headers(ofstream &output_file)
{
    output_file << "######################################################################\n";
    output_file << "\tAssignment 4 - Resizing the Stack\n";
    output_file << "\tCMPS 3013\n";
    output_file << "\tAshton Webb\n\n";
}

void print_config_params(ofstream &output_file, double tooFullThreshold, double tooEmptyThreshold, double enlargeThreshold, double shrinkThreshold)
{
    output_file << "\tConfig Params: \n";
    output_file << "\t  Full Threshold: " << tooFullThreshold << endl;
    output_file << "\t  Shrink Threshold: " << tooEmptyThreshold << endl;
    output_file << "\t  Grow Ratio: " << enlargeThreshold << endl;
    output_file << "\t  Shrink Ratio: " << shrinkThreshold << endl << endl;
}

void print_other_data(ofstream &output_file, int processedCommands, int maxSize, int endSize, int timesResized) {
    output_file << "\tProcessed " << processedCommands << " commands.\n\n";
    output_file << "\tMax Stack Size: " << maxSize << endl;
    output_file << "\tEnd Stack Size: " << endSize << endl;
    output_file << "\tStack Resized: " << timesResized << " times.\n\n";
    output_file << "######################################################################\n";
}