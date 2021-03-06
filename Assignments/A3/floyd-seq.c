/**
 * Sequential implementation of Floyds all-pairs shortest path algorithm
 *
 * Resources used in development:
 * http://www.mcs.anl.gov/~itf/dbpp/text/node35.html
 * http://www.scribd.com/doc/23340655/11/Floyd%E2%80%99s-sequential-algorithm
 *
 *  @author Stephen Young (st_youn@encs.concordia.ca)
 *  @course Comp428/4
 *
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sys/time.h>
using namespace std;

// Define a constant for infinity
#define INFINITY 999999

/**
 * GetClock
 * Used for benchmarking performance
 */
double getClock()
{
    struct timeval tp;
    struct timezone tzp;

    gettimeofday(&tp, &tzp);

    return (double)tp.tv_sec+((double)tp.tv_usec/1000000.0);
}

/**
 * FloydsAlgorithm (sequential)
 * Performs a test of an adjacency matrix (2-dimensional represented as single dimension)
 * to find the shortest distance between two nodes on the directed graph
 * @param int* data A square adjacency matrix
 * @param int N Size of a single dimension of the matrix
 */
void FloydsAlgorithm(int *data, int N){

	int k,i,j;
	int ij,ik,kj;

	// Maximum path length is N so we iterate N times
	for(k=0; k<N; k++){
		// Test rows
		for(i=0; i<N; i++){
			// Test columns
			for (j=0; j<N; j++){
				// Resolve some indices
				ij = i * N + j;
				ik = i * N + k;
				kj = k * N + j;

				// If i == j, the nodes are the same, so the distance is zero
				if(i==j){
					data[ij] = 0;
				}else{
					// Use an arbitrarily large number to test against
					if(data[ij] == 0) data[ij] = INFINITY;
					// If our data is smaller, replace it and set the output to be the current path length
					if(data[ik]+data[kj]< data[ij]){
						data[ij] = data[ik]+data[kj];
					}
				}
			}
		}
	}
}

/**
 * Main function
 * Performs a sample test of the algorithm, using the matrix sampled at
 * http://www.mcs.anl.gov/~itf/dbpp/text/node35.html
 * Output should be:
 *  	0 1 2 2
 *		2 0 1 1
 *		0 0 0 0
 *		1 2 1 0
 */
int main(int argc, char * argv[]){

	double startTime = getClock();

	char * file;

	if(argc > 1){
		file = argv[1];
	}else{
		cout << "Please supply a filename" << endl;
		return 1;
	}

	FILE *I_in;
	// Load the mask
	ifstream M_in(file, ios::in);
	int N,tmp;
	M_in >> N;

	int data[N*N];
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++){
			   M_in >> tmp;
			   data[y*N + x] = tmp;
		}
	// Perform the actual calculation (simple is passed by reference, so no return)
	FloydsAlgorithm(data,N);

	// Print out the new matrix with the returned results
	int index;
	for(int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			index = i*N+j;
			// Convert INFINITY values back to zero
			if(data[index] == INFINITY)
				cout << 0 << ' ';
			else
				cout << data[index] << ' ';
		}
		cout << endl;
	}

	cout << "Time: "<< getClock() - startTime << endl;

	return 0;
}
