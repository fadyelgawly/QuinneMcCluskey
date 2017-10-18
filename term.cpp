//
//  term.cpp
//  QM
//
//  Created by Fady Hanna on 10/18/17.
//  Copyright © 2017 Fady Hanna. All rights reserved.
//

#include "term.hpp"

term::term(int x,bool y){
    setDecimal(x);
    setMin(y);
    binary = decimalToBinaryString(decimal);
    ones = onesCounter(binary);
}

int term::onesCounter(std::string t){                     //This function takes a term object and return term with updated variable ones;
    int c = 0;
    for (int i = 0; i < t.size(); i++){
        if (t[i] == '1'){
            c++;
        }
    }
    return c;
}
std::string term::decimalToBinaryString(int num) { //Convert from Decimal to binary with the correct number of added zeros on the left
    std::string str;
    int rem;
    while(num > 0){
        rem = num % 2;
        num /= 2;
        str.append(std::to_string(rem));
    }
        
//    while (str.size()> numberOfVariables)   str = str.substr(1, str.size() - 1);
//    while (str.size()< numberOfVariables)   str.append(std::to_string(0));
    std::reverse(str.begin(), str.end()); //Reverse the string 1000 = 0001
    return str;
}


