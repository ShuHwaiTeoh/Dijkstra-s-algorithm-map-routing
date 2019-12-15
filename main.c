#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "map.h"

#define INF   (1500000000)   // The largest distance<=sqrt(200000000)*(Vert-1)

int main(int argc, char *argv[]) {
	FILE *fptr1 = NULL; //Pointer for the first input file
	FILE *fptr2 = NULL; //Pointer for the second input file
  int Vert = 0;//Number of vertices
  int Query = 0;//Number of quieries
  int Edge;//Number of edges
  int Start;//Starting vertex
	int Dest;//Ending Vertex
  int **XYbook = malloc(sizeof(int*)*2);//Store the x and y coordinate of the vertices
  int i,j;
  
  //Open the input files
  fptr1 = fopen(argv[1], "r");
  fscanf(fptr1,"%d %d",&Vert,&Edge);
  fptr2 = fopen(argv[2], "r");
  fscanf(fptr2,"%d",&Query);
  
  //Initialize the XYbook
  for(i=0; i<3; i++){
    XYbook[i] = malloc(sizeof(int) *Vert);
    for (j=0; j<Vert; j++){
      XYbook[i][j] = -1;
    }
  }
  
  //Read in the x and y coordinate and store them to the xybook
  build_XYbook(fptr1, XYbook, Vert);
  //Array of linked lists. Each node is an adjacent vertex.
  AdjList *AdjArray[Vert];
	//Let each slott of AdjArray point to a list 
  for(i = 0; i<Vert; i++) AdjArray[i] = build_List(i);
  //Read in the edges from the file and build the adjacent list in each slott of AdjArray
  build_AdjArray(fptr1, AdjArray, Vert, Edge);
  //Build a queue to store the distance of the edges for each pair of vertices
  Node *Node_array = malloc(sizeof(Node) *Vert);
  
	//Read in the Queries and find the shortest path
	for(i=0; i<Query; i++) { 
		fscanf(fptr2,"%d %d",&Start,&Dest); 
		if(Start>=Vert || Dest>=Vert){//If the quiery includes the vertex that is not exsiting
			printf("INF\n%d %d\n", Start, Dest);
		}
		else if (Start == Dest) {
    	printf("0\n%d %d\n", Start, Dest);
  	}
		else{
			Dijkstra(Vert,Start,Dest,XYbook,AdjArray,Node_array); 
		}
	}    
	
  fclose(fptr1);
  fclose(fptr2);
 return 0;
} 



