
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
vertex_buffer vr;
vertex_buffer vr1;
vertex_buffer vr2;
vertex_buffer vr3;
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

   vr=d_vb[fan[i*size+2]];
   vr1=d_vb[i];
   vr2=d_vb[fan[i*size+count+1]];
   
   for(int j=2;j<count+2;j++){
      //v1.x=d_vb[i].x-d_vb[fan[i*size+j]].x;
      //v1.y=d_vb[i].y-d_vb[fan[i*size+j]].y;

      v1.x=vr1.x-vr.x;
      v1.y=vr1.y-vr.y;



      if(j-1==count)index=2;
      else index=j+1;
      //v0.x=d_vb[fan[i*size+index]].x-d_vb[fan[i*size+j]].x;
      //v0.y=d_vb[fan[i*size+index]].y-d_vb[fan[i*size+j]].y;

      vr3.x=d_vb[fan[i*size+index]].x;
      vr3.y=d_vb[fan[i*size+index]].y;

      v0.x=vr3.x-vr.x;
      v0.y=vr3.y-vr.y;




      //if(j==2)index=count+1;
      //else index=j-1;

      //v2.x=d_vb[fan[i*size+index]].x-d_vb[fan[i*size+j]].x;
      //v2.y=d_vb[fan[i*size+index]].y-d_vb[fan[i*size+j]].y;

       v2.x=vr2.x-vr.x;
       v2.y=vr2.y-vr.y;

     //if(i==101)cout<<j<<" "<<v0.y<<" "<<v1.y<<" "<<v2.y<<endl;

      temp0=sqrtf(powf(v0.x,2)+powf(v0.y,2));
      temp1=sqrtf(powf(v1.x,2)+powf(v1.y,2));
      temp2=sqrtf(powf(v2.x,2)+powf(v2.y,2));

      alpha1=acos((v1.x*v2.x+v1.y*v2.y)/(temp1*temp2));
      alpha2=acos((v1.x*v0.x+v1.y*v0.y)/(temp1*temp0));

      beta=(alpha2-alpha1)/2;
      
      //sum.x+=d_vb[fan[i*size+j]].x+(d_vb[i].x-d_vb[fan[i*size+j]].x)*cos(beta)-(d_vb[i].y-d_vb[fan[i*size+j]].y)*sin(beta);
      //sum.y+=d_vb[fan[i*size+j]].y+(d_vb[i].x-d_vb[fan[i*size+j]].x)*sin(beta)+(d_vb[i].y-d_vb[fan[i*size+j]].y)*cos(beta);
 
      sum.x+=vr.x+(vr1.x-vr.x)*cos(beta)-(vr1.y-vr.y)*sin(beta);
      sum.y+=vr.y+(vr1.x-vr.x)*sin(beta)+(vr1.y-vr.y)*cos(beta);

      vr2=vr;
      vr=vr3;
   }
   //if(i==101)cout<<sum.x<<" "<<sum.y<<endl;
   output[i].x=sum.x/count;
   output[i].y=sum.y/count;
   }

}
void print_output(vertex_buffer* &output, int &v_count,index_buffer*&ib,int&f_count){

        printf("OFF\n");
        printf("%d %d %d\n",v_count,f_count,0);
        for(int i=0;i<v_count;i++)
          cout<<output[i].x<<" "<<output[i].y<<endl;

        for(int i=0;i<f_count;i++)
          cout<<ib[i].i1<<" "<<ib[i].i2<<" "<<ib[i].i3<<endl;

}

