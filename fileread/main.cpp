#include<iostream>
#include<fstream>
using namespace std;
struct Vex
{
	int num;
	char name[20];
	char desc[100];
};
struct Edge
{
	int v1;
	int v2;
	int w;
};
int main()
{
	int nV;
	Vex sVex[20];
	ifstream vfile("Vex.txt");
	for (int i = 0; i < 8; i++)
	{
		if (i == 0)
			vfile >> nV;
		else
		{
			
			
				vfile >> sVex[i-1].num>> sVex[i-1].name>> sVex[i-1].desc;
			
		}
	}
	vfile.close();
	for (int i = 0; i < 7; i++)
	{
		cout << sVex[i].num << sVex[i].name << sVex[i].desc << endl;
	}

	//Edge sEdge[10];
	//ifstream efile("Edge.txt");
	//if (!efile)
	//	cerr << "error\n";
	//for (int i = 0; i < 10&&!efile.eof(); i++)
	//{
	//	efile >> sEdge[i].v1 >> sEdge[i].v2 >> sEdge[i].w;
	//}
	//efile.close();
	//for (int j = 0; j < 10; j++)
	//{
	//	cout << sEdge[j].v1 << sEdge[j].v2 << sEdge[j].w << endl;
	//}


	return 0;
}