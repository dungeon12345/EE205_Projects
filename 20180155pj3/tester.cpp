#include <iostream>
#include <cstdlib>
#include <cassert>
#include <sys/time.h>
#include <iomanip>
#include <bits/stdc++.h> 
#include "bst.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////
static void
generateNumber(int *p, int max, int maxval)
{
	for (int i = 0; i < max; i++) 
		p[i] = rand() % maxval;
}

///////////////////////////////////////////////////////////////////////////
static void
printElapsedTime(const struct timeval* pstart, const char* str)
{
	struct timeval now;
	double elapsed;
	
	gettimeofday(&now, NULL);
	elapsed = 1e3 * (now.tv_sec - pstart->tv_sec)
		+ 1e-3 * (now.tv_usec - pstart->tv_usec);
	cout << str << ":\t" << std::setprecision(5) << elapsed << " ms " << endl;
}
///////////////////////////////////////////////////////////////////////////
static int intCompare(const void* pA, const void* pB)
{
	int a = *(int *)pA;
	int b = *(int *)pB;

	if (a > b) return 1;
	if (a == b) return 0;
	return -1;
}

///////////////////////////////////////////////////////////////////////////
int main(int argc, const char* argv[])
{
	IntBST bst;
    IntRBTree rb;
	int i, *k, *idx;
	int num = 1000;
	unsigned int token = 0;
	struct timeval t1, t2;
	map<int, int> m;
		
	// initialize with a seed
	if (argc >= 2) {
		token = atoi(argv[1]);
		srand(token);
	}
	if (argc == 3) {
		num = atoi(argv[2]);
		assert (num > 0);
	}

	cout << "<<Preprocessing starts>>" << endl;
	cout << "Random seed: " << token << "\t# of integers: " << num << endl; 

	// generate
	k   = new int[num];
	idx = new int[num];
	if (k == NULL || idx == NULL) {
		cerr << "memory allocation failed! " << endl;
		return -1;
	}

	// generate integers;
	cout << "Generating "<< num << " integers..." << endl;
	generateNumber(k, num, INT_MAX);
	generateNumber(idx, num, num);
	cout << "<<Preprocessing ends>>"<< endl << endl;

	// insert to BST
	gettimeofday(&t1, NULL);
	for (i = 0; i < num; i++)
		bst.insert(k[i]);
	printElapsedTime(&t1, "BST Insertion");

	assert(bst.size() == num);
	assert(bst.countRange(-1, INT_MAX) == num);
	
	// search in BST
	gettimeofday(&t1, NULL);
	for (i = 0; i < num; i++) 
		assert(bst.find(k[idx[i]]) >= 1);
	printElapsedTime(&t1, "BST Searching");

	// remove the keys from BST
	gettimeofday(&t1, NULL);
	for (i = 0; i < num; i++) 
		assert(bst.remove(k[i]) == true);
	printElapsedTime(&t1, "BST Removal");

	// correctness checking
	assert(bst.size() == 0);
	
    // insert to RBtree
	gettimeofday(&t1, NULL);
	for (i = 0; i < num; i++) 
		rb.insert(k[i]);
	printElapsedTime(&t1, "RB Insertion");

	// correctness checking
	assert(rb.size() == num);
	assert(rb.countRange(-1, INT_MAX) == num);
	
	// search in RBtree
	gettimeofday(&t1, NULL);
	for (i = 0; i < num; i++) 
		assert (rb.find(k[idx[i]]) >= 1);
	printElapsedTime(&t1, "RB Searching");

	// remove the keys from RBTree
	gettimeofday(&t1, NULL);
	for (i = 0; i < num; i++) 
		assert(rb.remove(k[i]) == true);
	printElapsedTime(&t1, "RB Removal");

	// correctness checking
	assert(rb.size() == 0);
	
	// remove dynamically-allocated memory
	delete k;
	delete idx;
	
	return 0;
}
