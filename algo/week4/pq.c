
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<limits.h>
#include<string.h>


//input 3 0 1 3 4 2 5 7 8 6 
//input 3 8 1 3 4 0 2 7 6 5
//input 3 5 1 3 4 0 2 7 6 8

int **goal;
int N;

typedef struct Node_ 
{ 
	int **mat; 
	int x, y; 
	int cost; 
	int level; 
	struct Node_ * parent; 

}Node; 


typedef struct PriorityQueue
{
    Node *data;
    int priority;
    struct PriorityQueue * next;
}pq;


int ** allocate_memory(int** arr)
{
  arr = malloc(N*sizeof(*arr));
  int i;
  for(i=0; i<N; i++)
    (arr)[i] = malloc(N*sizeof(*arr[i]));
     return arr;
} 

void display(int **m) 
{ 
	for (int i = 0; i < N; i++) 
	{ 
		for (int j = 0; j < N; j++) 
			printf("%d ", m[i][j]); 
		printf("\n"); 
	}
printf("------------------\n");
} 

pq* newpq(Node *d, int p) 
{ 
    pq* temp = (pq*)malloc(sizeof(pq)); 
    temp->data = d; 
    temp->priority = p; 
    temp->next = NULL; 
  
    return temp; 
} 

Node* peek(pq* head) 
{ 
	Node * x= (head)->data;
	return x;
} 

// Removes the element with the 
// highest priority form the list 
pq* pop(pq* head) 
{ 
	pq* temp = head; 
	(head) = (head)->next; 
        return head;
} 

// Function to push according to priority 
pq* push(pq* head, Node * d, int p) 
{ 
	pq* start = (head); 
	pq* temp = newpq(d, p); 
        if(head==NULL)
        {
          head=temp;
          temp->next=NULL;
          return head;
        } 
	if ((head)->priority > p) 
	{ 
		temp->next = head; 
		(head) = temp;
                 return head; 
	} 
	else 
	{ 
	while (start->next != NULL && start->next->priority < p) 
			start = start->next; 
		temp->next = start->next; 
		start->next = temp; 
	}
        return head; 
} 

int isEmpty(pq* head) 
{ 
	return (head) == NULL; 
} 

void swap(int *x,int *y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}


void printPath(Node* root) 
{ 
	if (root == NULL) 
		return; 
	printPath(root->parent); 
        display(root->mat);
} 



void createGoal() 
{
    goal=allocate_memory(goal);
    int k=0;
    for(int i=0;i<N;i++) 
    	for(int j=0;j<N;j++) 
    		goal[i][j] = ++k;
	goal[N-1][N-1]=0;
}

Node* newNode(int **mat, int x, int y, int newX, 
			int newY, int level, Node* parent) 
{ 
	Node* node = (Node *) malloc(sizeof(Node)); 
    
	node->parent = parent; 
        
        node->mat=allocate_memory(node->mat);
         for(int i=0;i<N;i++) 
    	for(int j=0;j<N;j++) 
            node->mat[i][j]=mat[i][j];
	swap(&node->mat[x][y], &node->mat[newX][newY]); 
	node->cost = INT_MAX; 
	node->level = level; 
	node->x = newX; 
	node->y = newY; 

	return node; 
} 

// bottom, left, top, right 
int row[] = { 1, 0, -1, 0 }; 
int col[] = { 0, -1, 0, 1 };

int calculateCost(int **initial) 
{ 
    int count = 0; 
    for (int i = 0; i < N; i++) 
      for (int j = 0; j < N; j++) 
        if (initial[i][j] && initial[i][j] != goal[i][j]) 
           count++; 
    return count; 
} 
/*
int calculateCost(int **intial)
{
int m=0;

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(intial[i][j]!=0){
            int calcI = (intial[i][j] - 1) / N;
            int calcJ = (intial[i][j] - 1) % N;
            if (i != calcI || j != calcJ)
            {
            int distanceI = i - calcI;
            m += distanceI < 0 ? distanceI * -1 : distanceI;
            int distanceJ = j - calcJ;
            m += distanceJ < 0 ? distanceJ * -1 : distanceJ;
            }
        }}
    }
    
    return m;
    
}
*/
bool equals(int **p,int **q) {
		int i,j;
	 for(i=0;i<N;i++) 
    	for(j=0;j<N;j++) 
    		if(p[i][j]!=q[i][j]) return false;
	return true;	
}


int isSafe(int x, int y) 
{ 
	return (x >= 0 && x < N && y >= 0 && y < N); 
}


void solve(int **initial, int x, int y) 
{ 
    printf("yessolve \n");
    Node *ro = newNode(initial, x, y, x, y, 0, NULL); 
    ro->cost = calculateCost(initial); 
  

    pq* p = newpq(ro, ro->cost+ro->level); 

    // Finds a live node with least cost, 
    // add its childrens to list of live nodes and 
    // finally deletes it from the list.
    
    while (!isEmpty(p)) { 
         //printf("yes empty\n");
         Node* min = peek(p);
        // Find a live node with least estimated cost 
        // The found node is deleted from the list of 
        // live nodes 
        p= pop(p); 
        if ( equals(min->mat,goal)) 
        { 
            // print the path from root to destination;
          printf("complete path----------\n");
          printPath(min);
          return ;
         }
        // do for each child of min 
        // max 4 children for a node 
        for (int i = 0; i < 4; i++) 
        { 
            if (isSafe(min->x + row[i], min->y + col[i])) 
            { 
                // create a child node and calculate 
                // its cost 
                Node* child = newNode(min->mat, min->x, 
                              min->y, min->x + row[i], 
                              min->y + col[i], 
                              min->level + 1,min); 
                child->cost = calculateCost(child->mat)+child->level;
                if(child->parent->parent!=NULL){
                if(!equals(child->mat,child->parent->parent->mat)) 
                p=push(p,child,child->cost);  }
                else
                 p=push(p,child,child->cost);
                 display(child->mat);
                 
                // Add child to list of live nodes 

            } 
        } 
    } 
} 





int main () {
   int **arr;
   printf("Enter input:");
   scanf("%d",&N);
   arr=allocate_memory(arr);  
    for(int i=0;i<N;i++) 
    	for(int j=0;j<N;j++) 
    		scanf("%d",&arr[i][j]);
    display(arr);
    createGoal();
    printf("Goal board :");
    display(goal);
    printf("yes\n");
     int i,j;
    int s=0;
    for(i=0;i<N;i++)
    {
    for(j=0;j<N;j++)
      if(arr[i][j]==0)
         {
           s=1;
           break;
         }
    if(s==1)
         break;
    }
  printf("%d,%d\n",i,j);
    solve(arr,i,j);
    for(int i=0;i<N;i++)
    {
       free(arr[i]);
       free(goal[i]);
     }
      free(arr);
      free(goal);  
  
	return 0;
}


