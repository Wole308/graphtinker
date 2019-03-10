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
	
	vector<vertexproperty_t> vertex_properties;
	
	vertexdata_t readdata(vertexid_t vertexid);
	vertexproperty_t readproperty(vertexid_t vertexid);
	void writedata(vertexid_t vertexid, vertexdata_t vertexdata);
	void update_vertex_property(edge_t edge, unsigned int edgeupdatecmd);
	void initialize();
	void print_first_n(unsigned int N);
 private:
};

#endif