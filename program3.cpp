#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;


// Draw graph start
void initmap(char m[7][7])
{
    for (int i=0; i<7; i++)
        for (int j=0; j<7; j++)
           m[i][j] = ' ';
}

void planets(char m[7][7])
{
    m[0][3] = 'A';
    m[4][0] = 'B';
    m[4][6] = 'C';
    m[2][0] = 'D';
    m[6][3] = 'E';
    m[2][6] = 'F';
    m[4][2] = 'G';
    m[2][4] = 'H';
    m[4][4] = 'I';
    m[2][2] = 'J';
}

void connect(char m[7][7], int a, int b)
{
    switch (a) {
    case 1:     // A
        if (b == 4)     // connect to D
        {
            m[0][0] = '+';
            m[0][1] = '-';
            m[0][2] = '-';
            m[1][0] = '|';
        }
        if (b == 6)     // connect to F
        {
            m[0][6] = '+';
            m[0][5] = '-';
			m[0][4] = '-';
            m[1][6] = '|';
        }
        if (b == 10)     // connect to J
        {
            m[0][2] = '+';
            m[1][2] = '|';
        }
        if (b == 8)      // connect to H
        {
            m[0][4] = '+';
            m[1][4] = '|';
        }
        break;
    case 2:     // B
        if (b == 5)     // connect to E
        {
            m[6][0] = '+';
            m[6][1] = '-';
            m[6][2] = '-';
            m[5][0] = '|';
        }
        if (b == 7)     // connect to G
        {
            m[4][1] = '-';
        }
        break;
    case 3:     // C
        if (b == 5)     // connect to E
        {
            m[6][6] = '+';
            m[6][5] = '-';
            m[6][4] = '-';
            m[5][6] = '|';
        }
    case 4:     // D
        if (b == 10)     // connect to J
        {
            m[2][1] = '-';
        }
		 if (b == 2)     // connect to B
        {
            m[3][0] = '|';
        }
        break;
    case 6:     // F
        if (b == 3)     // connect to C
        {
            m[3][6] = '|';
        }
        break;
    case 7:     // G
        if (b == 9)     // connect to I
        {
            m[4][3] = '-';
        }
		 if (b == 5)     // connect to E
        {
            m[5][2] = '\\';
			// m[6][2] = '+';
        }
        break;
    case 8:     // H
        if (b == 6)     // connect to F
        {
            m[2][5] = '-';
        }
        if (b == 9)     // connect to I
        {
            m[3][4] = '|';
        }
        break;
	case 9:     // I
        if (b == 5)     // connect to E
        {
            m[5][4] = '/';
        }
        if (b == 9)     // connect to C
        {
            m[4][5] = '-';
        }
        break;
	case 10:     // J
        if (b == 8)     // connect to H
        {
            m[2][3] = '-';
        }
		 if (b == 7)     // connect to G
        {
            m[3][2] = '|';
        }
        break;

    }

}

void display(char m[7][7])
{
    cout << endl;
    for (int i=0; i<7; i++)
    {
        cout << "  ";
        for (int j=0; j<7; j++)
           cout << m[i][j];
        cout << endl;
    }
}

// Draw graph end


struct Planet{
	string name;
	int x;
	int y;
	int z;
	int weight;
	int profit;
	int disjoint = -1;
	int order;
};

struct Edge{
	Planet *from;
	Planet *to;
	double distance;
};

void Union(vector<Edge> &edges, Edge edge, int &setNum){
	if(edge.from->disjoint == -1 && edge.to->disjoint == -1){
		edge.from->disjoint = setNum; 
		edge.to->disjoint = setNum;
	}
	else if(edge.from->disjoint == -1 && edge.to->disjoint != -1){
		edge.from->disjoint = edge.to->disjoint;
		
		
	}
	else if(edge.from->disjoint != -1 && edge.to->disjoint == -1){
		edge.to->disjoint = edge.from->disjoint;
	}
	else{
		for(int i = 0; i < edges.size(); ++i){
			if(edges[i].from->disjoint == edge.from->disjoint && edge.from->name != edges[i].from->name){
				edges[i].from->disjoint = edge.to->disjoint;
			}
			if(edges[i].to->disjoint == edge.from->disjoint && edge.from->name != edges[i].to->name){
				edges[i].to->disjoint = edge.to->disjoint;
			}
			
		}
		edge.from->disjoint = edge.to->disjoint;
	}    
}
int isCycle(vector<Edge> edges, Planet planets[]){
	
	vector<Edge> temp = edges;
	for(int i = 0; i < temp.size(); ++i){
		temp[i].from->disjoint = -1;
		temp[i].to->disjoint = -1;
	}
	int setNum = 0;
    for (int i = 0; i < temp.size(); ++i) {
        int x = temp[i].from->disjoint;
        int y = temp[i].to->disjoint;
        if (x == y && y != -1)
            return 1;

        Union(temp, temp[i], ++setNum);
    }
    return 0;
}
void heapify (Edge A[], int array_size, int j) {
  int max;
  int left = 2*j+1;
  int right = 2*j+2;
  if (left < array_size && A[left].distance > A[j].distance)
    max = left;
  else
    max = j;
  if (right < array_size && A[right].distance > A[max].distance)
    max = right;
  if (max != j) {
    swap (A[j], A[max]);
    heapify(A, array_size, max);
  }
}
void heap_sort (Edge A[], int array_size) {
  for (int j = (array_size-1)/2; j >= 0; j--) 
    heapify (A, array_size, j);
  for (int i = array_size-1; i >= 1; i--) {
    swap (A[0], A[i]);
    heapify (A, --array_size, 0);
  }
}



int main(){
	char map[7][7];

    initmap(map);

    planets(map);

	string path = __FILE__; //gets source code path, include file name
	path = path.substr(0,1+path.find_last_of('\\')); //removes file name
	path+= "A2planets.txt"; //adds input file to path
	ifstream readFile;
	// readFile.open("A2planets.txt");
	readFile.open (path, ios::in);

	Planet planets[10];
	Edge edges[18];
	for(int i = 0; i < 10; ++i){
		readFile >> planets[i].name; 
		readFile >> planets[i].x;
		readFile >> planets[i].y;
		readFile >> planets[i].z;
		readFile >> planets[i].weight;
		readFile >> planets[i].profit;
		planets[i].order = i+1;
	}

	edges[0].from = &planets[0];
	edges[0].to = &planets[3];
	edges[0].distance = sqrt(pow((planets[0].x - planets[3].x),2) + pow((planets[0].y - planets[3].y),2) + pow((planets[0].z - planets[3].z),2));

	edges[1].from = &planets[0];
	edges[1].to = &planets[9];
	edges[1].distance = sqrt(pow((planets[0].x - planets[9].x),2) + pow((planets[0].y - planets[9].y),2) + pow((planets[0].z - planets[9].z),2));

	edges[2].from = &planets[0];
	edges[2].to = &planets[7];
	edges[2].distance = sqrt(pow((planets[0].x - planets[7].x),2) + pow((planets[0].y - planets[7].y),2) + pow((planets[0].z - planets[7].z),2));

	edges[3].from = &planets[0];
	edges[3].to = &planets[5];
	edges[3].distance = sqrt(pow((planets[0].x - planets[5].x),2) + pow((planets[0].y - planets[5].y),2) + pow((planets[0].z - planets[5].z),2));

	edges[4].from = &planets[3];
	edges[4].to = &planets[9];
	edges[4].distance = sqrt(pow((planets[3].x - planets[9].x),2) + pow((planets[3].y - planets[9].y),2) + pow((planets[3].z - planets[9].z),2));

	edges[5].from = &planets[9];
	edges[5].to = &planets[7];
	edges[5].distance = sqrt(pow((planets[9].x - planets[7].x),2) + pow((planets[9].y - planets[7].y),2) + pow((planets[9].z - planets[7].z),2));

	edges[6].from = &planets[7];
	edges[6].to = &planets[5];
	edges[6].distance = sqrt(pow((planets[7].x - planets[5].x),2) + pow((planets[7].y - planets[5].y),2) + pow((planets[7].z - planets[5].z),2));

	edges[7].from = &planets[3];
	edges[7].to = &planets[1];
	edges[7].distance = sqrt(pow((planets[3].x - planets[1].x),2) + pow((planets[3].y - planets[1].y),2) + pow((planets[3].z - planets[1].z),2));

	edges[8].from = &planets[9];
	edges[8].to = &planets[6];
	edges[8].distance = sqrt(pow((planets[9].x - planets[6].x),2) + pow((planets[9].y - planets[6].y),2) + pow((planets[9].z - planets[6].z),2));

	edges[9].from = &planets[7];
	edges[9].to = &planets[8];
	edges[9].distance = sqrt(pow((planets[7].x - planets[8].x),2) + pow((planets[7].y - planets[8].y),2) + pow((planets[7].z - planets[8].z),2));

	edges[10].from = &planets[5];
	edges[10].to = &planets[2];
	edges[10].distance = sqrt(pow((planets[5].x - planets[2].x),2) + pow((planets[5].y - planets[2].y),2) + pow((planets[5].z - planets[2].z),2));

	edges[11].from = &planets[1];
	edges[11].to = &planets[6];
	edges[11].distance = sqrt(pow((planets[1].x - planets[6].x),2) + pow((planets[1].y - planets[6].y),2) + pow((planets[1].z - planets[6].z),2));

	edges[12].from = &planets[6];
	edges[12].to = &planets[8];
	edges[12].distance = sqrt(pow((planets[6].x - planets[8].x),2) + pow((planets[6].y - planets[8].y),2) + pow((planets[6].z - planets[8].z),2));

	edges[13].from = &planets[8];
	edges[13].to = &planets[2];
	edges[13].distance = sqrt(pow((planets[8].x - planets[2].x),2) + pow((planets[8].y - planets[2].y),2) + pow((planets[8].z - planets[2].z),2));

	edges[14].from = &planets[1];
	edges[14].to = &planets[4];
	edges[14].distance = sqrt(pow((planets[1].x - planets[4].x),2) + pow((planets[1].y - planets[4].y),2) + pow((planets[1].z - planets[4].z),2));

	edges[15].from = &planets[6];
	edges[15].to = &planets[4];
	edges[15].distance = sqrt(pow((planets[6].x - planets[4].x),2) + pow((planets[6].y - planets[4].y),2) + pow((planets[6].z - planets[4].z),2));

	edges[16].from = &planets[8];
	edges[16].to = &planets[4];
	edges[16].distance = sqrt(pow((planets[8].x - planets[4].x),2) + pow((planets[8].y - planets[4].y),2) + pow((planets[8].z - planets[4].z),2));

	edges[17].from = &planets[2];
	edges[17].to = &planets[4];
	edges[17].distance = sqrt(pow((planets[2].x - planets[4].x),2) + pow((planets[2].y - planets[4].y),2) + pow((planets[2].z - planets[4].z),2));

	cout << "Edges after sorting: "<<endl;
	cout << "  From   |     To     |   Forms a loop?   |   Distance "<<endl;
	cout << "---------|------------|-------------------|-------------"<<endl;
	heap_sort (edges, 18);
	vector<Edge> usedEdges;
	for(int i = 0; i < 18; ++i){
		cout << edges[i].from->name << " |  " << edges[i].to->name <<  "  |";
		usedEdges.push_back(edges[i]);
		if(isCycle(usedEdges, planets)){
			cout << "       Yes         "  << "|   " << edges[i].distance << endl;
			usedEdges.pop_back();
		}
		else{
			cout << "        No         " << "|   " << edges[i].distance <<  endl;
		}
	}

	for(int i = 0; i < usedEdges.size(); ++i){
		connect(map,usedEdges[i].from->order ,usedEdges[i].to->order);
	}

	cout << "\n\nGraph using to edges that doesn't form a loop: " << endl;
	display(map);
	
}

