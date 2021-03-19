/*
 * project3.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: aranawillow
 */

// Proejct 3 Spring 2021 Skeleton code

#include<iostream>

using namespace std;

// myString class and corresponding methods come here
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
class webLinks {

	friend ostream& operator << (ostream& s, webLinks& A);
	protected:
		myString URL;
		int currLinks;
		int numLinks;
		int numLinked;
		webLinks** hyperLinks;
		webLinks** hyperLinked;

	public:
		webLinks ();
		webLinks (myString& x, int n);
		~webLinks ();
		int getNumLinks();
		int getNumLinked();
		webLinks* getHyperLink(int i);
		webLinks* getHyperLinked(int i);
		myString& getURL();
        void addSite(myString& t);
		void addNeighbor(webLinks& link);
        void setNeighbors(int nei);
        void addHyperLinked(webLinks& link);


};

ostream& operator << (ostream& s, webLinks& A)
{
	s << A.URL;
	return s;
}

webLinks::webLinks()
{
	URL = NULL;
	numLinked = 0;
	numLinks = 0;
	hyperLinks = NULL;
	hyperLinked = NULL;
	currLinks = 0;
}

webLinks::webLinks(myString& x, int n)
{
	URL = x;
	numLinks = n;
	numLinked = 0;
	hyperLinks = new webLinks*[n];
	currLinks = 0;
	hyperLinked = NULL;
}

myString& webLinks::getURL()
{
	myString* copy = new myString(URL);
	return *copy;
}

int webLinks::getNumLinks()
{
	return numLinks;
}

webLinks* webLinks::getHyperLink(int i)
{
	return hyperLinks[i];
}
webLinks* webLinks::getHyperLinked(int i) {
	return hyperLinked[i];
}

webLinks::~webLinks()
{
	URL = NULL;
	numLinks = 0;
	numLinked = 0;
	currLinks = 0;
	if(hyperLinks != NULL) {
		for(int i = 0; i < numLinks; ++i) {
			delete hyperLinks[i];
		}
		delete [] hyperLinks;
	}
	if(hyperLinked != NULL) {
		for(int i = 0; i < numLinked; ++i) {
			delete hyperLinked[i];
		}
		delete [] hyperLinked;
	}

}

void webLinks::addSite(myString& t)
{
	webLinks* toAdd = new webLinks(t,0);
	addNeighbor(*toAdd);
}
void webLinks::addHyperLinked(webLinks& link) {
	webLinks** temp = new webLinks*[numLinked + 1];
	for(int i = 0; i < numLinked; ++i) {
		temp[i] = hyperLinked[i];
	}
	(*hyperLinked)[numLinked + 1] = link;
	if(hyperLinked != NULL) {
		delete [] hyperLinked;
	}
	hyperLinked = temp;
	++numLinked;
}

void webLinks::setNeighbors(int nei)
{
	numLinks = nei;
}

void webLinks::addNeighbor(webLinks& link)
{
	(*hyperLinks)[currLinks] = link;
	++currLinks;
	link.addHyperLinked(*this);
}
int main () {

	int numSites;
	int siteNo;
	int numNeighbors;
	int neighbor;

    char* token;
	myString* tokenString;

	cin >> numSites;
    cout << "Number of websites: " << numSites << endl;

	webLinks* myWeb = new webLinks [numSites];
	for (int i=0; i < numSites; i++)
	{
        // read all URL and store them in the myWeb array of webLink objects
	}

    // store the neighbours/hyperlinks
	for (int i = 0; i < numSites; i++)
	{
		cin >> siteNo >> numNeighbors;
		myWeb[i].setNeighbors(numNeighbors);
		for (int j=0; j < numNeighbors; j++)
		{
			cin >> neighbor;
			myWeb[siteNo].addNeighbor ((myWeb[neighbor]));
		}
	}

    // display all webLink objects using the overloaded << operator

	cout << "~~~~~Webpages contained as hyperLinks:" << endl;
    // display all the incoming nodes here

	delete [] myWeb;

	return 0;
}



