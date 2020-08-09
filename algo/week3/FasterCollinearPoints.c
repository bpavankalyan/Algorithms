

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

typedef struct lines
{
    point p1;
    point p2;
}linesegment;


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
       //printf("%f,%f",f1,f2);
    return 0;
   }
   return 1;
 }
int comparator(const void *p, const void *q) 
{ 

  point *p1 = (point *)p;
  point *p2 = (point *)q;

   float x1=slope(p1,p1->p);
   float y1=slope(p2,p2->p);
   if(x1>y1)
   return 1;
   if(x1<y1)
   return -1;
   if(x1==y1)
   {
       if(p1->x>p2->x)
       return 1;
       if(p1->x<p2->x)
       return -1;
   }
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
void fasterCollinear(point *p,int n)
{
       
     linesegment ls[n*5];    
    int a=0;
    for(int i=0;i<n;i++)
    {
        int c=n-i-1;
        point copy[c];
        for(int j=i+1;j<n;j++)
        {
            copy[j-1-i]=p[j];
            copy[j-1-i].p=&p[i];
        }
      
        qsort(copy,c,sizeof(point),comparator);
      
    
    int lineCounter = 2;
   for (int j = 1; j < c; j++) 
  {
    if (compareto(slope1(p[i],copy[j - 1]), slope1(p[i],copy[j])) == 0)
     {
         lineCounter++;
     }
    else 
    {
      if (lineCounter >= 4)
      {
        ls[a].p1=p[i];
        ls[a].p2=copy[j-1];
        a++;
       }
       lineCounter = 2;
     }
   }
   if (lineCounter >= 4) 
   {
      ls[a].p1=p[i];
      ls[a].p2=copy[c-1];
      a++;
    }
  }
    linesegment las[a-1];
    for(int i=0;i<a;i++)
    las[i]=ls[i];
    
    for(int i=0;i<a;i++)
    {
        for(int j=i+1;j<a;j++)
        {
            if(las[i].p1.x!=-1 && las[j].p2.x!=-1)
            if((las[i].p2.y==las[j].p2.y)&&(las[i].p2.x==las[j].p2.x))
            {
                if((las[i].p1.x<las[j].p1.x))
                las[j].p2.x=-1;
                else if((las[i].p1.x==las[j].p1.x)&&(las[i].p1.y<las[j].p1.y) )
                    las[j].p2.x=-1;
                    else
                    las[i].p1.x==-1;

            }
        }
    }
    printf("\n collinear are\n");
    for(int i=0;i<a;i++)
    {
        if(las[i].p1.x!=-1 && las[i].p2.x!=-1)
        printf("\n collinear is (%d,%d)->(%d,%d)",las[i].p1.x,las[i].p1.y,las[i].p2.x,las[i].p2.y);
    }
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
    
   qsort(pt,n,sizeof(point),comparator1);

   fasterCollinear(pt,n);

    return 0;
}





