#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
//	ifstream	pin;
//	ofstream	pout;
	FILE		*fin, *fout;
	int			n1, n2;
	
	// Open the Input and Output Files
	if(argc != 3) return(0);
//	pin.open(argv[1]);
//	pout.open(argv[2]);
	fin = fopen(argv[1], "r+");
	fout = fopen(argv[2], "w+");
	
	// Main Code
	fscanf(fin, "%d %d", &n1, &n2);
	fprintf(fout, "%d", n1 + n2);
	
	// Close the Input and Output Files
	fclose(fin);
	fclose(fout);
//	pin.close();
//	pout.close();
    return(0);
}
