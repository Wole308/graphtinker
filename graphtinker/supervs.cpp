#include <string.h>
#include <iostream>
#include <string>
#include "graphtinker.h"
using namespace std;

int sv_get_next_edge(
			unsigned int xvtx_id,
			vector<supervertex_t> &svs,
			vector<vertexid_t> & freed_edgeblock_list,
			edge_tt * edgett,
			margin_t wblkmargin,
			writebackunitcmd_t writebackunitcmd,
			int * tailhvtx_id,
			unsigned int * svs_index,
			unsigned int * numclusteredworkblocks,
			unsigned int geni,
			vector<edge_nt> & edge_block_array
			){
	// return 5;
	// we got here because the current subblock we're in is clustered, this cluster info has our svs index pointer (sv_ptr)
	unsigned int work_block_height = WORK_BLOCK_HEIGHT;
	unsigned int work_blocks_per_subblock = WORK_BLOCKS_PER_SUBBLOCK;
	unsigned int currworkblockaddr = get_edgeblock_offset(xvtx_id) + wblkmargin.top/work_block_height;
	
	// get tail edgeblock
	// unsigned int svs_index=0;	
	*tailhvtx_id = sv_get_tail_edgeblock(svs, currworkblockaddr, svs_index, geni, edge_block_array);
	if(*tailhvtx_id < 0){
		return 5;
	} else {
		
		// get offset of edgeblock in edge_block_array 
		unsigned int offset = get_edgeblock_offset(*tailhvtx_id);
		
		// pick any edge from it 
		int edgefound = -1;
		edgefound = sv_pick_edge(
				xvtx_id,
				offset,
				edgett,
				numclusteredworkblocks,
				edge_block_array
				);
				
		if(edgefound < 0){ return 6; }
		else { return 7; }
	}
	cout<<"bug! : should not get here (supervs)"<<endl;
	return NULLL;
}

int sv_get_tail_edgeblock(
			vector<supervertex_t> & svs,
			unsigned int currworkblockaddr,
			unsigned int *svs_index,
			unsigned int geni,
			vector<edge_nt> & edge_block_array 
			){
	// get where in svs the founfing father is pointing to
	if(currworkblockaddr >= edge_block_array.size()){ cout<<"bug! : addr out-of-range4 (supervs) "<<endl; }
	if(edge_block_array[currworkblockaddr].clusterinfo.flag != VALID){ cout<<"bug! : addr out-of-range8 (supervs) "<<endl; }
	*svs_index = edge_block_array[currworkblockaddr].clusterinfo.sv_ptr;
	
	// return FAILED if empty
	if(*svs_index >= svs.size()){ return -1; cout<<"bug! : addr out-of-range5 (supervs). *svs_index : "<<*svs_index<<", svs.size() : "<<svs.size()<<endl; return -1; }
	if(svs[*svs_index].hvtx_ids.empty()){
		return -1;
	}
	
	// return if deleted edge was not in a parent subblock
	if(*svs_index >= svs.size()){ cout<<"bug! : addr out-of-range6 (supervs) "<<endl; }
	if(geni >= (svs[*svs_index].geni_ofparentsubblock + svs[*svs_index].hvtx_ids.size())){
		return -1;
	}

	// get the last hvtx_id of that svs entry (pointed to by the founding father)
	vertexid_t hvtx_id = svs[*svs_index].hvtx_ids.back(); //***
	return hvtx_id;
}

int sv_pick_edge(
			unsigned int xvtx_id,
			unsigned int offset,
			edge_tt * edgett,
			unsigned int * numclusteredworkblocks,
			vector<edge_nt> & edge_block_array
			){
	// edge_tt eedge;
	unsigned int work_block_height = WORK_BLOCK_HEIGHT;
	unsigned int work_blocks_per_page = WORK_BLOCKS_PER_PAGE;
	*numclusteredworkblocks = 0;
	
	for(int addr=offset; addr<(offset+work_blocks_per_page); addr++){
		if(addr >= edge_block_array.size()){ cout<<"bug! : addr out-of-range6 (supervs) "<<endl; }
		if(edge_block_array[addr].clusterinfo.flag == VALID){ *numclusteredworkblocks += 1; }
		for(unsigned int f=0;f<work_block_height;f++){
			if(f >= work_block_height){ cout<<"bug! : addr out-of-range7 (supervs) "<<endl; }
			if(edge_block_array[addr].edges[f].flag == VALID){	
				*edgett = edge_block_array[addr].edges[f];	// edge picked
				
				edge_block_array[addr].edges[f].flag = DELETED; // mark location as deleted		
				return 1;
			}	
		}
	}
	// if it reaches here, then the edgeblock is emptied
	return -1;
}

