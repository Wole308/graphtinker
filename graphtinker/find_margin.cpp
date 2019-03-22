#include <string.h>
#include <iostream>
#include <string>
#include "graphtinker.h"
using namespace std;

void graphtinker::findwblkmargin(margin_t *blkmargin, bucket_t hadjvtx_id){
    bucket_t a;
    bucket_t ttop;
    
    a = hadjvtx_id/WORK_BLOCK_HEIGHT;
    ttop = a * WORK_BLOCK_HEIGHT; 
    
    blkmargin->top = ttop;
    blkmargin->bottom = ttop + (WORK_BLOCK_HEIGHT-1);
	return;
}

void graphtinker::findsubblkmargin(margin_t *subblkmargin, bucket_t hadjvtx_id){
    bucket_t a;
    bucket_t ttop;
    
    a = hadjvtx_id/sub_block_height;
    ttop = a * sub_block_height;
    
    subblkmargin->top = ttop;
    subblkmargin->bottom = ttop + (sub_block_height-1);	
	return;
}

unsigned int graphtinker::findsubblkId(vertexid_t vid){
	unsigned int a = vid % page_block_height;
	unsigned int subblockid = a / sub_block_height;
	return subblockid;	
}



