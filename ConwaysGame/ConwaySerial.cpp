//This is the serialized code
//by J. Shane Johnson
//The array that is displayed to the user is 100 x 100, but actual size
//of the array is 102 x 102.  The reason for this is to make the 
//calculations easier for the cells on the outermost "frame" of the grid.



#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

using namespace std;

//Copies one array to another.
void copy(int array1[102][102], int array2[102][102])
{
	for (int j = 0; j < 102; j++)
	{
		for (int i = 0; i < 102; i++)
			array2[j][i] = array1[j][i];
	}
}

//The life function is the most important function in the program.
//It counts the number of cells surrounding the center cell, and 
//determines whether it lives, dies, or stays the same.
void life(int array[102][102], char choice)
{
	//Copies the main array to a temp array so changes can be entered into a grid
	//without effecting the other cells and the calculations being performed on them.
	int temp[102][102];
	copy(array, temp);
	for (int j = 1; j < 101; j++)
	{
		for (int i = 1; i < 101; i++)
		{
			if (choice == 'm')
			{
				//The Moore neighborhood checks all 8 cells surrounding the current cell in the array.
				int count = 0;
				
				count = array[j - 1][i] +
					array[j - 1][i - 1] +
					array[j][i - 1] +
					array[j + 1][i - 1] +
					array[j + 1][i] +
					array[j + 1][i + 1] +
					array[j][i + 1] +
					array[j - 1][i + 1];
				//The cell dies.
				if (count < 2 || count > 3)
					temp[j][i] = 0;
				//The cell stays the same.
				if (count == 2)
					temp[j][i] = array[j][i];
				//The cell either stays alive, or is "born".
				if (count == 3)
					temp[j][i] = 1;
			}
		}
	}
	//Copies the completed temp array back to the main array.
	copy(temp, array);
}

//Checks to see if two arrays are exactly the same. 
//This is used to end the simulation early, if it 
//becomes stable before the 100th generation. Unfortunately this did not happen in my trials
//and instead just stabilized into a blinking effect after so many generations.
bool compare(int array1[102][102], int array2[102][102])
{
	int count = 0;
	for (int j = 0; j < 102; j++)
	{
		for (int i = 0; i < 102; i++)
		{
			if (array1[j][i] == array2[j][i])
				count++;
		}
	}

	//an easy way to check if the two arrays are equal is to compare the count to 
	//the dimensions of the array multiplied together.
	if (count == 102 * 102)
		return true;
	else
		return false;
}

//This function prints the array. A live cell is marked
//by a '*', and a dead or vacant cell by a ' '.
void print(int array[102][102])
{
	for (int j = 1; j < 101; j++)
	{
		for (int i = 1; i < 101; i++)
		{
			if (array[j][i] == 1)
				cout << '*';
			else
				cout << ' ';
		}
		cout << endl;
	}
}

int main()
{
	int gen0[102][102];
	int todo[102][102];
	int backup[102][102];
	char neighborhood;
	char again;
	char cont;
	bool comparison;
	string decoration;
	time_t start, end;

	//Introduction that prints out to the user
	cout << endl << "This program is a C++ implementation of John Conway's Game of Life."
		<< endl << "With it, you can simulate how \"cells\" interact with each other." << endl;
	
	time(&start);
	//Loop to check if user wants to keep simulating.
	do
	{
		//Loop to check for proper inputs.
		do
		{
			cout << "Please press m to begin: ";
			cin >> neighborhood;
		} while (neighborhood != 'm');
		
		int i = 0;

		//Loop that does the bulk of the simulation.
		do
		{
			
			//Generates the initial random state of the game board.
			srand(time(NULL));

			//The actual array is 102 x 102, but it's easier to just leave the surrounding part of
			//the array blank so it doesn't effect the calculations in the life function above.
			for (int j = 1; j < 101; j++)
			{
				for (int i = 1; i < 101; i++)
					gen0[j][i] = rand() % 2;
			}
			//Determines how big the decoration should be.
			if (i < 10)
				decoration = "#############";
			else if (i >= 10 && i < 100)
				decoration = "##############";
			else if (i >= 100 && i < 1000)
				decoration = "###############";
			else if (i >= 1000 && i < 10000)
				decoration = "################";
			else
				decoration = "#################";
			//Prints the generation.  If i == 0, the gen0 array is copied to the 
			//todo array, and is printed before any functions act upon it.
			cout << decoration << endl << "Generation " << i
				<< ":" << endl << decoration << endl << endl;
			//Initializes the arrays by copying the gen0 array to the todo array.
			if (i == 0)
				copy(gen0, todo);
			copy(todo, backup);
			print(todo);
			life(todo, neighborhood);
			i++;

			//Checks whether the generation is a multiple of 100 to ask 
			//the user if they want to continue the simulation. 
			if (i % 100 == 1 && i != 1)
			{
				cout << endl;
				//Loop to check for proper inputs.
				do
				{
					cout << "Would you like to continue this simulation? (y/n): ";
					cin >> cont;
				} while (cont != 'y' && cont != 'n');
				if (cont == 'n')
					break;
			}
			
			//Compares the current generation with a backup generation.
			//the system repeats the process until they are
			//the same or the user chooses to quit.
			comparison = compare(todo, backup);
			if (comparison == true)
				cout << endl;
				
		
		} while (comparison == false);
		//Loop to check for proper inputs.
		do
		{
			cout << "Would you like to run another simulation? (y/n): ";
			cin >> again;
		} while (again != 'y' && again != 'n');
	} while (again == 'y');
	time(&end);
	double diff;
	diff = difftime(end, start) * 1000;
	printf("Time to Complete Simulation:  %f  MilliSeconds\n", diff);
	Sleep(10000);
	return 0;
}