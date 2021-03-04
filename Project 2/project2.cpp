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
	for (int i=0; i < n; i++) //set each elemnt to '\'
	{A[i] = '\0';}
	}

// copy a string A to B of length n
void stringCopy (char* A, int n, char* B) {
	for (int i=0; i < n; i++) {
	B[i] = A[i]; //make a copy of each element and put it
				//into the other array
	}
	}

// return the length of a given string A
int stringLength (char* A) {
	int size = 0;
	while (A[size] != '\0') //only count elements that are valid
	size++;
	return size; //size is the last index position
	}

class myString;
class myString {
	friend ostream& operator << (ostream& s, myString& A);
	protected:
		char* strArray; //an array of chars that create a word when joined together
		int size; //the size of the strArray
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
	while (inpStr[i] != '\0')i++; //count up the number of valid elements
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
	stringCopy (B.strArray, size, strArray); //make a deep copy
}

//getter for the array of chars representing a word
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
		while (B[i] != '\0')i++; //count up the number of valid elements
		size = i; //the number of valid elements is the size
		strArray = new char[size];
		emptyString (strArray, size+1); //remove old elements
		for (int j=0; j < size; j++)
			strArray[j] = B[j]; //make a deep copy of the array
	return *this;
}
// overloading = operator - initialize object with an existing mystring object
myString& myString::operator = (myString& B) {
	//delete the old strArray to free up memory
	delete [] strArray;
		strArray = NULL;
		size = B.size;
		strArray = new char[size];
		//remove all old elements
		emptyString(strArray, size+1);
		//make a deep copy of the strArray
		stringCopy (B.strArray, size, strArray);
	return *this;
}
// checking if two myString objects are the same - return true or false
bool myString::operator == (myString& B) {
	//two myString objects can only be equal if they are the same size
	if(size == B.size ){
		bool same = true;
		for(int i = 0; i < size; ++i) {
			//check if there are any different elements
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

	//words that start with
	//capital letters are always smaller than words that
	//start with lower case letters
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

	//find the smaller size to know how many letters to compare
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

	//find the first character that is different
	for(int i = 0; i < smallestSize && !firstDiffFound; ++i) {
		if(strArray[i] != B.strArray[i]) {
			firstDiff = i;
			firstDiffFound = true;
		}
	}
	//if there is a different character, compare it
	//to see which is bigger
	if(firstDiffFound) {
		if(strArray[firstDiff] > B.strArray[firstDiff]) {
			return false;
		}
		else {
			return true;
		}
	}
	//if they are the same size and there are no differences,
	//they must be equal and therefore A could not be
	//less than B
	else if((!firstDiffFound) && sameSize) {
		return false;
	}
	else {
		//if there are no differences up to the length
		//of the first word, the longer one is greater
		if(bBigger) {
			return true;
		}
		else {
			return false;
		}
	}
	//if nothing else has been returned, something has failed
	//and we should not assume that it is true
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


		//words that start with capital letters are smaller than
		//words that start with lower case letters
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

		//find the smallest size to know which letters to
		//compare
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

		//find the first character that is different
		for(int i = 0; i < smallestSize && !firstDiffFound; ++i) {
			if(strArray[i] != B.strArray[i]) {
				firstDiff = i;
				firstDiffFound = true;
			}
		}
		//the first character that is different should be compared
		if(firstDiffFound) {
			if(strArray[firstDiff] < B.strArray[firstDiff]) {
				return false;
			}
			else {
				return true;
			}
		}
		//if there are no differences and the words are the
		//same size, they must be equal which means
		//A could not be greater than B
		else if((!firstDiffFound) && sameSize) {
			return false;
		}
		else {
			//if they are the same up until the length of
			//the longer one, the longer one is bigger
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
		myString* _words; //the list of words in the bagOfWords
		int* _frequencies; //the frequencies of each corresponding word in _words
		int _size; //the total number of words

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

//getter for the list of words
myString* bagOfWords::get_Words(){
	return _words;
}

//getter for the frequencies of each word
int* bagOfWords::get_Freq(){
	return _frequencies;
}

//getter for the total number of words
int bagOfWords::get_size(){
	return _size;
}

//set the total number of words
void bagOfWords::setSize(int i){
	_size = i;
}

// print the bag of words in dictionary format
void bagOfWords::display(){
	cout << "Bag of Words: " << _size << endl;
	//print each word in the list of words
	//followed by a colon and the corresponding frequency
	for(int i = 0; i < _size; ++i) {
		cout << _words[i] << ": " << _frequencies[i] << endl;
	}
	}

// sort the _words and _frequencies based on frequencies
void bagOfWords::sortFreq(){
	int maxFreq = 0;
	//find the maximum frequency in the list of frequencies
	for(int i = 0; i < _size; ++i) {
		if(_frequencies[i] > maxFreq) {
			maxFreq = _frequencies[i];
		}
	}
	//temporary arrays to add the words based on frequency
	myString* tempWords = new myString[_size];
	int* tempFreq = new int[_size];
	//keep track of the next spot to add
	int nextSpot = 0;
	//step through each possible frequency
	for(int i = 1; i <= maxFreq; ++i) {
		//step through each word in the words array
		for(int j = 0; j < _size; ++j) {
			//if this word has the desired frequency,
			//add it to the temporary array
			if(_frequencies[j] == i) {
				tempWords[nextSpot] = _words[j];
				tempFreq[nextSpot] = _frequencies[j];
				//move on to the next available spot
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

//merge two halves of an array into sorted order
void bagOfWords::merge( int l, int m, int r) {
	//The size of the first half of the array
	int size1 = m - l + 1;
	//The size of the second half of the array
	int size2 = r - m;

	//temporary arrays to hold both halves
	myString* temp1 = new myString[size1];
	myString* temp2 = new myString[size2];
	int* fTemp1 = new int[size1];
	int* fTemp2 = new int[size2];

	//copy the halves into the temporary arrays
	for(int i = 0; i < size1; ++i) {
		temp1[i] = _words[l + i];
		fTemp1[i] = _frequencies[l + i];
	}
	for(int j = 0; j < size2; ++j) {
		temp2[j] = _words[m + j + 1];
		fTemp2[j] = _frequencies[m + j + 1];
	}

	//current spot in the first half
	int i = 0;
	//current spot in the second half
	int j = 0;
	//current spot in the original array
	int k = l;

	//loop until one of the halves is full
	while(i < size1 && j < size2) {
		//find the smallest word of both halves and put it
		//into the main array at the next spot
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
	//fill with the remaining elements
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
	//delete the temporary arrays
	delete [] temp1;
	delete [] temp2;
}

//sort an array by repeatedly halving it and then
//merging it back into sorted order
void bagOfWords::mergeSort(int l, int r) {
	//while there are elements that can be divided into two
	//halves
	if(l < r) {
		//find the middle index
		int mid = (r + l) / 2;
		//sort the left half
		mergeSort(l, mid);
		//sort the right half
		mergeSort(mid + 1, r);
		//merge the two halves
		merge(l, mid, r);
	}
}

// sort the _words and _frequencies, alphabetically
void bagOfWords::sortWords(){
	//call merge sort to sort the words alphabetically
	mergeSort(0, _size - 1);
	}

//return a bagOfWords with the stop words removed
bagOfWords* bagOfWords::removeStopWords(myString* stopWords, int numStopWords){
	// create a new bag of words
	bagOfWords* newBag = new bagOfWords();
	//the current word to be added
	myString wordToAdd;
	//true if the current word to be added is a stop word
	bool doNotAdd = false;
	//walk through each word in the original list
	for(int i = 0; i < _size; ++i) {
		wordToAdd = _words[i];
		//compare it with each stop word
		for(int j = 0; j < numStopWords; ++j) {
			//if the word is a stop word, it should
			//not be added
			if(wordToAdd == stopWords[j]) {
				doNotAdd = true;
			}
		}
		//if the word can be added
		if(!doNotAdd) {
			//add the word, repeating until it reaches
			//its original frequency
			for(int k = 0; k < _frequencies[i]; ++k) {
			newBag->addWord(wordToAdd);
			}
		}
		//reset doNotAdd
		doNotAdd = false;
	}

	return newBag;
}

//search for a given word and return the index where it should be added if it is not found
//otherwise, return -1
int bagOfWords::binarySearch(myString& W, int first, int last) {
	int mid;
	int result = -1; //-t indicates that it was found
	myString midval;

	//while there is a section of words to look through
	if(first < last) {
		mid = (first + last) / 2;
		midval = _words[mid];
		//if the word is found, increment its frequency
		//and return -1
		if(W == midval) {
			++_frequencies[mid];
			result = -1;
		}
		else if(midval < W) {
			//search the upper half of the words
			result = binarySearch(W, mid + 1, last);
		}
		else {
			//search the lower half of the words
			result = binarySearch(W, first, mid);
		}
	}
	else {
		//check if the desired word is the last word
		if(W == _words[last]) {
			//increment its frequency if so
			++_frequencies[last];
			//return -1 since it was found
			result = -1;
		}
		//return the index that the word should be placed
					//compared to the closest word
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
//find where the word should be inserted or if it is already listed
	int location = binarySearch(wordToFind, 0, _size - 1);
	bool found;
	//if the location is -1, the word was found
	if(location == -1) {
		found = true;
	}
	else {
		found = false;
	}

	//if the word was not found, insert it
	if(!found) {
		//create bigger arrays with space for the new word
		myString* resized = new myString[_size + 1];
		int* newFrequencies = new int[_size + 1];
		//fill these with the original words
		for(int i = 0; i < _size; ++i) {
			resized[i] = _words[i];
			newFrequencies[i] = _frequencies[i];
		}
		//delete the old arrays
		if(_words != NULL) {
			delete[] _words;
		}
		if(_frequencies != NULL) {
			delete[] _frequencies;
		}
		//set _words and _frequencies to be the resized ones
		_words = resized;
		_frequencies = newFrequencies;
		//increment the size variable
		_size = _size + 1;
		//make room for the new array by moving each word
		//above it to the right by one
		for(int i = _size - 1; i > location; i--) {
			_words[i] = _words[i - 1];
			_frequencies[i] = _frequencies[i - 1];
		}
		//insert the word at its proper location
		_words[location] = wordToFind;
		//since it is being inserted for the first time,
		//its frequency is one
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
	//find and insert the new word
	binarySearchAndInsert(newWord);
	}

bagOfWords::~bagOfWords() {
	//delete the two dynamic class objects
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


	delete [] stopWordsList;
	delete myBag;
	delete newBag;


	}


