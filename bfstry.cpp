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
#include <map>
#include <set>
using namespace std;
#include <fstream>
#include <iostream>

void numOfFriends (int id, int iteration, map<int, vector<int> > m, set<int> &v, double &sum) {
    if (m.find(id) != m.end() && v.find(id) == v.end()) {
        v.insert(id);
        if (iteration >= 4) {
            sum += iteration;
            return;
        }
        else {
            int a = 0;
            while (a < m[id].size()) {
                numOfFriends(m[id].at(a), iteration+1, m, v, sum);
                sum += iteration;
                a++;
            }
        return;
        }
    }
    return;
}

int construct(string filename){

    map<int, vector<int> > m;
    ifstream file;
   
    file.open(filename.c_str());
    string line;
    int total = 0;
    while( getline(file, line ))
    {
        istringstream is (line);  
        total++; 
        int number;
        int index;
        char ch;
        vector<int> v;
        is>>index;
        while( is >> number ){
            v.push_back(number);
            is >> ch;       
        }
        m[index] = v;

    }//finish reading file data
    file.close();
    double sum1 = 0;
    
    for(std::map<int,vector<int> >::iterator iter = m.begin(); iter != m.end(); ++iter)
    {
    int id =  iter->first;
    cout << id;
set <int> processed;
double sum = 0;
    numOfFriends(id, 1, m, processed, sum);
    sum1 += sum/total;

    }
       
        
    
    return sum1 / total;
}

int main(int argc, const char * argv[]) {
    int x = construct(argv[1]);
    cout << "---------" <<x<<"------" <<endl;
    cout<<"program should end"<<endl;
    return 0;
}
