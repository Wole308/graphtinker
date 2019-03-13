#include <string.h>
#include <iostream>
#include <string>
#include "graphtinker.h"
using namespace std;

void graphtinker::compute_unit(
				moduleunitcmd_t moduleunitcmd,
				moduleparams_t * moduleparams,
				insertparams_t * insertparams, 
				insertreport_t * insertreport,		
				findparams_t findparams,
				findreport_t * findreport,				
				margin_t wblkmargin, 
				margin_t subblkmargin,
				margin_t start_wblkmargin,
				bucket_t hadjvtx_id, 
				edge_nt * edgeblock,
				edge_t * edge,
				vertexid_t xvtx_id,
				unsigned int rolledover,
				unsigned int edgeupdatecmd
				){	
	if(moduleunitcmd.mode == FINDONLYMODE){
	find_unit(
					moduleparams,
					findparams,
					findreport,								
					wblkmargin, 
					subblkmargin,
					hadjvtx_id, 
					edgeblock,
					edgeupdatecmd
					);
	} else if (moduleunitcmd.mode == INSERTONLYMODE) {
	insert_unit(
				moduleparams,
				insertparams,
				insertreport,
				wblkmargin,
				subblkmargin,
				hadjvtx_id,
				edgeblock,
				edge,
				xvtx_id,
				rolledover
				);
	} else { cout<<"bug! : should never get here (compute unit) : moduleunitcmd.mode = "<<moduleunitcmd.mode<<endl; }
	return;
}

