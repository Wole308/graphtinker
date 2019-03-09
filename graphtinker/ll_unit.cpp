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

void ll_unit(
		llgdsunitcmd_t llgdsunitcmd,
		moduleparams_t * moduleparams,
		insertparams_t * insertparams,
		edge_t edge,
		vector<edge_nt> & edge_block_array
		#ifdef EN_LLGDS
		,ll_edgeblock_t * ll_edge_block_array
		,ll_logicalvertexentity_t * ll_lva
		,ll_eba_tracker_t * ll_eba_tracker
		#endif
		){
	// if searchstopped and unsuccessful
	// append to LL, add {lastlocalbaseaddr, lastlocaladdr} to edge 
	// off we go to insert unit !
	// NB: this unit should be before interval unit***
	#ifdef EN_LLGDS
	if(llgdsunitcmd.verdict == INSERTCMD){
		ll_insert(
			edge,
			moduleparams,
			insertparams,
			ll_edge_block_array,
			ll_lva,		
			ll_eba_tracker
			);
	} else if (llgdsunitcmd.verdict == UPDATECMD){
		ll_update(
			edge,
			moduleparams->ll_localbaseaddrptr_x,
			moduleparams->ll_localaddrptr_x,
			ll_edge_block_array
			);
	} else if (llgdsunitcmd.verdict == DELETECMD){
		ll_delete(
			edge,
			moduleparams->ll_localbaseaddrptr_x,
			moduleparams->ll_localaddrptr_x,
			ll_edge_block_array
			);
	} else if (llgdsunitcmd.verdict == DELETEANDCRUMPLEINCMD){
		ll_deleteandcrumplein(
			edge,
			moduleparams->ll_localbaseaddrptr_x,
			moduleparams->ll_localaddrptr_x,
			ll_edge_block_array,
			ll_lva,		
			ll_eba_tracker,
			edge_block_array
			);
	} else if (llgdsunitcmd.verdict == UPDATEEDGEPTRSCMD){
		ll_updateedgeptrs(
			edge,
			*moduleparams,
			ll_edge_block_array
			);
	} else if (llgdsunitcmd.verdict == NOCMD){
		// do nothing
	} else { 
		cout<<"bug! : should never get here (update_edge45)"<<endl;
	}
	#endif
}