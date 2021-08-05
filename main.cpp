#include<iostream>
#include<fstream>
using namespace std;

//Prototypes
int getLength(char arr[]);			//no need for this function either.
bool isWordMatched(char arr1[], char arr2[]);
void resetWord(char word[]);		//did not used this function.
bool isStopword(char word[]);
bool garbageword(char word[]);
void convertWordtoLowerCase(char word[]);
void getCounts(char word[], int& positive, int& negative);//this function will get the counts.
void getNormalizedCounts(char word[], double& nPositive, double& nNegative);//this function will get normalized count as explained in under normalization heading.

void Sentiment();
void bonus();
void reading();
void sort_file();



int main()
{
		

	Sentiment();									
	char ch;
	cout << "\n\nDo you want to run the bonus part of the question y/n  \n";
	do {
		cout << "Enter your choice: ";
		cin >> ch;
	} while (ch != 'y' && ch != 'n');
	
	if (ch == 'y')
		bonus();				//bonus part takes about 80-90seconds to finish and asks in the user if they want to sort the final bonus_dic.txt.
	else
		cout << "\nGOODBYE\n";
	return 0;
}

			



//Function to get the length of Char array.
int getLength(char arr[])
{
	int len = 0;
	for (int i = 0; arr[i] != '\0'; i++) {
		len++;
	}
	return len;
}


// comparison between word (to write on file data.txt) and word (already written in file data.txt)
// i.e. finding whether the word ispreviously present in file data.txt or not ? 
bool isWordMatched(char arr1[], char arr2[])
{
	const int size = 300;
	char word[size];
	int checkk;
	bool check = false;
	ifstream find;
	find.open("bonus_dic.txt");
	while (!find.eof()) {
		find >> word;
		checkk = strcmp(word, arr1);
		if (checkk == 0) {
			for (int i = 0; arr1[i] != '\0'; i++) {
				cout << arr1[i];
			}
			cout << " is Already written\n";
			check = false;
			return check;
		}
		else {
			check = true;
		}
	}
	find.close();
	return check;
}


void resetWord(char word[]) // initialize/ set char variable word to NULL (we are going to read new word from sentence)
{

}


bool isStopword(char word[]) // Check the word is stop word or not?
{
	bool check;
	ifstream finn;
	const int size = 200;
	char cmp_word[size];
	finn.open("stopwords.txt");
	if (finn.is_open()) {
		while (!finn.eof()) {
			finn >> cmp_word;
			if (strcmp(cmp_word, word) == 0) {
				check = true;
				return check;
			}
		}
	}

	check = false;
	return check;
}

bool garbageword(char word[])
{
	bool check;
	for (int i = 0; word[i] != '\0'; i++) {
		if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) {
			continue;
		}
		else {
			check = true;
			return check;
		}	
	}
	check = false;
	return check;
}

void convertWordtoLowerCase(char word[]) // conversion to lower case
{
	for (int i = 0; word[i] != '\0'; i++) {
		if (word[i] >= 'A' && word[i] <= 'Z') {
			word[i] = word[i] - 'A' + 'a';
		}

	}
}


void getCounts(char word[], int& positive, int& negative)
{
	int total;
	int pos;
	int neg;
	ifstream fi;
	const int size = 200;
	char cmp_word[size];
	fi.open("dictionary.txt");
	if (fi.is_open()) {
		while (!fi.eof()) {
			fi >> cmp_word;
			if (strcmp(cmp_word, word) == 0) {
				fi >> total;
				fi >> pos;
				positive = positive + pos;
				fi >> neg;
				negative = negative + neg;
				break;
			}
			else
				fi.ignore(size, '\n');
		}
	}
		//cout << "Dictionary.txt is not opened to calculate Count\n";
}

void getNormalizedCounts(char word[], double& nPositive, double& nNegative)
{
	double total;
	double pos;
	double neg;
	ifstream fi;
	const int size = 200;
	char cmp_word[size];
	fi.open("dictionary.txt");
	if (fi.is_open()) {
		while (!fi.eof()) {
			fi >> cmp_word;
			if (strcmp(cmp_word, word) == 0) {
				fi >> total;
				fi >> pos;
				pos = pos / total;
				nPositive = nPositive + pos;
				fi >> neg;
				neg = neg / total;
				nNegative = nNegative + neg;
				break;
			}
			else
				fi.ignore(size, '\n');
		}
	}
	else
		cout << "Dictionary.txt is not opened to calculate Normalized Count\n";
}



	
void Sentiment() {

	

	int pos = 0;
	int neg = 0;
	double poss = 0.0;
	double negg = 0.0;
	bool check;
	bool check1 = 0;
	const int word_size = 100;
	char word[word_size];
	const int size = 300;
	//int word_len;					not used
	//char arr[size];				not used
	int choice;
	

	cout << "\n\nDo you want to read from the file or Input your own sentence. \n Enter 1: to read from the file. \n Enter 2: to enter your own sentence.\n";
	char temp[size];
	

	do {
		cout << "Enter your choice: ";
		cin >> choice;
	} while (choice != 1 && choice != 2);
	cout << "\n\n";
	if (choice == 2) {
		cout << "Enter your sentence:";
		cin.ignore();
		cin.getline(temp,size);
		ofstream fout;
		fout.open("smallraw.txt");
		fout << temp;
		fout.close();
	}
	ifstream fin;
	fin.open("smallraw.txt");
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin >> word;
			cout << word << ' ';
			check = garbageword(word);
			if (check == false) {
				check1 = isStopword(word);
			}
			if (check1 == false && check == false) {
				convertWordtoLowerCase(word);
				getCounts(word, pos, neg);
				getNormalizedCounts(word, poss, negg);
			}
		}
		fin.close();
	}
	else
		cout << "File is not Opened: \n";


	//fin.getline(arr, size);
	//word_len = getLength(arr);
	//cout << word_len << endl;
	cout << "\n\nWithout Normalization:";
	cout << "\nPositive Count = " << pos;
	cout << "\nNegative Count = " << neg << '\n';
	if (pos >= neg) {
		cout << "Text is positive. \n";
	}
	else
		cout << "Text is negative. \n";

	cout << "\n\nWith Normalization: ";
	cout << "\nPositive Count = " << poss;
	cout << "\nNegative Count = " << negg << '\n';

	if (poss >= negg) {
		cout << "Text is positive. \n";
	}
	else
		cout << "Text is negative. \n";
	
}	



void bonus() {
	reading();
	//removing sentences with space
	const int size = 300;
	char s[size];
	ifstream r;
	r.open("data.txt");
	ofstream w;
	w.open("new_data.txt");
	while (!r.eof()) {
		r.getline(s, size, '\n');
		if (s[0] == ' ') {
			cout << "DELETE";
		}
		else
		{
			for (int i = 0; s[i] != '\0'; i++) {
				w << s[i];
			}
			w << endl;
		}
	}
	r.close();
	w.close();
	cout << '\n';

	//removing dups
			
	bool check_bonus = false;
	char word_dic[size];
	char word_dic_cmp[size];
	int total = 0;
	int positive = 0;
	int negative = 0;
	int t = 0;
	int p = 0;
	int n = 0;
	ifstream readd;
	readd.open("new_data.txt");
	ifstream readd1;
	readd1.open("new_data.txt");
	ofstream file;
	file.open("bonus_dic.txt");
	while (!readd.eof()) {
		readd >> word_dic;
		readd.ignore(size, '\n');
		readd1.clear();
		readd1.seekg(0, ios::beg);
		check_bonus = isWordMatched(word_dic, word_dic);
		if (check_bonus == true) {
			while (!readd1.eof()) {
				readd1 >> word_dic_cmp;
				if (strcmp(word_dic, word_dic_cmp) == 0) {
					readd1 >> t >> p >> n;
					total = total + t;
					positive = positive + p;
					negative = negative + n;
				}
				readd1.ignore(size, '\n');
			}
		}
		if (check_bonus == true) {
			for (int i = 0; word_dic[i] != '\0'; i++) {
				file << word_dic[i];
				cout << word_dic[i];
			}
			file << ' ' << total << ' ' << positive << ' ' << negative << endl;
			cout << ' ' << total << ' ' << positive << ' ' << negative;
			total = 0;
			positive = 0;
			negative = 0;
			cout << " is written succesfully in the bonuc_dic.txt.\n";
		}

	}
	int choice;
	cout << "Do you want to sort the bonus_dic.txt alphabetically ! \n";
	do {
		cout << "Enter 1: To Sort\nEnter 2: To Exit\nEnter your choice: ";
		cin >> choice;
	} while (choice != 1 && choice != 2);
	if (choice == 1)
	{
		sort_file();
		cout << "\nBonus_dic.txt is sorted and stored in the file name sorted_dic.txt succesfully! \n GOODBYE\n";
	}
	else
		cout << "\n\n GOODBYE\n";

}





void reading()
{
	bool check = false;
	bool check1 = false;
	const int size = 300;
	char word[size];
	char sentence[size];
	ifstream read;
	ofstream fout;
	int lensen = 0;
	int wordlen = 0;
	int sentiment = 42;
	int count = 0;
	int j = 0;
	int i = 0;
	int len;
	read.open("bonus.txt");
	fout.open("data.txt");
	if (read.is_open()) {
		while (!read.eof()) 
		{
			read >> sentiment;
			j = 0;
			read.getline(sentence, size, '\n');
			do {
				i = 0;
				for (; ; i++) {
					word[i] = sentence[j];
					if (sentence[j] == ' ') {
						j++;
						break;
					}
					if (sentence[j] == '\0') {
						j++;
						break;
					}
					j++;
				}
				word[i] = '\0';
				check = garbageword(word);
				if (check == false) {
					check1 = isStopword(word);
				}
				if (check1 == false && check == false) {
					convertWordtoLowerCase(word);
					if (sentiment == 1) {
						fout << word << ' ' << 1 << ' ' << 1 << ' ' << 0 << '\n';
						cout << "Printed Positive\n";
					}
					else if (sentiment == 0) {
						fout << word << ' ' << 1 << ' ' << 0 << ' ' << 1 << '\n';
						cout << "Printed Negative\n";
					}
				}
				len = strlen(sentence);
			} while (j < len);
		}
	}
	read.close();
	fout.close();
}

void sort_file()
{
	char filename[] = "bonus_dic.txt";
	char line[100], temp[100];
	int total_lines = -1;
	int  x = -1; //counter for temp[100]
	char** words; //dynamic allocation for 2darray (pointer to pointer)
	int done = 0;
	ifstream fin(filename);
	while (!fin.eof())
	{
		fin.getline(line, 100, '\n');
		total_lines++;
	}
	fin.clear();
	fin.seekg(0, ios::beg);
	//dynamic allocation 2darray
	words = new char* [total_lines];
	for (int i = 0; i < total_lines; i++)
	{
		words[i] = new char[100];
		fin.getline(words[i], 100, '\n');
	}
	//sorting begins
	for (int i = 0; i < total_lines - done; i++)			//done reduce the loop cycles as it skips the last line after every sort.
	{
		for (int j = 0; j < total_lines - 1; j++)
		{
			for (int k = 0; words[j][k] != '\0'; k++)
			{
				if (words[j][k] < words[j + 1][k])
				{
					break;
				}
				else if (words[j][k] > words[j + 1][k])
				{
					//swapping
					do {
						x++; temp[x] = words[j][x];
					} while (words[j][x] != '\0'); x = -1;
					do {
						x++; words[j][x] = words[j + 1][x];
					} while (words[j + 1][x] != '\0'); x = -1;
					do {
						x++; words[j + 1][x] = temp[x];
					} while (temp[x] != '\0'); x = -1;
					break;
				}
			}
		}
		done++;
	}
	//writing sorted data to temp file
	ofstream fout("sorted_dic.txt");
	for (int i = 0; i < total_lines; i++)
	{
		fout << words[i] << endl;
	}
	fin.close(); fout.close();

	delete[]words;
}