#include"header.h"
#include<time.h>


int main(int argc, char **argv)
{
int v_count;//stores total no of vertex for mesh
int f_count;//stores faces count for mesh
vertex_buffer* d_vb=NULL;
index_buffer*  d_ib=NULL;
vertex_buffer* output=NULL;

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


  create_lists(fan,d_ib,f_count);

  delete[]d_ib;//done with index buffer list
  triangle_fan_create(d_vb,fan);


  output=new vertex_buffer[v_count];

   int row_size=fan[0].size();
   thrust::device_vector<int>d_fan(row_size*v_count);

   for(int j=0,i=0;i<v_count;i++){
    thrust::copy(fan[i].begin(),fan[i].end(),d_fan.begin()+j);
    j+=row_size;
   }

  int count;
  //cin>>count;
  count=atoi(argv[2]);

  for(int i=0;;i++)
   if(!(i%2))
   call_kernel(fan,d_fan,d_vb,output,row_size,v_count);
  else
 call_kernel(fan,d_fan,output,d_vb,row_size,v_count);



return 0;
}



