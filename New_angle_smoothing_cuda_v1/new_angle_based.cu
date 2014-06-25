#include"header.h"



void __global__ new_angle_based(const struct vertex_buffer *d_vb, struct vertex_buffer *result,int *fan,int vertices,int max,float *jacobian,function_info*funct,float*d1)
{
//__shared__ int fan_list[512][20];

//int tx=threadIdx.x;
int ty=threadIdx.y;
int count;
//int column=blockIdx.x * blockDim.x+tx;
int row=blockIdx.y *blockDim.y+ty;
struct vertex_buffer v0;
struct vertex_buffer v1;
struct vertex_buffer v2;
struct vertex_buffer vr;
struct vertex_buffer vr1;
struct vertex_buffer vr2;
struct vertex_buffer vr3;
struct vertex_buffer new_pos;
float temp0,temp1,temp2;
float alpha1;
float alpha2;
float beta;
int index;
int index1;
objective_function o;
//float temp[2][2];
float precision=0.000001;
float sn;
float sn_1;
float sn_temp;
float lamda;
float slope;


o.coeff_sqr_x=o.coeff_sqr_y=o.coeff_xy=o.rest.coeff_x=o.rest.coeff_y=o.rest.const_coeff=0;


if(row<vertices){
index1=row*max;

//if(row==1)printf("**greetings from row 60\n");
if(fan[index1+1]){
//for(int i=0;i<max;i++){
//fan_list[ty][i]=fan[row*max+i];
//if(row==60)
//printf("%d\n",fan_list[ty][i]);
//}


//if(fan_list[ty][1]==1){
//perform smoothing

count=fan[index1];

vr.x=d_vb[fan[index1+2]].x;
vr.y=d_vb[fan[index1+2]].y;
vr1.x=d_vb[row].x;
vr1.y=d_vb[row].y;
vr2.x=d_vb[fan[index1+count+1]].x;
vr2.y=d_vb[fan[index1+count+1]].y;

for(int j=2;j<count+2;j++){
      //vr.x=d_vb[fan_list[ty][j]].x;
      //vr.y=d_vb[fan_list[ty][j]].y;
      v1.x=vr1.x-vr.x;
      v1.y=vr1.y-vr.y;

      //if(row==68)
       //printf("%f %f\n",vr.x,vr.y);

      if(j-1==count)index=2;
      else index=j+1;

      vr3.x=d_vb[fan[index1+index]].x;
      vr3.y=d_vb[fan[index1+index]].y;
      //v0.x=d_vb[fan_list[ty][index]].x-vr.x;
      //v0.y=d_vb[fan_list[ty][index]].y-vr.y;


      v0.x=vr3.x-vr.x;
      v0.y=vr3.y-vr.y;


      //if(j==2)index=count+1;
      //else index=j-1;

      //v2.x=d_vb[fan_list[ty][index]].x-vr.x;
      //v2.y=d_vb[fan_list[ty][index]].y-vr.y;

       v2.x=vr2.x-vr.x;
       v2.y=vr2.y-vr.y;

      temp0=sqrtf(powf(v0.x,2)+powf(v0.y,2));
      temp1=sqrtf(powf(v1.x,2)+powf(v1.y,2));
      temp2=sqrtf(powf(v2.x,2)+powf(v2.y,2));

      alpha1=acos((v1.x*v2.x+v1.y*v2.y)/(temp1*temp2));
      alpha2=acos((v1.x*v0.x+v1.y*v0.y)/(temp1*temp0));

      beta=(alpha2+alpha1)/2;
      beta=alpha2-beta;

      
      new_pos.x=vr.x+(vr1.x-vr.x)*cos(beta)-(vr1.y-vr.y)*sin(beta);
      new_pos.y=vr.y+(vr1.x-vr.x)*sin(beta)+(vr1.y-vr.y)*cos(beta);


      temp0=new_pos.y-vr.y;
      temp1=vr.x-new_pos.x;
      temp2=vr.y*new_pos.x-vr.x*new_pos.y;
      slope=sqrtf(powf(temp0,2)+powf(temp1,2));
      temp0=funct[index1+j-2].coeff_x=temp0/slope;
      temp1=funct[index1+j-2].coeff_y=temp1/slope;
      temp2=funct[index1+j-2].const_coeff=temp2/slope;

//     if(row==104)printf("%f %f %f\n",temp0,temp1,temp2);


     o.coeff_sqr_x+=powf(temp0,2);
     o.coeff_sqr_y+=powf(temp1,2);
     o.coeff_xy+=2*temp0*temp1;
     o.rest.coeff_x+=2*temp0*temp2;
     o.rest.coeff_y+=2*temp1*temp2;
     o.rest.const_coeff+=powf(temp2,2);
      

      vr2=vr;
      vr=vr3;

   }//Inner loop ends here
   index=2*index1;
   //if(row==104)printf("%f %f %f %f %f %f\n",o.coeff_sqr_x,o.coeff_sqr_y,o.coeff_xy,o.rest.coeff_x,o.rest.coeff_y,o.rest.const_coeff);
   //temp[0][0]=temp[0][1]=temp[1][0]=temp[1][1]=0;
     vr3.x=vr3.y=vr2.x=vr2.y=0;
      for(int k=0;k<count;k++){
	temp0=jacobian[index+2*k]=funct[index1+k].coeff_x;
	temp1=jacobian[index+2*k+1]=funct[index1+k].coeff_y;
        vr2.y+=powf(temp0,2);   
        vr2.x+=(temp0*temp1);
        vr3.x+=powf(temp1,2);

       //if(row==104)printf("%f %f\n",jacobian[row*max*2+2*k],jacobian[row*max*2+2*k+1]);
   }

  // if(row==104)
   //   for(int k=0;k<count;k++){
    //   printf("%f %f\n",jacobian[row*max*2+2*k],jacobian[row*max*2+2*k+1]);
    //}

/*   temp[0][0]=temp[0][1]=temp[1][0]=temp[1][1]=0;
   for(int k=0;k<count;k++){
     temp[1][1]+=powf(jacobian[row*max*2+2*k],2);   
     temp[1][0]+=jacobian[row*max*2+2*k]*jacobian[row*max*2+2*k+1];
     temp[0][0]+=powf(jacobian[row*max*2+2*k+1],2);
    // if(row==104)
     //printf("%f %f \n",funct[row*max+k].coeff_x,funct[row*max+k].coeff_y);
   }
*/
   //temp[0][1]=temp[1][0];
     vr3.y=vr2.x;
   //  if(row==104)printf("%f %f %f %f\n",temp[0][0],temp[0][1],temp[1][0],temp[1][1]);

   //slope=(temp[0][0]*temp[1][1])-(temp[0][1]*temp[1][0]);
     slope=(vr3.x*vr2.y-vr3.y*vr2.x);

    vr3.x/=slope;
    vr3.y/=-slope;
    vr2.x/=-slope;
    vr2.y/=slope;

 //  if(row==104)printf("%f %f %f %f\n",temp[0][0],temp[0][1],temp[1][0],temp[1][1]);

   for(int ii=0;ii<count;ii++){
    d1[index+ii]=vr3.x*jacobian[index+2*ii];
    d1[index+ii]+=(vr3.y*jacobian[index+2*ii+1]);
    d1[index+ii+count]=vr2.x*jacobian[index+2*ii];
    d1[index+ii+count]+=(vr2.y*jacobian[index+2*ii+1]);

  //  if(row==104){printf("%f %f %f %f %f %f\n",temp[0][0],temp[0][1],temp[1][0],temp[1][1],jacobian[row*max*2+2*ii],jacobian[row*max*2+2*ii+1]);
    // printf("%f %f\n",d1[row*max*2+ii],d1[row*max*2+ii+count]);}
   }

//Initial guess of internal vertex
   v1.x=vr1.x;
   v1.y=vr1.y;

//Here begins the calculation of main algorithmic loop
  for(int kk=0;kk<10;kk++){
    //cout<<v1.x<<" "<<v1.y<<endl;
    //calculation of function vector reusing the jacobain matrix this time for function vector
  for(int ii=0;ii<count;ii++){
   jacobian[index+ii]=v1.x*funct[index1+ii].coeff_x+v1.y*funct[index1+ii].coeff_y+funct[index1+ii].const_coeff;
  // if(row==104)printf("****%f\n",jacobian[row*max*2+ii]);
    //printf("****%f %f \n",funct[row*max+ii].coeff_x,funct[row*max+ii].coeff_y); 
  }

   //First step of Algorithm
    sn=powf(v1.x,2)*o.coeff_sqr_x+powf(v1.y,2)*o.coeff_sqr_y+v1.x*v1.y*o.coeff_xy;
    sn+=v1.x*o.rest.coeff_x+v1.y*o.rest.coeff_y+o.rest.const_coeff;

  
  v0.x=v0.y=0;//Reinitializing the current vertex to calculate the new position
  for(int ii=0;ii<count;ii++){
    v0.x+=d1[index+ii]*jacobian[index+ii];
    v0.y+=d1[index+ii+count]*jacobian[index+ii];
  }
  
 //new coordinates i.e. xn+1 

  //if(row==104)printf("*****%f %f\n",v0.x,v0.y);
  v2.x=v1.x+v0.x;
  v2.y=v1.y+v0.y;

  sn_1=powf(v2.x,2)*o.coeff_sqr_x+powf(v2.y,2)*o.coeff_sqr_y+v2.x*v2.y*o.coeff_xy;
  sn_1+=v2.x*o.rest.coeff_x+v2.y*o.rest.coeff_y+o.rest.const_coeff;

  if(fabs((sn_1-sn)/sn) < precision){
    //puts("reached");
     break;}
   
  lamda=1;//step 3 of algorithm

 if(sn_1<sn){//puts("Here");
   v1.x=v2.x;v1.y=v2.y;continue;}//step 4 of algorithm


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

  //cout<<"lamda="<<lamda<<endl;

  //Step 7 of algorithm

   //if(row==104)printf("lamda=%f\n",lamda);
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
       jacobian[index+ii]=v1.x*funct[index1+ii].coeff_x+v1.y*funct[index1+ii].coeff_y+funct[index1+ii].const_coeff;

      v0.x=v0.y=0;//Reinitializing the current vertex to calculate the new position
     for(int ii=0;ii<count;ii++){
       v0.x+=d1[index+ii]*jacobian[index+ii];
       v0.y+=d1[index+ii+count]*jacobian[index+ii];
     }

     v2.x=v1.x+v0.x;
     v2.y=v1.y+v0.y;

      sn_1=powf(v2.x,2)*o.coeff_sqr_x+powf(v2.y,2)*o.coeff_sqr_x+v2.x*v2.y*o.coeff_xy;
      sn_1+=v2.x*o.rest.coeff_x+v2.y*o.rest.coeff_y+o.rest.const_coeff;

      k++;
      }

    if(k==10)break;

   }//Algorithm loop ends here*/

   //if(row==104)printf("%f %f\n",v1.x,v1.y);
   result[row].x=v1.x;
   result[row].y=v1.y;
   }

else{
result[row].x=d_vb[row].x;
result[row].y=d_vb[row].y;
}

}

}

