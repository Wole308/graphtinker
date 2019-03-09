#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "graphtinker.h"
using namespace std;

unsigned int getsvtracker(markertracker_t * svtracker){
	unsigned int ret = svtracker->marker;
	svtracker->marker++;
	return ret;
}

