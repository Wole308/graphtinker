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

void vertices::init(unsigned int _num_vertices){
	num_vertices = _num_vertices;
	vertex_properties.resize(_num_vertices); 
	initialize();
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

void vertices::update_vertex_property(vertexid_t xvtx_id, vertexid_t xadjvtx_id, unsigned int edgeupdatecmd, unsigned int graphdirectiontype){
	if(edgeupdatecmd == INSERTEDGE){
		vertex_properties[xvtx_id].outdegree += 1;
		if(graphdirectiontype == UNDIRECTEDGRAPH){
			vertex_properties[xvtx_id].indegree += 1;
		}
		vertex_properties[xvtx_id].flag = VALID;
	} else if (edgeupdatecmd == DELETEEDGE){		
		vertex_properties[xvtx_id].outdegree -= 1;
		if(graphdirectiontype == UNDIRECTEDGRAPH){
			vertex_properties[xvtx_id].indegree -= 1;
		}
		vertex_properties[xvtx_id].flag = VALID;
	}  else { cout<<"bug! : should never be seen here (vprop_update)"<<endl; }
	return;
}

void vertices::initialize(){
	cout<<"initializing vertices (vertices) "<<endl;
	for(unsigned int i=0; i<num_vertices; i++){
		vertex_properties[i].data = 0.15; //** change later (this is for PR) 
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

vector<id_t> & vertices::get_high_degree_vertexids(unsigned int percentage){
	vertexproperty_t highest_degree = get_highest_outdegree_vertex();
	vertexproperty_t lowest_degree = get_lowest_outdegree_vertex();
	
	unsigned int count = (percentage * (highest_degree.outdegree - lowest_degree.outdegree)) / 100;
	unsigned int threshold = count; //highest_degree.outdegree - count;
	
	for(id_t i=0; i<num_vertices; i++){
		if(vertex_properties[i].outdegree >= threshold){
			high_degree_vertexids.push_back(i);
		}
	}
	return high_degree_vertexids; 
}

vector<id_t> & vertices::get_low_degree_vertexids(unsigned int percentage){
	vertexproperty_t highest_degree = get_highest_outdegree_vertex();
	vertexproperty_t lowest_degree = get_lowest_outdegree_vertex();
	
	unsigned int count = (percentage * (highest_degree.outdegree - lowest_degree.outdegree)) / 100;
	unsigned int threshold = count; //highest_degree.outdegree - count;
	
	for(id_t i=0; i<num_vertices; i++){
		if(vertex_properties[i].outdegree <= threshold){
			low_degree_vertexids.push_back(i);
		}
	}
	return low_degree_vertexids; 
}

vertexproperty_t vertices::get_highest_outdegree_vertex(){
	vertexproperty_t maxp;
	maxp.outdegree = 0;
	for(id_t i=0; i<num_vertices; i++){
		if(vertex_properties[i].outdegree > maxp.outdegree){ maxp = vertex_properties[i]; }
	}
	return maxp;
}

vertexproperty_t vertices::get_lowest_outdegree_vertex(){
	vertexproperty_t minp;
	minp.outdegree = INFINITI;
	cout<<"vertex_properties[0].outdegree : "<<vertex_properties[0].outdegree<<endl;
	for(id_t i=0; i<num_vertices; i++){
		if(vertex_properties[i].outdegree < minp.outdegree){ minp = vertex_properties[i]; }
	}
	return minp;
}

unsigned int * vertices::classify_vertexids(unsigned int threshold){
	unsigned int * vertexids_and_degreeclasses = new unsigned int[num_vertices];
	unsigned int hd = 0;
	unsigned int ld = 0;
	
	for(id_t i=0; i<num_vertices; i++){
		if(vertex_properties[i].outdegree >= threshold){
			hd += 1;
			vertexids_and_degreeclasses[i] = HIGH_DEGREE_VERTEX;
		} else {
			ld += 1;
			vertexids_and_degreeclasses[i] = LOW_DEGREE_VERTEX;
		}
	}
	cout<<"number of low-degree vertices : "<<ld<<", number of high-degree vertices : "<<hd<<endl;
	return vertexids_and_degreeclasses;
}

unsigned int * vertices::classify_vertexids2(unsigned int percentage){
	unsigned int * vertexids_and_degreeclasses = new unsigned int[num_vertices];
	vertexproperty_t highest_degree = get_highest_outdegree_vertex();
	vertexproperty_t lowest_degree = get_lowest_outdegree_vertex();
	
	unsigned int count = (percentage * (highest_degree.outdegree - lowest_degree.outdegree)) / 100;
	unsigned int threshold = highest_degree.outdegree - count;
	
	for(id_t i=0; i<num_vertices; i++){
		if(vertex_properties[i].outdegree >= threshold){ 
			vertexids_and_degreeclasses[i] = HIGH_DEGREE_VERTEX;
		} else {
			vertexids_and_degreeclasses[i] = LOW_DEGREE_VERTEX;
		}
	}
	return vertexids_and_degreeclasses;
}

unsigned int vertices::get_num_vertices(){
	return num_vertices;
}