#include<iostream>
using namespace std;



struct Node{
 
    double x,y;                //x coordinate and y cordinate of the vertex
 
    struct Node *next,*prev;   //doubly linked list 
/* 
There are four types of vertices start,end,split,merge and regular
*/
    char vertextype;      //stores which type the vertex is
};


struct Node* polygon = NULL;     //storing the polygon as doubly linked circular list


//Mergesort function to sort coordinates according to y coordinates

void merge(double arr[], int l, int m, int r) 
{ 
    int n1 = m - l + 1; 
    int n2 = r - m; 
  
    // Create temp arrays  
    int L[n1], R[n2]; 
  
    // Copy data to temp arrays L[] and R[]  
    for(int i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for(int j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 
  
    // Merge the temp arrays back into arr[l..r] 
      
    // Initial index of first subarray 
    int i = 0;  
      
    // Initial index of second subarray 
    int j = 0;  
      
    // Initial index of merged subarray 
    int k = l; 
      
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j])  
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else 
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    // Copy the remaining elements of 
    // L[], if there are any  
    while (i < n1)  
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    // Copy the remaining elements of 
    // R[], if there are any  
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void mergeSort(double arr[], int l, int r) 
{ 
    if (l < r) 
    { 
          
        // Same as (l+r)/2, but avoids  
        // overflow for large l and h 
        int m = l + (r - l) / 2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m + 1, r); 
  
        merge(arr, l, m, r); 
    } 
} 
 


/*
Standard Insert function in a doubly linked list
*/

void insert(double x,double y){
    
    //if this is the first vertex
    if(polygon == NULL){
      
        struct Node* new_vertex = new Node;
      
        new_vertex->x = x;
      
        new_vertex->y = y;
      
        new_vertex->next = new_vertex->prev = new_vertex;  //both the next and previous pointers point to itself
      
        polygon = new_vertex;
      
        return;
    }

    //if list is not empty we insert it at the end as the vertices are given in clockwise cyclic order

    Node* last = (polygon)->prev;

    struct Node* new_vertex = new Node;

    new_vertex->x = x;  new_vertex->y = y;

    new_vertex->next = polygon;

    (polygon)->prev = new_vertex;

    new_vertex->prev = last;  last->next = new_vertex;


}

/*calculate area of triangle
Area of the triangle is used to check wether a point lies inside the triangle
*/
double TriangleArea(struct Node* p1,struct Node* p2, struct Node* p3){
 
    double area=0;
    
    area+= (p1->x*(p3->y - p2->y));
   
    area+= (p2->x*(p1->y - p3->y));
    
    area+= (p3->x*(p2->y - p1->y));
    
    return area/(2.0);
}

//check if the vertex is convex or reflexive
//Since points are given in clockwise order point is convex if area of triangle formed with neighbours is positive

bool convex(struct Node* p1,struct Node* p2, struct Node* p3){

    if(TriangleArea(p1,p2,p3)>0.0) return true;
  
    else return false;

}


/****************************

ALGORITHM:

1.Classify all vertices as split,merge,reflex,start and end

2.Sweep a horizontal line from top to bottom

3.Maintain the edges intersected by the sweep line

If we encounter:
    i)Start vertex(Vi)
     Add  ei(the edge containing start vertex) to sweep line 
     helper(ei) = Vi

    ii)Split vertex(Vi)
      Find an edge to the left of Vi
      Connect Vi to helper(ej)
      helper(ej) = Vi
      Insert ei to sweep line status
      helper(ei) = Vi

    iii)Merge Vertex(Vi)
      if helper(ei-1) is merge vertex, then connect Vi to helper(ei-1)
      Remove ei-1 for Sweepline status
      Find in SLS the edge ej directly to the left of Vi
      If helper(ej) is a merge vertex, then connect Vi to helper(ej)
      helper(ej) = Vi

    iv)Regular vertex(Vi)
      if the polygon's interior lies to the left of Vi then:
        Find in SLS the edge ej directly to the left of Vi
        If helper(ej) is a merge vertex, then connect Vi to helper(ej)
        helper(ej) = Vi

      else 
        If helper(ei-1) is a merge vertex,then connect Vi to helper(ei-1)
        Remove ei-1 from Sweep line status
        Insert ei into SLS
        helper(ei) = Vi

******************************/

main(){
    int n,sz;
    
    cout<<"Enter no. of vertices: ";
   
    cin>>n;

    sz = n;
   
    double a[n];

    //inserting the vertices into circular list 
    for(int i=0;i<n;i++){
        double x,y;
        cin>>x>>y;
        insert(x,y);
        a[i] = y;
    }

    struct Node* temp  = polygon;
  
    struct Node* start,*end; //start vertex is a convex vertex whose both neighbours are below it coordinate plane

//While loop to find start vertex
    while(1){
        
        if(!convex(temp->prev,temp,temp->next)){
        
            temp = temp->next;
        
            continue;
        
        } 

        if(temp->next->y >= temp->y){ 
        
            temp = temp->next;
        
            continue;
        
        }

        if(temp->prev->y >= temp->y){
        
            temp = temp->next;
        
            continue;
        
        }
        
        start = temp;
        
        break;
    }

    end = start;

//While loop to find end vertex -end vertex is convex whose both neighbours are above it

    while(1){
       
        if(!convex(end->prev,end,end->next)){
       
            end = end->next;
       
            continue;
       
        } 

        if(end->next->y <= end->y){ 
       
            end = end->next;
       
            continue;
       
        }

        if(end->prev->y <= end->y){
       
            end = end->next;
       
            continue;
       
        }
        
        break;

    }

/*Classifying vertices
s = start vertex, e = end vertex
r = regular vertex :convex vertex other than start and end vertices
p = split vertex :  reflex vertex whose neighbours lie below it 
m = merge vertex :  reflex vertex whose neighbours lie above it  
*/
    start->vertextype = 's'; end->vertextype = 'e';

    temp = start->next;

//Loop to assign vertex type
    while(temp!=start){

        if(convex(temp->prev,temp,temp->next)) temp->vertextype = 'r';

        else{

            if(temp->next->y <= temp->y  && (temp->prev->y <= temp->y)) temp->vertextype = 'p';

            if(temp->next->y >= temp->y  && (temp->prev->y >= temp->y)) temp->vertextype = 'm';

        }

        temp = temp->next;
    }


//sort according to y cordinates because we are going to sweep from top to bottom

    mergeSort(a,0,n-1);

//sweeping from top to bottom

/* 
Doubt

After adding the diagonals , a diagonal may belong to 2 polyogns
so how to maintain these polygons.
*/
}