#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include"header.h"

using namespace std;

void New_angle(vertex_buffer* &d_vb, vertex_buffer* &output,int *fan,int size, int v_count,float **jacobian,function_info**funct,float**d1)
{
vertex_buffer v0;
vertex_buffer v1;
vertex_buffer v2;
vertex_buffer new_pos;
float alpha1;
float alpha2;
float beta;
float temp0;
float temp1;
float temp2;
int count;
int index;
float slope;
float deno;
objective_function o;
float temp[2][2];
float precision=0.000001;
float sn;
float sn_1;
float sn_temp;
float lamda;
int count_i=0;

for(int i=0;i<v_count;i++){

   if(!fan[i*size+1]){
     output[i].x=d_vb[i].x;
     output[i].y=d_vb[i].y;
      continue;
   }
    count_i++;
   //cout<<"This index is appropriate for smoothing index:"<<i<<endl;
   new_pos.x=new_pos.y=0;
   count=fan[i*size];
   o.coeff_sqr_x=0;
   o.coeff_sqr_y=0;
   o.coeff_xy=0;
   o.rest.coeff_x=0;
   o.rest.coeff_y=0;
   o.rest.const_coeff=0;
   //cout<<"I="<<i<<endl;   
   for(int j=2;j<count+2;j++){
      v1.x=d_vb[i].x-d_vb[fan[i*size+j]].x;
      v1.y=d_vb[i].y-d_vb[fan[i*size+j]].y;


      if(j-1==count)index=2;
      else index=j+1;
      v0.x=d_vb[fan[i*size+index]].x-d_vb[fan[i*size+j]].x;
      v0.y=d_vb[fan[i*size+index]].y-d_vb[fan[i*size+j]].y;


      if(j==2)index=count+1;
      else index=j-1;

      v2.x=d_vb[fan[i*size+index]].x-d_vb[fan[i*size+j]].x;
      v2.y=d_vb[fan[i*size+index]].y-d_vb[fan[i*size+j]].y;

     /** if(i==1){
       cout<<v0.x<<" "<<v0.y<<endl;
       cout<<v1.x<<" "<<v1.y<<endl;
       cout<<v2.x<<" "<<v2.y<<endl;
      }**/

      temp0=sqrtf(powf(v0.x,2)+powf(v0.y,2));
      temp1=sqrtf(powf(v1.x,2)+powf(v1.y,2));
      temp2=sqrtf(powf(v2.x,2)+powf(v2.y,2));

      alpha1=acos((v1.x*v2.x+v1.y*v2.y)/(temp1*temp2));
      alpha2=acos((v1.x*v0.x+v1.y*v0.y)/(temp1*temp0));
      //cout<<"Before Smoothing"<<endl;
     // cout<<"alpha1="<<alpha1<<"alpha2="<<alpha2<<endl;
	beta=(alpha1+alpha2)/2;	
      //beta=(alpha2-alpha1)/2;
      //cout<<"beta="<<beta<<endl;
      beta=alpha2-beta;	      
      //cout<<"This is amount of angle beta="<<beta<<endl;
      new_pos.x=d_vb[fan[i*size+j]].x+(d_vb[i].x-d_vb[fan[i*size+j]].x)*cos(beta)-(d_vb[i].y-d_vb[fan[i*size+j]].y)*sin(beta);
      new_pos.y=d_vb[fan[i*size+j]].y+(d_vb[i].x-d_vb[fan[i*size+j]].x)*sin(beta)+(d_vb[i].y-d_vb[fan[i*size+j]].y)*cos(beta);

     //cout<<"New position="<<new_pos.x<<" "<<new_pos.y<<endl;

    //Check the angles between two vector if it is correct
     /* v1.x=new_pos.x-d_vb[fan[i*size+j]].x;
      v1.y=new_pos.y-d_vb[fan[i*size+j]].y;
      temp1=sqrtf(powf(v1.x,2)+powf(v1.y,2));

      alpha1=acos((v1.x*v2.x+v1.y*v2.y)/(temp1*temp2));
      alpha2=acos((v1.x*v0.x+v1.y*v0.y)/(temp1*temp0));
      cout<<"alpha1="<<alpha1<<"alpha2="<<alpha2<<endl;
     */
   //checking angles ends here

     //Here begins the calculation of new angle based smoothing
      funct[i][j-2].coeff_x=new_pos.y-d_vb[fan[i*size+j]].y;
      funct[i][j-2].coeff_y=d_vb[fan[i*size+j]].x-new_pos.x;
      funct[i][j-2].const_coeff=d_vb[fan[i*size+j]].y*new_pos.x-d_vb[fan[i*size+j]].x*new_pos.y;
      slope=sqrtf(powf(funct[i][j-2].coeff_x,2)+powf(funct[i][j-2].coeff_y,2));
      funct[i][j-2].coeff_x/=slope;
      funct[i][j-2].coeff_y/=slope;
      funct[i][j-2].const_coeff/=slope;
     //calculation of coefficient of function ends here

      //cout<<funct[i][j-2].coeff_x<<" "<<funct[i][j-2].coeff_y<<" "<<funct[i][j-2].const_coeff<<endl;


   //Calculation of objective function
     o.coeff_sqr_x+=powf(funct[i][j-2].coeff_x,2);
     o.coeff_sqr_y+=powf(funct[i][j-2].coeff_y,2);
     o.coeff_xy+=2*funct[i][j-2].coeff_x*funct[i][j-2].coeff_y;
     o.rest.coeff_x+=2*funct[i][j-2].coeff_x*funct[i][j-2].const_coeff;
     o.rest.coeff_y+=2*funct[i][j-2].coeff_y*funct[i][j-2].const_coeff;
     o.rest.const_coeff+=powf(funct[i][j-2].const_coeff,2);
  //End of objective function calculation;
   
   }//The Inner loop ends here

    //cout<<"***********************************************************"<<endl;
    ///cout<<o.coeff_sqr_x<<" "<<o.coeff_sqr_y<<" " <<o.coeff_xy<<" " <<o.rest.coeff_x<<" " <<o.rest.coeff_y<<" "<<o.rest.const_coeff<<endl;   
   //cout<<"*****************"<<endl;
   //storing the elements of jacobian matrix
   for(int k=0;k<count;k++){
	jacobian[i][2*k]=funct[i][k].coeff_x;
	jacobian[i][2*k+1]=funct[i][k].coeff_y;
	//cout<<jacobian[i][2*k]<<" "<<jacobian[i][2*k+1]<<endl;
   }
   //cout<<"*****************"<<endl;

  //Jacobian matrix ends here
   temp[0][0]=temp[0][1]=temp[1][0]=temp[1][1]=0;
   for(int j=0;j<count;j++){
     temp[1][1]+=powf(jacobian[i][2*j],2);   
     temp[1][0]+=jacobian[i][2*j]*jacobian[i][2*j+1];
     temp[0][0]+=powf(jacobian[i][2*j+1],2);
   }

   temp[0][1]=temp[1][0];
   slope=(temp[0][0]*temp[1][1])-(temp[0][1]*temp[1][0]);


   //cout<<"***********************************************************"<<endl;
   //cout<<temp[0][0]<<" "<<temp[0][1]<<" "<<temp[1][0]<<" "<<temp[1][1]<<endl;

   //cout<<"determinant="<<slope<<endl;

   

  //calculation of inverse matrix;
    temp[0][0]/=slope;
    temp[1][0]/=-slope;
    temp[0][1]/=-slope;
    temp[1][1]/=slope;

  //cout<<"***********************************************************"<<endl;
   // cout<<temp[0][0]<<" "<<temp[0][1]<<" "<<temp[1][0]<<" "<<temp[1][1]<<endl;

//The program seems correct upto this point

  //Jacobian matrix can be reused as d1 has already been calculated which is constant throughout iterations
   for(int ii=0;ii<count;ii++){
    d1[i][ii]=temp[0][0]*jacobian[i][2*ii];
    d1[i][ii]+=temp[0][1]*jacobian[i][2*ii+1];
    d1[i][ii+count]=temp[1][0]*jacobian[i][2*ii];
    d1[i][ii+count]+=temp[1][1]*jacobian[i][2*ii+1];
   }

   //Initial guess of internal vertex
   v1.x=d_vb[i].x;
   v1.y=d_vb[i].y;

  //Here begins the calculation of main algorithmic loop
  for(int kk=0;kk<10;kk++){
    //cout<<v1.x<<" "<<v1.y<<endl;
    //calculation of function vector reusing the jacobain matrix this time for function vector
  for(int ii=0;ii<count;ii++)
   jacobian[i][ii]=v1.x*funct[i][ii].coeff_x+v1.y*funct[i][ii].coeff_y+funct[i][ii].const_coeff;

   //First step of Algorithm
    sn=powf(v1.x,2)*o.coeff_sqr_x+powf(v1.y,2)*o.coeff_sqr_y+v1.x*v1.y*o.coeff_xy;
    sn+=v1.x*o.rest.coeff_x+v1.y*o.rest.coeff_y+o.rest.const_coeff;

  
  v0.x=v0.y=0;//Reinitializing the current vertex to calculate the new position
  for(int ii=0;ii<count;ii++){
    v0.x+=d1[i][ii]*jacobian[i][ii];
    v0.y+=d1[i][ii+count]*jacobian[i][ii];
  }
  
 //new coordinates i.e. xn+1 
  v2.x=v1.x+v0.x;
  v2.y=v1.y+v0.y;

  sn_1=powf(v2.x,2)*o.coeff_sqr_x+powf(v2.y,2)*o.coeff_sqr_y+v2.x*v2.y*o.coeff_xy;
  sn_1+=v2.x*o.rest.coeff_x+v2.y*o.rest.coeff_y+o.rest.const_coeff;

  if(fabs((sn_1-sn)/sn) < precision){//puts("reached");
    break;}
   
  lamda=1;//step 3 of algorithm

 if(sn_1<sn){v1.x=v2.x;v1.y=v2.y;continue;}//step 4 of algorithm


  //calculation of lamda using derivative;step 5 of algorithm

  lamda=(2*o.coeff_sqr_x*v0.x+o.coeff_xy*v0.y)*v1.x;
  lamda+=(2*o.coeff_sqr_y*v0.y+o.coeff_xy*v0.x)*v1.y;
  lamda+=o.rest.coeff_x*v0.x+o.rest.coeff_y*v0.y;
  lamda/=(o.coeff_sqr_x*powf(v0.x,2)+o.coeff_sqr_y*powf(v0.y,2)+o.coeff_xy*v0.x*v0.y);
  lamda/=(-2);

  v2.x=v1.x+lamda*v0.x;
  v2.y=v1.y+lamda*v0.y;

  sn_temp=powf(v2.x,2)*o.coeff_sqr_x+powf(v2.y,2)*o.coeff_sqr_y+v2.x*v2.y*o.coeff_xy;
  sn_temp+=v2.x*o.rest.coeff_x+v2.y*o.rest.coeff_y+o.rest.const_coeff; 

  //Step 6 of an algorithm
  if(sn>sn_1){
    if(sn_1<sn_temp)lamda=1;
   }
  else if(sn<sn_temp)lamda=0;

 // cout<<"lamda="<<lamda<<endl;

  //Step 7 of algorithm
    int k=kk;

    while(k<10){
    
     if(sn_1<sn){break;}
      //puts("***************");
      lamda/=2;
      v1.x=v1.x+lamda*v0.x;
      v1.y=v1.y+lamda*v0.y;

      sn=powf(v1.x,2)*o.coeff_sqr_x+powf(v1.y,2)*o.coeff_sqr_y+v1.x*v1.y*o.coeff_xy;
      sn+=v1.x*o.rest.coeff_x+v1.y*o.rest.coeff_y+o.rest.const_coeff;

      for(int ii=0;ii<count;ii++)
       jacobian[i][ii]=v1.x*funct[i][ii].coeff_x+v1.y*funct[i][ii].coeff_y+funct[i][ii].const_coeff;

      v0.x=v0.y=0;//Reinitializing the current vertex to calculate the new position
     for(int ii=0;ii<count;ii++){
       v0.x+=d1[i][ii]*jacobian[i][ii];
       v0.y+=d1[i][ii+count]*jacobian[i][ii];
     }

     v2.x=v1.x+v0.x;
     v2.y=v1.y+v0.y;

      sn_1=powf(v2.x,2)*o.coeff_sqr_x+powf(v2.y,2)*o.coeff_sqr_x+v2.x*v2.y*o.coeff_xy;
      sn_1+=v2.x*o.rest.coeff_x+v2.y*o.rest.coeff_y+o.rest.const_coeff;

      k++;
      }

    if(k==10)break;

   }//Algorithm loop ends here
    //cout<<v1.x<<" "<<v1.y<<endl;
   output[i].x=v1.x;
   output[i].y=v1.y;
   }//Outer loop ends here

//cout<<"Total no of internal vertex="<<count_i<<endl;
}




void print_output(vertex_buffer* &output, int &v_count,index_buffer*&ib,int&f_count){

	printf("OFF\n");
	printf("%d %d %d\n",v_count,f_count,0);
        for(int i=0;i<v_count;i++)
          cout<<output[i].x<<" "<<output[i].y<<endl;

	for(int i=0;i<f_count;i++)
	  cout<<ib[i].i1<<" "<<ib[i].i2<<" "<<ib[i].i3<<endl;

}
