#include<fstream>
#include<string> 
#include<vector>
#include<iostream>
#include "dec_tree.h"
#include<chrono>
using namespace std;

class data_points{
 public:   
    int batch_s=1000;// no of data points that can be in a batch 
    int col=1;
    bool eof=false;
    string line;
    std::ifstream file;
    /*-----vector storage for data points-------*/
    //vector<vector<float>>dpoints;
    vector<vector<float>> batch;
    
    
    vector<int> predict(string path,random_forest &rf) {

    ifstream file(path);
    vector<int> final_ans;

    string line;

    getline(file, line); // header

    int col = 1;
    for (char c : line)
        if (c == ',') col++;

 

 
    batch.reserve(batch_s);

    //random_forest rf("forest.bin"); //----->remove this 
   
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    while (true) {

        batch.clear();

        for (int i = 0; i < batch_s; i++) {

            if (!getline(file, line))
                break;

            vector<float> row;
            string temp = "";

            for (char c : line) {
                if (c == ',') {
                    row.push_back(stof(temp));
                    temp = "";
                } else {
                    temp += c;
                }
            }

            row.push_back(stof(temp));
            batch.push_back(row);
        }

        if (batch.empty())
            break;

        auto pred = rf.predict(batch);

        final_ans.insert(final_ans.end(), pred.begin(), pred.end());
    }
    

std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
 int elap=std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() ;

cout<<"bench:"<<elap<<endl; 

    return final_ans;
}
 
};