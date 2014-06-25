#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
using namespace std;
#include"header.h"

/*
  This function reads the input mesh data
*/


void read_input_mesh(ifstream &mesh_input, int &v_count, int & f_count,vertex_buffer* &d_vb,index_buffer* &d_ib)
{
  string header;
  int dummy;

  mesh_input>>header;//reading header

  if(header!="OFF"){
    cout<<"Invalid header"<<endl;
    exit(0);
  }


  mesh_input>>v_count>>f_count>>dummy;


  d_vb=new vertex_buffer[v_count];
  d_ib=new index_buffer[f_count];


  for(int i=0;i<v_count;i++)
    mesh_input >> d_vb[i].x >> d_vb[i].y;
    // mesh_input>>dummy >> d_vb[i].x >> d_vb[i].y;


  for(int i=0;i<f_count;i++){
    //mesh_input >> dummy >> d_ib[i].i1 >> d_ib[i].i2 >> d_ib[i].i3;
     mesh_input >>d_ib[i].i1 >> d_ib[i].i2 >> d_ib[i].i3;
      d_ib[i].i1--; d_ib[i].i2--; d_ib[i].i3--;
  }
  /*for(int i=0;i<f_count;i++)
  cout<<d_ib[i].i1<<" "<<d_ib[i].i2<<" "<<d_ib[i].i3<<" "<<endl;*/

}

