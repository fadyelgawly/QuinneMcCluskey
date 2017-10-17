//
//  main.cpp
//  QM
//
//  Created by Fady Hanna on 10/17/17.
//  Copyright © 2017 Fady Hanna. All rights reserved.
//

#include <iostream>

std::string decimalToBinaryString(int num, int numberOfVariables){
    std::string str ;
    int rem;
    for (int i = 0; i <= (num + 1); i++)
    {
        rem = num % 2;
        num /= 2;
        str.append(std::to_string(rem));
    }
    
    while (str.size()> numberOfVariables)   str = str.substr(1,str.size()-1);
    while (str.size()< numberOfVariables)   str.append(std::to_string(0));
    std::reverse(str.begin(), str.end());
    return str;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
