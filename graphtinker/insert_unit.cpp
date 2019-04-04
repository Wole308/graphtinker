#include <string.h>
#include <iostream>
#include <string>
#include "graphtinker.h"
using namespace std;

unsigned int debug_totaledgeinsertions;

void graphtinker::insert_unit(
				moduleparams_t *moduleparams,
				insertparams_t *insertparams, 
				insertreport_t *insertreport,
				margin_t wblkmargin, 
				margin_t subblkmargin,
				bucket_t hadjvtx_id, 
				edge_nt * edgeblock,
				edge_t * edge,
				vertexid_t xvtx_id,
				unsigned int rolledover,
				unsigned int geni
				){			
	bucket_t localoffset;
	
	vertexid_t entry_i; 
	bucket_t initialbucket_i;
	edgeweight_t edgeweight_i;
    flag_t flag_i;
	#ifdef EN_LLGDS
	vertexid_t ll_localbaseaddrptr_i;
	vertexid_t ll_localaddrptr_i;
	#endif
	
	bucket_t currbkt;
	bucket_t beginbkt;
	
	bucket_t DIB_i;
	bucket_t DIB_x;	

	// if this isn't altered in the for-loop, then this would be the report
	insertreport->exittype = PASSEDTHROUGH;
	insertreport->validbuckets_incr = 0;
	insertreport->overflowbkt = FIRST;
	insertreport->lastbktloadedinto = NONE;

	// get begin bucket
	beginbkt = insertparams->isstartblk==1? hadjvtx_id : wblkmargin.top;

	// traverse entries in block 
	for (currbkt=beginbkt; currbkt<=wblkmargin.bottom; currbkt++){
		
		// get entry's local offset
		localoffset = currbkt - wblkmargin.top; 

		// retrieve current entry 
		entry_i = edgeblock->edges[localoffset].xadjvtx_id; 	
		initialbucket_i = edgeblock->edges[localoffset].initialbucket; 	  
		edgeweight_i = edgeblock->edges[localoffset].edge_weight;
        flag_i = edgeblock->edges[localoffset].flag;
		
		#ifdef EN_LLGDS
		ll_localbaseaddrptr_i = edgeblock->edges[localoffset].ll_localbaseaddrptr;
		ll_localaddrptr_i = edgeblock->edges[localoffset].ll_localaddrptr;
		#endif	

		if(entry_i == insertparams->xadjvtx_id){
			if(flag_i == VALID){
				// should not be
				cout<<"bug! should not be (insert_unit45)"<<endl;				
			} /* else if (flag_i == DELETED){
				// do nothing. moving on ...			
			} */ else {
				// empty bucket found, insert and exit <//*** NB: this is repeated below>	
				
				edgeblock->edges[localoffset].xadjvtx_id = insertparams->xadjvtx_id;
				edgeblock->edges[localoffset].initialbucket = insertparams->initialbucket_x;
				edgeblock->edges[localoffset].edge_weight = insertparams->edge_weight;
				edgeblock->edges[localoffset].flag = VALID;			
				#ifdef EN_LLGDS
				edgeblock->edges[localoffset].ll_localbaseaddrptr = moduleparams->ll_localbaseaddrptr_x;
				edgeblock->edges[localoffset].ll_localaddrptr = moduleparams->ll_localaddrptr_x;
				#endif
				
				#ifdef EN_LLGDS
				// one-time-assignments : if initial edge, track its location
				if(insertparams->xadjvtx_id == edge->xadjvtx_id){ 
					edge->heba_hvtx_id = xvtx_id;
					edge->heba_workblockid = wblkmargin.top / WORK_BLOCK_HEIGHT;
					edge->heba_loffset = localoffset;
					// edge->which_gen_is_the_main_copy_located = geni;
				}
				#endif
				
				debug_totaledgeinsertions+=1;

				// update insertreport
				insertreport->exittype = LOADEDINTOEMPTYBUCKET;
				insertreport->validbuckets_incr = 1;
				insertreport->overflowbkt = NONE; 
				insertreport->lastbktloadedinto = currbkt;
				return;	
			}
		} else {
			if(flag_i == VALID){				
				// do nothing. moving on ...							
			} /* else if (flag_i == DELETED){
				// do nothing. moving on ...			
			} */ else {				
				// empty bucket found, insert and exit	
				
				edgeblock->edges[localoffset].xadjvtx_id = insertparams->xadjvtx_id;
				edgeblock->edges[localoffset].initialbucket = insertparams->initialbucket_x;
				edgeblock->edges[localoffset].edge_weight = insertparams->edge_weight;
				edgeblock->edges[localoffset].flag = VALID;			
				#ifdef EN_LLGDS
				edgeblock->edges[localoffset].ll_localbaseaddrptr = moduleparams->ll_localbaseaddrptr_x;
				edgeblock->edges[localoffset].ll_localaddrptr = moduleparams->ll_localaddrptr_x;
				#endif
				
				#ifdef EN_LLGDS
				// one-time-assignments : if initial edge, track its location
				if(insertparams->xadjvtx_id == edge->xadjvtx_id){ 
					edge->heba_hvtx_id = xvtx_id;
					edge->heba_workblockid = wblkmargin.top / WORK_BLOCK_HEIGHT;
					edge->heba_loffset = localoffset;
					// edge->which_gen_is_the_main_copy_located = geni;
				}
				#endif
				
				debug_totaledgeinsertions+=1;

				// update insertreport
				insertreport->exittype = LOADEDINTOEMPTYBUCKET;
				insertreport->validbuckets_incr = 1;
				insertreport->overflowbkt = NONE; 
				insertreport->lastbktloadedinto = currbkt; 
				return;	
			}
		}
	}
	return;
}

bucket_t graphtinker::getdib(bucket_t currbkt, bucket_t initialbucket, margin_t subblkmargin, unsigned int rolledover){
	bucket_t DIB=0;
	bucket_t rightpad=0;
	bucket_t leftpad=0;
	unsigned int work_blocks_per_subblock = work_blocks_per_subblock;
	unsigned int work_block_height = WORK_BLOCK_HEIGHT;
	
	bucket_t diff = currbkt - initialbucket;
	if(diff>=0){
		// DIB = currbkt - initialbucket;
		if(rolledover == YES){
			DIB = (work_blocks_per_subblock * work_block_height) + (currbkt - initialbucket);
		} else {
			DIB = currbkt - initialbucket;
		}
	} else {
		rightpad = subblkmargin.bottom - initialbucket;
		leftpad = currbkt - subblkmargin.top;
		DIB = rightpad + leftpad;
	}	
	return DIB;
}