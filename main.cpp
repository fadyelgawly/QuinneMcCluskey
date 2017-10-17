#include <string>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct Terms {
	string binary;
	int decimal;
	bool min = false;
	int number_of_1;
};

int onesCounter(string t){                     //This function takes a Terms object and return Terms with updated variable number_of_1;
    int c = 0;
    for (int i = 0; i < t.size(); i++){
        if (t[i] == '1'){
            c++;
        }
    }
    return c;
}
void sortVector(vector<Terms>& minterm){// Will not work until number_of_1 has a true value
    Terms x;
    Terms y;
    for (int i = 0; i < minterm.size(); i++){ // O(n^2)
        for (int j = 0; j < minterm.size();j++){
            if (minterm[i].number_of_1 < minterm[j].number_of_1){
                x = minterm[i];
                y = minterm[j];
                minterm[i] = y;
                minterm[j] = x;
            }
        }
    }
}
std::string decimalToBinaryString(int num, int numberOfVariables) {
	std::string str;
	int rem;
	while(num > 0){
		rem = num % 2;
		num /= 2;
		str.append(std::to_string(rem));
	}
	while (str.size()> numberOfVariables)   str = str.substr(1, str.size() - 1);
	while (str.size()< numberOfVariables)   str.append(std::to_string(0));
	std::reverse(str.begin(), str.end());
	return str;
}

int Input(int variables, vector<Terms>& minterm)
{
	int totalTerms;
	int total = pow(2, variables);
	Terms process;
	/*------------------------------Minterms Entery-------------------------------*/

	cout << "Choose the minterms between 0  and " << total - 1 << endl << " When done press -1" << endl;
	int i = 0;
	while (i != -1)
	{
		cin >> i;
        if (i != -1){
			if (i >= 0 && i < total) {
					process.min = true;
					process.decimal = i;
					process.binary = decimalToBinaryString(i, variables);
                    process.number_of_1 = onesCounter(process.binary);
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
                    process.number_of_1 = onesCounter(process.binary);
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

void Print(int total, vector<Terms>& minterm)
{

	for (int i = 0; i < total; i++){
        cout << (minterm[i].min? "m": "D") << minterm[i].decimal << " = " << minterm[i].binary << endl;
	}
}


int main()
{
	int variables, totalTerms;
	vector<Terms> minterm;
    cout << "Enter Number of variables: ";
	cin >> variables;
    
	totalTerms = Input(variables, minterm); //User input

    sortVector(minterm);
    
	Print(totalTerms, minterm);	//Print all the Minterms and dont cares

	system("pause");
    
    return 0;
}
