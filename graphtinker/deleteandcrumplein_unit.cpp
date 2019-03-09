#include <string.h>
#include <stdio.h>
#include <iostream>
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
#include "graphtinker.h"
using namespace std;

void deleteandcrumplein_unit(
			writebackunitcmd_t writebackunitcmd,
			findreport_t findreport,
			edge_t edge,
			vector<edge_nt> & edge_block_array,
			#ifdef EN_LLGDS
			ll_edgeblock_t * ll_edge_block_array,
			#endif
			vector<edgeblock_parentinfo_t> & edgeblock_parentinfo,
			vertexid_t xvtx_id,
			margin_t wblkmargin,
			margin_t subblkmargin,
			unsigned int geni
			,deleteandcrumpleincmd_t deleteandcrumpleincmd
			,vector<supervertex_t> & svs
			,vector<vertexid_t> & freed_edgeblock_list
			){
	unsigned int work_blocks_per_subblock = WORK_BLOCKS_PER_SUBBLOCK;	
	unsigned int work_blocks_per_page = WORK_BLOCKS_PER_PAGE;
		
	// only when an edge is removed from a clustered region do we have to pop-out and pop-back-in
	if(deleteandcrumpleincmd.verdict == DCI_CRUMPLEINCMD){
		// deletion successful
		#ifdef EN_OTHERS
		cout<<"dci (delete and crumple in) says : crumplein cmd (update_edge)"<<endl; 
		#endif
		
		int retstatus = -1;
		edge_tt edgett;
		vertexid_t ll_localbaseaddrptr = 0;
		vertexid_t ll_localaddrptr = 0;
		int tailhvtx_id = -1;
		unsigned int svs_index = 0;
		unsigned int numclusteredworkblocks = NULLL;
		
		retstatus = sv_get_next_edge(
						xvtx_id,
						svs,
						freed_edgeblock_list,
						&edgett,
						wblkmargin,
						writebackunitcmd,
						&tailhvtx_id,
						&svs_index,
						&numclusteredworkblocks,
						geni,
						edge_block_array
						);
						
		if(retstatus == 7){
			// retrieved tail edgeblock, and found a valid edge in it
			if(writebackunitcmd.addr >= edge_block_array.size()){ cout<<"bug! : addr out-of-range1 (update_edge) "<<endl; }
			if(findreport.localoffset >= WORK_BLOCK_HEIGHT){ cout<<"bug! : addr out-of-range2 (update_edge) "<<endl; }
			edge_block_array[writebackunitcmd.addr].edges[findreport.localoffset] = edgett;
			
			// redirect pointer (ll -> heba) (remember its a 2-way link)
			#ifdef EN_LLGDS
			unsigned int work_block_height = WORK_BLOCK_HEIGHT;					
			ll_edge_block_array[edgett.ll_localbaseaddrptr].ll_edgeblock[edgett.ll_localaddrptr].heba_hvtx_id = xvtx_id;
			ll_edge_block_array[edgett.ll_localbaseaddrptr].ll_edgeblock[edgett.ll_localaddrptr].heba_workblockid = wblkmargin.top / work_block_height;
			ll_edge_block_array[edgett.ll_localbaseaddrptr].ll_edgeblock[edgett.ll_localaddrptr].heba_loffset = findreport.localoffset;		
			#endif
			
		} else if (retstatus == 6) {
			// retrieved tail edgeblock, but could not find a valid edge in it
			
			// free what's needed to be free					
			if(tailhvtx_id > 0 && numclusteredworkblocks == 0){						
				
				// edgeblock is empty. free it //unsigned int 
				unsigned int offset = get_edgeblock_offset(tailhvtx_id);
				for(unsigned int addr=offset; addr<(offset+work_blocks_per_page); addr++){
					if(addr >= edge_block_array.size()){ cout<<"bug! : addr out-of-range3 (update_edge) "<<endl; }
					edge_block_array[addr].clusterinfo.flag = INVALID;
				}
				
				// detatch it from its father subblock
				unsigned int index = tailhvtx_id - EDGEBLOCKARRAYHEIGHT;
				if(index >= edgeblock_parentinfo.size()){ cout<<"bug! : addr out-of-range4 (update_edge) "<<endl; }
				if(edgeblock_parentinfo[index].flag != VALID){ cout<<"bug! : incorrect (update_edge66)"<<endl; }
				edgeblock_parentinfo_t parentinfo = edgeblock_parentinfo[index];
				unsigned int subblockbaseaddr = get_edgeblock_offset(tailhvtx_id) + (parentinfo.subblockid * work_blocks_per_subblock);
				for(unsigned int id=0;id<work_blocks_per_subblock;id++){
					edge_block_array[(subblockbaseaddr + id)].clusterinfo.flag = INVALID;
				}
				
				// update edgeblock_parentinfo
				if(index >= edgeblock_parentinfo.size()){ cout<<"bug! : addr out-of-range4 (update_edge) "<<endl; }
				edgeblock_parentinfo[index].flag = INVALID;
				
				// pop it out of svs
				if(svs_index >= svs.size()){ cout<<"bug! : addr out-of-range5 (update_edge) "<<endl; }
				if(svs[svs_index].hvtx_ids.back() != tailhvtx_id){ cout<<"bug! : incorrect (update_edge67)"<<endl; }
				if(!svs[svs_index].hvtx_ids.empty()){
					svs[svs_index].hvtx_ids.pop_back();
				}
				
				// add to free list
				freed_edgeblock_list.push_back(tailhvtx_id);
			}
			
		} else if (retstatus == 5) {
			// could not retrieve tail edgeblock
			
		} else { cout<<"bug! : should never get here2 (update_edge)"<<endl; }
		
	} else if (deleteandcrumpleincmd.verdict == DCI_JUSTQUITCMD){			
		#ifdef EN_OTHERS
		cout<<"dci (delete and crumple in) says : just quit cmd (update_edge)"<<endl; 
		#endif
	} else if (deleteandcrumpleincmd.verdict == DCI_NOCMD){
		#ifdef EN_OTHERS
		cout<<"dci (delete and crumple in) says : no cmd (update_edge)"<<endl; 
		#endif
	} else { cout<<"bug! : should never get here3 (update_edge)"<<endl; }
}