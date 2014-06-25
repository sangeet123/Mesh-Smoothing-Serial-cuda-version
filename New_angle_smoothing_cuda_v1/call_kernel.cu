#include"header.h"

void call_kernel(vector <vector<int> >&fan,thrust::device_vector<int> &d_fan, vertex_buffer* &h_vb, vertex_buffer* &output, int row_size,int v_count)
{

  cudaError_t err;
  vertex_buffer *d_vb;
  int *d_fan_ptr;
  vertex_buffer *d_result;
  int height;
  float *jacobian;
  function_info *funct;
  float *d1;



  d_fan_ptr = thrust::raw_pointer_cast(&d_fan[0]);


  err=cudaMalloc((void**)&d_vb,sizeof(struct vertex_buffer)*v_count);
  if(err!=cudaSuccess){
    cout<<"failed to allocate memory for d_vb\n";
    exit(0);
  }



  err=cudaMemcpy(d_vb,h_vb,sizeof(vertex_buffer)*v_count,cudaMemcpyHostToDevice);
  if(err!=cudaSuccess){
    cout<<"unable to copy host vertices lists to device vertices lists\n";
    exit(0);
  }


  output=new vertex_buffer[v_count];
  err=cudaMalloc((void**)&d_result,sizeof(vertex_buffer)*v_count);
  if(err!=cudaSuccess){
    cout<<"unable to allocate memory for d_result\n";
    exit(0);
  }

 

  err=cudaMalloc((void**)&jacobian,sizeof(float)*2*v_count*row_size);
  if(err!=cudaSuccess){
    cout<<"unable to allocate memory for jacobain\n";
    exit(0);
  }

  err=cudaMalloc((void**)&funct,sizeof(function_info*)*v_count*row_size);
  if(err!=cudaSuccess){
    cout<<"unable to allocate memory to store function information\n";
    exit(0);
  }


  err=cudaMalloc((void**)&d1,sizeof(float)*2*v_count*row_size);
  if(err!=cudaSuccess){
    cout<<"unable to allocate memory to store the d information\n";
    exit(0);
   }


  
      //height=1024/row_size;
        height=(v_count-1)/512+1;

  //dim3 dimGrid(1,((v_count-1)/height+1),1);
  //dim3 dimBlock(row_size,height,1);

   dim3 dimGrid(1,height,1);
   dim3 dimBlock(1,512,1);


  cudaEvent_t event1, event2;
  cudaEventCreate(&event1);
  cudaEventCreate(&event2);
  cudaEventRecord(event1,0);
  new_angle_based<<<dimGrid,dimBlock>>>(d_vb,d_result,d_fan_ptr,v_count,row_size,jacobian,funct,d1);
  cudaEventRecord(event2, 0);


  cudaEventSynchronize(event2); //wait for the event to be executed!


  float dt_ms;
  cudaEventElapsedTime(&dt_ms, event1, event2);

  printf("elapsed_time = %f\n",dt_ms);


  cudaMemcpy(output,d_result,sizeof(vertex_buffer)*v_count,cudaMemcpyDeviceToHost);


//  for(int i=0;i<v_count;i++)
//   cout<<output[i].x<<" "<<output[i].y<<endl;
}
