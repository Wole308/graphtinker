#include <string.h>
#include <iostream>
#include <string>
#include "graphtinker.h"
using namespace std;

void graphtinker::initallmoduleunit(moduleunitcmd_t *moduleunitcmd, moduleparams_t *moduleparams, vertexid_t xadjvtx_id, edgeweight_t edge_weight){
	moduleunitcmd->mode=FINDONLYMODE;
	
	moduleparams->rolledover = NO;
	moduleparams->clustered = NO;
	moduleparams->cptr = -1;		
	moduleparams->xadjvtx_id = xadjvtx_id;
	moduleparams->edge_weight = edge_weight;
	return; 
}

void graphtinker::initialize_moduleunit_params(moduleparams_t *moduleparams, vertexid_t xadjvtx_id, edgeweight_t edge_weight){
	moduleparams->rolledover = NO;
	moduleparams->clustered = NO;
	moduleparams->cptr = -1;		
	moduleparams->xadjvtx_id = xadjvtx_id;
	moduleparams->edge_weight = edge_weight;
	return; 
}

/**
initializes module unit's:
- traversal info fields
- cluster info fields
- additional info fields
(does not initialize the edge fields)
*/
void graphtinker::initialize_moduleunit_params2(moduleparams_t *moduleparams){
	moduleparams->rolledover = NO;
	moduleparams->clustered = NO;
	moduleparams->cptr = -1;
	return; 
}

void graphtinker::initialize_loadunit(loadunitcmd_t *loadunitcmd){
	loadunitcmd->load = YES;
	return;
}

void graphtinker::initialize_insertunit(insertparams_t *insertparams, insertreport_t *insertreport, vertexid_t xadjvtx_id, bucket_t hadjvtx_id, edgeweight_t edge_weight){
	insertparams->xadjvtx_id = xadjvtx_id; 
	insertparams->initialbucket_x = hadjvtx_id;
	insertparams->edge_weight = edge_weight;
	
	insertreport->exittype = PASSEDTHROUGH;
	insertreport->validbuckets_incr = 0;
	insertreport->overflowbkt = FIRST;
	insertreport->lastbktloadedinto = NONE;
	return;
}

/**
initializes insert unit's:
- additional info fields
(does not initialize the edge fields)
*/
void graphtinker::initialize_insertunit2(insertparams_t *insertparams, insertreport_t *insertreport){
	insertparams->isstartblk = 0;
	
	insertreport->exittype = PASSEDTHROUGH;
	insertreport->validbuckets_incr = 0;
	insertreport->overflowbkt = FIRST;
	insertreport->lastbktloadedinto = NONE;
	return;
}

void graphtinker::initialize_findunit(findparams_t *findparams, findreport_t *findreport, vertexid_t xadjvtx_id, bucket_t hadjvtx_id, edgeweight_t edge_weight){
	findparams->xadjvtx_id = xadjvtx_id; // edge info
	findparams->initialbucket_x = hadjvtx_id;
	findparams->edge_weight = edge_weight;	
	findparams->isstartblk = 0;

	findreport->localoffset = NULLL; 
	findreport->entryfound = NO;
	findreport->entrydeleted = NO;
	findreport->maxprobelengthreached = NO; 
	findreport->foundemptybkt = NO;
	return;
}

/**
initializes find unit's:
- additional info fields
(does not initialize the edge fields)
*/
void graphtinker::initialize_findunit2(findparams_t *findparams, findreport_t *findreport){
	findparams->isstartblk = 0;

	findreport->localoffset = NULLL; 
	findreport->entryfound = NO;
	findreport->entrydeleted = NO;
	findreport->maxprobelengthreached = NO; 
	findreport->foundemptybkt = NO;
	return;
}

void graphtinker::initialize_writebackunit(writebackunitcmd_t *writebackunitcmd){
	writebackunitcmd->writeback = NO;
	writebackunitcmd->addr = 0;
	writebackunitcmd->markasclustered = NO;
	return;
}

void graphtinker::initialize_llebaverdictcmd(llgdsunitcmd_t *llgdsunitcmd){
	llgdsunitcmd->verdict = NOCMD;
	return;
}

#ifdef EN_LLGDS
void graphtinker::clear_lleba_addresses_in_moduleparams(moduleparams_t *moduleparams){
	moduleparams->ll_localbaseaddrptr_x = 0; // we don't know the value yet  --edge.LLlocalbaseaddrptr;
	moduleparams->ll_localaddrptr_x = 0; // we don't know the value yet  --edge.LLlocaladdrptr;
	return;
}
#endif

void graphtinker::init_deleteandcrumplein_verdictcmd(deleteandcrumpleincmd_t *heba_deleteandcrumplein_cmd){
	heba_deleteandcrumplein_cmd->verdict = DCI_NOCMD;
	return;
}

