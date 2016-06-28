//
//  main.cpp
//  sha3
//
//  Created by Young on 6/27/16.
//  Copyright © 2016 杨言. All rights reserved.
//

#include "keccak.h"

void hexOutput(string res)
{
    for (int i = 0 ; i < res.size() ; i ++)
    {
        unsigned char tmp = res[i];
        int sum = 0;
        for (int j = 0 ; j <= 3 ; j ++)
        {
            sum *= 2;
            if ((tmp & (1 << j)) != 0)
                sum += 1;
        }
        cout << hex << sum;
        sum = 0;
        for (int j = 4 ; j <= 7 ; j ++)
        {
            sum *= 2;
            if ((tmp & (1 << j)) != 0)
                sum += 1;
        }
        cout << hex << sum;
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    Keccak sha3;
    string res = sha3.sha3_224("");
    hexOutput(res);
    return 0;
}
