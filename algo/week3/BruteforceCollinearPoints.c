// Online C compiler to run C online.
// Write C code in this online editor and run it.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <search.h>
#define inf INFINITY


typedef struct points
{
    int x;
    int y;
    struct points * p;
} point;


float slope1(point p1,point p2) 
{
 if(p2.y==p1.y && p2.x!=p1.x) return 0;//horizontal line segment
  else if(p2.x==p1.x && p2.y!=p1.y) return inf; //vertical line segment
  else if(p2.x==p1.x && p2.y==p1.y) return -inf;//point to itself
  else 
  return (p2.y-p1.y)/((float)(p2.x-p1.x));
}
float slope(point *p1,point *p2) {
   if(p2->y==p1->y && p2->x!=p1->x) return 0;//horizontal line segment
  else if(p2->x==p1->x && p2->y!=p1->y) return inf; //vertical line segment
  else if(p2->x==p1->x && p2->y==p1->y) return -inf;//point to itself
  else 
  return (p2->y-p1->y)/((float)(p2->x-p1->x));
}

int compareto(float f1, float f2)
 {
  float precision = 0.00001;
  
  if(f1==f2)
   {
    return 0;
   }
   return 1;
 }
int comparator(const void *p, const void *q) 
{ 

  point *p1 = (point *)p;
  point *p2 = (point *)q;

   float x=slope(p1,p1->p);
   float y=slope(p2,p2->p);
   if(x>y)
   return 1;
   if(x<y)
   return -1;
   return 0;
   
}
int comparator1(const void *p, const void *q) 
{ 

  point *p1 = (point *)p;
  point *p2 = (point *)q;

  int x1=p1->x;
  int y1=p1->y;
  int x2=p2->x;
  int y2=p2->y;
  
  if(x1==x2)
  {
      if(y1==y2)
        return 0;
        if(y1>y2)
        return 1;
        else
        return -1;
  }
  if(x1>x2)
  {
      return 1;
  }
   if(x1<x2)
   return -1;
   
   return 0;
 }

int main() {
    
    int n,x,y;
    printf("enter number of points\n");
    scanf("%d",&n);
    if(n<=4)
   {
    printf("points should be equal or greater than 4");
    return 0;
   } 
   point  pt[n];
    for(int i=0;i<n;i++)
    {

        scanf("%d,%d",&x,&y);
        pt[i].x=x;
        pt[i].y=y;
        pt[i].p=&pt[i];
    }
    printf("points are:\n");
     for(int i=0;i<n;i++)
    {
      printf("(%d,%d),%d,%d\n",pt[i].x,pt[i].y,(pt[i]).p->x,pt[i].p->y);
        
    }
    qsort(pt,n,sizeof(point),comparator1);
    
int arr[n][n];
 for (int i = 0; i < n; i++) 
    for (int j = 0; j < n; j++)
       arr[i][j] = 0; 
    
     for (int i = 0; i < n; i++)
     {
            for (int j = i + 1; j < n; j++)
            {
                for (int k = j + 1; k < n; k++)
                {
                    for (int m = k + 1; m < n; m++)
                    {
                        point p = pt[i];
                        point q = pt[j];
                        point r = pt[k];
                        point s = pt[m];
                        if (compareto(slope1(p,q),slope1(p,r)) == 0 &&compareto(slope1(p,q), slope1(p,s)) == 0)
                       {
                          
                          arr[i][m]= 1;   
                        }
                    }
                }
            }
        }

  
   for(int i=0;i<n;i++)
   {
       for(int j=n-1;j>=0;j--)
       {
           if(arr[i][j]==1)
           {
         printf("Collinear is(%d,%d),(%d,%d)\n",pt[i].x,pt[i].y,pt[j].x,pt[i].y);
           for(int k=0;k<j;k++)
           arr[i][k]=0;
           for(int k=i+1;k<n;k++)
           arr[k][j]=0;
           }
       }
   }
    return 0;
}





