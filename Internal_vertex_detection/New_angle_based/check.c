#include<stdio.h>
#include<math.h>

struct vector{
float x;
float y;
};

int main()
{
struct vector v1;
struct vector v2;
struct vector v3;

float t1;
float t2;
float t3;

 v1.x=5;
 v1.y=-16;


v2.x=-11;
v2.y=-15;


v3.x=-12;
v3.y=-17;


t1=sqrtf(powf(v1.x,2)+powf(v1.y,2));
t2=sqrtf(powf(v2.x,2)+powf(v2.y,2));
t3=sqrtf(powf(v3.x,2)+powf(v3.y,2));

printf("%f %f %f\n",t1,t2,t3);

float a=acos((v1.x*v2.x+v1.y*v2.y)/(t1*t2));
float b=acos((v3.x*v2.x+v3.y*v2.y)/(t3*t2));


printf("alpha1=%f alpha2=%f\n",a*57.2957795,b*57.2957795);


return 0;

}

