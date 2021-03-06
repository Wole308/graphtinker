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
using namespace std;

/**
cout<<"NUM_CORES: 2"<<endl;
cout<<"LLFULLDB: ON"<<endl;
cout<<"WORK_BLOCK_HEIGHT: 4"<<endl;
cout<<"SUB_BLOCK_HEIGHT: "<<endl;
cout<<"PAGE_BLOCKHEIGHT: "<<endl;
cout<<"BATCH_SIZE: "<<endl; */

class updates_test
{
  public:
    updates_test();
    ~updates_test();
 private:
};

updates_test::updates_test(){}
updates_test::~updates_test(){}

void insertions(graphtinker & tinker){
	cout<<"=== insertions started ==="<<endl;
	vector<tuple_t> src_dst_pairs;
	unsigned int edges_inserted = 0;
	unsigned int total_edges_inserted = 0;
	float insertion_timelapse_ms = 0;
	float total_insertion_time_lapse_ms = 0;
	float throughput = 0;
	float runningthroughput = 0;
	unsigned int batchid = 0;
	
	char path[] = "/net/zf15/oj2zf/datasets/rmat500k8m.edges";
	FILE* file = fopen (path, "r");
	if (file==NULL)	{ cout<<"error : cannot find the location of input file rmat500k8m.edges (test_updatesingleedge)"<<endl; }
	
	// char path[] = "/net/zf15/oj2zf/datasets/rmat500k8m_hd_inedges_84081_5038749.edges";
	// FILE* file = fopen (path, "r");
	// if (file==NULL)	{ cout<<"error : cannot find the location of input file rmat500k8m_hd_inedges_84081_5038749.edges (test_updatesingleedge)"<<endl; }
	
	// char path[] = "/net/zf15/oj2zf/datasets/rmat500k8m_ld_outedges_440207_3341252.edges";
	// FILE* file = fopen (path, "r");
	// if (file==NULL)	{ cout<<"error : cannot find the location of input file rmat500k8m_ld_outedges_440207_3341252.edges (test_updatesingleedge)"<<endl; }
	
	while(!feof(file)){
		src_dst_pairs.clear();
		
		// load batch of edges
		unsigned int src = 0;
		unsigned int dst = 0;
		unsigned int ew = 0;
		for(unsigned int i=0; i<BATCH_SIZE; i++){
			if(feof(file)) {
				cout<<"finished reading from file (updates_test)"<<endl; 				
				break;
			}
			if(fscanf (file, "%i", &src) < 0){ cout<<"fscan error (updates_test)"<<endl; }
			if(fscanf (file, "%i", &dst) < 0){ cout<<"fscan error (updates_test)"<<endl; }
			
			tuple_t t;
			t.A = src;
			t.B = dst;
			src_dst_pairs.push_back(t);
		}
		
		// insert edges
		edges_inserted = 0;
		std::clock_t start = std::clock();
		for(unsigned int j=0; j<src_dst_pairs.size(); j++){
			edges_inserted += 1;
			total_edges_inserted += 1;
			tinker.insert_edge((unsigned int)src_dst_pairs[j].A, (unsigned int)src_dst_pairs[j].B, 1);
			if(tinker.get_graphdirectiontype() == UNDIRECTEDGRAPH){
				edges_inserted += 1;
				total_edges_inserted += 1;
				tinker.insert_edge((unsigned int)src_dst_pairs[j].B, (unsigned int)src_dst_pairs[j].A, 1);
			}
		}
		insertion_timelapse_ms = 0;
		insertion_timelapse_ms = (std::clock() - start) / (double) (CLOCKS_PER_SEC / 1000);
		total_insertion_time_lapse_ms += insertion_timelapse_ms;
		throughput = ((edges_inserted / insertion_timelapse_ms) * 1000) / 1000000;
		runningthroughput = ((total_edges_inserted/total_insertion_time_lapse_ms) * 1000) / 1000000;
		cout<<endl<<"batch : "<<batchid<<endl;
		cout<<"edges loaded : "<<edges_inserted<<" edges"<<endl;
		cout<<"number of edges : "<<tinker.printv_edgecount()<<" edges"<<endl;
		cout<<"number of unique edges : "<<tinker.printv_uniqueedgecount()<<" edges"<<endl;
		#ifdef EN_LLGDS
		cout<<"number of edges in ll : "<<tinker.printll_edgecount()<<" edges"<<endl;
		#endif
		cout<<"timelapse (ms) : "<<(float)insertion_timelapse_ms<<" ms"<<endl;
		cout<<"total timelapse (ms) : "<<(float)total_insertion_time_lapse_ms<<" ms"<<endl;
		cout<<"running throughput : "<<(float)runningthroughput<<" million edges per sec"<<endl;
		batchid += 1;
	}
	
	fclose (file);
	src_dst_pairs.clear();
	return;
}

void deletions(graphtinker & tinker){
	cout<<"=== deletions started ==="<<endl;
	vector<tuple_t> src_dst_pairs;
	unsigned int edges_deleted = 0;
	unsigned int total_edges_deleted = 0;
	float deletion_timelapse_ms = 0;
	float total_deletion_time_lapse_ms = 0;
	float throughput = 0;
	float runningthroughput = 0;
	unsigned int batchid = 0;
	
	char path[] = "/net/zf15/oj2zf/datasets/rmat500k8m.edges";
	FILE* file = fopen (path, "r");
	if (file==NULL)	{ cout<<"error : cannot find the location of input file rmat500k8m.edges (test_updatesingleedge)"<<endl; }
	
	while(!feof(file)){
		src_dst_pairs.clear();
		
		// load batch of edges
		unsigned int src = 0;
		unsigned int dst = 0;
		unsigned int ew = 0;
		for(unsigned int i=0; i<BATCH_SIZE; i++){
			if(feof(file)) {
				cout<<"finished reading from file (updates_test)"<<endl; 				
				break;
			}
			if(fscanf (file, "%i", &src) < 0){ cout<<"fscan error (updates_test)"<<endl; }
			if(fscanf (file, "%i", &dst) < 0){ cout<<"fscan error (updates_test)"<<endl; }
			
			tuple_t t;
			t.A = src;
			t.B = dst;
			src_dst_pairs.push_back(t);
		}

		edges_deleted = 0;
		std::clock_t start = std::clock();
		for(unsigned int j=0; j<src_dst_pairs.size(); j++){
			edges_deleted += 1;
			total_edges_deleted += 1;
			tinker.delete_edge((unsigned int)src_dst_pairs[j].A, (unsigned int)src_dst_pairs[j].B, 1);
			if(tinker.get_graphdirectiontype() == UNDIRECTEDGRAPH){
				edges_deleted += 1;
				total_edges_deleted += 1;
				tinker.insert_edge((unsigned int)src_dst_pairs[j].B, (unsigned int)src_dst_pairs[j].A, 1);
			}
		}
		deletion_timelapse_ms = (std::clock() - start) / (double) (CLOCKS_PER_SEC / 1000);
		total_deletion_time_lapse_ms += deletion_timelapse_ms;
		throughput = ((edges_deleted / deletion_timelapse_ms) * 1000) / 1000000;
		runningthroughput = ((total_edges_deleted/total_deletion_time_lapse_ms) * 1000) / 1000000;		
		cout<<endl<<"batch : "<<batchid<<endl;
		cout<<"edges loaded : "<<edges_deleted<<" edges"<<endl;
		cout<<"number of edges : "<<tinker.printv_edgecount()<<" edges"<<endl;
		cout<<"number of unique edges : "<<tinker.printv_uniqueedgecount()<<" edges"<<endl;
		#ifdef EN_LLGDS
		cout<<"number of unique edges in ll : "<<tinker.printll_edgecount()<<" edges"<<endl;
		#endif
		cout<<"timelapse (ms) : "<<(float)deletion_timelapse_ms<<" ms"<<endl;
		cout<<"running throughput : "<<(float)runningthroughput<<" million edges per sec"<<endl;
		#ifdef EN_CRUMPLEINONDELETE
		cout<<"svs's size : "<<tinker.print_svs_size()<<endl;
		cout<<"freed edgeblock list's size : "<<tinker.print_freed_edgeblock_list_size()<<endl;
		#endif
		batchid += 1;
	}
	
	fclose (file);
	src_dst_pairs.clear();
	return;
}

int main(){	
	cout<<"started  (updates_test)"<<endl;	
	cout<<"NUM_CORES: 2"<<endl;
	cout<<"LLFULLDB: ON"<<endl;
	cout<<"WORK_BLOCK_HEIGHT: 4"<<endl;
	
	// graphtinker tinkerA(SELF, SELF, SELF, 0, 524288, 524288, 8380000, DIRECTEDGRAPH, 8, 64, 100000, 100000, 1000, 100, 10000);
	graphtinker tinkerA(SELF, SELF, SELF, 0, 524288, 524288, 8380000, DIRECTEDGRAPH, 8, 64);
	insertions(tinkerA);
	deletions(tinkerA);
	return 0;
}