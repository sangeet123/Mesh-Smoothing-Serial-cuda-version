#include<vector>
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;
#include"header.h"


void create_lists(vector <vector<edge> >&e,index_buffer* &d_ib,int & f_count)
{
edge temp;

  for(int i=0;i<f_count;i++){
    
      temp.s=d_ib[i].i2;
      temp.e=d_ib[i].i3;
      e[d_ib[i].i1].push_back(temp);
    
   
      temp.s=d_ib[i].i3;
      temp.e=d_ib[i].i1;
      e[d_ib[i].i2].push_back(temp);
    
      temp.s=d_ib[i].i1;
      temp.e=d_ib[i].i2;
      e[d_ib[i].i3].push_back(temp); 
    }

  /*for(int i=0;i<e.size();i++){
   for(int j=i+1;j<e[i].size();)
     if((e[i][j-1].s==e[i][j].s)&&(e[i][j-1].e==e[i][j].e))//cout<<"This is it"<<endl;
	e[i].erase(e[i].begin()+j);
     else j++;
    }
  */

/*for(int i=0;i<e.size();i++){
 for(int j=0;j<e[i].size();j++)
   cout<<" "<<e[i][j].s<<" "<<e[i][j].e;

  cout<<endl;
}
cout<<endl<<endl;
*/
}
