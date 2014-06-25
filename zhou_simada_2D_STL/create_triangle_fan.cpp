#include<vector>
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
#include"header.h"


void triangle_fan_create(vertex_buffer* &d_vb,vector <vector<int> >&fan)
{
int temp;
bool flag;
int max=0;
float sum;

  for(int i=0;i<fan.size();i++){
    if(fan[i][0]<3)continue;
    for(int j=3;j<fan[i].size()-1;j++){
      temp=fan[i][j];
      flag=false;
      for(int k=j+1;k<fan[i].size();k++){
	for(int ii=3;ii<fan[fan[i][k]].size();ii++){
	  if(fan[fan[i][k]][ii]==temp){
	   swap(fan[i][k],fan[i][j+1]);
	   flag=true;
	   break; 
	  }
	}
	
	if(flag)break;
     }  
       if(!flag){//For efficient processing resizing vector
         fan[i].resize(j+1);
	 fan[i][1]=fan[i].size()-3;
         break;
       }
       }
    if(flag)//If no link to temp is found it does not create closed polygon
    for(int k=3;k<fan[fan[i][fan[i].size()-1]].size();k++)
      if(fan[fan[i][fan[i].size()-1]][k]==fan[i][3]){
       fan[i][2]=1;
       if(max<fan[i][1])max=fan[i][1];	
	sum=0;
	int ii;
      for(ii=3;ii<fan[i].size()-2;ii++){
	sum+=(d_vb[fan[i][ii+1]].x-d_vb[fan[i][ii]].x)*(d_vb[fan[i][ii+1]].y+d_vb[fan[i][ii+1]].y);
	}
	sum+=(d_vb[fan[i][3]].x-d_vb[fan[i][ii]].x)*(d_vb[fan[i][3]].y+d_vb[fan[i][ii+1]].y);
	if(sum<0)reverse(fan[i].begin()+3,fan[i].end());//changing hai
	break;
      }
  }
max+=2;

cout<<"*****************"<<max<<endl;

for(int i=0;i<fan.size();i++){
fan[i].erase(fan[i].begin());
fan[i].resize(max,0);
}
/*
cout<<"***************************************************"<<endl;
for(int i=0;i<fan.size();i++){
  if(fan[i][1])cout<<i<<" ";
 for(int j=0;j<fan[i].size();j++)
    if(fan[i][1])
   cout<<fan[i][j]<<" ";
   if(fan[i][1])
 cout<<endl;
}*/					
}
