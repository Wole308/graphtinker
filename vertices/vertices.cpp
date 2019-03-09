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
#include "vertices.h" // Courtesy : Jinja 2.0
using namespace std;

vertices::vertices(){ 
	cout<<"vertices constructor called (vertices)"<<endl;
	vertex_properties.resize(EDGEBLOCKARRAYHEIGHT); 
	initialize(); 
}
vertices::~vertices(){
		
}

vertexdata_t vertices::readdata(vertexid_t vertexid){
	return vertex_properties[vertexid].data;
}

vertexproperty_t vertices::readproperty(vertexid_t vertexid){
	return vertex_properties[vertexid];
}

void vertices::writedata(vertexid_t vertexid, vertexdata_t vertexdata){
	vertex_properties[vertexid].data = vertexdata;
	return;
}

void vertices::update_vertex_property(edge_t edge, unsigned int edgeupdatecmd){
	if(edgeupdatecmd == INSERTEDGE){
		vertex_properties[edge.xvtx_id].outdegree += 1;
		vertex_properties[edge.xvtx_id].indegree += 1;
	} else if (edgeupdatecmd == DELETEEDGE){		
		vertex_properties[edge.xvtx_id].outdegree -= 1;
		vertex_properties[edge.xvtx_id].indegree -= 1;
	}  else { cout<<"bug! : should never be seen here (vprop_update)"<<endl; }
	return;
}

void vertices::initialize(){
	cout<<"initializing vertices (vertices) "<<endl;
	for(unsigned int i=0; i<EDGEBLOCKARRAYHEIGHT; i++){
		vertex_properties[i].data = 0.15; //** change later (this is for PR) 
		vertex_properties[i].indegree = 0;
		vertex_properties[i].outdegree = 0;
		vertex_properties[i].flag = INVALID;
	}
	return;
}


