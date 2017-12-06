//
//  main.cpp
//  rgbato16bytestrings
//
//  Created by Isam Hashmi on 11/24/17.
//  Copyright © 2017 Isam Hashmi. All rights reserved.


#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, const char * argv[])
{
    std::string filename = ""; //Input a file name to be converted to 16byte long string seperated by '"' and '\n'
    
    std::ifstream is (filename, std::ifstream::binary );
    
    if (is) {
        is.seekg (0, is.end);
        long long int length = is.tellg();
        is.seekg (0, is.beg);
        
        char * buffer = new char [length];
        
        // read data as a block:
        is.read (buffer,length);
        
       
        is.close();
        
        
        for(int x = 0; x < length; x++)
        {
            if(x %16 == 0)
            {
                cout << "\"" << endl << "\"" ;
            }
            printf("\\x%2x", (unsigned char)buffer[x]);
        
            
        }
        
        
        delete[] buffer;
    }
    cout << endl << endl;
    return 0;
}
