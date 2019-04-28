#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include "../../graphtinker/common/common.h"

class translator
{
	public:
		translator(vertexid_t _vertex_range);
		translator();
		~translator();
		
		vertexid_t vertex_range;
		vertex_translator_t * vertex_translator;
		tracker_t translator_tracker;
		
		void initialize(vertexid_t _vertex_range);		
		vertexid_t get_localvid(vertexid_t globalvid);
		vertexid_t get_localvid2(vertexid_t globalvid);
		vertexid_t get_globalvid(vertexid_t localvid);
		vertexid_t read_globalvid(vertexid_t localvid);
		void print_first_n_items_of_vertex_translator(unsigned int n);
		void initialize_vertex_translator();
		unsigned int get_translator_tracker_mark();
		vertex_translator_t * gettranslator();
		tracker_t gettranslatortracker();
		void settranslatortracker(tracker_t tracker);
		void deleteme();
 private:
};

#endif








