#include <string>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct Terms
{
	string binary; // 1010
	int decimal;
	bool min = false;
	int number_of_1;
};

Terms onesCounter(Terms t){                     //This function takes a Terms object and return Terms with updated variable number_of_1;
    for (int i = 0; i < t.binary.size(); i++){
        if (t.binary[i] == '1'){
            t.number_of_1++;
        }
    }
    
    return t;
    
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

	for (int i = 0; i < total; i++)
	{
		if (minterm[i].min == true)
			cout << "m" << minterm[i].decimal << " = " << minterm[i].binary << endl;
		else
			cout << "D" << minterm[i].decimal << " = " << minterm[i].binary << endl;
	}
}


int main()
{
	int variables, totalTerms;
	vector<Terms> minterm;
	cout << "Enter Number of variables" << endl;
	cin >> variables;
	totalTerms = Input(variables, minterm); //User input
	Print(totalTerms, minterm);	//Print all the Minterms and dont cares

	system("pause");
    
    return 0;
}
