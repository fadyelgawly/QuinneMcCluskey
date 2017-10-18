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

int onesCounter(string t){                     //This function takes a term object and return term with updated variable ones;
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

int Input(int variables, vector<term>& minterm) //User input and validation
{
	int totalTerms;
	int total = pow(2, variables);
	term process;
	/*------------------------------Minterms Entery-------------------------------*/

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
                cout << "out of boundries try again" << endl;
            }
        }
	}
	return totalTerms = int(minterm.size());

}

void Print(int total, vector<term>& minterm)
{

	for (int i = 0; i < total; i++){
        cout << (minterm[i].min? "m": "D") << minterm[i].decimal << " = " << minterm[i].binary << endl;
	}
}

void Adjacency(vector<term> &minterm, int variables,int total)//Takes the Vector, check adjacency
{
	vector<term>A;
	vector<term>B;
	term process;
	for (int i = 0; i < variables - 1; i++)
	{
		for (int j = 0; j < total; j++)
			if (minterm[j].ones == i)
				A.push_back = minterm[j].decimal;
			else if (minterm[j].ones == i + 1)
				B.push_back = minterm[j].decimal;
	}
}
int main()
{
	int variables=0, totalTerms;
	vector<term> minterm;
	while (variables>0 && variables<16)
	{
		cout << "Enter Number of variables between 1 and 16: ";
		cin >> variables;
	}
    
	totalTerms = Input(variables, minterm); //User input

    sortVector(minterm);
    
	Print(totalTerms, minterm);	//Print all the Minterms and dont cares


	//Ajacencey(minterm, variables,totalTerms);

    
    
    
#ifdef _WIN64       //Exclude if TARGET_OS_MAC or __linux__ 

    system("pause");
#endif
	
    
    return 0;
}
