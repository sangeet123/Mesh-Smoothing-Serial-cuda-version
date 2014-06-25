#include<vector>
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
#include"header.h"

void triangle_fan_create(vector <vector<edge> >&e,vertex_buffer* &d_vb,vector <vector<int> >&fan)
{
bool flag;
int max=0;
float sum;
for(int i=0;i<e.size();i++){
if(e[i].size()==0){
fan[i].push_back(0);
fan[i].push_back(0);
continue;
  }
  for(int j=0;j<e[i].size()-1;j++){
   for(int k=j+1;k<e[i].size();k++){
        flag=false;
	if(e[i][k].s==e[i][j].e){
	  //cout<<"*****"<<k<<" "<<j<<endl;
	  swap(e[i][k],e[i][j+1]);
	  flag=true;
	}
	else if(e[i][k].e==e[i][j].e){
	  swap(e[i][k].e,e[i][k].s);
	  //cout<<"index="<<i<<endl;
	  swap(e[i][k],e[i][j+1]);
	  //cout<<"*****"<<k<<" "<<j<<endl;
	  flag=true;
        }
       if(flag)break;
   }
  if(!flag)break;
  }
  if(!flag){
   fan[i].push_back(0);
   fan[i].push_back(0);
  }   
  else if(e[i][e[i].size()-1].e==e[i][0].s){
   fan[i].push_back(e[i].size());
   fan[i].push_back(1);
   for(int j=0;j<e[i].size();j++){
       //cout<<e[i][j].s<<" "<<e[i][j].e<<" ";
    fan[i].push_back(e[i][j].s);
   }
   //cout<<endl;
   if(max<fan[i].size())max=fan[i].size();
     sum=0;
     int ii;
      for(ii=2;ii<fan[i].size()-2;ii++){
	sum+=(d_vb[fan[i][ii+1]].x-d_vb[fan[i][ii]].x)*(d_vb[fan[i][ii+1]].y+d_vb[fan[i][ii+1]].y);
	}
	sum+=(d_vb[fan[i][2]].x-d_vb[fan[i][ii]].x)*(d_vb[fan[i][2]].y+d_vb[fan[i][ii+1]].y);
	if(sum<0)reverse(fan[i].begin()+2,fan[i].end());//changing hai
  }
  else{
   fan[i].push_back(0);
   fan[i].push_back(0);
  }
}

for(int i=0;i<fan.size();i++)
fan[i].resize(max,0);

/*
for(int i=0;i<fan.size();i++){
 for(int j=0;j<fan[i].size();j++)
     cout<<fan[i][j]<<" ";
 
cout<<endl;

}*/


}

/*

void triangle_fan_create(vertex_buffer* &d_vb,vector <vector<int> >&fan)
{
int temp;
bool flag;
int max=0;
float sum;
float vertexx[100];
float vertexy[100];


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
          for(int ii=0;ii<fan[i].size()-1;ii++){
	  vertexx[ii]=d_vb[fan[i][ii+3]].x;
	  vertexy[ii]=d_vb[fan[i][ii+3]].y;
	  //cout<<vertexx[ii]<<" "<<vertexy[ii]<<endl;
        }

       if(check_if_point_is_inside(fan[i].size()-3,vertexx,vertexy,d_vb[i].x,d_vb[i].y))
       fan[i][2]=1;
       else break;
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
for(int i=0;i<fan.size();i++){
 for(int j=0;j<fan[i].size();j++)
   //if(fan[i][1])
   cout<<fan[i][j]<<" ";
 
cout<<endl;}

max+=2;

//cout<<"*****************"<<max<<endl;

for(int i=0;i<fan.size();i++){
fan[i].erase(fan[i].begin());
fan[i].resize(max,0);
}

//cout<<"***************************************************"<<endl;

for(int i=0;i<fan.size();i++){
 for(int j=0;j<fan[i].size();j++)
   //if(fan[i][1])
   cout<<fan[i][j]<<" ";
 
cout<<endl;
}
cout<<endl;					
}

/*
Copied from http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
*/
/*
int check_if_point_is_inside(int nvert, float *vertx, float *verty, float testx, float testy)
{
  int i, j, c = 0;
  for (i = 0, j = nvert-1; i < nvert; j = i++) {
    if ( ((verty[i]>testy) != (verty[j]>testy)) &&
     (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]) )
       c = !c;
  }
  return c;
}*/
