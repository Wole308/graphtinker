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
	cout<<"vertices::vertices : vertices constructor called"<<endl;
	vertex_properties.resize(EDGEBLOCKARRAYHEIGHT); 
	initialize(); 
}
vertices::~vertices(){}

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
		#ifdef UNDIRECTEDGRAPH
		vertex_properties[edge.xvtx_id].indegree += 1;
		#endif
		vertex_properties[edge.xvtx_id].flag = VALID;
	} else if (edgeupdatecmd == DELETEEDGE){		
		vertex_properties[edge.xvtx_id].outdegree -= 1;
		#ifdef UNDIRECTEDGRAPH
		vertex_properties[edge.xvtx_id].indegree -= 1;
		#endif
		vertex_properties[edge.xvtx_id].flag = VALID;
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

void vertices::print_first_n(unsigned int N){
	for(unsigned int i=0; i<N; i++){
		cout<<"vertexid : "<<i<<" ";
		cout<<"data : "<<vertex_properties[i].data<<" ";
		cout<<"indegree : "<<vertex_properties[i].indegree<<" ";
		cout<<"outdegree : "<<vertex_properties[i].outdegree<<" ";
		cout<<"flag : "<<vertex_properties[i].flag<<" ";
		cout<<endl;
	}
	return;
}


