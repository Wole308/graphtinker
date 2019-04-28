#include <string.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <functional>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <cmath>
#include <omp.h>
#include "translator.h"
using namespace std;

translator::translator(vertexid_t _vertex_range){
	initialize(vertex_range);
}
translator::translator(){}
translator::~translator(){}

void translator::initialize(vertexid_t _vertex_range){
	vertex_range = _vertex_range;
	vertex_translator = new vertex_translator_t[vertex_range];		
	for(unsigned int i=0; i<vertex_range; i++){
		vertex_translator[i].globalvid = 0;
		vertex_translator[i].localvid = 0;
		vertex_translator[i].flag = INVALID;
		vertex_translator[i].lflag = INVALID;
	}
	translator_tracker.mark = 0;
	return;
}

vertexid_t translator::get_localvid2(vertexid_t globalvid){
	if((globalvid > vertex_range) || (vertex_translator[globalvid].flag != VALID)){ cout<<"translator::get_localvid : bug. out of range6^^^^. globalvid : "<<globalvid<<", vertex_range : "<<vertex_range<<endl; } 
	return vertex_translator[globalvid].localvid;
}

vertexid_t translator::get_localvid(vertexid_t globalvid){
	if(globalvid > vertex_range){ cout<<"translator::get_localvid : bug, out of range5. globalvid : "<<globalvid<<", vertex_range : "<<vertex_range<<endl; }
	if(translator_tracker.mark > vertex_range){ cout<<"translator::get_localvid : bug, out of range6. globalvid : "<<globalvid<<", vertex_range : "<<vertex_range<<endl; }
	if(vertex_translator[globalvid].flag != VALID){
		vertex_translator[translator_tracker.mark].globalvid = globalvid;
		vertex_translator[translator_tracker.mark].lflag = VALID;		
		vertex_translator[globalvid].localvid = translator_tracker.mark;
		vertex_translator[globalvid].flag = VALID;
		translator_tracker.mark += 1;
	}
	return vertex_translator[globalvid].localvid;
}

vertexid_t translator::get_globalvid(vertexid_t localvid){
	if(localvid > vertex_range){ cout<<"translator::get_globalvid : bug. out of range7 (localvid > vertex_range). localvid : "<<localvid<<", vertex_range : "<<vertex_range<<endl; } 
	/// if(vertex_translator[localvid].lflag != VALID){ cout<<"translator::get_globalvid : bug. out of range8 (lflag != VALID). localvid : "<<localvid<<", vertex_range : "<<vertex_range<<", vertex_translator["<<localvid<<"].globalvid : "<<vertex_translator[localvid].globalvid<<endl; } 
	return vertex_translator[localvid].globalvid;
}

vertexid_t translator::read_globalvid(vertexid_t localvid){
	if(localvid > vertex_range){ cout<<"translator::read_globalvid : bug, out of range. localvid : "<<localvid<<", vertex_range : "<<vertex_range<<endl; }
	return vertex_translator[localvid].globalvid;
}

void translator::print_first_n_items_of_vertex_translator(unsigned int n){
	cout<<"translator::print_first_n_items_of_vertex_translator : n : "<<n<<endl;
	for(unsigned int i=0; i<n; i++){
		cout<<i<<": [";
		cout<<vertex_translator[i].globalvid;
		cout<<", "<<vertex_translator[i].localvid;
		cout<<", "<<vertex_translator[i].flag;
		cout<<", "<<vertex_translator[i].lflag;
		cout<<"]"<<endl;
	}
	return;
}

unsigned int translator::get_translator_tracker_mark(){
	return translator_tracker.mark;
}

vertex_translator_t * translator::gettranslator(){
	return vertex_translator;
}

tracker_t translator::gettranslatortracker(){
	return translator_tracker;
}

void translator::settranslatortracker(tracker_t tracker){
	translator_tracker = tracker;
}

void translator::deleteme(){
	delete[] vertex_translator;
	translator_tracker.mark = 0;
}
