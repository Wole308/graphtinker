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

unsigned int get_edgeblock_offset(vertexid_t vid){
    unsigned int offset4rmbase = vid  * WORK_BLOCKS_PER_PAGE; 
	return offset4rmbase;
}