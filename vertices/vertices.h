#ifndef VERTICES_H
#define VERTICES_H

#include <iostream>
#include <vector>
#include "../common/common.h"
using namespace std;

class vertices{
  public:
	vertices();
	~vertices();
	
	unsigned int num_vertices;
	
	void init(unsigned int _num_vertices); // very important!
	
	vector<vertexproperty_t> vertex_properties;
	vector<vertexproperty_t> high_degree_vertices;
	vector<id_t> high_degree_vertices_ids;
	
	vertexdata_t readdata(vertexid_t vertexid);	
	void writedata(vertexid_t vertexid, vertexdata_t vertexdata);
	vertexproperty_t readproperty(vertexid_t vertexid);
	void writeproperty(vertexid_t vertexid, vertexproperty_t vertexproperty);
	void update_vertex_property(edge_t edge, unsigned int edgeupdatecmd);
	void initialize();
	void print_first_n(unsigned int n);
	void print_nth_vertex(unsigned int n);
	vector<vertexproperty_t> & get_vertex_properties();
	vector<vertexproperty_t> & get_high_degree_vertices(unsigned int percentage);
	vector<id_t> & get_high_degree_vertices_ids(unsigned int percentage);
	vertexproperty_t get_highest_outdegree_vertex();
	vertexproperty_t get_lowest_outdegree_vertex();
 private:
};

#endif