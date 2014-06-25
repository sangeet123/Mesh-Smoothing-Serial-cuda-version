
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
using namespace std;
#include"header.h"

void zhou_shimada(vertex_buffer* &d_vb, vertex_buffer* &output,int *fan,int size, int v_count)
{
vertex_buffer v0;
vertex_buffer v1;
vertex_buffer v2;
vertex_buffer sum;
float alpha1;
float alpha2;
float beta;
float temp0;
float temp1;
float temp2;
int count;
int index;

for(int i=0;i<v_count;i++){

   if(!fan[i*size+1]){
     output[i].x=d_vb[i].x;
     output[i].y=d_vb[i].y;
      continue;
   }
   sum.x=sum.y=0;
   count=fan[i*size];
   
   for(int j=2;j<count+2;j++){
      sum.x+=d_vb[fan[i*size+j]].x;
      sum.y+=d_vb[fan[i*size+j]].y;
   }

   output[i].x=sum.x/count;
   output[i].y=sum.y/count;
   }

}

void print_output(vertex_buffer* &output, int &v_count){

        for(int i=0;i<v_count;i++)
          cout<<output[i].x<<" "<<output[i].y<<" "<<endl;

}

