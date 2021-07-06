#include<iostream>
using namespace std;

//Structure to represent each coordinate

struct Node{
    double x,y;                  //x coordinate and y cordinate of the vertex
   
    struct Node *next,*prev;     //doubly linked list
};


struct Node* polygon = NULL;     //storing the polygon as doubly linked circular list


/*
Standard Insert function in a doubly linked list
*/
void insert(double x,double y){
    
    //if this is the first vertex, create a new node and assign polygon to this node

    if(polygon == NULL){
       
        struct Node* new_vertex = new Node;
       
        new_vertex->x = x;
       
        new_vertex->y = y;
       
        new_vertex->next = new_vertex->prev = new_vertex;  //both the next and previous pointers point to itself
       
        polygon = new_vertex;
       
        return;
    }

//if list is not empty we insert it at the end as the vertices are given in clockwise cyclic order

/*Point the previous pointer to last node and next pointer to the first node
Last node's next pointer points to newly added node
*/

    Node* last = (polygon)->prev;

    struct Node* new_vertex = new Node;

    new_vertex->x = x;  new_vertex->y = y;                      
                                                            
    new_vertex->next = polygon;

    (polygon)->prev = new_vertex;

    new_vertex->prev = last;  last->next = new_vertex;
}




//calculate area of triangle
/* Area of the triangle is used to check wether a point lies inside the triangle
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


/*
check if the given point lies inside triangle formed by three points
if sum of areas of triangles formed by the point we are checking with other points is equal to area of the 
triangle , then point lies inside triangle formed by other 3

                 B
                / \
               /   \
              /     \
             /   P   \               if area of PAB + PAC + PCB = ABC the P lies inside
            /         \
     A(0,0) ----------- C(20,0) 
*/
bool insideTriangle(struct Node* p1,struct Node* p2,struct Node* p3,struct Node* check){
   
    double totalarea = TriangleArea(p1,p2,p3);
   
    double a1 = TriangleArea(p1,p2,check);
   
    double a2 = TriangleArea(p2,p3,check);
   
    double a3 = TriangleArea(p1,p3,check);
   
    if((TriangleArea(p1,p2,check) + TriangleArea(p2,p3,check) + TriangleArea(p1,p3,check)) == totalarea) return true;
   
    return false;
}



/*check if the vertex is an Ear
Logic:
We check if the vertex is convex and no other vertex other than neighbours lie in the triangle
*/
bool checkEar(struct Node* v){
    bool isConvex = convex(v->prev,v,v->next);

    if(!isConvex) return false; //if veretx is reflexive then it cannot be an Ear

    struct Node* temp = v;
   
    temp = temp->next; temp = temp->next;
   
    while(temp!= v->prev){

        if(insideTriangle(v->prev,v,v->next,temp)) return false;

        temp = temp->next;

    }

    return true;
}

void display(struct Node* start){
    struct Node *temp = start;
    
    while(temp->next!= start){
        
        printf("%f %f \n",temp->x,temp->y);
        
        temp = temp->next;
    }

    printf("%f %f \n",temp->x,temp->y);
}




/***********************
ALGORITHM:

1.Start from the first vertex

2.While there are more than 3 vertices remaining go through the polygon

3.If current Coordinate is an Ear:
    Remove this cordinate and add the diagonal from previous node to next node of current node

4.Else:
    Go to the next node 

************************/


main(){
    int n,sz;
    
    cout<<"Enter no. of vertices: ";
    cin>>n;

    sz = n;
    pair<double,double> a[n];

    //inserting the vertices into circular list 
    cout<<"Enter the vertices(x,y) in clockwise order:\n";
    for(int i=0;i<n;i++){
        double x,y;
        cin>>x>>y;
        insert(x,y);
        a[i].first  = x;
        a[i].second = y;
    }


    int idx = 0;
    int ans[sz-3][2];               //(n-3)*2 matrix for storing diagonals
    pair<double,double> pts[n-3][2];

    int k=0,i=0,prevnode = sz-1,nextnode = 1;

    
    while(polygon->next->next!= polygon->prev){
       
        if(checkEar(polygon)){
       
            struct Node* temp = polygon->prev;
       
            polygon->prev->next = polygon->next;
       
            ans[i][0] = prevnode;

            ans[i][1] = nextnode;

            pts[i][0].first = polygon->prev->x; pts[i][0].second = polygon->prev->y; 

            pts[i][1].first = polygon->next->x; pts[i][1].second = polygon->next->y;

            polygon->next->prev = polygon->prev;


            polygon->next = polygon->next->next;

            polygon = polygon->next;

            i++;            k++;
            
            nextnode = (nextnode+1)%sz;
        
        }
        
        else{
        
            polygon = polygon->next;
        
            k++;
        
            prevnode = (prevnode+1)%sz;
        
            nextnode = (nextnode+1)%sz;
       
        }

    }

    for(int i=0;i<(sz-3);i++){

        cout<<"Diagonals between point number: ";
        cout<<ans[i][0]<<" and "<<ans[i][1]<<"\n";

    }
}