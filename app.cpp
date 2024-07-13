#include<iostream>
#include <string>
#include "List.h"
#include "LibStudent.h"

//#define current_date = 2458938;

using namespace std;

bool Redundant(List*, LibStudent);
bool ReadFile(string, List*);
bool DeleteRecord(List*, char*);
int menu();
bool SearchStudent(List*, char*, LibStudent&);
bool InsertBook(string, List*);
int calculateJulianDate(int, int, int);


int main() {
	List* stulist = new List();
	string filename;
	char a = 'Y';
	char stuID[10];
	LibStudent STU;
	do
	{
		switch (menu())
		{
		case 1:
		{
			filename = "student";
			if (!ReadFile(filename, stulist))
			{
				cout << "Unable to read file." << endl;
			}

			break;
		}
		case 2: {

			if (!DeleteRecord(stulist, stuID))
				cout << "This Student couldn't be found." << endl;
			break;
		}
		case 3: {

			if (!SearchStudent(stulist, stuID, STU))
				cout << "This Student couldn't be found." << endl;

			break;
		}
		case 4: {
			InsertBook("book.txt", stulist);
			break;
		}
		case 5: {
			//Display(stulist, 1, 1);
			break;
		}
		}
	} while (a == 'Y');



	cout << "\n\n";
	system("pause");
	return 0;
}
int menu() {
	int a;

	cout << "Please select your choice: " << endl;
	cout << "1. Read file " << endl;
	cout << "2. Delete record " << endl;
	cout << "3. Search student " << endl;
	cout << "4. Insert book " << endl;
	cout << "5. Display output" << endl;
	cout << "6. Compute and Display Statistics" << endl;
	cout << "7. Student with Same Book " << endl;
	cout << "8. display Warned Student" << endl;
	cout << "9. Exit " << endl;
	cin >> a;
	cout << endl;

	return a;
}

bool ReadFile(string filename, List* list) {
	LibStudent student;
	ifstream infile;
	string a;
	int count = 0;

	infile.open(filename + ".txt");

	if (infile.fail())
		return false;

	while (!infile.eof()) {
		for (int h = 0; h < 3; h++)
			infile >> a;
		infile >> student.id;
		for (int c = 0; c < 2; c++)
			infile >> a;
		infile.get();
		infile.getline(student.name, 30);
		for (int d = 0; d < 2; d++)
			infile >> a;
		infile >> student.course;
		for (int e = 0; e < 3; e++)
			infile >> a;
		infile >> student.phone_no;

		if (!Redundant(list, student)) {
			list->insert(student);
		}
		else {

			cout << student.id << " is already save in Node." << endl;

		}

	}
	cout << "Data Saved." << endl;

	infile.close();

	return true;
}

bool Redundant(List* stulist1, LibStudent student) {
	Node* cur;

	cur = stulist1->head;
	while (cur != NULL)
	{
		if (cur->item.compareName2(student))
			return true;

		cur = cur->next;
	}
	return false;
}

bool DeleteRecord(List* stulist, char* ID) {
	LibStudent temp;
	if (stulist->empty())
		return false;

	cout << "Please key in student ID that you want to delete: " << endl;
	cin >> ID;
	cout << "ID= " << ID << endl;
	for (int i = 1; i <= stulist->size(); i++) {
		if (stulist->get(i, temp)) {
			if (strcmp(temp.id, ID) == 0) {
				stulist->remove(i);
				cout << "The data of student " << ID << " have been remove." << endl;
				return true;
			}

		}
	}
	return false;

}
bool SearchStudent(List* stulist, char* id, LibStudent& STU) {

	if (stulist->empty())
		return false;

	cout << "Please key in student ID of the student that you want to search:  " << endl;
	cin >> id;

	for (int i = 1; i <= stulist->size(); i++) {

		if (stulist->get(i, STU)) {
			if (strcmp(STU.id, id) == 0) {

				STU.print(cout);

				return true;
			}
		}
	}

	return false;
}
bool InsertBook(string filename, List* list)
{
	// LibBook to be inserted into student
	LibBook book;

	char id[10];
	int difference_day = 0;
	ifstream inFile;
	inFile.open(filename);
	char hold[256];
	const int current = 2458938;
	
	if (!inFile)
	{
		cout << "Unavailable to open the files" << endl;
		return false;
	}
	else
	{
		while (!inFile.eof())
		{
			// ID
			inFile >> hold;
			strcpy(id, hold);

			// Author
			inFile >> hold; // Tony_Gaddis/Godfrey_Mugand
			string author_hold = "";
			int author_count = 0;
			for (int i = 0; i < strlen(hold); i++)
			{
				// Get author name
				if (hold[i] != '/')
				{
					author_hold += hold[i];
					if (i == strlen(hold) - 1)
					{
						// Remove '_'
						for (int j = 0; j < author_hold.length(); j++)
						{
							if (author_hold[j] == '_')
								author_hold[j] = ' ';

						}
						// Insert to LibBook
						//List* stulist = new List();
						book.author[author_count] = new char[author_hold.length()];
						strcpy(book.author[author_count++], author_hold.c_str());
						author_hold = "";
					}
				}
				else if (hold[i] == '/') // Finished 1 author
				{
					// Remove '_'
					for (int j = 0; j < author_hold.length(); j++)
					{
						if (author_hold[j] == '_')
							author_hold[j] = ' ';

					}

					// Insert to LibBook
					book.author[author_count] = new char[author_hold.length()];
					strcpy(book.author[author_count++], author_hold.c_str());
					author_hold = "";
				}
			}

			// Title
			inFile >> hold;
			// Remove '_'
			for (int i = 0; i < strlen(hold); i++)
			{
				if (hold[i] == '_')
					hold[i] = ' ';

			} strcpy(book.title, hold); // Insert to LibBook

			// Publisher
			inFile >> hold;
			strcpy(book.publisher, hold); // Insert to LibBook

			// ISBN
			inFile >> hold;
			strcpy(book.ISBN, hold); // Insert to LibBook

			// yearPublished
			inFile >> hold;
			book.yearPublished = atoi(hold); // Insert to LibBook

			// callNum
			inFile >> hold;
			strcpy(book.callNum, hold); // Insert to LibBook

			string hold_date = "";
			int rotation = 0;
			// borrow (12/2/2020)
			Date borrow;
			inFile >> hold;
			for (int i = 0; i < strlen(hold); i++)
			{
				if (hold[i] != '/' && i != strlen(hold) - 1)
					hold_date += hold[i];
				else
				{
					switch (rotation)
					{
					case 0:
						borrow.day = stoi(hold_date);
						rotation++;
						break;

					case 1:
						borrow.month = stoi(hold_date);
						rotation++;
						break;

					case 2:
						hold_date += hold[i];
						borrow.year = stoi(hold_date);
						rotation = 0;
						break;
					}
					hold_date = "";
				}
			}
			book.borrow = borrow; // Insert to LibBook

			// due
			Date due;
			inFile >> hold;
			for (int i = 0; i < strlen(hold); i++)
			{
				if (hold[i] != '/' && i != strlen(hold) - 1)
					hold_date += hold[i];
				else
				{
					switch (rotation)
					{
					case 0:
						due.day = stoi(hold_date);
						rotation++;
						break;

					case 1:
						due.month = stoi(hold_date);
						rotation++;
						break;

					case 2:
						hold_date += hold[i];
						due.year = stoi(hold_date);
						rotation = 0;
						break;
					}
					hold_date = "";
				}
			}
			book.due = due; // Insert to LibBook

			
			// How to assigned the date into here
			int julianDate = calculateJulianDate(due.year, due.month, due.day);
			
			difference_day = current - julianDate;
			// do if else ( positive then no countt , negative count)
			if (difference_day > 0)
			{
				book.fine = static_cast<double>(difference_day) * 0.50;

			}
			else
			{
				book.fine = 0.0;
			}
		
			book.print(cout);
			cout << "\n" << endl;
			// Insert to Specified Student
			LibStudent student;
			for (int i = 0; i < list->count; i++)
			{
				list->get(i + 1, student);
				if (strcmp(student.id, id) == 0)
				{
					student.book[student.totalbook++] = book;
					//student.calculateTotalFine();
					list->set(i + 1, student);
				}
			}

		} inFile.close();
		return true;
	}

	return 0;

}

bool Display(List* list, int source, int detail) {
	ofstream outfile;
	ofstream outfile2;
	Node* temp = list->head;//traverse the node one by one

	outfile.open("stu_info.txt");
	outfile2.open("stu_booklist.txt");

	if (list->empty()) {
		return false;
	}
	if (source == 1 && detail == 1) {
		for (int a = 1; temp != NULL; temp = temp->next, a++) {
			cout << "=====================================" << endl;
			cout << "Student " << a << endl;
			temp->item.print(cout);
			cout << endl;

			for (int i = 0; i < temp->item.totalbook; i++) {
				cout << "----------------------------------" << endl;
				cout << "Book " << i + 1 << endl;
				temp->item.book[i].print(cout);
			}

		}
		cout << "Successfully display output." << endl;
		cout << endl;
		return true;

	}
	else if (source == 1 && detail == 2) {
		for (int a = 1; temp != NULL; temp = temp->next, a++) {
			cout << "=====================================" << endl;
			cout << "Student " << a << endl;
			temp->item.print(cout);
			cout << endl;
		}
		cout << "Successfuly display output." << endl;
		cout << endl;
		return true;
	}

	else if (source == 2 && detail == 1) {
		for (int a = 1; temp != NULL; temp = temp->next, a++) {
			outfile2 << "==========================================" << endl;
			outfile2 << "Student " << a << endl;
			temp->item.print(outfile2);
			cout << endl;

			for (int i = 0; i < temp->item.totalbook; i++) {
				outfile2 << "----------------------------------------" << endl;
				outfile2 << "Book " << i + 1 << endl;
				temp->item.book[i].print(outfile2);
			}
		}

		cout << "Displayed in stu_booklist.txt." << endl;
		cout << endl;
		return true;
	}
	else if (source == 2 && detail == 2) {
		for (int a = 1; temp != NULL; temp = temp->next, a++) {
			outfile << "-----------------------------" << endl;
			outfile << "Student " << a << endl;
			temp->item.print(outfile);
			cout << endl;
		}
		cout << "Displayed in stu_list." << endl;
		cout << endl;
		return true;
	}

}

int calculateJulianDate(int year, int month, int day)
{
	// Check for valid month and day values
	if (month < 1 || month > 12 || day < 1 || day > 31) 
	{
		std::cerr << "Invalid input date." << std::endl;
		return -1; // Return an error value
	}

	// Adjust month and year for January and February
	if (month <= 2)
	{
		year--;
		month += 12;
	}

	// Calculate the Julian date formula
	double julianDate = (1461 * (year + 4800 + (month - 14) / 12)) / 4 +
		(367 * (month - 2 - 12 * ((month - 14) / 12))) / 12 -
		(3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4 +
		day - 32075;

	return julianDate;
}





