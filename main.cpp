#include <string>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct term {
	string  binary;
	int     decimal;
	bool    min = false;
	int     ones;
};

int onesCounter(string t){    //This function takes a term object and return term with updated variable ones;
    int c = 0;
    for (int i = 0; i < t.size(); i++){
        if (t[i] == '1'){
            c++;
        }
    }
    return c;
}
void sortVector(vector<term>& minterm){// Will not work until ones has a true value
    term x;
    term y;
    for (int i = 0; i < minterm.size(); i++){ // O(n^2)
        for (int j = 0; j < minterm.size();j++){
            if (minterm[i].ones < minterm[j].ones){
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
	while(num > 0){
		rem = num % 2;
		num /= 2;
		str.append(std::to_string(rem));
	}
	while (str.size()> numberOfVariables)   str = str.substr(1, str.size() - 1);
	while (str.size()< numberOfVariables)   str.append(std::to_string(0));
	std::reverse(str.begin(), str.end()); //Reverse the string 1000 = 0001
	return str;
}
bool checkAdjacency(term t1, term t2){
    int c = 0;
    for (int i = 0; i< t1.binary.size(); i++){
        if (t1.binary[i] != t2.binary[i]){  //0001
            c++;                            //0000
        }
    }
    return (c == 1);
}
term combineTerms (term t1, term t2){
    term temp;
    
    for (int i = 0; i< t1.binary.size(); i++){
        if (t1.binary[i] == t2.binary[i]){
            //0001
            temp.binary.append(t1.binary.substr(i,1));
        } else{
            temp.binary.append("x");
        }
    }

    
    return temp;
}
vector<term> combineTwoVectors (vector<term>& A,vector<term>& B){
    vector<term> C;
    term temp;
    for (int i = 0; i < A.size(); i++){
        for (int j = 0; j < B.size(); j++){
            if (checkAdjacency(A[i], B[j])){
                temp = combineTerms(A[i], B[j]);        //FLAGS CAN BE ADDED HERE
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
	
    cout << "Choose the minterms between 0  and " << total - 1 <<  " and enter -1 to end" << endl;
	int i = 0;
	while (i != -1)
	{
		cin >> i;
        if (i != -1){
			if (i >= 0 && i < total) {
					process.min = true;
					process.decimal = i;
					process.binary = decimalToBinaryString(i, variables);
                    process.ones = onesCounter(process.binary);
					minterm.push_back(process);
				
			}
            else {
                cout << "Please try again" << endl;
            }
        }
	}
	/*------------------------------Dont Care Entery-------------------------------*/
	cout << "Choose the DontCare between 0  and " << total - 1 << endl << " When done press -1" << endl;

	int j = 0;
	while (j != -1)
	{
		cin >> j;
        if (j != -1){
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
                cout << "Please try again" << endl;
            }
        }
	}
	return totalTerms = int(minterm.size());

}
void printVector(vector<term> &x){
	cout << "Vector Size = " << x.size() << endl;
	for (int i = 0; i < x.size(); i++)
	cout << "0b" << x[i].binary << endl;
}


void Adjacency(vector<term> &minterm, int variables, int total)//Takes the Vector, check adjacency
{
	vector<term>A;
	vector<term>B;
	vector<term>prime;
    
	for (int i = 0; i < variables; i++)
	{
		for (int j = 0; j < minterm.size()-1; j++)
		{
			if (minterm[j].ones == i)
				A.push_back(minterm[j]); //Not Changing the Minterm
			else if (minterm[j].ones == i + 1)
				B.push_back(minterm[j]);
		}
		vector <term> AB;
		AB = combineTwoVectors(A, B);
		for (int i = 0; i < AB.size(); i++)
			prime.push_back(AB[i]);



//            cout << "___________________________________" << endl;
//            cout << "AB Vector:-" << endl;
//            printVector(AB);
//            cout << "___________________________________" << endl;
//            cout << "prime Vector:-" << endl;
//            printVector(prime);
//            cout << "___________________________________" << endl;
            A.clear();
            B.clear();
	}
}




int main()
{
    
    
	int variables, totalTerms;
	vector<term> minterm;
    cout << "Please enter how much variables does your function have: ";
	cin >> variables;
    
	totalTerms = Input(variables, minterm); //User input

    sortVector(minterm);
    for (int i = 0; i < minterm.size(); i++) cout << (minterm[i].min? "m": "D") << minterm[i].decimal << " = " << minterm[i].binary << endl;
	Adjacency(minterm, variables,totalTerms);

    system("pause");
    
    return 0;
}

