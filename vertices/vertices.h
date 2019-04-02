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
	
	void initialize(unsigned int _num_vertices, float initvalue); // very important!
	
	vector<vertexproperty_t> vertex_properties;
	
	vertexdata_t readdata(vertexid_t vertexid);	
	void writedata(vertexid_t vertexid, vertexdata_t vertexdata);
	vertexproperty_t readproperty(vertexid_t vertexid);
	void writeproperty(vertexid_t vertexid, vertexproperty_t vertexproperty);
	void update_vertex_property(vertexid_t xvtx_id, vertexid_t xadjvtx_id, unsigned int edgeupdatecmd, unsigned int graphdirectiontype);
	void initialize(float initvalue);
	void print_first_n(unsigned int n);
	void print_nth_vertex(unsigned int n);
	vector<vertexproperty_t> & get_vertex_properties();
	unsigned int get_num_vertices();
 private:
};

#endif