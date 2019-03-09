#include <string.h>
#include <iostream>
#include <string>
#include "graphtinker.h"
using namespace std;

void load_params(
				moduleparams_t moduleparams,				
				insertparams_t *insertparams,		
				findparams_t *findparams,				
				margin_t wblkmargin, 
				bucket_t hadjvtx_id
				){	
    if(hadjvtx_id>=wblkmargin.top && moduleparams.rolledover==NO){ insertparams->isstartblk=1; findparams->isstartblk=1; } 
    else { insertparams->isstartblk=0; findparams->isstartblk=0; }
	return;
}