//Jose Villanueva Vigil
//COSC 1437
//Program set 2, problem 3 (TextVowelRatio)
//For references, I used the PDF covering program set 2

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


//Declaring a maximum size for an array of characters
const int SIZE = 5000;
char Text[SIZE];

//function TextChecker is used to count the consonnts and vowel
bool TextChecker(double&, double&, int, char []);


int main()
{

	double Consonant = 0, Vowel = 0, Ratio = 0;
	int counter3 = 0;

	string FileName;
	char BlockText;
	ifstream InputFile;


	cout << "Enter file name: ";
	cin >> FileName;
	cout << " " << endl;


	//Opens file required for program to run
	InputFile.open(FileName);

	//if there is no file then an error is displayed
	if (InputFile.fail())
	{
		cout << "An error has Occured while opening the file\n";
	}

	//if the file is opened, the program starts
	else
	{

		//the contants of the file are moved into an array using a while loop
		while (InputFile >> BlockText)
		{
			Text[counter3] = BlockText;
			counter3++;
		}

		//function TextChecker is called
		TextChecker(Consonant, Vowel, counter3, Text);

		//if checks to see if the consonants and vowels are valid(values above 0)
		//if they are valid then the ratio will be calculated
		if (Consonant > 0 && Vowel > 0)
		{
			cout << "Consonants: " << Consonant << endl;
			cout << "Vowels: " << Vowel << endl;
			Ratio = Vowel / Consonant;
			cout << setprecision(3) << fixed;
			cout << "Ratio: " << Ratio << endl;
		}

		//if either values are 0, then the following statements are executed
		//the ratio calculation is skipped and indef. is shown
		else if (Consonant == 0 || Vowel == 0)
		{
			cout << "Consonants: " << Consonant << endl;
			cout << "Vowels: " << Vowel << endl;
			cout << "Ratio: indef." << endl;
		}
	}
	return 0;

}

/*-------------------------------------------------------------------------------------------

TextChecker is a function used to count the vowels and consonants of a given set of characetrs

-The function runs through a for loop which moves through the character array used to hold
the files data
-The data from the character array is processed in the for loop using if statements
-if a consonnt or vowel is detected then the values are incremeneted 
-if the # character is detetced, then the function ends

--------------------------------------------------------------------------------------------*/
bool TextChecker(double& consonants, double& vowels,int coun, char txt[])
{
	//the for loop moves through the contents of the character array
	for (int index = 0; index < coun; index++)
	{

		//if the character is a valid character then the following statement will execute
		if (isalpha(txt[index]))
		{
			//if current chracter within the index is not a vowel
			//then consonants is incremnted
			if (txt[index] != 'A'
				&& txt[index] != 'a'
				&& txt[index] != 'E'
				&& txt[index] != 'e'
				&& txt[index] != 'I'
				&& txt[index] != 'i'
				&& txt[index] != 'O'
				&& txt[index] != 'o'
				&& txt[index] != 'U'
				&& txt[index] != 'u')
			{
				consonants++;
			}
		}

		//if the character is a valid character then the following statement will execute
		if (isalpha(txt[index]))
		{
			//if current chracter within the index is not a consonant 
			//then vowels is incremnted
			if (txt[index] == 'A'
				|| txt[index] == 'a'
				|| txt[index] == 'E'
				|| txt[index] == 'e'
				|| txt[index] == 'I'
				|| txt[index] == 'i'
				|| txt[index] == 'O'
				|| txt[index] == 'o'
				|| txt[index] == 'U'
				|| txt[index] == 'u')
			{
				vowels++;
			}
		}

		//if the current character is a #, then the value returned 
		//to the bool function (current function running)
		//is 0 and the function ends
		if (txt[index] == '#')
		{
			return 0;
		}
	}
	return 1;
}