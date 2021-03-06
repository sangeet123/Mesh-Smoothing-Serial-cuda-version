#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<vector>
#include<math.h>
#include<thrust/host_vector.h>
#include<thrust/device_vector.h>
#include<thrust/sort.h>



using namespace std;


struct vertex_buffer{
float x;
float y;
};

struct index_buffer{
unsigned int i1;
unsigned int i2;
unsigned int i3;
};

struct function_info{
float coeff_x;
float coeff_y;
float const_coeff;
};

struct objective_function{
float coeff_sqr_x;
float coeff_sqr_y;
float coeff_xy;
function_info rest;
};


void read_input_mesh(ifstream &,int &, int &,vertex_buffer*&,index_buffer*&);
void create_lists(vector< vector<int> > &,index_buffer* &,int &);
void triangle_fan_create(vertex_buffer* &,vector <vector<int> >&);
//void New_angle(vertex_buffer* &, vertex_buffer* &,int *,int, int,float**,function_info**,float**);
void print_output(vertex_buffer* &, int &);
//void call_kernel(vector< <vector<int> > &, thrust::device_vector<int> &,vertex_buffer* &,vertex_buffer* &,int ,int);
void call_kernel(vector< vector<int> > &,thrust::device_vector<int> &, vertex_buffer* &, vertex_buffer* &, int,int);
void __global__ new_angle_based(const struct vertex_buffer *, struct vertex_buffer *,int *,int,int,float *,function_info*,float*);

