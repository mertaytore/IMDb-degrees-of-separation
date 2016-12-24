//
//  main.cpp
//  top10
//
//  Created by Berker Senol on 12/20/16.
//  Copyright © 2016 Berker Senol. All rights reserved.
//
#include <iostream>     // std::cout
#include <sstream>      // std::istringstream
#include <string>       // std::string
#include <stdlib.h>     /* atoi */
#include <fstream>
#include <vector>
#include <set>
using namespace std;
#include <fstream>
#include <iostream>

template <typename T>
string NumberToString ( T Number )
{
    ostringstream ss;
    ss << Number;
    return ss.str();
}
static void top(string filename,int moreThanThis){

    int moreThan = moreThanThis;
    ofstream outputFile;
    string outName = "MoreThan"+NumberToString(moreThanThis)+".txt";
    outputFile.open(outName.c_str());
    vector<string> vect;//temps vector
    ifstream file;
    file.open(filename.c_str());
    string line;
    int bigCount=0;
    while( getline(file, line ))
    {
        istringstream is(line);
        int num;
        is>>num;
        
        if (is.peek() == ',' || is.peek() == ' '){
                    is.ignore();
        }else{
            if (num - 1 > moreThan){
                bigCount++;
                cout << NumberToString(bigCount)<<endl;
                outputFile << line << endl;
            }
        }

    }//finish reading file data
    
    cout<< ".............................."<<endl;
    cout<< ".............................."<<endl;

    cout<< "NUMBER OF ACTORS: " + NumberToString(bigCount) <<endl;
    outputFile.close();
}

int main(int argc, const char * argv[]) {
    int number = atoi(argv[2]);
    std::cout << "Hello, World!\n";
    top(argv[1], number);
    cout<<"program should end"<<endl;
    return 0;
}
