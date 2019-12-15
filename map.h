#define INF   (1500000000)   // The largest distance<=sqrt(200000000)*(Vert-1)
//Structure for the adjacent list
typedef struct AdjList {
  int num; //vertex number
  struct AdjList *next;//neighbor
} AdjList;
//Structure for
typedef struct Node {
  int vert;//vertex number
  int t_dist;//distance from the union
} Node;

//Functions declared
void build_XYbook(FILE *fptr1, int ** XYbook, int Vert); 
AdjList *build_List(int num);
void build_AdjArray(FILE *fptr1, AdjList *AdjArray[], int Vert, int Edge);
void Dijkstra(int Vert, int start, int dest, int **XYbook, AdjList *AdjArray[], Node *Node_array);
int CalDist(int nearest, int num, int **XYbook);
int FindNear(Node *Node_array, int *visit, int Vert);

//Function to read in the x and y coordinate and store them to the xybook
void build_XYbook(FILE * fptr1, int ** XYbook, int Vert) { 
	int index=0, x=0, y=0; 
	int row=0, column=0;
	int i; 
	
	for(i=0; i<Vert; i++){ 
		fscanf(fptr1, "%d %d %d", &index, &x, &y); 
		XYbook[row][column]=index; 
		row++; 
		XYbook[row][column]=x; 
		row++; 
		XYbook[row][column]=y; 
		row=0; 
		column++; 
  } 
} 

//Function to build a node for the list in the array
AdjList *build_List(int num) { 
	AdjList *node = malloc(sizeof(AdjList));
	 
	node->num = num;
	node->next = NULL; 
	return node; 
} 

//Function to read in the edges from the file and build the adjacent list in each slott of AdjArray
void build_AdjArray(FILE * fptr1, AdjList * AdjArray[], int Vert, int Edge){
	int index = 0; //Vertex1 of the edge: AdjArray index which equals to the number of each vertex
	int ListNum = 0; //Vertex1 of the edge: Number store into linked list
	AdjList *current;
	AdjList *previous; 
	AdjList *temp; 
	
  //Since its an undirected grapgh, build the edge in two directions
  while(fscanf(fptr1,"%d %d",&index,&ListNum) != EOF){
  	//Diresction from the first vertex to the second vertex
    current = build_List(ListNum);
    if(AdjArray[index]->next != NULL){
      previous = AdjArray[index]->next;
      temp = previous;
      while (previous->next != NULL) {
				previous = previous->next;
      }
      previous->next = current;
      AdjArray[index]->next = temp;
    } 
		else {
      AdjArray[index]->next = current;
    }
		//Diresction from the second vertex to the first vertex
    current = build_List(index);
    if (AdjArray[ListNum]->next != NULL) {
      previous = AdjArray[ListNum]->next;
      temp = previous;
      while (previous->next != NULL) {
				previous = previous->next;
      }
      previous->next = current;
      AdjArray[ListNum]->next = temp;
    } 
		else {
			AdjArray[ListNum]->next = current;
    }
  }
}

//Function to find the shortest path
void Dijkstra(int Vert, int start, int dest, int **XYbook, AdjList *AdjArray[], Node *Node_array) {
  int *distance = malloc(sizeof(int)*Vert);//distance from the union compsed by start vertex and visited vertices
  int *previous = malloc(sizeof(int)*Vert);//record the path
  int *visit = malloc(sizeof(int)*Vert);//record whether a vertex is visited
  AdjList *current; 
  int nearest;//The nearest vertex from the current vertex
  int d;//distance between the current vertex and its nearest vertex
  int total;//total distance of the path
  int i, index, count;
  
  //Initialize distance[], previous[], visit[] 
  for(i=0; i<Vert; i++){
    previous[i] = -1;
    visit[i] = 0;
    Node_array[i].vert = i;
    distance[i] = INF;
    Node_array[i].t_dist = INF;
  }
  //Start vertex is visited and the distance from itself is 0
  distance[start]=0;
  Node_array[start].t_dist = 0;

	//Find the shortest path
  for (i=0; i<Vert; i++) {
    nearest = FindNear(Node_array,visit,Vert);
    if (nearest == dest) {
      break;
    }
    visit[nearest] = 1;
    current = AdjArray[nearest];
    while (current->next != NULL) {
      current = current->next;
      d = CalDist(nearest, current->num, XYbook);      
      total = distance[nearest] + d;
      if (total < distance[current->num]) {
				distance[current->num] = total;
				previous[current->num] = nearest;
				Node_array[current->num].t_dist = total;
      }
    }
  }
	//print the distance of the shortest path
  printf("%d\n", distance[dest]);
  //print the path
  index = dest;
  count = 2;//Count path array length. 2 is for start and dest
  while (previous[index] != start) {
    count++;
    index = previous[index];
  }
  
  int path = previous[dest];
  int *path_array = malloc(sizeof(int)*count);//array to store the path
  path_array[0] = start;
  path_array[count-1] = dest;
  for(i=count-2; i>0; i--){
  	path_array[i] = path;
    path = previous[path];
	}
  for (i = 0; i < count; i++) {
    printf("%d ",path_array[i]);
  }
  printf("\n");
}

//Function to find the nearest vertex
int FindNear(Node *Node_array, int *visit, int Vert) {
  int i;
  int min = INF;
  int nVert=0;
  
  for (i = 0;i<Vert; i++) {
    if (Node_array[i].t_dist< min && visit[i] != 1) {
      min = Node_array[i].t_dist;
      nVert = Node_array[i].vert;
    }
  }
  return nVert;
}

//Function to calculate the distance between the two vertices
int CalDist(int nearest, int num, int **XYbook) {
  int x1,x2,y1,y2;
  x1 = XYbook[1][nearest];
  y1 = XYbook[2][nearest];
  x2 = XYbook[1][num];
  y2 = XYbook[2][num];
  
  return sqrt(pow((x2-x1),2) + pow((y2-y1),2));
}
