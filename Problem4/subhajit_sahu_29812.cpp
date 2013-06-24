#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	ifstream	pin;
	ofstream	pout;
	FILE		*fin, *fout;
	
	// Open the Input and Output Files
	if(argc != 3) return(0);
	pin.open(argv[1]);
	pout.open(argv[2]);
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	
	// Main Code
	pout << "Hello.\n";
	fprintf(fout, "Hello2.\n");
	
	// Close the Input and Output Files
	pin.close();
	pout.close();
    return(0);
}
