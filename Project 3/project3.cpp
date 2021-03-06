/*
 * project3.cpp
 *
 *  Created on: Mar 18, 2021
 *      Author: aranawillow
 */

// Proejct 3 Spring 2021 Skeleton code

#include<iostream>

using namespace std;

// myString class and corresponding methods
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
	if(strArray != NULL) {
	delete [] strArray;
	}
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
	char* str = new char[25]; //assumes a max token size of 20
	emptyString (str, 25);
	char c;
	int i = 0;
	while (!cin.eof()) {
		cin.get(c);
		if (!cin.eof ()) {
			if ((c != '\n') && (c != ' ')) {
				if ( ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')) || (c == '.') ||(c == '-') ||(c == '_'))
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
		myString URL; //the URL of the website
		int currLinks; //the current number of links
		int numLinks; //the total number of links
		webLinks** hyperLinks; //the hyperlinks contained in the website

	public:
		webLinks ();
		webLinks (myString& x, int n);
		~webLinks ();
		int getNumLinks();
		webLinks* getHyperLink(int i);
		myString& getURL();
        void addSite(myString& t);
		void addNeighbor(webLinks& link);
        void setNeighbors(int nei);


};

//prints out the URL of the website
ostream& operator << (ostream& s, webLinks& A)
{
	s << A.URL;
	return s;
}

//default constructor: initializes ints to 0 and dynamic arrays to size 0
webLinks::webLinks()
{
	numLinks = 0;
	hyperLinks = new webLinks*[0]; //create space in memory for the array of size 0
	currLinks = 0;
}

//non-default constructor: initialize the URL of the website and its number of hyperlinks
webLinks::webLinks(myString& x, int n)
{
	URL = x;
	numLinks = n;
	hyperLinks = new webLinks*[n]; //create space in memory for the array of size 0
	currLinks = 0; //this is 0 because no links have been added yet
}

//returns the URL of the website
myString& webLinks::getURL()
{
	return URL;
}

//returns the number of hyperlinks contained in the website
int webLinks::getNumLinks()
{
	return numLinks;
}

//returns a particular hyperlink at index i
webLinks* webLinks::getHyperLink(int i)
{
	return hyperLinks[i];
}

//destructor: set ints back to 0 and delete dynamically created objects
webLinks::~webLinks()
{
	numLinks = 0;
	currLinks = 0;
	if(hyperLinks != NULL) {
		delete [] hyperLinks;
	}

}

//set the URL of the website
void webLinks::addSite(myString& t)
{
	URL = t;
}

//set the number of neighbors of the website
void webLinks::setNeighbors(int nei)
{
	//create a new hyperLinks array with the desired number of neighbors
	hyperLinks = new webLinks*[nei];
	numLinks = nei;
}

//add a new neighbor to the website
void webLinks::addNeighbor(webLinks& link)
{
	hyperLinks[currLinks] = &link; //put the link in the next spot in the array
	++currLinks; //increment the current number of links because one is being added
}

int main () {

	int numSites; //the total number of websites
	int siteNo; //the current site number
	int numNeighbors; //the number of neighbors of the website
	int neighbor; //the index of the neighbor

    char* token; //a char array containing the input
	myString* tokenString; //the input contained as a myString object

	cin >> numSites;
    cout << "Number of websites: " << numSites << endl;

	webLinks* myWeb = new webLinks [numSites];
	for (int i=0; i < numSites; i++)
	{
		token = getNextToken(); //get the next token from the input file
		tokenString = new myString(token); //turn that token into a myString object
		myWeb[i].addSite(*(tokenString)); //set the URL of the current webLinks object
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
	cout << "~~~~~WebLinks: " << endl;
	for(int i = 0; i < numSites; ++i) {
		cout << myWeb[i] << ": " << endl; //print out each webLinks object
		for(int j = 0; j < myWeb[i].getNumLinks(); ++j) {
			cout << "** " << *(myWeb[i].getHyperLink(j)) << endl; //print out each hyperlink
		}
		cout << endl;
	}
	cout << "~~~~~Webpages contained as hyperLinks: " << endl;
    // display all the incoming nodes
	int counter = 0; //number of times a website has been a hyperlink, initialized to 0
	//array of the incoming nodes , initialized to size 0
	webLinks** incomingNodes = new webLinks*[0];
	//temporary array of webLinks pointers used for increasing the size of the incomingNodes
	//array
	webLinks** temp;
	for(int i = 0; i < numSites; ++i) { //step through each website
		//step through each website to see if it contains the original site as a hyperlink
		for(int j = 0; j < numSites; ++j ) {
			//step through the website's hyperlinks
 			for(int k = 0; k < myWeb[j].getNumLinks(); ++k) {
 				//check if the hyperLink is the original website
				if(myWeb[j].getHyperLink(k) == &myWeb[i]) {
					//create a temporary array with a greater size
					temp = new webLinks*[counter + 1];
					//copy over the incomingNodes array
						for(int l = 0; l < counter; ++l) {
							if(temp[l] == NULL) {
							temp[l] = new webLinks();
							}
							temp[l] = incomingNodes[l];
						}
						if(temp[counter] == NULL) {
						temp[counter] = new webLinks();
						}
						//add the new website in to the last spot of the temporary array
						temp[counter] = &myWeb[j];
						//set the incomingNodes array to be the temporary array
						incomingNodes = temp;
						//increment the number of websites that have the original as a
						//hyperlink
						++counter;
					}
				}
			}
		//print out the number of webpages that contained the original as a hyperlink
		cout << myWeb[i] << ": " << counter << endl;
		//print out each webpage that contained the original as a hyperlink
		for(int m = 0; m < counter; ++m) {
			cout << "** " << (*incomingNodes[m]) << endl;
		}
		if(!(i == (numSites - 1)))
		cout << endl;
		counter = 0;
		//delete the incomingNodes object since there will be different incomingNodes
		//for the next webpage
		delete [] incomingNodes;
		//reset the incomingNodes array to a new object of size 0
		incomingNodes = new webLinks*[0];
	}


	delete [] myWeb;
	delete [] incomingNodes;
	delete temp;

	return 0;
}



