#include <string>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct term {
	string  binary;
	int decimal;
	bool    min = false;
	int     ones;
    int     xs;
	vector<int> track;// tracks the ess. imps.
    bool operator==(const term &t){return (binary == t.binary);}
};
int onesCounter(string t);
void printFunction(vector<term> s);
void sortVectorAccordingToBinary(vector<term>& minterm);
void removeDuplicates(vector<term> &vec);
void sortVectorAccordingToNumberOfOnes(vector<term>& minterm);
std::string decimalToBinaryString(int num, int numberOfVariables);
bool checkAdjacency(term t1, term t2);
term combineTerms(term t1, term t2);
vector<term> combineTwoVectors(vector<term>& A, vector<term>& B);
int Input(int variables, vector<term>& minterm) ;
void Print(int total, vector<term>& minterm);
void printVector(vector<term> &x);
vector<term> Adjacency(vector<term> &minterm, int variables);
int calculateMaximumNumberOfVariables(const vector<term> &v);
void takeInputFromUserInto(vector <term> &v);








int main()
{
    //          #######################DATA ENTRY ####################################
//    cout << "Quinne McClusky Algorism Implementation\n---------------------------------------\n";
//    vector<term> inputTerms;
//
//    takeInputFromUserInto(inputTerms);
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
	int variables, totalTerms;
	vector<term> minterm;
	vector<term> PrimeImplicants;
	cout << "Please enter how much variables does your function have: ";
	cin >> variables;

	totalTerms = Input(variables, minterm); //User input
	sortVectorAccordingToNumberOfOnes(minterm);
	Print(totalTerms, minterm);	//Print all the Minterms and dont cares
	PrimeImplicants = Adjacency(minterm, variables); //First call i have to call the user given
    printFunction(PrimeImplicants);
    for (int i = 0; i<variables - 2; i++){	//Any other time I call my PrimeImplicants and work on it
		PrimeImplicants = Adjacency(PrimeImplicants, variables);
        printFunction(PrimeImplicants);}
	//printVector(PrimeImplicants);
    printFunction(PrimeImplicants);

	system("pause");

	return 0;
}


void takeInputFromUserInto(vector <term> &v){
    
    cout << "\tPlease enter each of your minterm followed by return and use -1 to finish\n";
    int input = 0;
    
    term temp;
    while (input >= 0 && input < pow(2,16)){
        cout << "\t\tm";
        cin >> input;
        if (input < -1 || input >= pow(2,16) ){
            cout << "Invalid input: This term was not recorded.\n";
        } else if (input == -1){
            cout << "\tPlease enter each of your Dont Cares followed by return and use -1 to finish\n";
        } else{
            temp.decimal = input;
            temp.min = true;
            v.push_back(temp);
        }
    }
    input = 0; temp.min = false;
    while (input >= 0 && input < pow(2,16)){
        cout << "\t\tD";
        cin >> input;
        if (input < -1 || input >= pow(2,16) ){
            cout << "Invalid input: This term was not recorded.\n";
        } else if (input == -1){
            cout << "\n----------------------------\n";
        } else{
            temp.decimal = input;
            temp.min = false;
            v.push_back(temp);
        }
    }
    
    for(int i = 0; i < v.size(); i++){
        
    }
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




int onesCounter(string t) {    //This function takes a term object and return term with updated variable ones;
    int c = 0;
    for (int i = 0; i < t.size(); i++) {
        if (t[i] == '1') {
            c++;
        }
    }
    return c;
}
void printFunction(vector<term> s){
    string ss = "F= ";
    for (int i = 0; i < s.size();i++){
        for (int j = 0; j < s[i].binary.size();i++){
            if (s[i].binary[j] == '0'){
                ss.append(to_string(j));
                ss.append("'");
            }
            if (s[i].binary[j] == '1')
                ss.append(to_string(j));
        }
        ss.append(" + ");
    }
    cout << ss << endl;
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
    if (vec.size())
        for (int i = 0;i < vec.size() -1;i++)
            if (vec[i] == vec[i + 1])
                vec.erase(vec.begin() + i);
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
    return (c == 1);
}

term combineTerms(term t1, term t2) {
    term temp;
    
    
    for (int i = 0; i < t1.track.size(); i++)
    {
        if (i == 0)
        {
            temp.track.push_back(t1.decimal);
            temp.track.push_back(t2.decimal);
        }
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
    
    
    return temp;
}

vector<term> combineTwoVectors(vector<term>& A, vector<term>& B) {
    vector<term> C;
    term temp;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++) {
            if (checkAdjacency(A[i], B[j])) {
                temp = combineTerms(A[i], B[j]);        //FLAGS CAN BE ADDED HERE
                C.push_back(temp);
            }
        }
    }
    return C;
}



void Print(int total, vector<term>& minterm)
{
    
    for (int i = 0; i < total; i++) {
        cout << (minterm[i].min ? "m" : "D") << minterm[i].decimal << " = " << minterm[i].binary << endl;
    }
}

void printVector(vector<term> &x)//For testing ONLY
{
    cout << "Vector Size = " << x.size() << endl;
    for (int i = 0; i < x.size(); i++)
    {
        //    cout << "Decimal: " << x[i].decimal << endl;
        cout << "Binary:" << x[i].binary << "\t\t\t";
        for (int j = 0; j < x[i].track.size(); j++)
            cout << x[i].track[j] << ", "; cout << endl; //Prints track vector
        
        //    cout << "Minterm: " << x[i].min << endl;
        //cout << "" <<  << endl;
    }
}

vector<term> Adjacency(vector<term> &minterm, int variables)//Takes the Vector, check adjacency
{
    vector<term>A;
    vector<term>B;
    vector<term>prime;
    removeDuplicates(minterm);
    for (int i = 0; i < minterm.size(); i++)    // count binnary in the new implicants
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
            prime.push_back(AB[i]);
        
        A.clear();
        B.clear();
    }
    
    removeDuplicates(prime);
    printVector(prime);
    return prime;
}

int calculateMaximumNumberOfVariables(const vector<term> &v){
    int max = 0;
    for (int i = 0; i < v.size(); i++){
        if( v[i].decimal > max)
            max = v[i].decimal;
    }
    for (int i = 0; i < 16; i++){
        if (pow(2,i) > max){
            return i;
        }
    }
    return 0;
}




