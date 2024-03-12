//Jose Villanueva Vigil
//COSC 1437
//Program Problem 2
//For references, I used the PDF covering program set 2

#include <iostream>
#include <string>

using namespace std;

const int SIZE = 100;
string Words[SIZE];
string word, word1, word2;
string Alpha;

int WordVal[SIZE];
int WordVal2[SIZE];
char WORD1[SIZE];
char WORD2[SIZE];
 

int main()
{
	int counter = 0;
	int counter2 = 0;
	bool empty = false;
	bool sorted = true;

	char choice = 'Y';


	//a while loop is used to repeat the program
	while (choice != 'N')
	{

		//alphabet is entered here
		cout << "Enter alphabet: ";
		cin >> Alpha;

		//words are entered here
		cout << "Enter words: ";
		cin >> word;

		//a while loop is used to enter words
		//while bool empty is false, then the loop will continue
		while (empty == false)
		{
			Words[counter] = word;
			counter++;

			cin >> word;

			//if PLESESTOP is entered, then empty changes to true and the loop ends
			if (word == "PLEASESTOP")
			{
				empty = true;
			}
		}


		//this while loop is used to assign words into arrays, assign words numeric values, and check to see
		//if the given wordlist is sorted
		while (counter2 != (counter - 1))
		{
			//these statements are used to assign strings from the word array
			//to seperate word strings
			word1 = Words[counter2];
			word2 = Words[counter2 + 1];

			//this for loop assigns the array WORD1 with the characters from word1 
			for (int index = 0; index < word1.length(); index++)
			{
				WORD1[index] = word1[index];

			}

			//this for loop assigns the array WORD2 with the characters from word2 
			for (int index = 0; index < word2.length(); index++)
			{
				WORD2[index] = word2[index];
			}

			//Two for loops are used, the 1st moves through a word, the 2nd moves through the alphabet
			//this for loop is used to assign the WordVal array numeric data 
			//depending on what position a letter is depending on the alphabet 
			//Example: if a is the first letter of the alphabet, then any character that is an a, is assigned a value of 0 
			for (int index = 0; index < word1.length(); index++)
			{
				for (int index2 = 0; index2 < Alpha.length(); index2++)
				{
					if (tolower(WORD1[index]) == tolower(Alpha[index2]))
					{
						WordVal[index] = index2;
					}
				}
			}

			//this for loop is identical to the for loop above, but this is used for the second word
			for (int index = 0; index < word2.length(); index++)
			{
				for (int index2 = 0; index2 < Alpha.length(); index2++)
				{
					if (tolower(WORD2[index]) == tolower(Alpha[index2]))
					{
						WordVal2[index] = index2;
					}
				}
			}

			//this if statement checks to see which word is bigger
			if (word1.length() < word2.length())
			{

				//this for loop is used to move through the contents of WordVal and WordVal2
				for (int index = 0; index < word1.length(); index++)
				{

					//if the value of WordVal2 is greater than WordVal
					//then the index is set to the length of word1 to end the loop 
					//this indicates that the words are sorted
					if (WordVal[index] < WordVal2[index])
					{
						index = static_cast<int>(word1.length());
					}

					//if the value of WordVal is greater than WordVal2
					//then the index is set to the length of word1 to end the loop
					//and sorted is set to false
					else if (WordVal[index] > WordVal2[index])
					{
						index = static_cast<int>(word1.length());
						sorted = false;
					}
				}
			}

			//this else if statement checks to see which word is bigger
			else if (word1.length() > word2.length())
			{

				//this for loop is used to move through the contents of WordVal and WordVal2
				for (int index = 0; index < word2.length() + 1; index++)
				{

					//if the value of WordVal is greater than WordVal2
					//then the index is set to the length of word1 to end the loop
					//and sorted is set to false
					if (WordVal[index] > WordVal2[index])
					{
						index = static_cast<int>(word2.length());
						sorted = false;
					}

					//if the value of WordVal2 is greater than WordVal
					//then the index is set to the length of word1 to end the loop 
					//this indicates that the words are sorted
					else if (WordVal[index] < WordVal2[index])
					{
						index = static_cast<int>(word2.length());
					}

					//if the index is word2.length-1 and the length of word1 is greater than word2
					//then sorted is false, because the smaller word take priority 
					else if (index == word2.length() && word1.length() > word2.length())
					{
						sorted = false;
					}
				}
			}

			//this else statement is used if both words are of equal length
			else if (word1.length() == word2.length())
			{

				//this for loop is used to move through the contents of WordVal and WordVal2
				for (int index = 0; index < word1.length(); index++)
				{

					//if the value of WordVal2 is greater than WordVal
					//then the index is set to the length of word1 to end the loop 
					//this indicates that the words are sorted
					 if (WordVal[index] < WordVal2[index])
					{
						index = static_cast<int>(word1.length());

					}

					//if the value of WordVal is greater than WordVal2
					//then the index is set to the length of word1 to end the loop
					//and sorted is set to false
					else if (WordVal[index] > WordVal2[index])
					{
						index = static_cast<int>(word1.length());
						sorted = false;
					}
				}
			}

			counter2++;
		}

		cout << " " << endl;

		//if sorted is false then the not sorted message is displayed
		if (sorted == false)
		{
			cout << "Not sorted wordlist." << endl;
		}

		//if sorted is ture then the sorted message is displayed
		else if (sorted == true)
		{
			cout << "Sorted wordlist." << endl;
		}

		cout << " " << endl;
		cout << "Run Again (Y/N): ";
		cin >> choice;

		choice = toupper(choice);

		//if an invalid choice is entered to run the program again
		//then an error is displyed and will continue to run until 
		//the user enters  valid choice
		while (choice != 'Y' && choice != 'N')
		{
			cout << "An invalid choice was entered, plese try again." << endl;
			cin >> choice;
			
			choice = toupper(choice);
		}

		//all values are reset here to perpare for another run
		counter = 0;
		counter2 = 0;
		empty = false;
		sorted = true;
		cout << " " << endl;
	}
	return 0;

}