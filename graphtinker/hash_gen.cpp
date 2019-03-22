#include <string.h>
#include "graphtinker.h"

#define KMULTFACTOR 1

bucket_t graphtinker::googlehash(vertexid_t vid, unsigned int geni){
	bucket_t hashval=0;
	bucket_t exthashval=0;	
	unsigned int page_blockheight = page_block_height;
	
	// get extended edgeblock range
	unsigned int ext_edgeblock_range = page_blockheight + (KMULTFACTOR * (geni-1));
	
	// do basicHash on extended edgeblock range
	exthashval = vid % ext_edgeblock_range;    
	
	// now hash to edgeblock range 
	hashval = exthashval % page_blockheight;
    return hashval;
}