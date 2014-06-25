#include"header.h"
#include<time.h>
#include"my_setup_3D.h"

void copy(vertex_buffer* &, vertex_buffer* &, int);
vertex_buffer* d_vb=NULL;
index_buffer*  d_ib=NULL;
vertex_buffer* output=NULL;
int count=0;
int *test;

int v_count;//stores total no of vertex for mesh
int f_count;//stores faces count for mesh
int size;
void display_func()
{
glClear(GL_COLOR_BUFFER_BIT);

glPushMatrix();
//glScalef(500,500,500);
glScalef(10,10,5);
if(count%2!=0)glTranslatef(-10,-40,-0);
else glTranslatef(-10,-10,-0);
for(int i=0;i<f_count;i++){
   glBegin(GL_LINE_LOOP);
   glVertex2f(d_vb[d_ib[i].i1].x,d_vb[d_ib[i].i1].y);
   glVertex2f(d_vb[d_ib[i].i2].x,d_vb[d_ib[i].i2].y);
   glVertex2f(d_vb[d_ib[i].i3].x,d_vb[d_ib[i].i3].y);
   glEnd();
}
glPopMatrix();

glPushMatrix();
glScalef(10,10,5);
if(count%2==0)glTranslatef(-10,-50,-10);
else glTranslatef(-10,-10,-0);
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
zhou_shimada(output,d_vb,test,size,v_count);
//print_output(d_vb,v_count);
glutPostRedisplay();
}
else if((count%2)){
count++;
zhou_shimada(d_vb,output,test,size,v_count);
//print_output(output,v_count);
glutPostRedisplay();
}
}

int main(int argc, char **argv)
{
vertex_buffer *output1[1000];
//        glutInit(&argc,argv);
//	my_setup(canvas_Width,canvas_Height,canvas_Name);

vector <int >new_fan;


  if(argc!=3){
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


  vector < vector<int> >fan(v_count);
  vector < vector<edge> >e(v_count);
  
  create_lists(e,d_ib,f_count);

//for(int i=0;i<1000;i++)
//output1[i]=new vertex_buffer[v_count];
  
  //delete[]d_ib;//done with index buffer list
  triangle_fan_create(e,d_vb,fan);


  output=new vertex_buffer[v_count];

size=fan[0].size();

  for(int i=0;i<fan.size();i++){
    for(int j=0;j<size;j++){
        new_fan.push_back(fan[i][j]);
        }
  }

  test=&new_fan[0];

  //clock_t start=clock();
  int count;
  //cin>>count;
   count=atoi(argv[2]);
  for(int i=0;i<count;i++)
  if(!(i%2)){
  zhou_shimada(d_vb,output,test,fan[0].size(),v_count);
  //copy(output,output1[i],v_count);
  }
  else{
  zhou_shimada(output,d_vb,test,fan[0].size(),v_count);
  //copy(d_vb,output1[i],v_count);
  } 
 // clock_t stop=clock();

  //cout<<"Elapsed time="<<(double)((stop-start))/CLOCKS_PER_SEC<<endl;
  if((count%2))
  print_output(output,v_count,d_ib,f_count);
  else
  print_output(d_vb,v_count,d_ib,f_count);
int flag;
/*     float threshold=0.0000001;
     for(int j=0;j<v_count;j++){
	flag=0;
       for(int i=1;i<1000;i++)
        //cout<<fabs(output1[i][j].x-output1[i-1][j].x)<<"\t"<<fabs(output1[i][j].y-output1[i-1][j].y)<<"\t";
	  if((fabs(output1[i][j].x-output1[i-1][j].x)< threshold && fabs(output1[i][j].y-output1[i-1][j].y)<threshold &&  !flag )){
		cout<<j<<"\t"<<i<<endl;
		break;
	 }
        //cout<<endl;
     }
*/
//  glutDisplayFunc(display_func);
//  glutKeyboardFunc(keyboard);
//  glutMainLoop();


return 0;
}


void copy(vertex_buffer* &output, vertex_buffer* &output1, int v_count)
{

  for(int i=0;i<v_count;i++){
    output1[i].x=output[i].x;
    output1[i].y=output[i].y;
   }
}  
