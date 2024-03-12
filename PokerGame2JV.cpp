// Author: Jose Villanueva 
// Course: COSC 1437
// Required Program
// For references, I used the PDF covering program set 2


#include <iostream> 
#include <string> 
#include <iomanip>
#include <fstream>

using namespace std;

bool ROYAL_FLUSH = 0;
bool FLUSH = 0;
bool FOUR_OF_A_KIND = 0;
bool THREE_OF_A_KIND = 0;
bool ONE_PAIR = 0;
bool TWO_PAIR = 0;
bool HIGH_CARD = 1;
bool FULL_HOUSE = 0;
bool STRAIGHT_FLUSH = 0;
bool STRAIGHT = 0;

const int RANKS = 15;
const int SUITS = 4;
const int SIZE = 5;

int HandVal = 0;
int HandVal2 = 0;
int HighCardVals = 0;
int HighCardVals2 = 0;

int HandRankValues[SIZE];
int HandRankValues2[SIZE];

int FourKindVals;
int FourKindVals2;
int ThreeKindVals;
int ThreeKindVals2;
int PairKindVals;
int PairKindVals2;

int FullThreeVals;
int FullTwoVals;
int FullThreeVals2;
int FullTwoVals2;

int TwoPairVals[2];
int TwoPairVals2[2];

string FourKindVal;
string FourKindVal2;
string ThreeKindVal;
string ThreeKindVal2;
string PairKindVal;
string PairKindVal2;

string FullThree;
string FullPair;
string FullThree2;
string FullPair2;

string TwoPairVal[2];
string TwoPairVal2[2];

string Suits[SUITS] = { "D", "C", "S", "H" };
string Ranks[RANKS] = { "A","2","3","4","5","6","7","8","9","T","J","Q","K","A" };

string PlayerOne[SIZE];
string PlayerTwo[SIZE];


string HandSuits[SIZE];
string HandRanks[SIZE];
string HandSuits2[SIZE];
string HandRanks2[SIZE];

string HandType;
string HighCardType;
string HandType2;
string HighCardType2;

string HandSuitType;
string HandSuitType2;



//These functions are used to determine the hand type
bool Flush(string[], string[], int);
bool RoyalFlush(string[], string[], int[], const int);
bool StraightFlush(string[], string[], int[], const int);
bool Pair(string[], string[], const int);
bool TwoPair(string[], string[], const int);
bool FourOfAKind(string[], string[], const int);
bool ThreeOfAKind(string[], string[], const int);
bool FullHouse(string[], string[], const int);
bool Straight(string[], string[], int[]);

//the following functions are used to assign values to a players hand
//these values are used to determine the winner 
void ValueAssign(string[], string[], string[], string[], string[], int[]);
void HandValueGiver(bool, bool, bool, bool, bool, bool, bool, bool, bool, bool, string&,
    int&, string[], string[], string[], string[], string&, string&, string&, string&, string&, string&, string[]
    , int&, int&, int&, int&, int&, int[]);
void HighCardVal(int&, int[], string&);
void BoolReset(bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&, bool&);

//the following function is used to sort an array of integers in order
//(will be used to determine straights)
void BubbleSortArray(int[]);

int main()
{
    int sum1 = 0;
    int sum2 = 0;

    int counters = 0;

    ifstream InputFile;

    string FileName;
    string GameData;

    cout << "Enter file name: ";

    cin >> FileName;
    cout << " " << endl;
    InputFile.open(FileName);

    //if the program fails to open the file, then the file is terminted 
    if (InputFile.fail())
    {
        cout << "An Error Has Occured, ending application";
        return 0;
    }

    //if the file is opened, then the program process the data from the file
    else
    {
        //while data is still being retrieved from the file, the program will continue to loop
        while (InputFile >> GameData)
        {
            sum1 = 0;
            sum2 = 0;
            //this loop process the file contents for the 1st players hand
            for (int index = 0; index < 5; index++)
            {
                PlayerOne[index] = GameData;

                //this if is used to offset the data being retrieved so no 
                //values/data from the file is skipped
                if (index < 4)
                {
                    InputFile >> GameData;
                }
            }

            //this loop process the file contents for the 2nd players hand
            for (int index = 0; index < 5; index++)
            {
                InputFile >> GameData;
                PlayerTwo[index] = GameData;
            }

            //this function is used to assign a value to a hand
            ValueAssign(PlayerOne, Ranks, Suits, HandSuits, HandRanks, HandRankValues);

            //the HandRankValues Array is sorted using a bubble sort 
            BubbleSortArray(HandRankValues);

            //the functions are used to check the hand type
            FLUSH = Flush(HandSuits, Suits, SUITS);
            ROYAL_FLUSH = RoyalFlush(Suits, HandSuits, HandRankValues, SUITS);
            STRAIGHT_FLUSH = StraightFlush(Suits, HandSuits, HandRankValues, SUITS);
            ONE_PAIR = Pair(Ranks, HandRanks, RANKS);
            TWO_PAIR = TwoPair(Ranks, HandRanks, RANKS);
            FOUR_OF_A_KIND = FourOfAKind(Ranks, HandRanks, RANKS);
            THREE_OF_A_KIND = ThreeOfAKind(Ranks, HandRanks, RANKS);
            FULL_HOUSE = FullHouse(Ranks, HandRanks, RANKS);
            STRAIGHT = Straight(Suits, HandSuits, HandRankValues);


            //the function is used to assign a hand type and hand value
            HighCardVal(HighCardVals, HandRankValues, HighCardType);
            HandValueGiver(ROYAL_FLUSH, STRAIGHT_FLUSH, FOUR_OF_A_KIND, FULL_HOUSE, FLUSH, STRAIGHT, THREE_OF_A_KIND,
                TWO_PAIR, ONE_PAIR, HIGH_CARD, HandType, HandVal, HandSuits, HandRanks, Suits,
                Ranks, HandSuitType, FourKindVal, ThreeKindVal, PairKindVal, FullThree, FullPair, TwoPairVal
                , FourKindVals, ThreeKindVals, PairKindVals, FullThreeVals, FullTwoVals, TwoPairVals);
            BoolReset(ROYAL_FLUSH, STRAIGHT_FLUSH, FOUR_OF_A_KIND, FULL_HOUSE, FLUSH, STRAIGHT, THREE_OF_A_KIND, TWO_PAIR, ONE_PAIR);


            //this function is used to assign  value to a hand
            ValueAssign(PlayerTwo, Ranks, Suits, HandSuits2, HandRanks2, HandRankValues2);

            //the HandRankValues Array is sorted using a bubble sort 
            BubbleSortArray(HandRankValues2);

            //the functions are used to check the hand type
            FLUSH = Flush(HandSuits2, Suits, SUITS);
            ROYAL_FLUSH = RoyalFlush(Suits, HandSuits2, HandRankValues2, SUITS);
            STRAIGHT_FLUSH = StraightFlush(Suits, HandSuits2, HandRankValues2, SUITS);
            ONE_PAIR = Pair(Ranks, HandRanks2, RANKS);
            TWO_PAIR = TwoPair(Ranks, HandRanks2, RANKS);
            FOUR_OF_A_KIND = FourOfAKind(Ranks, HandRanks2, RANKS);
            THREE_OF_A_KIND = ThreeOfAKind(Ranks, HandRanks2, RANKS);
            FULL_HOUSE = FullHouse(Ranks, HandRanks2, RANKS);
            STRAIGHT = Straight(Suits, HandSuits2, HandRankValues2);

            //the function is used to assign a hand type and hand value
            HighCardVal(HighCardVals2, HandRankValues2, HighCardType2);

            HandValueGiver(ROYAL_FLUSH, STRAIGHT_FLUSH, FOUR_OF_A_KIND, FULL_HOUSE, FLUSH, STRAIGHT, THREE_OF_A_KIND,
                TWO_PAIR, ONE_PAIR, HIGH_CARD, HandType2, HandVal2, HandSuits2, HandRanks2, Suits,
                Ranks, HandSuitType2, FourKindVal2, ThreeKindVal2, PairKindVal2, FullThree2, FullPair2, TwoPairVal2
                , FourKindVals2, ThreeKindVals2, PairKindVals2, FullThreeVals2, FullTwoVals2, TwoPairVals2);

            BoolReset(ROYAL_FLUSH, STRAIGHT_FLUSH, FOUR_OF_A_KIND, FULL_HOUSE, FLUSH, STRAIGHT, THREE_OF_A_KIND, TWO_PAIR, ONE_PAIR);


            //this displays the hand number
            counters++;
            cout << "Hand " << counters << ": ";

            //this is checks to see if HandVal > HandVal2
            //if the statement is true then a victory message will be printed
            if (HandVal > HandVal2)
            {
                //the is statement below process the data from the players hand to display 
                //the winning message, this same process is repeated for all HandVal ranging from 2-10
                //(this excludes 1 because it implies that PlayerOne lost)
                if (HandVal == 2)
                {
                    cout << HandType << ", " << PairKindVal << "'s beats ";
                }
                else if (HandVal == 3)
                {
                    cout << HandType << ", " << TwoPairVal[1] << "'s and " << TwoPairVal[0] << "'s beats ";
                }
                else if (HandVal == 4)
                {
                    cout << HandType << ", " << ThreeKindVal << "'s beats ";
                }
                else if (HandVal == 5)
                {
                    cout << HandType << ", " << HighCardType << " High beats";
                }
                else if (HandVal == 6)
                {
                    cout << HandType << ", " << HandSuitType << ", " << HighCardType << " High beats ";
                }
                else if (HandVal == 7)
                {
                    cout << HandType << ", " << FullThree << "'s full of " << FullPair << "'s beats ";
                }
                else if (HandVal == 8)
                {
                    cout << HandType << ", " << FourKindVal << "'s beats ";
                }
                else if (HandVal == 9)
                {
                    cout << HandType << ", " << HandSuitType << ", " << HighCardType << " High beats ";
                }
                else if (HandVal == 10)
                {
                    cout << HandType << ", " << HandSuitType << " beats ";
                }

                //the following if statements print the contents of PlayerTwo's hand
                //this applies to all HandVal ranging from 9-1 (10 is excluded bc that implies that 
                //PlayerTwo won)
                if (HandVal2 == 9)
                {
                    cout << HandType2 << ", " << HandSuitType2 << ", " << HighCardType2 << " High" << endl;
                }
                else if (HandVal2 == 8)
                {
                    cout << HandType2 << ", " << FourKindVal2 << "'s " << endl;
                }
                else if (HandVal2 == 7)
                {
                    cout << HandType2 << ", " << FullThree2 << "'s full of " << FullPair2 << "'s " << endl;
                }
                else if (HandVal2 == 6)
                {
                    cout << HandType2 << ", " << HandSuitType2 << ", " << HighCardType2 << " High" << endl;
                }
                else if (HandVal2 == 5)
                {
                    cout << HandType2 << ", " << HighCardType2 << " High " << endl;
                }
                else if (HandVal2 == 4)
                {
                    cout << HandType2 << ", " << ThreeKindVal2 << "'s " << endl;
                }
                else if (HandVal2 == 3)
                {
                    cout << HandType2 << ", " << TwoPairVal2[1] << "'s and " << TwoPairVal2[0] << "'s " << endl;
                }
                else if (HandVal2 == 2)
                {
                    cout << HandType2 << ", " << PairKindVal2 << "'s " << endl;
                }
                else if (HandVal2 == 1)
                {
                    cout << HandType2 << ", " << HighCardType2 << " High " << endl;
                }
            }

            //the else if statement checks to see if HandVal < HandVal2
            //if the statement is true, then a lose message will be printed for PlayerOne
            else if (HandVal < HandVal2)
            {
                //these if statements are nearly identical from the if statements that are used to print
                //the victory message except beat is replaced with loses and the HandVal's range from 1-9
                if (HandVal == 1)
                {
                    cout << HandType << ", " << HighCardType << " High loses to ";
                }
                else if (HandVal == 2)
                {
                    cout << HandType << ", " << PairKindVal << "'s loses to ";
                }
                else if (HandVal == 3)
                {
                    cout << HandType << ", " << TwoPairVal[1] << "'s and " << TwoPairVal[0] << "'s loses to ";
                }
                else if (HandVal == 4)
                {
                    cout << HandType << ", " << ThreeKindVal << "'s loses to ";
                }
                else if (HandVal == 5)
                {
                    cout << HandType << ", " << HighCardType << " High loses to ";
                }
                else if (HandVal == 6)
                {
                    cout << HandType << ", " << HandSuitType << ", " << HighCardType << " High loses to ";
                }
                else if (HandVal == 7)
                {
                    cout << HandType << ", " << FullThree << "'s full of " << FullPair << "'s loses to ";
                }
                else if (HandVal == 8)
                {
                    cout << HandType << ", " << FourKindVal << "'s loses to ";
                }
                else if (HandVal == 9)
                {
                    cout << HandType << ", " << HandSuitType << ", " << HighCardType << " High loses to ";
                }

                //these if statements are nearly identical from the if statements that are used to print
                //the contents of PlayerTwo's hand, except the HandVal2's range from 10-2
                if (HandVal2 == 10)
                {
                    cout << HandType2 << ", " << HandSuitType2 << endl;
                }
                else if (HandVal2 == 9)
                {
                    cout << HandType2 << ", " << HandSuitType2 << ", " << HighCardType2 << " High" << endl;
                }
                else if (HandVal2 == 8)
                {
                    cout << HandType2 << ", " << FourKindVal2 << "'s " << endl;
                }
                else if (HandVal2 == 7)
                {
                    cout << HandType2 << ", " << FullThree2 << "'s full of " << FullPair2 << "'s " << endl;
                }
                else if (HandVal2 == 6)
                {
                    cout << HandType2 << ", " << HandSuitType2 << ", " << HighCardType2 << " High" << endl;
                }
                else if (HandVal2 == 5)
                {
                    cout << HandType2 << ", " << HighCardType2 << " High " << endl;
                }
                else if (HandVal2 == 4)
                {
                    cout << HandType2 << ", " << ThreeKindVal2 << "'s " << endl;
                }
                else if (HandVal2 == 3)
                {
                    cout << HandType2 << ", " << TwoPairVal2[1] << "'s and " << TwoPairVal2[0] << "'s " << endl;
                }
                else if (HandVal2 == 2)
                {
                    cout << HandType2 << ", " << PairKindVal2 << "'s " << endl;
                }
            }

            //this else if statement checks to see if the hands are tied
            else if (HandVal == HandVal2)
            {

                //if HandVal == 1
                //then it will have two options for a tie
                //it checks to see which high card is greater and if the high cards are equal 
                if (HandVal == 1)
                {
                    if (HighCardVals > HighCardVals2)
                    {
                        cout << HandType << ", " << HighCardType << " High beats " << HandType2 << ", " << HighCardType2 << " High" << endl;
                    }
                    else if (HighCardVals < HighCardVals2)
                    {
                        cout << HandType << ", " << HighCardType << " High loses to " << HandType2 << ", " << HighCardType2 << " High" << endl;
                    }
                    else
                    {
                        for (int i = 0; i < 5; i++)
                        {
                            sum1 += HandRankValues[i];

                            if (HandRankValues[i] == 0)
                            {
                                sum1 += 13;
                            }

                            sum2 += HandRankValues2[i];

                            if (HandRankValues2[i] == 0)
                            {
                                sum2 += 13;
                            }
                        }

                        sum1 = (sum1 - HighCardVals);
                        sum2 = (sum2 - HighCardVals2);

                        if (sum1 > sum2)
                        {
                            cout << HandType << ", " << HighCardType << " High beats " << HandType2 << ", " << HighCardType2 << " High" << endl;
                        }
                        else if (sum1 < sum2)
                        {
                            cout << HandType << ", " << HighCardType << " High loses to " << HandType2 << ", " << HighCardType2 << " High" << endl;
                        }
                        else
                        {
                            cout << HandType << ", " << HighCardType << " High ties " << HandType2 << ", " << HighCardType2 << " High" << endl;

                        }
                    }
                }

                //if HandVal == 2
                //then there will be three options to determine who wins
                //the first winner option checks for a greater pair
                //the second winner option checks to see who has a greater high card
                //the third winner option checks to see if the hands are tied (both hands are equal)
                else if (HandVal == 2)
                {
                    if (PairKindVals > PairKindVals2)
                    {
                        cout << HandType << ", " << PairKindVal << "'s beats "
                            << HandType2 << ", " << PairKindVal2 << "'s" << endl;
                    }
                    else if (PairKindVals < PairKindVals2)
                    {
                        cout << HandType << ", " << PairKindVal << "'s loses to "
                            << HandType2 << ", " << PairKindVal2 << "'s" << endl;
                    }
                    else if (PairKindVals == PairKindVals2)
                    {
                        for (int i = 0; i < 5; i++)
                        {
                            sum1 += HandRankValues[i];

                            if (HandRankValues[i] == 0)
                            {
                                sum1 += 13;
                            }

                            sum2 += HandRankValues2[i];

                            if (HandRankValues2[i] == 0)
                            {
                                sum2 += 13;
                            }
                        }

                        sum1 = (sum1 - (PairKindVals * 2));
                        sum2 = (sum2 - (PairKindVals2 * 2));

                        if (sum1 > sum2)
                        {
                            cout << HandType << ", " << PairKindVal << "'s beats "
                                << HandType2 << ", " << PairKindVal2 << "'s" << endl;
                        }
                        else if (sum1 < sum2)
                        {
                            cout << HandType << ", " << PairKindVal << "'s loses to "
                                << HandType2 << ", " << PairKindVal2 << "'s" << endl;
                        }
                        else if (sum1 == sum2)
                        {
                            cout << HandType << ", " << PairKindVal << "'s ties "
                                << HandType2 << ", " << PairKindVal2 << "'s" << endl;
                        }
                    }
                }

                //if HandVal == 3
                //then there will be three options to determine who wins
                //the first winner option checks for a greater TwoPair
                //the second winner option checks to see who has a greater high card
                //the third winner option checks to see if the hands are tied (both hands are equal)
                else if (HandVal == 3)
                {
                    if (TwoPairVals[0] > TwoPairVals2[0])
                    {
                        cout << HandType << ", " << TwoPairVal[1] << "'s and " << TwoPairVal[0] << "'s beats "
                            << HandType2 << ", " << TwoPairVal2[1] << "'s and " << TwoPairVal2[0] << "'s " << endl;
                    }
                    else if (TwoPairVals[0] < TwoPairVals2[0])
                    {
                        cout << HandType << ", " << TwoPairVal[1] << "'s and " << TwoPairVal[0] << "'s loses to "
                            << HandType2 << ", " << TwoPairVal2[1] << "'s and " << TwoPairVal2[0] << "'s " << endl;
                    }
                    else if (TwoPairVals[0] == TwoPairVals2[0])
                    {
                        if (TwoPairVals[1] > TwoPairVals2[1])
                        {
                            cout << HandType << ", " << TwoPairVal[1] << "'s and " << TwoPairVal[0] << "'s beats "
                                << HandType2 << ", " << TwoPairVal2[1] << "'s and " << TwoPairVal2[0] << "'s " << endl;
                        }
                        else if (TwoPairVals[1] < TwoPairVals2[1])
                        {
                            cout << HandType << ", " << TwoPairVal[1] << "'s and " << TwoPairVal[0] << "'s loses to "
                                << HandType2 << ", " << TwoPairVal2[1] << "'s and " << TwoPairVal2[0] << "'s " << endl;
                        }
                        else
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                sum1 += HandRankValues[i];

                                if (HandRankValues[i] == 0)
                                {
                                    sum1 += 13;
                                }

                                sum2 += HandRankValues2[i];

                                if (HandRankValues2[i] == 0)
                                {
                                    sum2 += 13;
                                }
                            }

                            sum1 = (sum1 - ((TwoPairVals[0] * 2) + (TwoPairVals[1] * 2)));
                            sum2 = (sum2 - ((TwoPairVals2[0] * 2) + (TwoPairVals2[1] * 2)));


                            if (sum1 > sum2)
                            {
                                cout << HandType << ", " << TwoPairVal[1] << "'s and " << TwoPairVal[0] << "'s beats "
                                    << HandType2 << ", " << TwoPairVal2[1] << "'s and " << TwoPairVal2[0] << "'s " << endl;
                            }
                            else if (sum1 < sum2)
                            {
                                cout << HandType << ", " << TwoPairVal[1] << "'s and " << TwoPairVal[0] << "'s loses to "
                                    << HandType2 << ", " << TwoPairVal2[1] << "'s and " << TwoPairVal2[0] << "'s " << endl;
                            }
                            else
                            {
                                cout << HandType << ", " << TwoPairVal[1] << "'s and " << TwoPairVal[0] << "'s ties "
                                    << HandType2 << ", " << TwoPairVal2[1] << "'s and " << TwoPairVal2[0] << "'s " << endl;
                            }
                        }
                    }
                }

                //if HandVal == 4
                //then it will have two options for a tie
                //it checks to see which three of a kind is greater and which high card is greater
                //if the three of a kind's are tied then it will check the high cards
                else if (HandVal == 4)
                {
                    if (ThreeKindVals > ThreeKindVals2)
                    {
                        cout << HandType << ", " << ThreeKindVal << "'s beats "
                            << HandType2 << ", " << ThreeKindVal2 << "'s " << endl;
                    }
                    else if (ThreeKindVals < ThreeKindVals2)
                    {
                        cout << HandType << ", " << ThreeKindVal << "'s loses to "
                            << HandType2 << ", " << ThreeKindVal2 << "'s " << endl;
                    }
                    else if (ThreeKindVals == ThreeKindVals2)
                    {
                        for (int i = 0; i < 5; i++)
                        {
                            sum1 += HandRankValues[i];

                            if (HandRankValues[i] == 0)
                            {
                                sum1 += 13;
                            }

                            sum2 += HandRankValues2[i];

                            if (HandRankValues2[i] == 0)
                            {
                                sum2 += 13;
                            }
                        }

                        sum1 = (sum1 - (ThreeKindVals * 3));
                        sum2 = (sum2 - (ThreeKindVals2 * 3));

                        if (sum1 > sum2)
                        {
                            cout << HandType << ", " << ThreeKindVal << "'s beats "
                                << HandType2 << ", " << ThreeKindVal2 << "'s " << endl;
                        }
                        else if (sum1 < sum2)
                        {
                            cout << HandType << ", " << ThreeKindVal << "'s loses to "
                                << HandType2 << ", " << ThreeKindVal2 << "'s " << endl;
                        }
                        else if (sum1 == sum2)
                        {
                            cout << HandType << ", " << ThreeKindVal << "'s ties "
                                << HandType2 << ", " << ThreeKindVal2 << "'s " << endl;
                        }
                    }
                }

                //if HandVal == 5
                //then it will have two options for a tie
                //it checks to see which high card is greater and if the high cards are tied
                else if (HandVal == 5)
                {
                    if (HighCardVals > HighCardVals2)
                    {
                        cout << HandType << ", " << HighCardType << " High beats " <<
                            HandType2 << ", " << HighCardType2 << " High " << endl;
                    }
                    else if (HighCardVals < HighCardVals2)
                    {
                        cout << HandType << ", " << HighCardType << " High loses to " <<
                            HandType2 << ", " << HighCardType2 << " High " << endl;
                    }
                    else if (HighCardVals == HighCardVals2)
                    {
                        cout << HandType << ", " << HighCardType << " High ties " <<
                            HandType2 << ", " << HighCardType2 << " High " << endl;
                    }
                }

                //if HandVal == 6
                //then it will have two options for a tie
                //it checks to see which high card is greater and if the high cards are tied
                else if (HandVal == 6)
                {
                    if (HighCardVals > HighCardVals2)
                    {
                        cout << HandType << ", " << HandSuitType << ", " << HighCardType << " High beats " <<
                            HandType2 << ", " << HandSuitType2 << ", " << HighCardType2 << " High " << endl;
                    }
                    else if (HighCardVals < HighCardVals2)
                    {
                        cout << HandType << ", " << HandSuitType << ", " << HighCardType << " High loses to " <<
                            HandType2 << ", " << HandSuitType2 << ", " << HighCardType2 << " High " << endl;
                    }
                    else if (HighCardVals == HighCardVals2)
                    {
                        for (int i = 0; i < 5; i++)
                        {
                            sum1 += HandRankValues[i];

                            if (HandRankValues[i] == 0)
                            {
                                sum1 += 13;
                            }

                            sum2 += HandRankValues2[i];

                            if (HandRankValues2[i] == 0)
                            {
                                sum2 += 13;
                            }
                        }

                        sum1 = (sum1 - HighCardVals);
                        sum2 = (sum2 - HighCardVals2);

                        if (sum1 > sum2)
                        {
                            cout << HandType << ", " << HandSuitType << ", " << HighCardType << " High beats " <<
                                HandType2 << ", " << HandSuitType2 << ", " << HighCardType2 << " High " << endl;
                        }
                        else if (sum1 < sum2)
                        {
                            cout << HandType << ", " << HandSuitType << ", " << HighCardType << " High loses to " <<
                                HandType2 << ", " << HandSuitType2 << ", " << HighCardType2 << " High " << endl;
                        }
                        else
                        {
                            cout << HandType << ", " << HandSuitType << ", " << HighCardType << " High ties " <<
                                HandType2 << ", " << HandSuitType2 << ", " << HighCardType2 << " High " << endl;
                        }
                    }
                }

                //if HandVal == 7
                //then there will be two options to determine who wins
                //the first winner option checks for a greater full house
                //the second winner option checks to see if the hands are tied
                else if (HandVal == 7)
                {
                    if (FullThreeVals > FullThreeVals2)
                    {
                        cout << HandType << ", " << FullThree << "'s full of " << FullPair << "'s beats "
                            << HandType2 << ", " << FullThree2 << "'s full of " << FullPair2 << "'s " << endl;
                    }
                    else if (FullThreeVals < FullThreeVals2)
                    {
                        cout << HandType << ", " << FullThree << "'s full of " << FullPair << "'s loses to "
                            << HandType2 << ", " << FullThree2 << "'s full of " << FullPair2 << "'s " << endl;
                    }
                    else if (FullThreeVals == FullThreeVals2)
                    {
                        if (FullTwoVals > FullTwoVals2)
                        {
                            cout << HandType << ", " << FullThree << "'s full of " << FullPair << "'s beats "
                                << HandType2 << ", " << FullThree2 << "'s full of " << FullPair2 << "'s " << endl;
                        }
                        else if (FullTwoVals < FullTwoVals2)
                        {
                            cout << HandType << ", " << FullThree << "'s full of " << FullPair << "'s loses to "
                                << HandType2 << ", " << FullThree2 << "'s full of " << FullPair2 << "'s " << endl;
                        }
                        else
                        {
                            cout << HandType << ", " << FullThree << "'s full of " << FullPair << "'s ties "
                                << HandType2 << ", " << FullThree2 << "'s full of " << FullPair2 << "'s " << endl;

                        }
                    }
                }

                //if HandVal == 8
                //then it will have two options for a tie
                //it checks to see which four of a kind is greater and which high card is greater
                //if the four of a kind's are tied then it will check the high cards
                else if (HandVal == 8)
                {
                    if (FourKindVals > FourKindVals2)
                    {
                        cout << HandType << ", " << FourKindVal << "'s beats "
                            << HandType2 << ", " << FourKindVal2 << "'s " << endl;
                    }
                    else if (FourKindVals < FourKindVals2)
                    {
                        cout << HandType << ", " << FourKindVal << "'s loses to "
                            << HandType2 << ", " << FourKindVal2 << "'s " << endl;
                    }
                    else if (FourKindVals == FourKindVals2)
                    {
                        if (HighCardVals > HighCardVals2)
                        {
                            cout << HandType << ", " << FourKindVal << "'s beats "
                                << HandType2 << ", " << FourKindVal2 << "'s " << endl;
                        }
                        else if (HighCardVals < HighCardVals2)
                        {
                            cout << HandType << ", " << FourKindVal << "'s loses to "
                                << HandType2 << ", " << FourKindVal2 << "'s " << endl;
                        }
                        else if (HighCardVals == HighCardVals2)
                        {
                            cout << HandType << ", " << FourKindVal << "'s ties "
                                << HandType2 << ", " << FourKindVal2 << "'s " << endl;
                        }
                    }
                }

                //if HandVal == 9
                //then it will have two options for a tie
                //it checks to see which high card is greater and if the high cards are equal 
                else if (HandVal == 9)
                {
                    if (HighCardVals > HighCardVals2)
                    {
                        cout << HandType << ", " << HandSuitType << ", " << HighCardType << " High beats " <<
                            HandType2 << ", " << HandSuitType2 << ", " << HighCardType2 << " High " << endl;
                    }
                    else if (HighCardVals < HighCardVals2)
                    {
                        cout << HandType << ", " << HandSuitType << ", " << HighCardType << " High loses to " <<
                            HandType2 << ", " << HandSuitType2 << ", " << HighCardType2 << " High " << endl;
                    }
                    else if (HighCardVals == HighCardVals2)
                    {
                        cout << HandType << ", " << HandSuitType << ", " << HighCardType << " High ties " <<
                            HandType2 << ", " << HandSuitType2 << ", " << HighCardType2 << " High " << endl;
                    }
                }

                //if HandVal == 10
                //then there will only be one option for the tie
                //a royal flush will always tie a royal flush
                else if (HandVal == 10)
                {
                    cout << HandType << ", " << HandSuitType << " ties " << HandType2 << ", " << HandSuitType2 << endl;
                }
            }
        }
    }

    InputFile.close();

    return 0;
}

/*----------------------------------------------------------------------------------------

The bubble sort array is used to sort the values of the HandRankValues in asecnding order

----------------------------------------------------------------------------------------*/

void BubbleSortArray(int HandValues[])
{
    bool swap;
    int temp;
    int ArraySize = 5;
    int size = ArraySize - 1;

    //While the bool swap is not false, the loop will continue to 
    //sort the contents of the HandValueRanks Array
    //once swap is true, then the sorting is completeed 
    do
    {
        swap = false;

        //the for loop steps through the HandRankValues(HandValues) Array
        for (int count = 0; count < size; count++)
        {

            //if the current position of the array
            //is greater than the next position,
            //then the two values are swapped
            if (HandValues[count] > HandValues[count + 1])
            {
                temp = HandValues[count];
                HandValues[count] = HandValues[count + 1];
                HandValues[count + 1] = temp;
                swap = true;
            }
        }
        size--;
    } while (swap != false);

}

/*-------------------------------------------------------------

The RoyalFlush function is used to determine if the given hand
is a royal flush, if the hand is a royal flush,
then the value returned is a 1 (true), if else, the value
is returned as a 0 (false)

-------------------------------------------------------------*/

bool RoyalFlush(string suit[], string HandSuits[], int HandValues[], const int Suit)
{
    int counter = 0;

    //the for loop steps through the SUITS(suit) array
    for (int index = 0; index < Suit; index++)
    {

        //the for loop steps through the HandSuits Array
        for (int index2 = 0; index2 < 5; index2++)
        {

            //if a value in the HandSuits Array is equal 
            //to a value in the suit Array, then counter is incremented by one
            if (HandSuits[index2] == suit[index])
            {
                counter++;
            }
        }

        //if the value of the counter is equal to 5(checks for 5 matching suits)
        //then the HandValues are check to see if they are a royal flush
        if (counter == 5)
        {

            //if the statement is true then the value returned is 1 (true)
            if (HandValues[0] == 0 &&
                HandValues[1] == 9 &&
                HandValues[2] == 10 &&
                HandValues[3] == 11 &&
                HandValues[4] == 12)
            {
                return 1;
            }
        }

        //the value of counter is set to 0
        counter = 0;
    }
    return 0;
}

/*-------------------------------------------------------------

The Flush function is used to determine if the given hand
is a flush, if the hand is a flush,
then the value returned is a 1 (true), if else, the value
is returned as a 0 (false)

-------------------------------------------------------------*/

bool Flush(string hand_suits[], string suit[], const int Suit)
{
    int counter = 0;

    //the for loop steps through the contents of the suit array
    for (int index = 0; index < Suit; index++)
    {
        counter = 0;

        //the for loop moves through the contents of the hand_suits array
        for (int index2 = 0; index2 < 5; index2++)
        {
            //if a value in the hand_suits array is equal to a value in the suits array
            //then the counter is incremented by one
            if (hand_suits[index2] == suit[index])
            {
                counter++;
            }
        }

        //if the value of the counter is equal to five, then the value returned is one (true)
        if (counter == 5)
        {
            return 1;
        }
    }
    return 0;
}

/*----------------------------------------------------------------

The StraightFlush function is used to determine if the given hand
is a straight flush, if the hand is a straight flush,
then the value returned is a 1 (true), if else, the value
is returned as a 0 (false)

---------------------------------------------------------------*/

bool StraightFlush(string suit[], string HandSuit[], int HandValues[], const int Suit)
{
    int counter = 0;

    //the for loop steps through the SUITS(suit) array
    for (int index = 0; index < Suit; index++)
    {

        //the for loop steps through the HandSuits Array
        for (int index2 = 0; index2 < 5; index2++)
        {

            //if a value in the HandSuits Array is equal 
            //to a value in the suit Array, then counter is incremented by one
            if (HandSuits[index2] == suit[index])
            {
                counter++;
            }
        }

        //if the value of the counter is equal to 5(checks for 5 matching suits)
        //then the HandValues are check to see if they are a straight flush
        if (counter == 5)
        {

            //the for loop moves through the contents of the HandValues Array to see
            //if they are a straight flush
            for (int index3 = 0; index3 <= 9; index3++)
            {

                //if the statement is true then the value returned is 1 (true)
                if (HandValues[0] == 0 + index3 &&
                    HandValues[1] == 1 + index3 &&
                    HandValues[2] == 2 + index3 &&
                    HandValues[3] == 3 + index3 &&
                    HandValues[4] == 4 + index3)
                {
                    return 1;
                }
            }
        }
        counter = 0;
    }
    return 0;
}

/*----------------------------------------------------------------

The Pair function is used to determine if the given hand
is a Pair, if the hand is a Pair,
then the value returned is a 1 (true), if else, the value
is returned as a 0 (false)

---------------------------------------------------------------*/
bool Pair(string rank[], string rank_suits[], const int ranks)
{
    int count = 0;

    //this for loop is used to step through the players hands and look for any pairs
    for (int index = 0; index < ranks; index++)
    {
        for (int index2 = 0; index2 < 5; index2++)
        {

            //when a value from the players hand matches the ranks
            //a counter will be incremented
            if (rank_suits[index2] == rank[index])
            {
                count++;
            }
        }

        //if the counters value is 2, then the value returned is a 1
        //indicating that a pair was found
        if (count == 2)
        {
            return 1;
        }

        count = 0;
    }

    return 0;
}

/*----------------------------------------------------------------

The TwoPair function is used to determine if the given hand
is has two pairs, if the hand has two pairs,
then the value returned is a 1 (true), if else, the value
is returned as a 0 (false)

---------------------------------------------------------------*/
bool TwoPair(string rank[], string rank_suits[], const int ranks)
{
    int count = 0;
    int twopair = 0;

    //this for loop is used to step through the players hands and look for any pairs
    for (int index = 0; index < ranks; index++)
    {
        for (int index2 = 0; index2 < 5; index2++)
        {
            //when a value from the players hand matches the ranks
            //a counter will be incremented
            if (rank_suits[index2] == rank[index])
            {
                count++;
            }
        }

        //if the counters value is 2, then the twopair counter is incremented by 1
        if (count == 2)
        {
            twopair++;
        }

        //if the twopair value is 2, then the value returned is 1
        //indicating that two pairs were found
        if (twopair == 2)
        {
            return 1;
        }
        count = 0;
    }

    return 0;
}

/*----------------------------------------------------------------

The FourOfAKind function is used to determine if the given hand
is a four of a kind, if the hand is a four of a kind,
then the value returned is a 1 (true), if else, the value
is returned as a 0 (false)

---------------------------------------------------------------*/
bool FourOfAKind(string rank[], string rank_suits[], const int ranks)
{
    int count = 0;

    //this for loop is used to step through the players hands and look for any four of a kinds
    for (int index = 0; index < ranks; index++)
    {
        for (int index2 = 0; index2 < 5; index2++)
        {
            //when a value from the players hand matches the ranks
            //a counter will be incremented
            if (rank_suits[index2] == rank[index])
            {
                count++;
            }
        }

        //if the counters value is 4, then the value returned is a 1
        //indicating that a four of a kind was found
        if (count == 4)
        {
            return 1;
        }
        count = 0;
    }

    return 0;
}

/*----------------------------------------------------------------

The ThreeOfAKind function is used to determine if the given hand
is a three of a kind, if the hand is a three of a kind,
then the value returned is a 1 (true), if else, the value
is returned as a 0 (false)

---------------------------------------------------------------*/
bool ThreeOfAKind(string rank[], string rank_suits[], const int ranks)
{
    int count = 0;

    //this for loop is used to step through the players hands and look for any three of a kinds
    for (int index = 0; index < ranks; index++)
    {
        for (int index2 = 0; index2 < 5; index2++)
        {

            //when a value from the players hand matches the ranks
            //a counter will be incremented
            if (rank_suits[index2] == rank[index])
            {
                count++;
            }
        }

        //if the counters value is 3, then the value returned is a 1
        //indicating that a three of a kind was found
        if (count == 3)
        {
            return 1;
        }
        count = 0;
    }

    return 0;
}

/*----------------------------------------------------------------

The FullHouse function is used to determine if the given hand
is a Full House, if the hand is a Full House,
then the value returned is a 1 (true), if else, the value
is returned as a 0 (false)

---------------------------------------------------------------*/
bool FullHouse(string rank[], string rank_suits[], const int ranks)
{
    bool HousePair = 0;
    bool HouseThree = 0;

    int count = 0;

    //this for loop is used to step through the players hands and look for any pairs or three of a kinds
    for (int index = 0; index < ranks; index++)
    {
        for (int index2 = 0; index2 < 5; index2++)
        {

            //when a value from the players hand matches the ranks
            //a counter will be incremented
            if (rank_suits[index2] == rank[index])
            {
                count++;
            }
        }

        //if the counters value is 2, then the HousePair bool is changed to true
        //indicating that a pair was found
        if (count == 2)
        {
            HousePair = 1;
        }

        //if the counters value is 3, then the HouseThree bool is changed to true
        //indicating that a three of a kind was found
        if (count == 3)
        {
            HouseThree = 1;
        }

        //if both bools are true, then the value returned is 1
        //indicating that a full house was found
        if (HouseThree == 1 && HousePair == 1)
        {
            return 1;
        }

        count = 0;
    }

    return 0;
}

/*----------------------------------------------------------------

The Straight function is used to determine if the given hand
is a Straight, if the hand is a straight,
then the value returned is a 1 (true), if else, the value
is returned as a 0 (false)

---------------------------------------------------------------*/
bool Straight(string suits[], string hand_suits[], int HandRankVal[])
{
    int count = 0;
    int check = 0;

    //the for loop steps through the players suits hand to check for more than 2 suits
    //to ensure that the hand has the requirements for a straight
    for (int index = 0; index < 4; index++)
    {
        for (int index2 = 0; index2 < 5; index2++)
        {

            //if a suit from the players hand matches a suit from the suits array
            //then the counter is incremented
            if (suits[index] == hand_suits[index2])
            {
                count++;
            }
        }

        //if the counter is greater than 0, then check is incremented by 1
        if (count > 0)
        {
            check++;
        }

        count = 0;
    }

    //if check is greater than 2 or = to 2
    //then the if statements checks to see if the players hand is a straight
    if (check >= 2)
    {

        //the for loop is used to contains the if and for loop used to look
        //for a straight
        for (int index = 0; index < 1; index++)
        {
            //if the statement is true then counter is incremented by one
            if (HandRankVal[0] == 0 &&
                HandRankVal[1] == 9 &&
                HandRankVal[2] == 10 &&
                HandRankVal[3] == 11 &&
                HandRankVal[4] == 12)
            {
                count++;
            }

            //the for loop moves throught a series of given values
            for (int index3 = 0; index3 < 10; index3++)
            {

                //if the statement is true, then the counter is incremented by one
                if (HandRankVal[0] == 0 + index3 &&
                    HandRankVal[1] == 1 + index3 &&
                    HandRankVal[2] == 2 + index3 &&
                    HandRankVal[3] == 3 + index3 &&
                    HandRankVal[4] == 4 + index3)
                {
                    count++;
                }
            }

            //if the value of the counter is equal to one then the bool is changed to one (true)
            if (count == 1)
            {
                return 1;
            }
        }
    }

    return 0;
}

/*----------------------------------------------------------------

The ValueAssign function is used to assign values to a players hand
the values are used to check for all hands and highcards

---------------------------------------------------------------*/
void ValueAssign(string player[], string R[], string S[], string HS[], string HR[], int Rval[])
{
    //the for loop is used to step through the players hand
    for (int index = 0; index < 5; index++)
    {

        //the for loop is used to step through the suits
        for (int index2 = 0; index2 < 4; index2++)
        {

            //the for loop is used to step through the ranks
            for (int index3 = 0; index3 < 15; index3++)
            {

                //if a combination of suits and ranks matches the players current card
                //then a value is assigned to two arrays, 1 array for the rank of the card and another array for the suit of the card
                //and a value is assigned to another array to store the number of the rank
                if (player[index] == (R[index3] + S[index2]))
                {
                    HS[index] = S[index2];
                    HR[index] = R[index3];


                    //these if statements are used to assign a value to the rank hands array
                    if (HR[index] == "A")
                    {
                        Rval[index] = 0;
                    }

                    else if (HR[index] == "2")
                    {
                        Rval[index] = 1;
                    }

                    else if (HR[index] == "3")
                    {
                        Rval[index] = 2;
                    }

                    else if (HR[index] == "4")
                    {
                        Rval[index] = 3;
                    }

                    else if (HR[index] == "5")
                    {
                        Rval[index] = 4;
                    }

                    else if (HR[index] == "6")
                    {
                        Rval[index] = 5;
                    }

                    else if (HR[index] == "7")
                    {
                        Rval[index] = 6;
                    }

                    else if (HR[index] == "8")
                    {
                        Rval[index] = 7;
                    }

                    else if (HR[index] == "9")
                    {
                        Rval[index] = 8;
                    }

                    else if (HR[index] == "T")
                    {
                        Rval[index] = 9;
                    }

                    else if (HR[index] == "J")
                    {
                        Rval[index] = 10;
                    }

                    else if (HR[index] == "Q")
                    {
                        Rval[index] = 11;
                    }

                    else if (HR[index] == "K")
                    {
                        Rval[index] = 12;
                    }
                }
            }
        }
    }
}

/*-------------------------------------------------------------------

The HandValueGiver is used to assign a hand value to a players hand,
it also assigns the hand type and high cards needed if a tie occurs

------------------------------------------------------------------*/
void HandValueGiver(bool royalflush, bool straightflush, bool fourofakind, bool fullhouse, bool f_lush,
    bool straight, bool threeofakind, bool twopair, bool onepair, bool highcard, string& hand_type,
    int& hand_val, string HS[], string HR[], string S[], string R[], string& HT, string& FK, string& TK,
    string& PK, string& FT, string& FP, string TPV[], int& FKV, int& TKV, int& PKV, int& FTV,
    int& FPV, int tpv[])
{
    int c = 0;
    int p = 0;

    //if the players hand is a royal flush then the suit type and values for a royal flush are assigned to the players hand
    if (royalflush == 1)
    {
        hand_type = "ROYAL FLUSH";
        hand_val = 10;

        //the for loop steps through the players suits and the suits array 
        for (int index = 0; index < 5; index++)
        {

            //if a value from both hands matches then the c counter is incremented
            for (int index2 = 0; index2 < 5; index2++)
            {
                if (HS[index2] == S[index])
                {
                    c++;
                }
            }

            //if the c counters value is 5, and a position in the array matches the counter
            //then the suit type for the hand is assigned
            if (c == 5)
            {
                if (S[index] == "D")
                {
                    HT = "Diamonds";
                }
                else if (S[index] == "S")
                {
                    HT = "Spades";
                }
                else if (S[index] == "C")
                {
                    HT = "Clubs";
                }
                else if (S[index] == "H")
                {
                    HT = "Hearts";
                }
            }

            c = 0;
        }
    }
    //if the players hand is a straight flush then the suit type and values for a straight flush are assigned to the players hand
    else if (straightflush == 1)
    {
        hand_type = "STRAIGHT FLUSH";
        hand_val = 9;

        //the for loop steps through the players suits and the suits array 
        for (int index = 0; index < 5; index++)
        {
            for (int index2 = 0; index2 < 5; index2++)
            {
                if (HS[index2] == S[index])
                {
                    c++;
                }
            }
            //if the c counters value is 5, and a position in the array matches the counter
            //then the suit type for the hand is assigned
            if (c == 5)
            {
                if (S[index] == "D")
                {
                    HT = "Diamonds";
                }
                else if (S[index] == "S")
                {
                    HT = "Spades";
                }
                else if (S[index] == "C")
                {
                    HT = "Clubs";
                }
                else if (S[index] == "H")
                {
                    HT = "Hearts";
                }
            }

            c = 0;
        }
    }
    //if the players hand is a four of a kind
    //then values for a four of a kind are assigned to the players hand
    else if (fourofakind == 1)
    {
        hand_type = "FOUR OF A KIND";
        hand_val = 8;


        //the for loop steps through the ranks array
        for (int index = 0; index < 15; index++)
        {
            //the for loop steps through the players hand
            for (int index2 = 0; index2 < 5; index2++)
            {
                //if a value matches from both arrays then the c counter is incremented 
                if (HR[index2] == R[index])
                {
                    c++;
                }
            }

            //if the c counters value is 4, then the values needed for a four of a kind
            //are assigned to the hand 
            if (c == 4)
            {
                FK = R[index];
                FKV = index;

                //this checks for an ace four of a kind
                if (FKV == 0)
                {
                    FKV = 13;
                }
            }

            c = 0;
        }
    }
    //if the players hand is a full house
    //then values for a full house are assigned to the players hand
    else if (fullhouse == 1)
    {
        hand_type = "FULL HOUSE";
        hand_val = 7;

        //the for loop steps through the ranks array
        for (int index = 0; index < 15; index++)
        {

            //the for loop steps through the players hand
            for (int index2 = 0; index2 < 5; index2++)
            {
                //if a value matches from both arrays then the c counter is incremented 
                if (HR[index2] == R[index])
                {
                    c++;
                }
            }

            //if the c counters value is 2 then the values of the 
            //current arrays position are assigned to the full house pair
            if (c == 2)
            {
                FP = R[index];
                FPV = index;


                //checks for an ace pair
                if (FPV == 0)
                {
                    FPV = 13;
                }
            }

            //if the c counters value is 3 then the values of the 
            //current arrays position are assigned to the full house three of a kind
            else if (c == 3)
            {
                FT = R[index];
                FTV = index;

                //checks for an ace three of a kind
                if (FTV == 0)
                {
                    FTV = 13;
                }
            }

            c = 0;
        }
    }
    //if the players hand is a flush
    //then values for a flush are assigned to the players hand
    else if (f_lush == 1)
    {
        hand_type = "FLUSH";
        hand_val = 6;

        //the for loop steps through the players suits and the suits array 
        for (int index = 0; index < 5; index++)
        {
            //if a value from both hands matches then the c counter is incremented
            for (int index2 = 0; index2 < 5; index2++)
            {
                if (HS[index2] == S[index])
                {
                    c++;
                }
            }

            //if the c counters value is 5, and a position in the array matches the counter
            //then the suit type for the hand is assigned
            if (c == 5)
            {
                if (S[index] == "D")
                {
                    HT = "Diamonds";
                }
                else if (S[index] == "S")
                {
                    HT = "Spades";
                }
                else if (S[index] == "C")
                {
                    HT = "Clubs";
                }
                else if (S[index] == "H")
                {
                    HT = "Hearts";
                }
            }

            c = 0;
        }
    }
    //if the players hand is a straight
    //then values for a straight are assigned to the players hand
    else if (straight == 1)
    {
        hand_type = "STRAIGHT";
        hand_val = 5;
    }
    //if the players hand is a three of a kind
    //then values for a three of a kind are assigned to the players hand
    else if (threeofakind)
    {
        hand_type = "THREE OF A KIND";
        hand_val = 4;

        //the for loop steps through the ranks array
        for (int index = 0; index < 15; index++)
        {
            //the for loop steps through the players hand
            for (int index2 = 0; index2 < 5; index2++)
            {
                //if a value matches from both arrays then the c counter is incremented 
                if (HR[index2] == R[index])
                {
                    c++;
                }
            }

            //if the c counters value is 3, then the values needed for a three of a kind
            //are assigned to the hand 
            if (c == 3)
            {
                TK = R[index];
                TKV = index;

                //this checks for an ace three of a kind
                if (TKV == 0)
                {
                    TKV = 13;
                }
            }

            c = 0;
        }
    }
    //if the players hand is a two pair
    //then values for a two pair are assigned to the players hand
    else if (twopair == 1)
    {
        hand_type = "TWO PAIR";
        hand_val = 3;

        //the for loop steps through the ranks array
        for (int index = 0; index < 15; index++)
        {
            c = 0;
            //the for loop steps through the players hand
            for (int index2 = 0; index2 < 5; index2++)
            {
                //if a value matches from both arrays then the c counter is incremented 
                if (HR[index2] == R[index])
                {
                    c++;
                }
            }

            //if the value of c counter is 2, then p counter is incremented
            //and the pair value is assigned to the pair value array
            if (c == 2)
            {
                //this is used to look for the position of the array
                if (p == 0)
                {

                    //value is assigned to the array
                    TPV[p] = static_cast<string>(R[index]);
                    tpv[p] = index;

                    //checks for an ace pair
                    if (tpv[p] == 0)
                    {
                        tpv[p] = 13;
                    }
                    p++;
                }
                else
                {
                    //assigns a value to the array
                    TPV[p] = static_cast<string>(R[index]);
                    tpv[p] = index;

                    //checks for an ace pair
                    if (tpv[p] == 0)
                    {
                        tpv[p] = 13;
                    }
                }

            }
        }
    }
    //if the players hand is a pair
    //then values for a pair are assigned to the players hand
    else if (onepair == 1)
    {
        hand_type = "ONE PAIR";
        hand_val = 2;

        //the for loop steps through the ranks array
        for (int index = 0; index < 15; index++)
        {
            //the for loop steps through the players hand
            for (int index2 = 0; index2 < 5; index2++)
            {
                //if a value matches from both arrays then the c counter is incremented 
                if (HR[index2] == R[index])
                {
                    c++;
                }
            }

            //if the c counters value is 2, then the values needed for a pair
            //are assigned to the hand 
            if (c == 2)
            {
                PK = R[index];
                PKV = index;

                //this checks for an ace pair
                if (PKV == 0)
                {
                    PKV = 13;
                }
            }

            c = 0;
        }
    }
    //if the players hand is a high card
    //then values for a high card are assigned to the players hand
    else if (highcard == 1)
    {
        hand_type = "HIGH CARD";
        hand_val = 1;
    }
}

/*----------------------------------------------------------------

The HighCardVal function is used to assign a high card value to
a Players hand, as well as the type of High Card the card is

---------------------------------------------------------------*/

void HighCardVal(int& max_val, int HandRankVal[], string& type)
{
    max_val = HandRankVal[0];

    //the for loop checks for a 0, a 0 represents an Ace
    //and the highest value of 13 is assigned to the max_val
    //(the Ace is originally 0 to check for a wrap around for some hands)

    for (int index = 0; index < 5; index++)
    {
        if (HandRankVal[index] == 0)
        {
            max_val = 13;
        }
    }

    //this for loop checks for the highest card in the players hand and assigns it to the 
    //max_val
    for (int index = 0; index < 5; index++)
    {
        if (HandRankVal[index] > max_val)
        {
            max_val = HandRankVal[index];

        }
    }

    //the if statements assign the HighCard Symbol to the players hand
    if (max_val == 13)
    {
        type = "A";
    }
    else if (max_val == 1)
    {
        type = "2";
    }
    else if (max_val == 2)
    {
        type = "3";
    }
    else if (max_val == 3)
    {
        type = "4";
    }
    else if (max_val == 4)
    {
        type = "5";
    }
    else if (max_val == 5)
    {
        type = "6";
    }
    else if (max_val == 6)
    {
        type = "7";
    }
    else if (max_val == 7)
    {
        type = "8";
    }
    else if (max_val == 8)
    {
        type = "9";
    }
    else if (max_val == 9)
    {
        type = "10";
    }
    else if (max_val == 10)
    {
        type = "J";
    }
    else if (max_val == 11)
    {
        type = "Q";
    }
    else if (max_val == 12)
    {
        type = "K";
    }
}


/*----------------------------------------------------------------

The BoolReset function is used to set all bool values to false
to prepare them for the next hands that will be processed

---------------------------------------------------------------*/

void BoolReset(bool& a, bool& b, bool& c, bool& d, bool& e, bool& f, bool& g, bool& h, bool& i)
{
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
    f = 0;
    g = 0;
    h = 0;
    i = 0;
}
