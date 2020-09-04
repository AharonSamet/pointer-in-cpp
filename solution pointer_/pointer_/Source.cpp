//Aaron Samet. 
//Exercise 8 - dynamic pointers;

#include <iostream>
using namespace std;

//The possible to choose between 0-7;
enum choices { EXIT, ADD, DELETE, PRINT, SEARCH, AVG_TRAVEL, AVG_STOPS, SHORTEST_TRAVEL };

//'Sort' to sort the array. (by sorting bubbles);
void sort(int**& buses, int& num_Buses, int line);

// 'prints' (case = 3) to print out the buses that are saved in the database;
void print(int** buses, int num_Buses);

//'search' (case = 4) to find if the number of the bus-line is in the array database;
int search(int** buses, int num_Buses, int line);

//'add_line'(case = 1) to add a line in the array;
void add_Line(int**& buses, int& num_Buses, int line, int stops, int duration_Of_Ride);

//'delete line'(case = 2) to delete information of a line;
void delete_Line(int**& buses, int& num_Buses, int line, int choice_0 = 1);

//'average_Travel' (case = 5) to calculate the average travel time;
float average_Travel(int** buses, int num_Buses);

//'average_Stops' (case = 6) to calculation the average number of stations;
float average_Stops(int** buses, int num_Buses);

//'shortest' (case = 7) to find the line with minimum travel time;
int shortest(int** buses, int num_Buses);

int main() {
	int** buses = NULL;
	int num_Buses = 0;
	int line;
	int stops;
	int duration_Of_Ride;
	int choice;
	//bool Temp = true;

	do {
		cout << "enter 0-7 (EXIT, ADD, DELETE, PRINT, SEARCH, AVG_TRAVEL, AVG_STOPS, SHORTEST_TRAVEL)" << endl;
		cin >> choice;
		switch (choice) {
		case ADD: // add a line to the array of buses
			cout << "enter the line to add" << endl;
			cin >> line;
			cout << "enter the number of stops" << endl;
			cin >> stops;
			cout << "enter the duration of the ride" << endl;
			cin >> duration_Of_Ride;


			if (num_Buses == 0)
			{
				num_Buses++;

				buses = new int* [1];
			}
			else
			{
				num_Buses++;
			}
			add_Line(buses, num_Buses, line, stops, duration_Of_Ride);
			sort(buses, num_Buses, line);

			print(buses, num_Buses);
			break;

		case DELETE:	// delete a line from the array of buses					cout << "enter the line to delete" << endl;

			cout << "enter the line to delete" << '\n';
			cin >> line;

			delete_Line(buses, num_Buses, line);
			print(buses, num_Buses);
			break;
		case PRINT: // print all lines

			print(buses, num_Buses);
			break;
		case SEARCH: // search for a particular line
			cout << "enter the line to search for" << endl;
			cin >> line;
			cout << search(buses, num_Buses, line) << endl;
			break;
		case AVG_TRAVEL: // calculate average travel time of all buses
			cout << average_Travel(buses, num_Buses) << endl;
			break;
		case AVG_STOPS:  // calcuate average stops of all buses
			cout << average_Stops(buses, num_Buses) << endl;
			break;
		case SHORTEST_TRAVEL:// calculate the bus with the shortest travel time
			cout << shortest(buses, num_Buses) << endl;
			break;
		case EXIT: break;   // exit the program

		default:  cout << "ERROR" << endl;
		}// switch
	} while (choice != 0);
	if (choice == 0)
	{
		int temp = num_Buses;
		for (int i = 0; i < temp; i++)
		{
			delete_Line(buses, num_Buses, *(*(buses + num_Buses - 1) + 0), 0);
			num_Buses--;
		}
	}
	for (int i = 0; i < num_Buses; i++)
	{
		delete[] buses[i];
	}
	if (num_Buses > 0)
	{
		delete[] buses;
	}
		system("pause");
	return 0;
}
//------------------------------------------------------------------------------------------------------
void sort(int**& buses, int& num_Buses, int line)
{
	bool flag = true;
	int i = 1;
	while (flag)
	{
		flag = false;
		for (int j = 0; j < num_Buses - i; j++)
		{
			if (*(*(buses + j) + 0) > * (*(buses + j + 1) + 0))
			{
				int* temp = new int[3];
				*(temp + 0) = *(*(buses + j) + 0);
				*(temp + 1) = *(*(buses + j) + 1);
				*(temp + 2) = *(*(buses + j) + 2);

				*(*(buses + j) + 0) = *(*(buses + j + 1) + 0);
				*(*(buses + j) + 1) = *(*(buses + j + 1) + 1);
				*(*(buses + j) + 2) = *(*(buses + j + 1) + 2);

				*(*(buses + j + 1) + 0) = *(temp + 0);
				*(*(buses + j + 1) + 1) = *(temp + 1);
				*(*(buses + j + 1) + 2) = *(temp + 2);

				delete[]temp;

				flag = true;

			}
		}
		i++;
	}
}
//------------------------------------------------------------------------------------------------------
void print(int** buses, int num_Buses)
{
	if (num_Buses == 0) {
		return;
	}
	else
	{

		for (int i = 0; i < num_Buses; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << *(*(buses + i) + j) << " ";
			}
			cout << endl;
		}
	}
}
//------------------------------------------------------------------------------------------------------
int search(int** buses, int num_Buses, int line) {
	int i = 0;
	bool A = false;
	for (i; i < num_Buses; i++)
	{
		if (*(*(buses + i) + 0) == line)
		{
			A = true;
			break;
		}
	}
	if (A)
	{
		return i;
	}
	else
	{
		return -1;
	}


}
//------------------------------------------------------------------------------------------------------
void add_Line(int**& buses, int& num_Buses, int line, int stops, int duration_Of_Ride) {
	if (num_Buses > 1)
	{
		int** help = new int* [num_Buses];
		for (int i = 0; i < num_Buses; i++)
		{
			*(help + i) = new int[3];
		}
		for (int i = 0; i < (num_Buses - 1); i++)
		{

			*(*(help + i) + 0) = *(*(buses + i) + 0);
			*(*(help + i) + 1) = *(*(buses + i) + 1);
			*(*(help + i) + 2) = *(*(buses + i) + 2);

		}

		*(*(help + (num_Buses - 1)) + 0) = line;
		*(*(help + (num_Buses - 1)) + 1) = stops;
		*(*(help + (num_Buses - 1)) + 2) = duration_Of_Ride;
		if (num_Buses > 1) {
			for (int i = 0; i < num_Buses - 1; i++)
			{
				delete[]buses[i];
			}
		}
		delete[]buses;
		buses = new int* [num_Buses];
		for (int i = 0; i < num_Buses; i++)
		{
			*(buses + i) = new int[3];
		}
		for (int i = 0; i < num_Buses; i++)
		{
			*(*(buses + i) + 0) = *(*(help + i) + 0);
			*(*(buses + i) + 1) = *(*(help + i) + 1);
			*(*(buses + i) + 2) = *(*(help + i) + 2);


		}

		for (int i = 0; i < num_Buses - 1; i++)
		{
			delete[]help[i];
		}
		delete[]help;


	}
	else
	{
		*(buses + num_Buses - 1) = new int[3];
		*(*(buses + (num_Buses - 1)) + 0) = line;
		*(*(buses + (num_Buses - 1)) + 1) = stops;
		*(*(buses + (num_Buses - 1)) + 2) = duration_Of_Ride;
	}
}
//------------------------------------------------------------------------------------------------------
void delete_Line(int**& buses, int& num_Buses, int line, int choice_0) {
	int i = search(buses, num_Buses, line);

	if (i >= 0)//i != (-1)
	{

		if (i + 1 != num_Buses)
		{
			*(*(buses + i) + 0) = *(*(buses + (num_Buses - 1)) + 0);
			*(*(buses + i) + 1) = *(*(buses + (num_Buses - 1)) + 1);
			*(*(buses + i) + 2) = *(*(buses + (num_Buses - 1)) + 2);

			int* temp3;
			temp3 = *(buses + (num_Buses - 1));
			delete[]temp3;

		}

		else
		{
			int* temp3;

			temp3 = *(buses + num_Buses - 1);

			delete[]temp3;

		}
		if (choice_0 != 0)
		{
			num_Buses--;
			sort(buses, num_Buses, line);

		}


	}


}
//------------------------------------------------------------------------------------------------------
float average_Travel(int** buses, int num_Buses) {
	float sum = 0;
	//int *duration_of_Ride = *(buses + 2);
	for (int i = 0; i < num_Buses; i++)
	{
		sum += *(*(buses + i) + 2);
	}

	return sum / num_Buses;

}
//------------------------------------------------------------------------------------------------------
float average_Stops(int** buses, int num_Buses) {

	float sum = 0;
	for (int i = 0; i < num_Buses; i++)
	{
		sum += *(*(buses + i) + 1);
	}

	return sum / num_Buses;
}
//------------------------------------------------------------------------------------------------------
int shortest(int** buses, int num_Buses) {
	if (num_Buses == 0)
	{
		return -1;
	}
	else
	{
		int minimum = *(*(buses + 0) + 2);
		int line_minimum = *(*(buses + 0) + 0);
		for (int i = 1; i < num_Buses; i++)
		{
			if (*(*(buses + i) + 2) <= minimum)
			{
				minimum = *(*(buses + i) + 2);
				line_minimum = *(*(buses + i) + 0);

			}
		}
		return line_minimum;
	}


}
//------------------------------------------------------------------------------------------------------
/*
										******Example Running the program with all options******
enter 0-7
1                          //to add new line;
enter the line to add
1
enter the number of stops
1
enter the duration of the ride
1
1 1 1

enter 0-7
1                          //to add new line;
enter the line to add
3
enter the number of stops
3
enter the duration of the ride
3
1 1 1
3 3 3

enter 0-7
1                          //to add new line;
enter the line to add
5
enter the number of stops
5
enter the duration of the ride
5
1 1 1
3 3 3
5 5 5

enter 0-7
1                          //to add new line;
enter the line to add
2
enter the number of stops
2
enter the duration of the ride
2
1 1 1
2 2 2
3 3 3
5 5 5

enter 0-7
1                          //to add new line;
enter the line to add
4
enter the number of stops
4
enter the duration of the ride
4
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5

enter 0-7
1                          //to add new line;
enter the line to add
6
enter the number of stops
6
enter the duration of the ride
6
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5
6 6 6


enter 0-7
5555                          //  Shows the default;
ERROR


enter 0-7
1645                         //  Shows the default;
ERROR

enter 0-7
2                           //to delete a line;
enter the line to delete
4
1 1 1
2 2 2
3 3 3
5 5 5
6 6 6

enter 0-7
3                    //to print;
1 1 1
2 2 2
3 3 3
5 5 5
6 6 6

enter 0-7
4                     //to search a line
enter the line to search for
2
1               //it in index number 1....

enter 0-7
5            // to calculate the average travel time;
3.4

enter 0-7
6                 //   to calculation the average number of stations;
3.4

enter 0-7
1                             //to add a line;
enter the line to add
1
enter the number of stops
2
enter the duration of the ride
3
1 1 1
1 2 3
2 2 2
3 3 3
5 5 5
6 6 6

enter 0-7
2                             //to delete a line;
enter the line to delete
6
1 1 1
1 2 3
2 2 2
3 3 3
5 5 5

enter 0-7
2                            //to delete a line;
enter the line to delete
5
1 1 1
1 2 3
2 2 2
3 3 3

enter 0-7
2                                   //to delete a line;
enter the line to delete
1
1 2 3
2 2 2
3 3 3

enter 0-7
2                                 //to delete a line;
enter the line to delete
1
2 2 2
3 3 3

enter 0-7
2                             //to delete a line;
enter the line to delete
2
3 3 3

enter 0-7
2                           //to delete a line;
enter the line to delete
3

enter 0-7
1                          //to add new line;
enter the line to add
1
enter the number of stops
2
enter the duration of the ride
3
1 2 3

enter 0-7
1                          //to add new line;
enter the line to add
4
enter the number of stops
5
enter the duration of the ride
6
1 2 3
4 5 6

enter 0-7
1                          //to add new line;
enter the line to add
7
enter the number of stops
8
enter the duration of the ride
9
1 2 3
4 5 6
7 8 9

enter 0-7
4                          //to search;
enter the line to search for
1
0

enter 0-7
5                                //to calculate the average travel time;
6

enter 0-7
6                   // to calculation the average number of stations;
5


enter 0-7
7
1

enter 0-7
0                        //exit;
Press any key to continue . . .

*/
