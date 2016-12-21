//
//  main.cpp
//  degrees of separation
//
//  Created by orhun çağlayan on 16/12/16.
//  Copyright © 2016 orhun çağlayan. All rights reserved.
//

#include <iostream>     // std::cout
#include <sstream>      // std::istringstream
#include <string>       // std::string
#include <stdlib.h>     /* atoi */
#include <fstream>
#include <vector>
#include <set>
#include "hyperloglog.hpp"
using namespace std;
using namespace hll;
static int hash32shift(int key){
    key = ~key + (key << 15); // key = (key << 15) - key - 1;
    key = key ^ (key >> 12);
    key = key + (key << 2);
    key = key ^ (key >> 4);
    key = key * 2057; // key = (key + (key << 3)) + (key << 11);
    key = key ^ (key >> 16);
    return key;
}
static string NumberToString ( int Number )
{
    ostringstream ss;
    ss << Number;
    return ss.str();
}
static double avgDegreeOfsep( string file,int arrSize,int* &arr, int h){
    int count =0;
    vector<int> vect;
    ifstream newfile;
    newfile.open("/Users/orhuncaglayan/Desktop/out.txt");
    string line;
    int* res1 = new int[arrSize];
    while( getline(newfile, line ))
    {
	count++;
        istringstream is(line);
        int number;
        while( is >> number ){
            vect.push_back(number);
            if (is.peek() == ',' || is.peek() == ' ')
                is.ignore();
        }
        res1[vect.at(0)] = (int)vect.size()-1;
        vect.clear();
    }
    arr = res1;
    newfile.close();
    //code works till here
    
    cout<<arr[1000008]<<endl;
    int* res = new int[arrSize];
    cout<<res<<endl;
    cout<<arr<<endl;
    for( int j = 2; j<= h;j++){
        //cout<<"h is "<<j<<" "<<arr[1000008]<<endl;
        newfile.open("/Users/orhuncaglayan/Desktop/out.txt");
        fill(res,res+1000010,0);
        string line;
        // cout<<"10000008         "<<res[1000008]<<endl;
        while( getline(newfile, line ))
        {
            istringstream is(line);
            int number;
            is>>number;
            if( number<= 1000009)
                res[number] = arr[number];
            vect.push_back(number);
            //cout<<"vect   "<<vect.at(0);
            while( is >> number ){
                vect.push_back(number);
                if (is.peek() == ',' || is.peek() == ' ')
                    is.ignore();
                if( number<= 1000009)
                    res[vect.at(0)] += arr[number];
                //cout<<"res value is "<<vect.at(0)<<"       "<<res[vect.at(0)]<<endl;
            }
            vect.clear();
        }
        newfile.close();
        for( int i = 0;i<arrSize;i++)
            arr[i] = res[i];
        for( int i = 0;i<arrSize;i++)
            res[i]=0;
        
    }
    cout<<"done"<<endl;
    return 0;
}
static double Anf(string filename, int arrSize,int* &arr,int h){
   // unsigned long totGraphFriend= 0;//total friendships in graph
    //unsigned long totWGraphFriends=0;
    int tot = 0;
    int count = 0;
    unsigned long* friendAtLevels = new unsigned long[h+1];
    for( int t=0;t<=h;t++)
        friendAtLevels[t]=0;
   // int * fCount = new int[arrSize];//weighted friednship count each person
    vector<int> vect;//temps vector
    vector<vector<int> > vectors(arrSize);//list of all actors friends
    vector<vector<int> > newVectors(arrSize);//new vector
    set<int> vectList;
    ifstream newfile;
    newfile.open(filename.c_str());
    string line;
    while( getline(newfile, line ))
    {
	count++;
        istringstream is(line);
        int number,size;// number of friends of each actor
	is>>size;//ignore first int 
        while( is >> number ){
            vect.push_back(number);
            if (is.peek() == ',' || is.peek() == ' '||is.peek()=='\t')
                is.ignore();
        }
 
       cout<<"assigning vector for actor: "<<size<<endl;
      //  fCount[size] = (int)vect.size();
        vectList.insert(vect.begin(),vect.end());
        vect.clear();
        vect.assign(vectList.begin(), vectList.end());
        cout<<"vectList size is "<<vectList.size()<<endl;
        vectList.clear();
        friendAtLevels[1] += vect.size();
        vectors[size] = vect;
        vect.clear();
        cout<<vectors.at(size).size()<<endl;
        tot+=vectors.at(size).size();
    }//finish reading file data
	friendAtLevels[0] = count;    
    cout<<"vector size: "<<vectors.size()<<endl;
    //arr = res1;
    newfile.close();
    //code works till here
    cout<<"first part ended"<<endl;
    cout<<"total of h = 0  is "<<count<<endl;
    for( int j = 2; j<= h;j++){//for each height level h
	cout<<"calculating h = "<<j<<endl; 
       for( int i =0;i<vectors.size();i++){//for each actor i
            newVectors.resize(arrSize);//resize vector for input
            for( int m = 0;m< vectors.at(i).size();m++){//for each friend of an actor
                //if(vectors.at(i).at(m)< 1000010)
                    vectList.insert(vectors.at(vectors.at(i).at(m)).begin(),vectors.at(vectors.at(i).at(m)).end());//insert M(y,h-1) to set
            }
            vectList.insert(vectors.at(i).begin(),vectors.at(i).end());//insert M(x,h) to set
            vector<int> res(vectList.begin(),vectList.end());//insertions unioned the vectors, now hold these values in vector
            //friendAtLEvels[j-1]+= res.size();
            newVectors[i] = res;//add vector list t
            friendAtLevels[j] +=newVectors.at(i).size();//find num of all nodes within distance h 
            vectList.clear();
            res.clear();
        
        }
        vectors = newVectors;
        newVectors.clear();
        
    }
    for( int m = 0;m< arrSize;m++)
        arr[m] = (int)vectors.at(m).size();
    cout<<"second part ended"<<endl;
    for( int v =1;v<=h;v++)
        cout<<friendAtLevels[v]<<endl;
    cout<<endl;
    double avg = 0;
	cout<<"friends at level h= 0 is: "<<friendAtLevels[0]<<endl;
    for( int m = 1;m<=h;m++){
     	cout<<"friends at level h= "<<m<<" is: "<<friendAtLevels[m]<<endl;
	   avg += (m)*(friendAtLevels[m]-friendAtLevels[m-1]);
    }
    cout<<"avg is "<<avg<<endl;
    return avg/(friendAtLevels[h]-friendAtLevels[0]);
}

static double hyperAnf(string filename, int arrSize,int* &arr,int h){
    HyperLogLog hll(10);
    HyperLogLog hll2(10);
    //set<HyperLogLog> hllset,hllset2;
    HyperLogLog* hllarr = new HyperLogLog[arrSize];
    HyperLogLog* hllarr2 = new HyperLogLog[arrSize];
    for( int y = 0;y<arrSize;y++){
        hllarr[y] = HyperLogLog(10);
        hllarr2[y] = HyperLogLog(10);
    }
    int tot = 0;
    int count = 0;
    double* friendAtLevels = new double[h+1];
    for( int t=0;t<=h;t++)
        friendAtLevels[t]=0;
    // int * fCount = new int[arrSize];//weighted friednship count each person
    vector<string> vect;//temps vector
    vector<vector<string> > vectors(arrSize);//list of all actors friends
    set<string> vectList;
    ifstream newfile;
    newfile.open(filename.c_str());
    string line;
    while( getline(newfile, line ))
    {
        count++;
        istringstream is(line);
        int number,id;// number of friends of each actor
        is>>id;//ignore first int
        while( is >> number ){
            vect.push_back(NumberToString(number));
            if (is.peek() == ',' || is.peek() == ' '||is.peek()=='\t')
                is.ignore();
        }
        
        cout<<"assigning vector for actor: "<<id<<endl;
        //  fCount[size] = (int)vect.size();
        vectList.insert(vect.begin(),vect.end());
         std::vector<std::string>::iterator iter = vect.begin();
         std::vector<std::string>::iterator iter_end = vect.end();
        for(;iter != iter_end; ++iter){
            hll.add(iter->c_str(), iter->size());
        }
        hll2.merge(hll);
        hllarr2[id] = hll2;
        hll2.clear();
        vect.clear();
        vect.assign(vectList.begin(), vectList.end());
        cout<<"vectList size is "<<vectList.size()<<endl;
        vectList.clear();
       // friendAtLevels[1] += vect.size();
        vectors[id] = vect;
        vect.clear();
        cout<<vectors.at(id).size()<<endl;
        tot+=vectors.at(id).size();
    }//finish reading file data
    
    friendAtLevels[0] = hll.estimate();
    cout<<"vector size: "<<vectors.size()<<endl;
    //arr = res1;
    newfile.close();
    //code works till here
    cout<<"first part ended"<<endl;
    cout<<"total of h = 0  is "<<count<<endl;
    cout<<"estimation is for h=0 : "<<hll.estimate()<<endl;
    hll.clear();
    
    for( int j = 1; j<= h;j++){//for each height level h
        cout<<"calculating h = "<<j<<endl;
        for( int i =0;i<vectors.size();i++){//for each actor i
            hllarr2[i].merge(hllarr[i]);//M(x,h) = M(x,h-1)
            for( int m = 0;m< vectors.at(i).size();m++){//for each friend of an actor
                string str = vectors.at(i).at(m);
                hllarr2[i].merge(hllarr[atoi(str.c_str())]);
            }
            
            friendAtLevels[j] +=hllarr2[i].estimate();//find num of all nodes within distance h
        }
        for( int y = 0;y<arrSize;y++){
            hllarr[y] = hllarr2[y];
            hllarr2[y].clear();
        }
    }
    
    cout<<"second part ended"<<endl;
    for( int v =1;v<=h;v++)
        cout<<friendAtLevels[v]<<endl;
    cout<<endl;
    double avg = 0;
    cout<<"friends at level h= 0 is: "<<friendAtLevels[0]<<endl;
    for( int m = 1;m<=h;m++){
        cout<<"friends at level h= "<<m<<" is: "<<friendAtLevels[m]<<endl;
        avg += (m)*(friendAtLevels[m]-friendAtLevels[m-1]);
    }
    cout<<"avg is "<<avg<<endl;
    return avg/(friendAtLevels[h]-friendAtLevels[0]);
}
int main(int argc, const char * argv[]) {
    int h = atoi(argv[1]);
    int arrSize = atoi(argv[2]);
    cout<<"file name is "<<argv[3]<<endl;   
    // insert code here...
    std::cout << "Hello, World!\n";
    int* arr = new int[arrSize];
    //avgDegreeOfsep("out.txt", 1000010,arr , 1);
   //for( int i = 1000000;i<=1000009;i++)
     //  cout<<arr[i]<<endl;
    //cout<<"anf is "<<Anf(argv[3], arrSize+1,arr,h)<<endl;
    cout<<hyperAnf(argv[3], arrSize+1,arr,h)<<endl;
    for( int i = 1000000;i<=1000009;i++)
        cout<<arr[i]<<endl;
    cout<<"program should end"<<endl;
    return 0;
}

