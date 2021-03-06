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
}
vertices::~vertices(){}

void vertices::initialize(unsigned int _num_vertices, float initvalue){
	num_vertices = _num_vertices;
	vertex_properties.resize(_num_vertices); 
	initialize(initvalue);
}

vertexdata_t vertices::readdata(vertexid_t vertexid){
	if(vertexid >= num_vertices){ cout<<"vertices::readdata : out of range4. vertexid : "<<vertexid<<", num_vertices : "<<num_vertices<<endl; }
	return vertex_properties[vertexid].data;
}

void vertices::writedata(vertexid_t vertexid, vertexdata_t vertexdata){
	if(vertexid >= num_vertices){ cout<<"vertices::writedata : out of range5. vertexid : "<<vertexid<<", num_vertices : "<<num_vertices<<endl; }
	vertex_properties[vertexid].data = vertexdata;
	return;
}

vertexproperty_t vertices::readproperty(vertexid_t vertexid){
	if(vertexid >= num_vertices){ cout<<"vertices::readproperty : out of range6. vertexid : "<<vertexid<<", num_vertices : "<<num_vertices<<endl; }
	return vertex_properties[vertexid];
}

void vertices::writeproperty(vertexid_t vertexid, vertexproperty_t vertexproperty){
	if(vertexid >= num_vertices){ cout<<"vertices::writeproperty : out of range7. vertexid : "<<vertexid<<", num_vertices : "<<num_vertices<<endl; }
	vertex_properties[vertexid] = vertexproperty;
	return;
}

void vertices::increment_outdegree(vertexid_t vertexid){
	if(vertexid >= num_vertices){ cout<<"vertices::increment_outdegree : out of range5. vertexid : "<<vertexid<<", num_vertices : "<<num_vertices<<endl; }
	vertex_properties[vertexid].outdegree +=1;
	return;
}

void vertices::update_vertex_property(vertexid_t xvtx_id, vertexid_t xadjvtx_id, unsigned int edgeupdatecmd, unsigned int graphdirectiontype){
	if(edgeupdatecmd == INSERTEDGE){
		if(graphdirectiontype == DIRECTEDGRAPH){
			if(xvtx_id < num_vertices){ vertex_properties[xvtx_id].outdegree += 1; }
			if(xadjvtx_id < num_vertices){ vertex_properties[xadjvtx_id].indegree += 1; }
		} else if (graphdirectiontype == UNDIRECTEDGRAPH){
			if(xvtx_id < num_vertices){ vertex_properties[xvtx_id].outdegree += 1; }
			if(xvtx_id < num_vertices){ vertex_properties[xvtx_id].indegree += 1; }
			if(xadjvtx_id < num_vertices){ vertex_properties[xadjvtx_id].outdegree += 1; }
			if(xadjvtx_id < num_vertices){ vertex_properties[xadjvtx_id].indegree += 1; }
		} else if(graphdirectiontype == REVERSE_DIRECTED_GRAPH){
			if(xvtx_id < num_vertices){ vertex_properties[xvtx_id].indegree += 1; }
			if(xadjvtx_id < num_vertices){ vertex_properties[xadjvtx_id].outdegree += 1; }
		} else { cout<<"vertices::update_vertex_property : error1"<<endl; }
	} else if (edgeupdatecmd == DELETEEDGE){
		if(graphdirectiontype == DIRECTEDGRAPH){
			if(xvtx_id < num_vertices){ vertex_properties[xvtx_id].outdegree -= 1; }
			if(xadjvtx_id < num_vertices){ vertex_properties[xadjvtx_id].indegree -= 1; }
		} else if (graphdirectiontype == UNDIRECTEDGRAPH){
			if(xvtx_id < num_vertices){ vertex_properties[xvtx_id].outdegree -= 1; }
			if(xvtx_id < num_vertices){ vertex_properties[xvtx_id].indegree -= 1; }
			if(xadjvtx_id < num_vertices){ vertex_properties[xadjvtx_id].outdegree -= 1; }
			if(xadjvtx_id < num_vertices){ vertex_properties[xadjvtx_id].indegree -= 1; }
		} else if(graphdirectiontype == REVERSE_DIRECTED_GRAPH){
			if(xvtx_id < num_vertices){ vertex_properties[xvtx_id].indegree -= 1; }
			if(xadjvtx_id < num_vertices){ vertex_properties[xadjvtx_id].outdegree -= 1; }
		} else { cout<<"vertices::update_vertex_property : error2"<<endl; }
	}
	return;
}

void vertices::initialize(float initvalue){
	cout<<"initializing vertices (vertices) "<<endl;
	for(unsigned int i=0; i<num_vertices; i++){
		vertex_properties[i].data = initvalue;
		vertex_properties[i].indegree = 0;
		vertex_properties[i].outdegree = 0;
		vertex_properties[i].flag = INVALID;
	}
	return;
}

void vertices::print_first_n(unsigned int n){
	for(unsigned int i=0; i<n; i++){
		cout<<"vertexid : "<<i<<" ";
		cout<<"data : "<<vertex_properties[i].data<<" ";
		cout<<"indegree : "<<vertex_properties[i].indegree<<" ";
		cout<<"outdegree : "<<vertex_properties[i].outdegree<<" ";
		cout<<"flag : "<<vertex_properties[i].flag<<" ";
		cout<<endl;
	}
	return;
}

void vertices::print_nth_vertex(unsigned int n){
	cout<<"vertexid : "<<n<<" ";
	cout<<"data : "<<vertex_properties[n].data<<" ";
	cout<<"indegree : "<<vertex_properties[n].indegree<<" ";
	cout<<"outdegree : "<<vertex_properties[n].outdegree<<" ";
	cout<<"flag : "<<vertex_properties[n].flag<<" ";
	cout<<endl;
	return;
}

vector<vertexproperty_t> & vertices::get_vertex_properties(){
	return vertex_properties;
}

unsigned int vertices::get_num_vertices(){
	return num_vertices;
}
