#include<vector>
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
#include"header.h"


void create_lists(vector <vector<int> >&fan,index_buffer* &d_ib,int & f_count)
{

  for(int i=0;i<fan.size();i++){
    fan[i].push_back(0);//added statements
    fan[i].push_back(0);
    fan[i].push_back(0);
  } 

  for(int i=0;i<f_count;i++){
    fan[d_ib[i].i1].push_back(d_ib[i].i2);
    fan[d_ib[i].i1].push_back(d_ib[i].i3); 
    fan[d_ib[i].i2].push_back(d_ib[i].i1); 
    fan[d_ib[i].i2].push_back(d_ib[i].i3); 
    fan[d_ib[i].i3].push_back(d_ib[i].i1); 
    fan[d_ib[i].i3].push_back(d_ib[i].i2);
    //Added Staments to track the face counts
    fan[d_ib[i].i1][0]++;
    fan[d_ib[i].i2][0]++;
    fan[d_ib[i].i3][0]++;    
      }

  for(int i=0;i<fan.size();i++){
   sort(fan[i].begin()+3,fan[i].end());
   fan[i].erase(unique(fan[i].begin()+3,fan[i].end()),fan[i].end());
   fan[i][1]=fan[i].size()-3;
  }

/*for(int i=0;i<fan.size();i++){
 for(int j=0;j<fan[i].size();j++)
   cout<<fan[i][j]<<" ";
 cout<<endl;
}*/

}
