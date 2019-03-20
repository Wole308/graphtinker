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
	vector<id_t> high_degree_vertexids;
	vector<id_t> low_degree_vertexids;
	
	vertexdata_t readdata(vertexid_t vertexid);	
	void writedata(vertexid_t vertexid, vertexdata_t vertexdata);
	vertexproperty_t readproperty(vertexid_t vertexid);
	void writeproperty(vertexid_t vertexid, vertexproperty_t vertexproperty);
	void update_vertex_property(vertexid_t xvtx_id, vertexid_t xadjvtx_id, unsigned int edgeupdatecmd, unsigned int graphdirectiontype);
	void initialize();
	void print_first_n(unsigned int n);
	void print_nth_vertex(unsigned int n);
	vector<vertexproperty_t> & get_vertex_properties();
	vector<id_t> & get_high_degree_vertexids(unsigned int percentage);
	vector<id_t> & get_low_degree_vertexids(unsigned int percentage);
	vertexproperty_t get_highest_outdegree_vertex();
	vertexproperty_t get_lowest_outdegree_vertex();
	unsigned int * classify_vertexids(unsigned int threshold);
	unsigned int * classify_vertexids2(unsigned int percentage);
	unsigned int get_num_vertices();
 private:
};

#endif