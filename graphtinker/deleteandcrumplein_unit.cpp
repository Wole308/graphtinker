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

/// this function is only used when when an edge is removed from a *clustered region*
void graphtinker::deleteandcrumplein_unit(
			writebackunitcmd_t writebackunitcmd,
			findreport_t findreport,
			edge_t edge,
			vector<edge_nt> & edge_block_array_m,
			vector<edge_nt> & edge_block_array_c,
			#ifdef EN_LLGDS
			vector<ll_edgeblock_t> & ll_edge_block_array,
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
	unsigned int work_blocks_per_subblock = work_blocks_per_subblock;	
	unsigned int work_blocks_per_page = work_blocks_per_page;
		
	/// only when an edge is removed from a *clustered region* do we have to pop-out and pop-back-in
	if(deleteandcrumpleincmd.verdict == DCI_CRUMPLEINCMD){
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
						edge_block_array_m,
						edge_block_array_c
						);
						
		if(retstatus == 7){
			// retrieved tail edgeblock, and found a valid edge in it			
			if(geni == 1){
				if(writebackunitcmd.addr >= edge_block_array_m.size()){ cout<<"bug! : addr out-of-range1 (update_edge) "<<endl; }
				if(findreport.localoffset >= WORK_BLOCK_HEIGHT){ cout<<"bug! : addr out-of-range2 (update_edge) "<<endl; }
				edge_block_array_m[writebackunitcmd.addr].edges[findreport.localoffset] = edgett;
			} else {
				if(writebackunitcmd.addr >= edge_block_array_c.size()){ cout<<"bug! : addr out-of-range1 (update_edge) "<<endl; }
				if(findreport.localoffset >= WORK_BLOCK_HEIGHT){ cout<<"bug! : addr out-of-range2 (update_edge) "<<endl; }
				edge_block_array_c[writebackunitcmd.addr].edges[findreport.localoffset] = edgett;
			}
			
			// redirect pointer (ll -> heba) (remember its a 2-way link)
			// remember that ll may need to update which edgeblockarray (m or c) it's now pointing to!
			#ifdef EN_LLGDS
			unsigned int work_block_height = WORK_BLOCK_HEIGHT;			
			ll_edge_block_array[edgett.ll_localbaseaddrptr].ll_edgeblock[edgett.ll_localaddrptr].heba_hvtx_id = xvtx_id;
			ll_edge_block_array[edgett.ll_localbaseaddrptr].ll_edgeblock[edgett.ll_localaddrptr].heba_workblockid = wblkmargin.top / work_block_height;
			ll_edge_block_array[edgett.ll_localbaseaddrptr].ll_edgeblock[edgett.ll_localaddrptr].heba_loffset = findreport.localoffset;
			ll_edge_block_array[edgett.ll_localbaseaddrptr].ll_edgeblock[edgett.ll_localaddrptr].which_gen_is_the_main_copy_located = geni;
			#endif
			
		} else if (retstatus == 6) {
			// retrieved tail edgeblock, but could not find a valid edge in it			
			// free what needs to be free					
			if(tailhvtx_id > 0 && numclusteredworkblocks == 0){						
				
				// edgeblock is empty. free it. edge_block_array_c is always used because tailhvtx_id can never be in edge_block_array_m
				unsigned int offset = get_edgeblock_offset(tailhvtx_id);
				for(unsigned int addr=offset; addr<(offset+work_blocks_per_page); addr++){
					if(addr >= edge_block_array_c.size()){ cout<<"bug! : addr out-of-range3 (update_edge) "<<endl; }
					edge_block_array_c[addr].clusterinfo.flag = INVALID;
				}
				
				// detatch it from its father subblock
				unsigned int index = tailhvtx_id;
				if(index >= edgeblock_parentinfo.size()){ cout<<"bug! : addr out-of-range4 (update_edge) "<<endl; }
				if(edgeblock_parentinfo[index].flag != VALID){ cout<<"bug! : incorrect (update_edge66)"<<endl; }
				edgeblock_parentinfo_t parentinfo = edgeblock_parentinfo[index];
				unsigned int subblockbaseaddr = get_edgeblock_offset(parentinfo.xvtx_id) + (parentinfo.subblockid * work_blocks_per_subblock);
				if(parentinfo.gen_of_parent == 1){
					for(unsigned int id=0; id<work_blocks_per_subblock; id++){
						edge_block_array_m[(subblockbaseaddr + id)].clusterinfo.flag = INVALID;
					}
				} else {
					for(unsigned int id=0; id<work_blocks_per_subblock; id++){
						edge_block_array_c[(subblockbaseaddr + id)].clusterinfo.flag = INVALID;
					}
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
		
	} 
	else if (deleteandcrumpleincmd.verdict == DCI_JUSTQUITCMD){ } 
	else if (deleteandcrumpleincmd.verdict == DCI_NOCMD){ } 
	else { cout<<"bug! : should never get here3 (update_edge)"<<endl; }
}