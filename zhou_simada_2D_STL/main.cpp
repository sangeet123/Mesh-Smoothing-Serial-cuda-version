#include"header.h"
#include<time.h>
#include"my_setup_3D.h"

vertex_buffer* d_vb=NULL;
index_buffer*  d_ib=NULL;
vertex_buffer* output=NULL;
int count=0;
int *test;
vector < vector<int> >fan(500000);

int v_count;//stores total no of vertex for mesh
int f_count;//stores faces count for mesh
int size;

void display_func()
{
glClear(GL_COLOR_BUFFER_BIT);

glPushMatrix();
//glScalef(500,500,500);
glScalef(5,5,5);
if(count%2!=0)glTranslatef(-0,-800,-0);
for(int i=0;i<f_count;i++){
   glBegin(GL_LINE_LOOP);
   glVertex2f(d_vb[d_ib[i].i1].x,d_vb[d_ib[i].i1].y);
   glVertex2f(d_vb[d_ib[i].i2].x,d_vb[d_ib[i].i2].y);
   glVertex2f(d_vb[d_ib[i].i3].x,d_vb[d_ib[i].i3].y);
   glEnd();
}
glPopMatrix();

glPushMatrix();
glScalef(5,5,5);
if(count%2==0)glTranslatef(-0,-800,-10);
for(int i=0;i<f_count;i++){
   glBegin(GL_LINE_LOOP);
   glVertex2f(output[d_ib[i].i1].x,output[d_ib[i].i1].y);
   glVertex2f(output[d_ib[i].i2].x,output[d_ib[i].i2].y);
   glVertex2f(output[d_ib[i].i3].x,output[d_ib[i].i3].y);
   glEnd();
}
glPopMatrix();

glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y)
{

if(!(count%2)){
count++;
zhou_shimada(output,d_vb,fan,size,v_count);
//print_output(d_vb,v_count);
glutPostRedisplay();
}
else if((count%2)){
count++;
zhou_shimada(d_vb,output,fan,size,v_count);
//print_output(output,v_count);
glutPostRedisplay();
}
}

int main(int argc, char **argv)
{
        glutInit(&argc,argv);
	my_setup(canvas_Width,canvas_Height,canvas_Name);

//vector <int >new_fan;


  if(argc!=2){
    cout<<"<usuage>:mismatched arguments"<<endl;
    exit(0);
  }

  ifstream mesh_input(argv[1]);

  if(mesh_input.is_open())
    read_input_mesh(mesh_input,v_count,f_count,d_vb,d_ib);
  else{
    cout<<"Cannot open input mesh"<<endl;
    exit(0);
  }

  mesh_input.close();//Finised with reading mesh data


  //vector < vector<int> >fan(v_count);
  
  create_lists(fan,d_ib,f_count);


  
  //delete[]d_ib;//done with index buffer list
  triangle_fan_create(d_vb,fan);


  output=new vertex_buffer[v_count];

  /*size=fan[0].size();

  for(int i=0;i<fan.size();i++){
    for(int j=0;j<size;j++){
        new_fan.push_back(fan[i][j]);
        }
  }

  test=&new_fan[0];*/

  clock_t start=clock();
  //for(int i=0;i<100;i++)	
  zhou_shimada(d_vb,output,fan,fan[0].size(),v_count);
  clock_t stop=clock();

  cout<<"Elapsed time="<<(double)((stop-start))/CLOCKS_PER_SEC<<endl;

//  print_output(output,v_count);  
  glutDisplayFunc(display_func);
  glutKeyboardFunc(keyboard);
  glutMainLoop();


return 0;
}



