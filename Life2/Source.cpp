#include<iostream>
#include<thread>
#include<chrono>
#include<random>
using namespace std;

random_device dev;
mt19937 rng(dev());
uniform_int_distribution<> gen32(0,1);

void first_gen(bool *massive[], int columns, int rows)
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			massive[i][j] = gen32(rng);
		}
	}
}
void print_array(bool* massive[], int columns, int rows)
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (massive[i][j])
				cout << '*';
			else
				cout << ' ';
			cout << ' ';
		}
		cout << '\n';
	}
}
int countNeighbours(bool* massive[], int x, int y, int columns, int rows)
{
	int count = 0;

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int current_column = x + i;
			int current_row = y + j;
			bool isInline = current_column >=0 && current_column < columns 
				&& current_row >=0 && current_row<rows;
			bool isSelf = (current_column == x && current_row == y);
			if (isInline && massive[current_column][current_row]&&!isSelf)
			{
				count++;
			}

		}
	}
	
	return count;
}
void copy_array(bool* source[], bool* dest[], int columns, int rows)
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			dest[i][j] = source[i][j];

		}
	}
}
void create_next_gen(bool* massive[], int columns, int rows)
{
	bool** temp_array = new bool* [columns];
	for (int i = 0; i < columns; i++)
	{
		temp_array[i] = new bool[rows];
	}
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			bool hasLife = massive[i][j];
			int count_of_neighbours = countNeighbours(massive, i, j, columns, rows);
			if (hasLife && (count_of_neighbours < 2 || count_of_neighbours>3))
				temp_array[i][j] = false;
			else if (!hasLife && count_of_neighbours == 3)
				temp_array[i][j] = true;
			else
				temp_array[i][j] = massive[i][j];
			cout << count_of_neighbours <<" ";
		}
		cout << "\n";
	}
	copy_array(temp_array, massive, columns, rows);
	for (int i = 0; i < columns; i++)
	{
		delete []temp_array[i];
	}
	delete[]temp_array;
}
int isAlive(bool* massive[], int columns, int rows)
{
	int count = 0;
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (massive[i][j] == true)
			{
				count++;
			}
		}
		
	}
	return count;
}
int main()
{
	int columns;
	int rows;
	cout << "Enter number of columns: ";
	cin >> columns;
	cout << "Enter number of rows: ";
	cin >> rows;
	bool** array = new bool* [columns];
	for (int i = 0; i < columns; i++)
	{
		array[i] = new bool[rows];
	}
	first_gen(array, columns, rows);

	while (true)
	{

		print_array(array, columns, rows);
		create_next_gen(array, columns, rows);
		this_thread::sleep_for(chrono::milliseconds(2000));
		system("cls");
	
		
		
	}
	print_array(array, columns, rows);
	return 0;
}