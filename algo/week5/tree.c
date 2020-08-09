
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <math.h>


#define k 2

typedef struct Node_
{
  int data[k];
  struct Node_ * left;
  struct Node_ *right;
  bool color;
  int size;
}node;



// data structures related to rectangle
typedef struct Rect_
{
  int xmin;
  int xmax;
  int ymin;
  int ymax;
} rect;

bool rectContains(rect *R, int point[k]) {
	return ((point[0] >= R->xmin && point[0] <=R->xmax) && (point[1] >= R->ymin && point[1] <= R->ymax));
}



node * newNode(int point[k])
{
  node * tree_node=(node*) malloc(sizeof(node));
  for(int i=0;i<k;i++){
  tree_node->data[i]=point[i];
  }
  tree_node->left=NULL;
  tree_node->right=NULL;
  tree_node->color=true;
  tree_node->size=1;
  return tree_node;
}

 
node * insert(node * root,  int depth,int point[k])
{

  if(root==NULL){
     return newNode(point);
   }
   else{
   unsigned dimension =depth%k;
   if(point[dimension]< root->data[dimension]){
      root->left=insert(root->left,depth+1,point);
   }
   else{
    root->right=insert(root->right,depth+1,point);
   }
  }
  return root;
} 

bool arePointsSame(int point1[],int point2[])
{
  for(int i=0;i<k;i++)
     if(point1[i]!=point2[i])
        return false;
  return true;
}

bool search(node* root, int point[k], size_t depth)
{
  if(root==NULL)
    return false;
  if(arePointsSame(root->data,point))
     return true;
  size_t dimension=depth%k;
 if (point[dimension] < root->data[dimension]) 
        return search(root->left, point, depth + 1); 
  
    return search(root->right, point, depth + 1);
  
}


void rangeNode(node * root, rect * rect,int depth)
{
  printf("range search \n");
  if(root==NULL)
     return;
  if(rectContains(rect,root->data))
     printf("point is (%d,%d)",root->data[0],root->data[1]);
  int cd =depth%2;
  if(cd ==0)
  {
    if(root->data[cd] > rect->xmin)
     {
        rangeNode(root->left,rect, depth+1);}
    if(root->data[cd] <= rect->xmax)
        rangeNode(root->right,rect, depth+1);
  }
  else
  {
    if(root->data[cd] > rect->ymin)
     {
        rangeNode(root->left,rect, depth+1);}
    if(root->data[cd] <= rect->ymax)
        rangeNode(root->right,rect, depth+1);
  }
}




float distance (int point1[k],int point2[k])
{
   double x=0;
   for(int i=0;i<k;i++)
       x+=(point1[i]-point2[i])*(point1[i]-point2[i]);
   return sqrt(x);
}
      

node * nearestsearch(node * current,node * nearest, int point[k])
{
  if(current==NULL || distance(nearest->data,point) < distance(current->data,point))
return nearest;

if(distance(current->data,point) < distance(nearest->data,point))
nearest=current;

node * nleft=nearestsearch(current->left,nearest,point);
if(distance(nleft->data,point) < distance(nearest->data,point))
nearest=nleft;

node * nright=nearestsearch(current->right,nearest,point);
if(distance(nright->data,point) < distance(nearest->data,point))
nearest=nright;

return nearest;
}

node * nearest (node * root,int point[k])
{
  if(root==NULL)
     return NULL;
  return nearestsearch(root,root,point);
}



int height( node* node)
{
   if (node==NULL)
       return 0;
   else
   {
     int lheight = height(node->left);
     int rheight = height(node->right);
  
     if (lheight > rheight)
         return(lheight+1);
     else
        return(rheight+1);
   }
}
 

void printLevel( node* root, int level)
{
    if(root == NULL)
        return;
    if(level == 1)
        printf("(%d,%d)  ", root->data[0],root->data[1]);
    else if (level > 1)
    {
        printLevel(root->left, level-1);
        printLevel(root->right, level-1);
    }
} 
     
   void levelorder( node* root)
{
    int h = height(root);
    int i;
    for(i=1; i<=h; i++){
        printLevel(root, i);
        printf("..\n");
   }
}    
  
void inorder(node *node) 
{ 
    if (node) 
    { 
        inorder(node -> left); 
        printf("(%d,%d) ", node -> data[0],node->data[1]); 
        inorder(node -> right);  
    } 
} 


int main()
{
    node *root = NULL;
    printf("start\n"); 
   
    int points[][k] = {{3, 6}, {17, 15}, {13, 15}, {6, 12}, 
                       {9, 1}, {2, 7}, {10, 19}}; 
  
    int n = sizeof(points)/sizeof(points[0]); 

    for (int i=0; i<n; i++) {
       root = insert(root, 0,points[i]); 
       root->color=false;
       }
   levelorder(root);
      int p[2]={10,11};
      node * x=nearest(root,p);
              printf(" NEAREST for point (%d,%d) is (%d,%d)\n  ",p[0],p[1], x->data[0],x->data[1]);
     rect * r = malloc(sizeof(rect));
    printf("\n Enter min and max coordinates of rectangle with space between them\n"); 
    scanf("%d,%d %d,%d",&r->xmin,&r->ymin,&r->xmax,&r->ymax);
    printf("\nnodes inside rectangle are:\n");
    rangeNode(root,r,0);
    return 0; 
 }



