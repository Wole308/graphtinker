#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <functional>
#include <sys/time.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <omp.h>
#include "../graphtinker/graphtinker.h"
#include "../vertices/vertices.h"
#define ___use_omp___
using namespace std;

class multicore_updates_test
{
  public:
    multicore_updates_test();
    ~multicore_updates_test();
 private:
};

multicore_updates_test::multicore_updates_test(){}
multicore_updates_test::~multicore_updates_test(){}

 void insertions(graphtinker & tinkerA, graphtinker & tinkerB, vector<tuple_t> & src_dst_pairs){
	cout<<endl<<"insertions started : src_dst_pairs size : "<<src_dst_pairs.size()<<endl;
	#ifdef ___use_omp___
	#pragma omp parallel sections 
	{
		#pragma omp section  
        {
			for(unsigned int j=0; j<src_dst_pairs.size(); j++){
				tinkerA.insert_edge((unsigned int)src_dst_pairs[j].A, (unsigned int)src_dst_pairs[j].B, 1);
			}
			cout<<"number of edges in tinkerA : "<<tinkerA.printv_edgecount()<<" edges"<<endl;
		}
		#pragma omp section  
        {
			for(unsigned int j=0; j<src_dst_pairs.size(); j++){
				tinkerB.insert_edge((unsigned int)src_dst_pairs[j].B, (unsigned int)src_dst_pairs[j].A, 1);
			}
			cout<<"number of edges in tinkerB : "<<tinkerB.printv_edgecount()<<" edges"<<endl;
		}
	}
	#else 
	tinkerA.create(SELF, SELF, SELF, 0, 524288, 524288, 8380000, DIRECTEDGRAPH, 8, 64);
	for(unsigned int j=0; j<src_dst_pairs.size(); j++){
		tinkerA.insert_edge((unsigned int)src_dst_pairs[j].A, (unsigned int)src_dst_pairs[j].B, 1);
	}
	cout<<"number of edges in tinkerA : "<<tinkerA.printv_edgecount()<<" edges"<<endl;
	tinkerB.create(SELF, SELF, SELF, 0, 524288, 524288, 8380000, DIRECTEDGRAPH, 8, 64);
	for(unsigned int j=0; j<src_dst_pairs.size(); j++){
		tinkerB.insert_edge((unsigned int)src_dst_pairs[j].B, (unsigned int)src_dst_pairs[j].A, 1);
	}
	cout<<"number of edges in tinkerB : "<<tinkerB.printv_edgecount()<<" edges"<<endl;	
	#endif
	return;
}

 
int main(){
	#pragma omp parallel
	{
		int ID = omp_get_thread_num();
		cout<<" hello world from thread : "<<ID<<endl;
	}
	// return 0;
	
	graphtinker tinkerA(SELF, SELF, SELF, 0, 524288, 524288, 8380000, DIRECTEDGRAPH, 8, 64);
	graphtinker tinkerB(SELF, SELF, SELF, 0, 524288, 524288, 8380000, DIRECTEDGRAPH, 8, 64);
	
	float timelapse_clock = 0;
	float timelapse_tod = 0;
	
	struct timeval start1_tod, end1_tod;
	
	vector<tuple_t> src_dst_pairs;
	src_dst_pairs.clear();
	
	char path[] = "/net/zf15/oj2zf/datasets/rmat500k8m.edges";
	FILE* file = fopen (path, "r");
	if (file==NULL)	{ cout<<"error : cannot find the location of input file rmat500k8m.edges (test_updatesingleedge)"<<endl; }
	
	// insert edges into tinkers
	unsigned int src = 0;
	unsigned int dst = 0;
	unsigned int ew = 0;
	for(unsigned int i=0; i<1000000; i++){
		if(feof(file)) {
			cout<<"finished reading from file (multicore_updates_test)"<<endl; 				
			break;
		}
		if(fscanf (file, "%i", &src) < 0){ cout<<"fscan error (multicore_updates_test)"<<endl; }
		if(fscanf (file, "%i", &dst) < 0){ cout<<"fscan error (multicore_updates_test)"<<endl; }
		
		tuple_t t;
		t.A = src;
		t.B = dst;
		src_dst_pairs.push_back(t);
	}

	gettimeofday(&start1_tod, NULL); 
	std::clock_t start = std::clock();
	
	insertions(tinkerA, tinkerB, src_dst_pairs); ///

	timelapse_clock = (std::clock() - start) / (double) (CLOCKS_PER_SEC / 1000);
	gettimeofday(&end1_tod, NULL);
	timelapse_tod = (float)((end1_tod.tv_sec * 1000000 + end1_tod.tv_usec) - (start1_tod.tv_sec * 1000000 + start1_tod.tv_usec))/1000;

	cout<<"number of edges A : "<<tinkerA.printv_edgecount()<<" edges"<<endl;
	cout<<"number of edges B : "<<tinkerB.printv_edgecount()<<" edges"<<endl;
	
	cout<<"jurassicpark::run_jpasyn : time lapse (clock) : "<<timelapse_clock<<" ms"<<endl;		
	cout<<"jurassicpark::run_jpasyn : time lapse (tod) : "<<timelapse_tod<<" ms"<<endl;
	cout<<"jurassicpark::run_jpasyn : threads ran : "<<omp_get_num_threads()<<" threads"<<endl;
	cout<<"finished."<<endl;
	return 0;
}