#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <sstream>
#include "graphtinker.h" 
using namespace std;

unsigned int printv_edgecount(vertexid_t start_vid, vertexid_t stop_vid, vector<edge_nt> & edge_block_array){
	unsigned int edgecount = 0;
	for(vertexid_t vid=start_vid; vid<stop_vid; vid++){
		unsigned int offset = get_edgeblock_offset(vid);		
		for(unsigned int j=offset; j<(offset+WORK_BLOCKS_PER_PAGE); j++){ 
			for(unsigned int k=0; k<WORK_BLOCK_HEIGHT; k++){
				if (edge_block_array[j].edges[k].flag == VALID){ edgecount += 1; }
			}
		}
	}
	return edgecount;
}

unsigned int printv_uniqueedgecount(vertexid_t start_vid, vertexid_t stop_vid, vector<edge_nt> & edge_block_array){
	unsigned int edgecount = 0;
	for(vertexid_t vid=start_vid; vid<stop_vid; vid++){
		unsigned int offset = get_edgeblock_offset(vid);		
		for(unsigned int j=offset; j<(offset+WORK_BLOCKS_PER_PAGE); j++){ 
			for(unsigned int k=0; k<WORK_BLOCK_HEIGHT; k++){
				if (edge_block_array[j].edges[k].flag == VALID){ edgecount += edge_block_array[j].edges[k].edge_weight; }
			}
		}
	}
	return edgecount;
}