#include <string>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


/*_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_*/
struct term {
	string  binary;

	bool    min = false; // True if it is a minterm
	bool operator == (const term &t) { return (binary == t.binary); }
	bool used = false; //Check if the term is used in any type of simplifications
	int     ones; //number of ones in each term
	int decimal;

	vector<int> track;// tracks the ess. imps.
};

vector<term>  EssPrimeImplicants;

void printVector(vector<term> &x) //For testing ONLY
{
	cout << "Vector Size = " << x.size() << endl;
	for (int i = 0; i < x.size(); i++)
	{
		//	cout << "Decimal: " << x[i].decimal << endl;
		cout << "Binary:" << x[i].binary << "\t\t\t";
		for (int j = 0; j < x[i].track.size(); j++)
			cout << x[i].track[j] << ", ";
		cout << endl;
	}
}

int onesCounter(string t) {    //This function takes a term object and return term with updated variable ones;
	int c = 0;
	for (int i = 0; i < t.size(); i++) {
		if (t[i] == '1') {
			c++;
		}
	}
	return c;
}

void sortVectorAccordingToBinary(vector<term>& minterm) {
    term x;
    term y;
    for (int i = 0; i < minterm.size(); i++) { // O(n^2)
        for (int j = 0; j < minterm.size(); j++) {
            if (minterm[i].binary < minterm[j].binary) {
                x = minterm[i];
                y = minterm[j];
                minterm[i] = y;
                minterm[j] = x;
            }
        }
    }
}

void removeDuplicates(vector<term> &vec){
    sortVectorAccordingToBinary(vec);
	if(vec.size())
    for (int i = 0; i < vec.size()-1 ;i++)
        if (vec[i] == vec[i + 1])
            vec.erase(vec.begin() + i);
     
    
}

void removeDontCares(vector<term> &vec) {
	removeDuplicates(vec);
	if (vec.size())
		for (int i = 0; i < vec.size(); i++)
			if (!vec[i].min)
				vec.erase(vec.begin() + i);
	removeDuplicates(vec);
}

void sortVectorAccordingToNumberOfOnes(vector<term>& minterm) {// Will not work until ones has a true value
	term x;
	term y;
	for (int i = 0; i < minterm.size(); i++) { // O(n^2)
		for (int j = 0; j < minterm.size(); j++) {
			if (minterm[i].ones < minterm[j].ones) {
				x = minterm[i];
				y = minterm[j];
				minterm[i] = y;
				minterm[j] = x;
			}
		}
	}
}

std::string decimalToBinaryString(int num, int numberOfVariables) { //Convert from Decimal to binary with the correct number of added zeros on the left
	std::string str;
	int rem;
	while (num > 0) {
		rem = num % 2;
		num /= 2;
		str.append(std::to_string(rem));
	}
	while (str.size()> numberOfVariables)   str = str.substr(1, str.size() - 1);
	while (str.size()< numberOfVariables)   str.append(std::to_string(0));
	std::reverse(str.begin(), str.end()); //Reverse the string 1000 = 0001
	return str;
}

bool checkAdjacency(term t1, term t2) {
	int c = 0;
	for (int i = 0; i< t1.binary.size(); i++) {
		if (t1.binary[i] != t2.binary[i]) {  //0001
			c++;                            //0000
		}
	}
	if (c == 1) {
		for (int i = 0; i < EssPrimeImplicants.size(); i++) {
			if ((EssPrimeImplicants[i] == t1 || EssPrimeImplicants[i] == t2))
				EssPrimeImplicants.erase(EssPrimeImplicants.begin() + i);
		}
	} 
	return (c == 1);
}

term combineTerms(term &t1, term &t2) {
	term temp;
	

	if (t1.track.size() == 0){
		temp.track.push_back(t1.decimal);
		temp.track.push_back(t2.decimal);
	}

	for (int i = 0; i < t1.track.size(); i++){
		temp.track.push_back(t1.track[i]);
		temp.track.push_back(t2.track[i]);
	}

	for (int i = 0; i< t1.binary.size(); i++) {
		if (t1.binary[i] == t2.binary[i]) {
			temp.binary.append(t1.binary.substr(i, 1));
		}
		else {
			temp.binary.append("x");
		}
	}
	if (t1.min || t2.min)
		temp.min = true;
	EssPrimeImplicants.push_back(temp);
	return temp;
}

vector<term> combineTwoVectors(vector<term> &A, vector<term>& B) {
	vector<term> C;
	term temp;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < B.size(); j++) {
			if (checkAdjacency(A[i], B[j])) {
				
				temp = combineTerms(A[i], B[j]);   										
				C.push_back(temp);
			}
			
		}
	}

	return C;
}

int Input(int variables, vector<term>& minterm) //User input and validation
{
	int totalTerms;
	int total = pow(2, variables);
	term process;
	/*------------------------------Minterms Entery-------------------------------*/
	cout << "Choose the minterms between 0  and " << total - 1 << " and enter -1 to end" << endl;
	int i = 0;
	while (i != -1)
	{
		cin >> i;
		if (i != -1) {
			if (i >= 0 && i < total) {
				process.min = true;
				process.decimal = i;
				process.binary = decimalToBinaryString(i, variables);
				process.ones = onesCounter(process.binary);
				minterm.push_back(process);
			}
			else {
				cout << "out of boundries try again" << endl;
			}
		}
	}
	/*------------------------------Dont Care Entery-------------------------------*/
	cout << "Choose the DontCare between 0  and " << total - 1 << endl << " When done press -1" << endl;

	int j = 0;
	while (j != -1)
	{
		cin >> j;
		if (j != -1) {
			if (j >= 0 && j < total) {
				{
					process.min = false;
					process.decimal = j;
					process.binary = decimalToBinaryString(j, variables);
					process.ones = onesCounter(process.binary);
					minterm.push_back(process);

				}
			}
			else {
				cout << "out of boundries try again" << endl;
			}
		}
	}
	return totalTerms = int(minterm.size());

}

void Print(int total, vector<term>& minterm)
{

	for (int i = 0; i < total; i++) {
		cout << (minterm[i].min ? "m" : "D") << minterm[i].decimal << " = " << minterm[i].binary << endl;
	}
}

vector<term> Adjacency(vector<term> &minterm, int variables)//Takes the Vector, check adjacency
{
	vector<term>A;
	vector<term>B;
	vector<term>prime;
	for (int i = 0; i < minterm.size(); i++)	// count binnary in the new implicants
		minterm[i].ones = onesCounter(minterm[i].binary);

	for (int i = 0; i < variables; i++)
	{
		for (int j = 0; j < minterm.size(); j++)
		{
			if (minterm[j].ones == i)
				A.push_back(minterm[j]); //Not Changing the Minterm
			else if (minterm[j].ones == i + 1)
				B.push_back(minterm[j]);
		}
		

		vector <term> AB;
		AB = combineTwoVectors(A, B);

		for (int i = 0; i < AB.size(); i++)
			EssPrimeImplicants.push_back(AB[i]);




		
		for (int i = 0; i < AB.size(); i++)
			prime.push_back(AB[i]);

		

		A.clear();
		B.clear();
	}

	removeDuplicates(prime);
	return prime;
}

string Letter(char j, char &c) // j= 10- , c = ABC
{
	string  L =  "  ";
	switch (j)
	{
	case '-':	L = ""; break;
	case '1':	L = c; break;
	case '0':	L[0] = '`'; L[1] = c; break;
	}
	return L;
}

void Output(vector<term> PrimeImplicants)
{
	string out="";
	char c;

		//A,B,C,D,E,F,G,H,I,G,K,L,M,N,K,O,P
	for (int i = 0; i < PrimeImplicants.size(); i++)
	{
		for (int j = 0 ; j <PrimeImplicants[i].binary.size(); j++)
		{
			switch (j)
			{
			case 0: c = 'A'; out = out + Letter(PrimeImplicants[i].binary[j], c); break;
			case 1:	c = 'B'; out = out + Letter(PrimeImplicants[i].binary[j], c); break;
			case 2:	c = 'C'; out = out + Letter(PrimeImplicants[i].binary[j], c); break;
			case 3: c = 'D'; out = out + Letter(PrimeImplicants[i].binary[j], c); break;
			case 4: c = 'E'; out = out + Letter(PrimeImplicants[i].binary[j], c); break;
				/*
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
			case 12:
			case 13:
			*/
			}
		}
		out = out + "+";
	}
	cout << "Output" << out;
}

int main()
{
	int variables, totalTerms;
	vector<term> minterm;
	vector<term> PrimeImplicants;

	cout << "Please enter how much variables does your function have: ";
	cin >> variables;

	
	totalTerms = Input(variables, minterm); //User input

	EssPrimeImplicants = minterm;
	sortVectorAccordingToNumberOfOnes(minterm);

	Print(totalTerms, minterm);	//Print all the Minterms and dont cares
	
	PrimeImplicants = Adjacency(minterm, variables); //First call have to call the user givings

	vector<term> test;

	while (1)
	{
		test = Adjacency(PrimeImplicants, variables); //vector of vectors
		if (!test.size()) break;
		PrimeImplicants = test;
	}


	cout << "Prime\n";
	printVector(PrimeImplicants);


	removeDontCares(EssPrimeImplicants);
	cout << "Ess\n";
	printVector(EssPrimeImplicants);


	Output(PrimeImplicants);

	system("pause");

	return 0;
}

