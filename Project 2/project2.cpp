/*
 * project2.cpp
 *
 *  Created on: Feb 19, 2021
 *      Author: aranawillow
 */

#include <iostream>
using namespace std;

// used to empty a given string A of length n
void emptyString (char* A, int n) {
	for (int i=0; i < n; i++)
	{A[i] = '\0';}
	}

// copy a string A to B of length n
void stringCopy (char* A, int n, char* B) {
	for (int i=0; i < n; i++) {
	B[i] = A[i];
	}
	}

// return the length of a given string A
int stringLength (char* A) {
	int size = 0;
	while (A[size] != '\0')
	size++;
	return size; //size is the last index position
	}

class myString;
class myString {
	friend ostream& operator << (ostream& s, myString& A);
	protected:
		char* strArray;
		int size;
		void strCpy (char* A, char* B, int n);
	public:
		myString ();
		myString(char* inpStr);
		myString (myString& B);
		int Size();
		char* getWord();
	    bool operator == (myString& B);
	    bool operator > (myString& B);
	    bool operator < (myString& B);
	    myString& operator = (myString& B);
	    myString& operator = (char* B);
	    ~myString();
	    };

// outputs a given string A
ostream& operator << (ostream& s, myString& A) {
	s << A.strArray;
	return s;
}
// default constructor - initializes with a NULL as the first character
myString::myString () {
	size = 0;
	strArray = new char[1];
	strArray[0] = '\0';
}
// non default constructor - initialize object with an existing string
myString::myString (char* inpStr) {
	int i = 0;
	while (inpStr[i] != '\0')i++;
	size = i;
	strArray = new char[size];
	emptyString (strArray, size+1);
	for (int j=0; j < size; j++)
		strArray[j] = inpStr[j];
}
// non default constructor - initialize object with an existing mystring object
myString::myString (myString& B) {
	delete [] strArray;
	strArray = NULL;
	size = B.size;
	strArray = new char[size];
	emptyString(strArray, size+1);
	stringCopy (B.strArray, size, strArray);
}
char* myString::getWord(){
	return strArray;
}
// getter for size of myString
int myString::Size () {
	return size;
}
// overloading = operator - initialize object with an existing string
myString& myString::operator = (char* B) {
	int i = 0;
		while (B[i] != '\0')i++;
		size = i;
		strArray = new char[size];
		emptyString (strArray, size+1);
		for (int j=0; j < size; j++)
			strArray[j] = B[j];
	return *this;
}
// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {
	delete [] strArray;
		strArray = NULL;
		size = B.size;
		strArray = new char[size];
		emptyString(strArray, size+1);
		stringCopy (B.strArray, size, strArray);
	return *this;
}
// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {
	if(size == B.size ){
		bool same = true;
		for(int i = 0; i < size; ++i) {
			if(strArray[i] != B.strArray[i]) {
				same = false;
			}
		}
		return same;
	}
	else {
	return false;
	}
}
// comparison of myString A if less than myString B - return true or false
bool myString::operator < (myString& B) {
	int smallestSize;
	int firstDiff = -1;
	bool sameSize = false;
	bool bBigger = false;
	bool aCapital = false;
	bool bCapital = false;
	bool firstDiffFound = false;

	if(((strArray[0] <= 'Z') && (B.strArray[0] >= 'a'))) {
		aCapital = true;
	}
	else if (((strArray[0] >= 'Z') && (B.strArray[0] < 'a'))) {
		bCapital = true;
	}

	if(aCapital) {
		return true;
	}

	if(bCapital) {
		return false;
	}

	if(size < B.size) {
		smallestSize = size;
		bBigger = true;
	}
	else if(size == B.size) {
		smallestSize = size;
		sameSize = true;
	}
	else {
		smallestSize = B.size;
	}

	for(int i = 0; i < smallestSize && !firstDiffFound; ++i) {
		if(strArray[i] != B.strArray[i]) {
			firstDiff = i;
			firstDiffFound = true;
		}
	}

	if(firstDiffFound) {
		if(strArray[firstDiff] > B.strArray[firstDiff]) {
			return false;
		}
		else {
			return true;
		}
	}
	else if((!firstDiffFound) && sameSize) {
		return false;
	}
	else {
		if(bBigger) {
			return true;
		}
		else {
			return false;
		}
	}
	//compare each value in strArray and find first one to be different
	//compare that value to know which is smaller
	//if they have all the same values at the end of the smallest size,
	//and same size is not true then bigger size is greater
	//if same size is true at that point return false
return false;
}
// comparison of myString A if greater than myString B - return true or false
bool myString::operator > (myString& B) {
	int smallestSize;
		int firstDiff = -1;
		bool sameSize = false;
		bool bBigger = false;
		bool aCapital = false;
		bool bCapital = false;
		bool firstDiffFound = false;

		if(((strArray[0] <= 'Z') && (B.strArray[0] >= 'a'))) {
			aCapital = true;
		}
		else if (((strArray[0] >= 'Z') && (B.strArray[0] <= 'a'))) {
			bCapital = true;
		}

		if(aCapital) {
			return false;
		}

		if(bCapital) {
			return true;
		}

		if(size < B.size) {
			smallestSize = size;
		   bBigger = true;
		}
		else if(size == B.size) {
			smallestSize = size;
			sameSize = true;
		}
		else {
			smallestSize = B.size;
		}

		for(int i = 0; i < smallestSize && !firstDiffFound; ++i) {
			if(strArray[i] != B.strArray[i]) {
				firstDiff = i;
				firstDiffFound = true;
			}
		}

		if(firstDiffFound) {
			if(strArray[firstDiff] < B.strArray[firstDiff]) {
				return false;
			}
			else {
				return true;
			}
		}
		else if((!firstDiffFound) && sameSize) {
			return false;
		}
		else {
			if(bBigger) {
				return false;
			}
			else {
				return true;
			}
		}
	return false;
}

myString::~myString() {
	if(strArray != NULL) {
		delete [] strArray;
	}
}
// get one token from redirected input and return that string (alphanumeric)
char* getNextToken () {
	char* str = new char[20]; //assumes a max token size of 20
	emptyString (str, 20);
	char c;
	int i = 0;
	while (!cin.eof()) {
		cin.get(c);
		if (!cin.eof ()) {
			if ((c != '\n') && (c != ' ')) {
				if ( ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')) )
					str[i++] = c;
			}
			else if ((c == '\n') && (i > 0))
				return str;
			else if ((c == ' ') && (i > 0))
				return str;
		}
	}
	if (i > 0) return str;
	else return NULL;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class bagOfWords {
	private:
		int binarySearchAndInsert (myString& W);
		int binarySearch(myString& wordToFind, int first, int last);
		void merge(int l, int m, int r);
		void mergeSort(int l, int r);

	protected:
		myString* _words;
		int* _frequencies;
		int _size;

	public:
		bagOfWords ();
		bagOfWords (int numOfWords);
		myString* get_Words();
		int* get_Freq();
		int get_size();
		void setSize(int i);
		void addWord (myString& W); //insert word w into the array _words - keep it sorted alphabetically
		void sortFreq(); //sort words array based on frequency
		void sortWords(); //sort words array alphabetically
		void display(); //print word followed by a colon followed by a single space and frequencuy
		bagOfWords* removeStopWords(myString* stopWords, int numStopWords); //stopWords from _words array
		~bagOfWords();
};

// default constructor - initializes with no words
bagOfWords::bagOfWords(){
	_size = 0;
	_words = new myString[0];
	_frequencies = new int[0];
}

// non default constructor - initializes with a known number of words
bagOfWords::bagOfWords (int numOfWords){
	_size = numOfWords;
	_words = new myString[numOfWords];
	_frequencies = new int[numOfWords];
}

myString* bagOfWords::get_Words(){
	return _words;
}

int* bagOfWords::get_Freq(){
	return _frequencies;
}

int bagOfWords::get_size(){
	return _size;
}

void bagOfWords::setSize(int i){
	_size = i;
}

// print the bag of words in dictionary format
void bagOfWords::display(){
	cout << "Bag of Words: " << _size << endl;
	for(int i = 0; i < _size; ++i) {
		cout << _words[i] << ": " << _frequencies[i] << endl;
	}
	}

// sort the _words and _frequencies based on frequencies
void bagOfWords::sortFreq(){
	//find the max frequency
	//using a for loop, step through each frequency and add each word of that
	//to a temporary array, then add all of those to another _words2 array keeping track of
	//the last index.
	int maxFreq = 0;
	for(int i = 0; i < _size; ++i) {
		if(_frequencies[i] > maxFreq) {
			maxFreq = _frequencies[i];
		}
	}

	myString* tempWords = new myString[_size];
	int* tempFreq = new int[_size];
	int nextSpot = 0;
	for(int i = 1; i <= maxFreq; ++i) {
		for(int j = 0; j < _size; ++j) {
			if(_frequencies[j] == i) {
				tempWords[nextSpot] = _words[j];
				tempFreq[nextSpot] = _frequencies[j];
				++nextSpot;
			}
		}
	}
	//copy tempWords and tempFreq over to _words and _frequencies
	if(_words != NULL) {
			delete[] _words;
		}
		if(_frequencies != NULL) {
			delete[] _frequencies;
		}

		_words = tempWords;
		_frequencies = tempFreq;
	}

void bagOfWords::merge( int l, int m, int r) {
	int size1 = m - l + 1;
	int size2 = r - m;


	myString* temp1 = new myString[size1];
	myString* temp2 = new myString[size2];
	int* fTemp1 = new int[size1];
	int* fTemp2 = new int[size2];

	for(int i = 0; i < size1; ++i) {
		temp1[i] = _words[l + i];
		fTemp1[i] = _frequencies[l + i];
	}
	for(int j = 0; j < size2; ++j) {
		temp2[j] = _words[m + j + 1];
		fTemp2[j] = _frequencies[m + j + 1];
	}

	int i = 0;
	int j = 0;
	int k = l;

	while(i < size1 && j < size2) {
		if(temp1[i] < temp2[j] || temp1[i] == temp2[j]) {
			_words[k] = temp1[i];
			_frequencies[k] = fTemp1[i];
			++i;
		}
		else {
			_words[k] = temp2[j];
			_frequencies[k] = fTemp2[j];
			++j;
		}
		++k;
	}

	while(i < size1) {
		_words[k] = temp1[i];
		_frequencies[k] = fTemp1[i];
		++i;
		++k;
	}

	while(j < size2) {
		_words[k] = temp2[j];
		_frequencies[k] = fTemp2[j];
		++j;
		++k;
	}
	delete [] temp1;
	delete [] temp2;
}

void bagOfWords::mergeSort(int l, int r) {
	if(l < r) {
		int mid = (r + l) / 2;
		mergeSort(l, mid);
		mergeSort(mid + 1, r);
		merge(l, mid, r);
	}
}

// sort the _words and _frequencies, alphabetically
void bagOfWords::sortWords(){
	mergeSort(0, _size - 1);
	}


bagOfWords* bagOfWords::removeStopWords(myString* stopWords, int numStopWords){
	// TODO
	bagOfWords* newBag = new bagOfWords();
	myString wordToAdd;
	bool doNotAdd = false;
	for(int i = 0; i < _size; ++i) {
		wordToAdd = _words[i];
		for(int j = 0; j < numStopWords; ++j) {
			if(wordToAdd == stopWords[j]) {
				doNotAdd = true;
			}
		}
		if(!doNotAdd) {
			for(int k = 0; k < _frequencies[i]; ++k) {
			newBag->addWord(wordToAdd);
			}
		}
		doNotAdd = false;
	}

	return newBag;
}

int bagOfWords::binarySearch(myString& W, int first, int last) {
	int mid;
	int result = -1;
	myString midval;

	if(first < last) {
		mid = (first + last) / 2;
		midval = _words[mid];
		if(W == midval) {
			++_frequencies[mid];
			result = -1;
		}
		else if(midval < W) {
			result = binarySearch(W, mid + 1, last);
		}
		else {
			result = binarySearch(W, first, mid);
		}
	}
	else {
		mid = (first + last) / 2;
		midval = _words[mid];
		if(W == midval) {
			++_frequencies[mid];
			result = -1;
		}
		else if((first == last) && _words[first] < W) {
			result = first + 1;
		}
		else {
			result = first;
		}
	}
	return result;
}
// to search for a given word in _words - returns 0 if not found, 1 if found
int bagOfWords::binarySearchAndInsert (myString& wordToFind){
	//find if it's already there and increment frequency if so

	//look at textbook to figure out how to do binary search and change the code below
	//if needed

	int location = binarySearch(wordToFind, 0, _size - 1);
	bool found;
	if(location == -1) {
		found = true;
	}
	else {
		found = false;
	}

	//re-do this part to insert instead of put at end and then re-sort
	//if it's not there make space and add it to the end and increment size class variable
	if(!found) {
		myString* resized = new myString[_size + 1];
		int* newFrequencies = new int[_size + 1];
		for(int i = 0; i < _size; ++i) {
			resized[i] = _words[i];
			newFrequencies[i] = _frequencies[i];
		}

		if(_words != NULL) {
			delete[] _words;
		}
		if(_frequencies != NULL) {
			delete[] _frequencies;
		}

		_words = resized;
		_frequencies = newFrequencies;
		_size = _size + 1;

		for(int i = _size - 1; i > location; i--) {
			_words[i] = _words[i - 1];
			_frequencies[i] = _frequencies[i - 1];
		}

		_words[location] = wordToFind;
		_frequencies[location] = 1;
	}
	if(found) {
		return 1;
	}
	else {
		return 0;
	}
}

// method to add words to the bagOfWords object
void bagOfWords::addWord(myString& newWord){
	binarySearchAndInsert(newWord);
	}

bagOfWords::~bagOfWords() {
	if(_words != NULL) {
		delete [] _words;
	}
	if(_frequencies !=NULL) {
		delete [] _frequencies;
	}
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main () {
	int numStopWords;
	char* token;
	myString* tokenString;

	//read the first number from the file that contains the number of stop words
	cin >> numStopWords;
	cout << "Number of Stop words: " << numStopWords << endl;
	myString* stopWordsList = new myString[numStopWords];

	//read the stop words
	for (int i=0; i < numStopWords; i++){
		token = getNextToken ();
		stopWordsList[i] = token; //calls the overloaded = operator on myStringclass
		}

	//Now read a text and put them in the bagOfWords instance.
	bagOfWords* myBag = new bagOfWords ();
	token = getNextToken();
	 while (token != NULL) {
		tokenString = new myString (token); //create a myString object with thetoken
		(*myBag).addWord(*tokenString); //add token to myBag
		token = getNextToken ();
	}






	// this should display the token and frequency;
	// note that becuase you are using binary search and insert the tokens will
	// be sorted alphabetically
	cout << endl;
	cout << "Input display:" << endl;
	(*myBag).display ();

	(*myBag).sortFreq ();
	cout << endl;
	cout << "myBag - Sorted based on frequency:" << endl;
	(*myBag).display ();

	(*myBag).sortWords();
	cout << endl;
	cout << "myBag - Sorted alphabetically:" << endl;
	(*myBag).display ();

	bagOfWords* newBag = (*myBag).removeStopWords(stopWordsList, numStopWords); // new parameter added here
	cout << endl;

	cout << "newBag - Sorted alphabetically:" << endl;
	(*newBag).display();
	(*newBag).sortFreq ();
	cout << endl;

	cout << "newBag - Sorted based on frequency:" << endl;
	(*newBag).display ();

	// TODO: destructors

	delete [] stopWordsList;
	delete myBag;
	delete newBag;


	}


