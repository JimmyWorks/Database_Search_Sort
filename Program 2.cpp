//============================================================================
// Name        : Database Searching and Sorting Through Parallel Arrays
// Author      : Jimmy Nguyen
// Version     :
// Copyright   : 
// Description : This is a program that will perform sorting and searching across records stored in a file.
//				The program will first query the user for a filename. The program will open the file and read
//				the first entry. It defines the number of records in the file. The program will read each record
//				and store it into memory. Each record in the file will have sets of three lines. Each set consists of:
//				last name, first name, and birthdate.

//				The program will prompt the user for a command:

//				Searching - The user will input a search value and the program will
//				print any entries that start with that value. Searching available by first name, last name
//				and birthdates. There may be multiple values returned.

//				Sorting - The user will be able to choose to print the data in its original unsorted form,
//				sorted by first name, or sorted by last name.

//				Quit – Exit the program
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

void FirstNameSearch(string *, string *, string *, int);
void LastNameSearch(string *, string *, string *, int);
void BirthdateSearch(string *, string *, string *, int);

void FirstNameSort(string *, string *, string *, int);
void LastNameSort(string *, string *, string *, int);

int main() {

	//Declare Variables
	string inputfile_name; 	//declare name-holders for input and output files
	ifstream inputfile;  	//declare input and output file stream
	int elements;			//number of elements in each array

//============================Loading Input File===============================
	//Prompt User to Enter the Name for the Input File
	askinput:  														// Goto if the user defines an improper input file
		cout << "Please enter the input file name: " << endl;
		cin >> inputfile_name;
		cout << "The user entered file name: " << inputfile_name << endl;

	//Open the input file for reading.
		inputfile.open(inputfile_name.c_str());

	//Check if we successfully opened input file.
		if (!inputfile){

			cout << "Error: Unable to open file '" << inputfile_name << "' for reading." << endl;
			cout << "Please try again." << endl << endl;
			goto askinput;
		}

		//Pull Number of Elements in Each Array
		inputfile >> elements;

		//Check for Errors
		if(elements < 1){
				cout << "Error: '" << inputfile_name << "' wants to create a list of '" << elements << "' records.\n" << "At least 1 record or more is required." << endl;
				cout << "Closing file '" << inputfile_name << "'.  Please try again below." << endl << endl;
				inputfile.close();
				goto askinput;
			}

				cout << "Successfully opened the input file!" << endl << endl << endl;

		//Use Dynamic Memory Allocation to Declare Arrays (for Creating Arrays of Unknown Length)
		string *lastnameArray = new string[elements];
		string *firstnameArray = new string[elements];
		string *birthdateArray = new string[elements];
		string *lastnameArraySorted = new string[elements];
		string *firstnameArraySorted = new string[elements];
		string *birthdateArraySorted = new string[elements];
		//First three arrays are for searching specific record and printing out original unsorted data.
		//Second three arrays are for sorting by first and last name.

		//Fill Arrays with Data from Input File
		for(int i=0; i < elements; i++){
			inputfile >> lastnameArray[i];
			lastnameArraySorted[i] = lastnameArray[i];
			inputfile >> firstnameArray[i];
			firstnameArraySorted[i] = firstnameArray[i];
			inputfile >> birthdateArray[i];
			birthdateArraySorted[i] = birthdateArray[i];
		}

		//Check if Arrays are Filled with Correct Data
		cout << "Uploaded the following database values:" << endl << endl;
		for(int i=0; i < elements; i++){
					cout << lastnameArray[i] << endl;
					cout << firstnameArray[i] << endl;
					cout << birthdateArray[i] << endl;
				}

		cout << endl << "Upload Successful!" << endl << endl;

//============================Navigating the GUI===============================

		int userinput = -1; //Initialized sentinel for errors

		//Ask User What They Want to Do
		page1:
		cout << "Please select one of the following options:" << endl << endl;
		cout << "\t1 - Search Record" << endl << endl;
		cout << "\t2 - Sort Database" << endl << endl;
		cout << "\t3 - Exit Program" << endl << endl << endl;
		cout << "Please enter corresponding number and hit enter." << endl;
		cin >> userinput;

		//Send User to Corresponding Page (and Check for Valid Input)
		switch(userinput){
		case 1:goto Search;
		case 2:goto Sort;
		case 3:goto Exit;
		default:cout << endl << "You have made an invalid selection.  Please try again." << endl;
				userinput=-1;
				goto page1;
		}
//============================  Searching  ===============================
		//Ask User What They Want to Search For
		Search:
		cout << endl << "You have selected to search records." << endl << "Please select from the following:" << endl << endl;

		cout << "\t1 - Search by First Name" << endl << endl;
		cout << "\t2 - Search by Last Name" << endl << endl;
		cout << "\t3 - Search by Birthdate" << endl << endl;
		cout << "4 - Main Menu             5 - Exit Program" << endl << endl << endl;
		cout << "Please enter corresponding number and hit enter." << endl;
		cin >> userinput;

		//Send User to Corresponding Search Type
		switch(userinput){
		//case 1:goto FirstNameSearch;
		case 1: FirstNameSearch(firstnameArray, lastnameArray, birthdateArray, elements);
				break;
		case 2: LastNameSearch(firstnameArray, lastnameArray, birthdateArray, elements);
				break;
		case 3: BirthdateSearch(firstnameArray, lastnameArray, birthdateArray, elements);
				break;
		case 4:userinput=-1;
			   goto page1;
		case 5:goto Exit;
		default:cout << endl << "You have made an invalid selection.  Please try again." << endl;
				userinput=-1;
		}
		goto Search;

//============================  Sorting  ===============================
		Sort:
		cout << endl << "You have selected to sort records." << endl << "Please select from the following:" << endl << endl;

		cout << "\t1 - Alphabetize by First Name" << endl << endl;
		cout << "\t2 - Alphabetize by Last Name" << endl << endl;
		cout << "\t3 - Print Original Unsorted Database" << endl << endl;
		cout << "4 - Main Menu             5 - Exit Program" << endl << endl << endl;
		cout << "Please enter corresponding number and hit enter." << endl;
		cin >> userinput;

		//Send User to Corresponding Sort Type
		switch(userinput){
		case 1: cout << endl << endl;
				FirstNameSort(firstnameArraySorted, lastnameArraySorted, birthdateArraySorted, elements);
				break;
		case 2: cout << endl << endl;
				LastNameSort(firstnameArraySorted, lastnameArraySorted, birthdateArraySorted, elements);
				break;
		case 3: cout << endl << endl;
				for(int i=0; i<elements; i++)
					cout << lastnameArray[i] << ", " << firstnameArray[i] << " " << birthdateArray[i] << endl;
				break;
		case 4:userinput=-1;
			   goto page1;
		case 5:goto Exit;
		default:cout << endl << "You have made an invalid selection.  Please try again." << endl;
				userinput=-1;
		}
		goto Sort;

//============================End Program===============================
		Exit:
		cout << endl << endl << "Ending Program... Thank you for using Database - Search and Sort!" << endl << endl;
		cout << "Written by: Jimmy Nguyen." << endl;
		cout << "For all questions, email: Jimmy@JimmyWorks.net" << endl;

//============================Delete All Dynamically Created Arrays===============================
		delete [] lastnameArray;
		delete [] firstnameArray;
		delete [] birthdateArray;
		delete [] lastnameArraySorted;
		delete [] firstnameArraySorted;
		delete [] birthdateArraySorted;

	return 0;
}

void FirstNameSearch(string *firstnameArray, string *lastnameArray, string *birthdateArray, int elements){
		string findname = "error";
		cout << endl << "Searching by first name.  Please enter name (no spaces):" << endl;
		cin >> findname;
		cout << endl << endl;

		int total = 0;
		for(int i=0; i<elements; i++){
			int result = -1;
			result = firstnameArray[i].find(findname);
			if(result>=0){
				cout << firstnameArray[i] << " " << lastnameArray[i] << " " << birthdateArray[i] << endl;
				total++;
			}
		}
		cout << endl << endl << total << " result(s) found!" << endl << endl;

		return;
}

void LastNameSearch(string *firstnameArray, string *lastnameArray, string *birthdateArray, int elements){
		string findname = "error";
			cout << endl << "Searching by last name.  Please enter name (no spaces):" << endl;
			cin >> findname;
			cout << endl << endl;

			int total = 0;
			for(int i=0; i<elements; i++){
				int result = -1;

				result = lastnameArray[i].find(findname);
				if(result>=0){
					cout << firstnameArray[i] << " " << lastnameArray[i] << " " << birthdateArray[i] << endl;
					total++;
				}
			}
			cout << endl << endl << total << " result(s) found!" << endl << endl;

			return;
}
void BirthdateSearch(string *firstnameArray, string *lastnameArray, string *birthdateArray, int elements){
	string inputdate = "error";
		cout << endl << "Searching by birthdate.  Please enter numeric day, month or year or full birthdate (DD/MM/YYYY):" << endl;
		cin >> inputdate;
		cout << endl << endl;

		int total = 0;
		for(int i=0; i<elements; i++){
			int result = -1;

			result = birthdateArray[i].find(inputdate);
			if(result>=0){
				cout << firstnameArray[i] << " " << lastnameArray[i] << " " << birthdateArray[i] << endl;
				total++;
			}
		}
		cout << endl << endl << total << " result(s) found!" << endl << endl;

		return;
}

void FirstNameSort(string *firstnameArraySorted, string *lastnameArraySorted, string *birthdateArraySorted, int elements){
	bool swap;
	do{
		swap = false;
		for(int i=0; i<(elements-1); i++){
			if(firstnameArraySorted[i]>firstnameArraySorted[i+1]){

				string temp = firstnameArraySorted[i];
				firstnameArraySorted[i]=firstnameArraySorted[i+1];
				firstnameArraySorted[i+1]=temp;

				string temp2 = lastnameArraySorted[i];
				lastnameArraySorted[i]=lastnameArraySorted[i+1];
				lastnameArraySorted[i+1]=temp2;

				string temp3 = birthdateArraySorted[i];
				birthdateArraySorted[i]=birthdateArraySorted[i+1];
				birthdateArraySorted[i+1]=temp3;
				swap = true;
			}
		}

	}while(swap);

	for(int i=0; i<elements; i++){
		cout << firstnameArraySorted[i] << " " << lastnameArraySorted[i] << " " << birthdateArraySorted[i] << endl;
	}

	cout << endl << endl;

	return;
}
void LastNameSort(string *firstnameArraySorted, string *lastnameArraySorted, string *birthdateArraySorted, int elements){
	bool swap;
		do{
			swap = false;
			for(int i=0; i<(elements-1); i++){
				if(lastnameArraySorted[i]>lastnameArraySorted[i+1]){

					string temp = firstnameArraySorted[i];
					firstnameArraySorted[i]=firstnameArraySorted[i+1];
					firstnameArraySorted[i+1]=temp;

					string temp2 = lastnameArraySorted[i];
					lastnameArraySorted[i]=lastnameArraySorted[i+1];
					lastnameArraySorted[i+1]=temp2;

					string temp3 = birthdateArraySorted[i];
					birthdateArraySorted[i]=birthdateArraySorted[i+1];
					birthdateArraySorted[i+1]=temp3;
					swap = true;
				}
			}

		}while(swap);

		for(int i=0; i<elements; i++){
			cout << lastnameArraySorted[i] << ", " << firstnameArraySorted[i] << " " << birthdateArraySorted[i] << endl;
		}

		cout << endl << endl;

	return;
}
