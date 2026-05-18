#include<fstream>
#include<string> 
#include<vector>
#include<iostream>
using namespace std;

class data_points{
 public:   
    int batch_s=10;// no of data points that can be in a batch 
    int col=1;
    bool eof=false;
    string line;
    std::ifstream file;
    /*-----vector storage for data points-------*/
    vector<vector<float>>dpoints;
    
    
    data_points(string path){
      
     this->file.open(path);

      /*----------------------------*/
      std::getline(this->file,this->line);//getting of the header columns 

      for(auto c:this->line){
      if(c==','){
      	this->col++;
      }
      }
      /*------------------------------*/
      
      dpoints.resize(batch_s,vector<float>(col));//resize 


      while(!this->eof){
      	int t_col=0;
        string t_s="";

      /*--------BATCH PROCESSING----------*/
       for(int i=0;i<this->batch_s;i++){
       	if(!std::getline(this->file,this->line)){
       		eof=true;
       		break;
       	}

      

       	t_col=0;
         t_s="";


       	for(auto c:this->line){

          if(c!=','){
          	t_s+=c;
          }else{
          	//cout << "[" << t_s << "]" << endl;

this->dpoints[i][t_col] = stof(t_s);
            t_s="";
          	t_col++;
          }

       	}

       	this->dpoints[i][t_col]=stof(t_s);
        t_s="";

       }
     /*-----------------------------------*/  

      }

      


     cout<<"loaded"<<endl;
    }



 
};