#include <string.h>
#include <iostream>
#include <string>
#include "graphtinker.h"
using namespace std;

void findwblkmargin(margin_t *blkmargin, bucket_t hadjvtx_id){
    bucket_t a;
    bucket_t ttop;
    
    a = hadjvtx_id/WORK_BLOCK_HEIGHT;
    ttop = a * WORK_BLOCK_HEIGHT; 
    
    blkmargin->top = ttop;
    blkmargin->bottom = ttop + (WORK_BLOCK_HEIGHT-1);
	return;
}

void findsubblkmargin(margin_t *subblkmargin, bucket_t hadjvtx_id){
    bucket_t a;
    bucket_t ttop;
    
    a = hadjvtx_id/SUB_BLOCK_HEIGHT;
    ttop = a * SUB_BLOCK_HEIGHT;
    
    subblkmargin->top = ttop;
    subblkmargin->bottom = ttop + (SUB_BLOCK_HEIGHT-1);	
	return;
}

unsigned int findsubblkId(vertexid_t vid){
	unsigned int a = vid % PAGE_BLOCKHEIGHT;
	unsigned int subblockid = a / SUB_BLOCK_HEIGHT;
	return subblockid;	
}



