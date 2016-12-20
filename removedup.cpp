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

static void removeDuplicates(string filename){
    
    ofstream outputFile;
    string outName = "WoutDup___"+filename+".txt";
    outputFile.open(outName.c_str());

    set <int> hst;//hashset
    
    ifstream file;
    
    file.open(filename.c_str());
    string line;
    while( getline(file, line ))
    {
        istringstream is(line);
        int num;
        is>>num;
        
        if (is.peek() == ',' || is.peek() == ' '){
            is.ignore();
        }
        hst.insert(num);
        cout<<num<<endl;
    }//finished adding ids
    file.clear();
    file.seekg(0, ios_base::beg);

    while( getline(file, line ))
    {
        istringstream is(line);
        int number,size;// number of friends of each actor

        is>>size;
        is>>size;
        string temp = NumberToString(size) + " ";
        while( is >> number ){

            if(hst.find(number) != hst.end()){
                temp = temp + "," + NumberToString(number);
            }
            if (is.peek() == ',' || is.peek() == ' ' || is.peek()== '\t')
                is.ignore();
        }
        cout << temp<<endl;
        outputFile<<temp<<endl;
    }//finish reading file data
    file.close();
    
    outputFile.close();
}

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
   // removeDuplicates(argv[1]);
    removeDuplicates(argv[1]);
    cout<<"program should end"<<endl;
    return 0;
}
