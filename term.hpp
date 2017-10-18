//
//  term.hpp
//  QM
//
//  Created by Fady Hanna on 10/18/17.
//  Copyright © 2017 Fady Hanna. All rights reserved.
//

#ifndef term_hpp
#define term_hpp

#include <stdio.h>
#include <string>

class term{
    
public:
    static int numberOfVariables;
    term(int,bool);
    
    
    void setDecimal(int x){decimal = x;}
    void setMin(bool x)   {min = x;}
    
    int getDecimal()        {return decimal ;}
    bool isMinTerm()        {return min     ;}
    int getOnes()           {return ones    ;}
    std::string getBinary() {return binary  ;}
    
private:
    std::string binary;
        int     decimal;
        bool    min = false;
        int     ones;
    
        int     onesCounter(std::string);
    std::string decimalToBinaryString(int);

    
    
};

#endif /* term_hpp */
