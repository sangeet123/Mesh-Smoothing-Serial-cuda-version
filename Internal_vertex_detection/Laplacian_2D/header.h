#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<vector>
#include<math.h>
#include<GL/glut.h>
#include <GL/freeglut.h>
#define BITMAP GLUT_BITMAP_9_BY_15
#define canvas_Width 800
#define canvas_Height 800
#define canvas_Name "Mesh Smoothing"


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

struct edge{
int s;
int e;
};

void read_input_mesh(ifstream &,int &, int &,vertex_buffer*&,index_buffer*&);
void create_lists(vector< vector<edge> > &,index_buffer* &,int &);
void triangle_fan_create(vector <vector<edge> >&,vertex_buffer* &,vector <vector<int> >&);
void zhou_shimada(vertex_buffer* &, vertex_buffer* &,int *,int, int);
void print_output(vertex_buffer* &, int &);

