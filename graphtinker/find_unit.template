#include <string.h>
#include <iostream>
#include <string>
#include "graphtinker.h"
using namespace std;

unsigned int debug_totaledgealreadyfound;
		
void graphtinker::find_unit(
			moduleparams_t * moduleparams,
			findparams_t findparams,
			findreport_t * findreport,				
			margin_t wblkmargin, 
			margin_t subblkmargin,
			bucket_t hadjvtx_id, 
			edge_nt * edgeblock,
			unsigned int edgeupdatecmd){	
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
	findreport->localoffset = NULLL; // local offset from first bucket in the current workblock
	findreport->entryfound = NO;
	findreport->entrydeleted = NO;
	findreport->maxprobelengthreached = NO; 
    findreport->foundemptybkt = NO;
	
	// get begin bucket
	beginbkt = findparams.isstartblk==1? hadjvtx_id : wblkmargin.top;
	
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

		if(entry_i == findparams.xadjvtx_id){
			if(flag_i == VALID){		
				// found edge!				
				debug_totaledgealreadyfound+=1;
					 
				findreport->localoffset = localoffset;
				findreport->entryfound = YES;
				
				if(edgeupdatecmd == INSERTEDGE){
					edgeblock->edges[localoffset].edge_weight+=1; // update it!
				} 
				#ifdef EN_CRUMPLEINONDELETE				
				else if (edgeupdatecmd == DELETEEDGE){
					edgeblock->edges[localoffset].flag = DELETED; // remove it!
				} 
				#else
				else if (edgeupdatecmd == DELETEEDGE){
					edgeblock->edges[localoffset].flag = DELETED; // remove it!
				}
				#endif
				else { cout<<"bug! : should never be seen here (find_unit56)"<<endl; }
			
				#ifdef EN_LLGDS
				moduleparams->ll_localbaseaddrptr_x = ll_localbaseaddrptr_i;
				moduleparams->ll_localaddrptr_x = ll_localaddrptr_i;
				#endif
				return;
			} else if (flag_i == DELETED){
				// continue searching...				
			} else {
				// cout<<"something fishy if this is seen too much (find_unit5)"<<endl;
				// empty bucket found, stop search
				findreport->foundemptybkt = YES; return; 
			}
		} else {
			if(flag_i == VALID){
				// continue searching...				
			} else if (flag_i == DELETED){
				// continue searching...			
			} else {
				 
				findreport->foundemptybkt = YES; return; 
			}			
		}
	}
	// not found. to be continued in next block
	return;
}