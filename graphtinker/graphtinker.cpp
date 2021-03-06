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
#include "../vertices/vertices.h"
#include "graphtinker.h"
using namespace std;

graphtinker::graphtinker(
			unsigned int _sgh_for_xvtxid, 
			unsigned int _sgh_for_xadjvtxid, 
			unsigned int _updatev, 
			unsigned int _min_vertex, 
			unsigned int _max_vertex, 
			unsigned int _num_vertices, 
			unsigned int _num_edges, 
			unsigned int _graphdirectiontype,
			unsigned int _sub_block_height, 
			unsigned int _page_block_height,
			unsigned int _eba_m_expansion_addition_height,
			unsigned int _eba_c_expansion_addition_height,
			unsigned int _ll_eba_expansion_addition_height,
			unsigned int _ll_lva_expansion_addition_height,
			unsigned int _eba_expansion_padding
			){				
	create(
		_sgh_for_xvtxid, 
		_sgh_for_xadjvtxid, 
		_updatev, 
		_min_vertex, 
		_max_vertex, 
		_num_vertices,
		_num_edges, 
		_graphdirectiontype,
		_sub_block_height, 
		_page_block_height,
		_eba_m_expansion_addition_height,
		_eba_c_expansion_addition_height,
		_ll_eba_expansion_addition_height,
		_ll_lva_expansion_addition_height,
		_eba_expansion_padding
		);
}
graphtinker::graphtinker(
			unsigned int _sgh_for_xvtxid, 
			unsigned int _sgh_for_xadjvtxid, 
			unsigned int _updatev, 
			unsigned int _min_vertex, 
			unsigned int _max_vertex, 
			unsigned int _num_vertices, 
			unsigned int _num_edges, 
			unsigned int _graphdirectiontype,
			unsigned int _sub_block_height, 
			unsigned int _page_block_height
			){
	unsigned int _eba_m_expansion_addition_height = 100000;
	unsigned int _eba_c_expansion_addition_height = 100000;
	unsigned int _ll_eba_expansion_addition_height = 1000;
	unsigned int _ll_lva_expansion_addition_height = 100;
	unsigned int _eba_expansion_padding = 10000;
	create(
		_sgh_for_xvtxid, 
		_sgh_for_xadjvtxid, 
		_updatev, 
		_min_vertex, 
		_max_vertex, 
		_num_vertices,
		_num_edges, 
		_graphdirectiontype,
		_sub_block_height, 
		_page_block_height,
		_eba_m_expansion_addition_height,
		_eba_c_expansion_addition_height,
		_ll_eba_expansion_addition_height,
		_ll_lva_expansion_addition_height,
		_eba_expansion_padding
		);
}
graphtinker::graphtinker(){};
graphtinker::~graphtinker(){
	printf("graphtinker::~graphtinker : graphtinker destructor called \n");
	/** edge_block_array_m.clear();
	edge_block_array_c.clear();
	delete [] vertex_translator;
	#ifdef EN_LLGDS	
	ll_edge_block_array.clear();
	ll_lva.clear();
	#endif */
}

void graphtinker::create(
			unsigned int _sgh_for_xvtxid, 
			unsigned int _sgh_for_xadjvtxid, 
			unsigned int _updatev, 
			unsigned int _min_vertex, 
			unsigned int _max_vertex, 
			unsigned int _num_vertices, 
			unsigned int _num_edges,
			unsigned int _graphdirectiontype,
			unsigned int _sub_block_height, 
			unsigned int _page_block_height
			){
	unsigned int _eba_m_expansion_addition_height = 100000;
	unsigned int _eba_c_expansion_addition_height = 100000;
	unsigned int _ll_eba_expansion_addition_height = 1000;
	unsigned int _ll_lva_expansion_addition_height = 100;
	unsigned int _eba_expansion_padding = 10000;
	create(
		_sgh_for_xvtxid, 
		_sgh_for_xadjvtxid, 
		_updatev, 
		_min_vertex, 
		_max_vertex, 
		_num_vertices,
		_num_edges, 
		_graphdirectiontype,
		_sub_block_height, 
		_page_block_height,
		_eba_m_expansion_addition_height,
		_eba_c_expansion_addition_height,
		_ll_eba_expansion_addition_height,
		_ll_lva_expansion_addition_height,
		_eba_expansion_padding
		);
}

void graphtinker::create(
			unsigned int _sgh_for_xvtxid, 
			unsigned int _sgh_for_xadjvtxid, 
			unsigned int _updatev, 
			unsigned int _min_vertex, 
			unsigned int _max_vertex, 
			unsigned int _num_vertices, 
			unsigned int _num_edges,
			unsigned int _graphdirectiontype,
			unsigned int _sub_block_height, 
			unsigned int _page_block_height,
			unsigned int _eba_m_expansion_addition_height,
			unsigned int _eba_c_expansion_addition_height,
			unsigned int _ll_eba_expansion_addition_height,
			unsigned int _ll_lva_expansion_addition_height,
			unsigned int _eba_expansion_padding
			){
	printf("graphtinker::graphtinker : graphtinker constructor called \n");
	cout<<"graphtinker::graphtinker constructor called : parameters : "<<endl;
	cout<<"sgh_for_xvtxid : "<<_sgh_for_xvtxid<<endl;
	cout<<"sgh_for_xadjvtxid : "<<_sgh_for_xadjvtxid<<endl;
	cout<<"updatev : "<<_updatev<<endl;
	cout<<"min_vertex : "<<_min_vertex<<endl;
	cout<<"max_vertex : "<<_max_vertex<<endl;
	cout<<"num_vertices : "<<_num_vertices<<endl;
	cout<<"num_edges : "<<_num_edges<<endl;
	cout<<"graphdirectiontype : "<<_graphdirectiontype<<endl;
	cout<<"WORK_BLOCK_HEIGHT : "<<WORK_BLOCK_HEIGHT<<endl;
	cout<<"sub_block_height : "<<_sub_block_height<<endl;
	cout<<"page_block_height : "<<_page_block_height<<endl;	
	cout<<"eba_m_expansion_addition_height : "<<_eba_m_expansion_addition_height<<endl;
	cout<<"eba_c_expansion_addition_height : "<<_eba_c_expansion_addition_height<<endl;
	cout<<"ll_eba_expansion_addition_height : "<<_ll_eba_expansion_addition_height<<endl;
	cout<<"ll_lva_expansion_addition_height : "<<_ll_lva_expansion_addition_height<<endl;
	cout<<"eba_expansion_padding : "<<_eba_expansion_padding<<endl;
	
	sgh_for_xvtxid = _sgh_for_xvtxid;
	sgh_for_xadjvtxid = _sgh_for_xadjvtxid;
	updatev = _updatev;
	vertex_range = _max_vertex - _min_vertex;
	num_vertices = _num_vertices + 200;
	num_edges = _num_edges;
	graphdirectiontype = _graphdirectiontype;
	
	eba_m_expansion_addition_height = _eba_m_expansion_addition_height;
	eba_c_expansion_addition_height = _eba_c_expansion_addition_height;
	ll_eba_expansion_addition_height = _ll_eba_expansion_addition_height;
	ll_lva_expansion_addition_height = _ll_lva_expansion_addition_height;
	eba_expansion_padding = _eba_expansion_padding;
	
	sub_block_height = _sub_block_height;
	page_block_height = _page_block_height;
	work_blocks_per_page = page_block_height / WORK_BLOCK_HEIGHT;
	sub_blocks_per_page = page_block_height / sub_block_height;
	work_blocks_per_subblock = sub_block_height / WORK_BLOCK_HEIGHT;
	
	edge_block_array_m.resize((num_vertices * work_blocks_per_page));
	edge_block_array_c.resize((100 * work_blocks_per_page));
	lvatracker.mark = 100;
	cout<<"lvatracker start mark : "<<lvatracker.mark<<endl;
	
	#ifdef EN_LLGDS
	ll_edge_block_array.resize(((num_vertices * page_block_height) / LLEDGEBLOCKSIZE));
	ll_lva.resize(((num_vertices + (LVACOARSENESSWIDTH - 1)) / LVACOARSENESSWIDTH));
	ll_eba_tracker.ptraddr=0;	
	initialize_lvas();
	#endif
	
	// vertices & translator
	if(updatev == SELF){
		vertices_handler.initialize(vertex_range, 0.15);
	} else {}
	if((sgh_for_xvtxid == SELF) || (sgh_for_xadjvtxid == SELF)){
		translator_handler.initialize(vertex_range);
	}
	
	// metadata (for delete and crumple in)
	#ifdef EN_CRUMPLEINONDELETE
	edgeblock_parentinfo.resize((num_edges / (page_block_height / 2)));
	#endif
	cout<<"edge_block_array_m.size() : "<<edge_block_array_m.size()<<endl;
	cout<<"edge_block_array_c.size() : "<<edge_block_array_c.size()<<endl;
	#ifdef EN_LLGDS
	cout<<"ll_edge_block_array.size() : "<<ll_edge_block_array.size()<<endl;
	cout<<"ll_lva.size() : "<<ll_lva.size()<<endl;
	cout<<"ll_eba_tracker.ptraddr : "<<ll_eba_tracker.ptraddr<<endl;
	#endif
	return;	
}

void graphtinker::insert_edge(unsigned int src, unsigned int dst, unsigned int ew){
	unsigned int edgeupdatecmd = INSERTEDGE;
	if(sgh_for_xvtxid == SELF){ src = translator_handler.get_localvid((vertexid_t)src); }
	if(sgh_for_xadjvtxid == SELF){ dst = translator_handler.get_localvid((vertexid_t)dst); }
	check_whether_to_resize_edgeblockarray_m(src);
	update_edge(src, dst, ew, edgeupdatecmd, vertices_handler);
	return;
}

void graphtinker::insert_edge(unsigned int src, unsigned int dst, unsigned int ew, vertices & external_vertices_handler){
	unsigned int edgeupdatecmd = INSERTEDGE;
	if(sgh_for_xvtxid == SELF){ src = (unsigned int)translator_handler.get_localvid((vertexid_t)src); }
	if(sgh_for_xadjvtxid == SELF){ dst = (unsigned int)translator_handler.get_localvid((vertexid_t)dst); }
	check_whether_to_resize_edgeblockarray_m(src);
	update_edge(src, dst, ew, edgeupdatecmd, external_vertices_handler);
	return;
}

void graphtinker::insert_edge(unsigned int src, unsigned int dst, unsigned int ew, translator & translator_handler){
	if(src > vertex_range){ cout<<"graphtinker::insert_edge : bug, out of range19. src : "<<src<<", vertex_range : "<<vertex_range<<endl; }
	unsigned int edgeupdatecmd = INSERTEDGE;
	if(sgh_for_xvtxid == OTHER){ src = (unsigned int)translator_handler.get_localvid((vertexid_t)src); }
	if(sgh_for_xadjvtxid == OTHER){ dst = (unsigned int)translator_handler.get_localvid((vertexid_t)dst); }
	check_whether_to_resize_edgeblockarray_m(src);
	update_edge(src, dst, ew, edgeupdatecmd, vertices_handler);
	return;
}

void graphtinker::insert_edge(unsigned int src, unsigned int dst, unsigned int ew, vertices & external_vertices_handler, translator & translator_handler){
	if(src > vertex_range){ cout<<"graphtinker::insert_edge : bug, out of range199. src : "<<src<<", vertex_range : "<<vertex_range<<endl; }
	unsigned int edgeupdatecmd = INSERTEDGE;
	if(sgh_for_xvtxid == OTHER){ src = (unsigned int)translator_handler.get_localvid((vertexid_t)src); }
	if(sgh_for_xadjvtxid == OTHER){ dst = (unsigned int)translator_handler.get_localvid((vertexid_t)dst); }
	check_whether_to_resize_edgeblockarray_m(src);
	update_edge(src, dst, ew, edgeupdatecmd, external_vertices_handler);
	return;
}

void graphtinker::delete_edge(unsigned int src, unsigned int dst, unsigned int ew){
	unsigned int edgeupdatecmd = DELETEEDGE;
	if(sgh_for_xvtxid == SELF){ src = translator_handler.get_localvid((vertexid_t)src); }
	if(sgh_for_xadjvtxid == SELF){ dst = translator_handler.get_localvid((vertexid_t)dst); }
	update_edge(src, dst, ew, edgeupdatecmd, vertices_handler);
	return;
}

void graphtinker::delete_edge(unsigned int src, unsigned int dst, unsigned int ew, vertices & external_vertices_handler){
	unsigned int edgeupdatecmd = DELETEEDGE;
	if(sgh_for_xvtxid == SELF){ src = translator_handler.get_localvid((vertexid_t)src); }
	if(sgh_for_xadjvtxid == SELF){ dst = translator_handler.get_localvid((vertexid_t)dst); }
	update_edge(src, dst, ew, edgeupdatecmd, external_vertices_handler);
	return;
}

void graphtinker::update_edge(unsigned int src, unsigned int dst, unsigned int ew, unsigned int edgeupdatecmd, vertices & external_vertices_handler){
	// create an edge object
	edge_t edge;
	edge.xvtx_id = src;								
	edge.xadjvtx_id = dst;
	edge.edgew = 1; 
	edge.flag = VALID;
	#ifdef EN_LLGDS
	edge.heba_hvtx_id = -1;
	edge.heba_workblockid = -1;
	edge.heba_loffset = -1;
	#endif
	
	// variables & parameter registers and RAM declared
	unsigned int eit;
	unsigned int geni;
	vertexid_t xvtx_id;
	unsigned int tripiteration_lcs=0;		

	///////////////////////conversion unit  
	//hash xadjvtx_id 
	bucket_t hadjvtx_id=0;  

	///////////////////////edgeblock
	edge_nt edgeblock;

	///////////////////////margins & traversal trackers
	margin_t wblkmargin;
	margin_t start_wblkmargin;
	margin_t first_wblkmargin;
	margin_t subblkmargin; 

	///////////////////////params and report
	//module parameters and reports
	moduleunitcmd_t moduleunitcmd;
	moduleparams_t moduleparams;
	
	//load unit 
	loadunitcmd_t loadunitcmd;

	//insert-unit parameters and reports
	insertparams_t insertparams;
	insertreport_t insertreport;  
	
	//find-unit parameters and reports
	findparams_t findparams;
	findreport_t findreport;
	searchreport_t searchreport;
	
	//writeback unit 
	writebackunitcmd_t writebackunitcmd;
	
	//interval unit 
	intervalunitcmd_t intervalunitcmd;
	
	//LL unit 
	#ifdef EN_LLGDS	
	llgdsunitcmd_t llgdsunitcmd;
	#endif
	
	#ifdef EN_CRUMPLEINONDELETE
	deleteandcrumpleincmd_t deleteandcrumpleincmd;
	#endif

	//exit condition (this should be after: 'insert-unit parameters and reports')
	unsigned int quitstatus=0;	
	
	////////////////////////// initial assignments
	// initialize appropriate module globals
	geni = 1;
	xvtx_id = edge.xvtx_id;	
	tripiteration_lcs = 0;
	hadjvtx_id = googlehash(edge.xadjvtx_id, geni);
	findwblkmargin(&wblkmargin, hadjvtx_id); //find margins
	start_wblkmargin = wblkmargin;
	first_wblkmargin = wblkmargin;
	findsubblkmargin(&subblkmargin, hadjvtx_id);
	#ifdef EN_CRUMPLEINONDELETE
	// keep track of workblock address before moving to a lower generation (or in first launch) -  might be needed in the lower generation if we decide to share supervertex entry
	unsigned int lastgenworkblockaddr = get_edgeblock_offset(xvtx_id) + wblkmargin.top/WORK_BLOCK_HEIGHT;
	#endif

	//initialize module unit 
	moduleunitcmd.mode=FINDONLYMODE;
		
	// initialize appropriate fields of lcs units
	// everything is initialized here
	initialize_moduleunit_params(&moduleparams, edge.xadjvtx_id, edge.edgew);
	initialize_loadunit(&loadunitcmd);
	initialize_insertunit(&insertparams, &insertreport, edge.xadjvtx_id, hadjvtx_id, edge.edgew);
	initialize_findunit(&findparams, &findreport, edge.xadjvtx_id, hadjvtx_id, edge.edgew);
	initialize_writebackunit(&writebackunitcmd);
	#ifdef EN_LLGDS		
	initialize_llebaverdictcmd(&llgdsunitcmd);
	clear_lleba_addresses_in_moduleparams(&moduleparams);
	#endif
	#ifdef EN_CRUMPLEINONDELETE
	init_deleteandcrumplein_verdictcmd(&deleteandcrumpleincmd);
	#endif

	//initialize trip iteration
	unsigned int infiniti=0;
	unsigned int prevLoadAddr=NAv;
	
	vertexid_t xvtxid = 0;
	vertexid_t xadjvtxid = 0;
	
	if(updatev != OFF){
		// update vertex of first edge
		xvtxid = edge.xvtx_id; xadjvtxid = edge.xadjvtx_id;
		if(sgh_for_xvtxid == SELF){ xvtxid = translator_handler.get_globalvid(edge.xvtx_id); }
		if(sgh_for_xadjvtxid == SELF){ xadjvtxid = translator_handler.get_globalvid(edge.xadjvtx_id); }		
		external_vertices_handler.update_vertex_property(xvtxid, xadjvtxid, edgeupdatecmd, graphdirectiontype);
	}

	//***
	//***
	//***
	//***
	//***
	//***
	//***
	//*** loop
	for(infiniti=0; infiniti<SOMELARGENO; infiniti++){
		
		//***********************************************************************************************//Load unit
		if(geni == 1){
		load_unit(
				&moduleparams,
				loadunitcmd,				
				&insertparams, 		
				&findparams,
				wblkmargin,
				xvtx_id,
				edge,
				&edgeblock,
				edge_block_array_m,
				&prevLoadAddr,
				geni
				);
		} else {
		load_unit(
				&moduleparams,
				loadunitcmd,				
				&insertparams, 		
				&findparams,
				wblkmargin,
				xvtx_id,
				edge,
				&edgeblock,
				edge_block_array_c,
				&prevLoadAddr,
				geni
				);
		}
		//***********************************************************************************************
		
		//***********************************************************************************************//load compute-params unit
		load_params(
					moduleparams,				
					&insertparams,		
					&findparams,
					wblkmargin, 
					hadjvtx_id
					);
		//***********************************************************************************************
		
		//***********************************************************************************************//Compute unit
		/// one-time-fields of incomming edge is updated here
		compute_unit(				
					moduleunitcmd,
					&moduleparams,
					&insertparams, 
					&insertreport,		
					findparams,
					&findreport,				
					wblkmargin, 
					subblkmargin,
					start_wblkmargin,
					hadjvtx_id, 
					&edgeblock,
					&edge,
					xvtx_id,
					moduleparams.rolledover,
					edgeupdatecmd,
					geni
					);
		//***********************************************************************************************
		
		//***********************************************************************************************//Inference unit
		inference_unit(
					edgeupdatecmd,
					&moduleunitcmd,
					&moduleparams,				
					&loadunitcmd,
					findparams,
					findreport,
					insertparams,
					insertreport,				
					&writebackunitcmd,				
					&intervalunitcmd,				
					&wblkmargin, 
					subblkmargin,
					start_wblkmargin,				
					xvtx_id
					#ifdef EN_LLGDS	
					,&llgdsunitcmd
					#endif
					#ifdef EN_CRUMPLEINONDELETE
					,&deleteandcrumpleincmd
					#endif
		);
		//***********************************************************************************************
		
		//***********************************************************************************************//EBA port unit
		writeback_unit(
					&moduleparams,				
					writebackunitcmd,
					edge,
					&edgeblock,
					edge_block_array_m,
					edge_block_array_c,
					#ifdef EN_CRUMPLEINONDELETE
					edgeblock_parentinfo,
					#endif
					&lvatracker,
					xvtx_id,
					first_wblkmargin,
					subblkmargin,
					geni,
					edgeupdatecmd
					#ifdef EN_CRUMPLEINONDELETE
					,lastgenworkblockaddr
					,svs
					#ifdef EN_LLGDS
					,ll_edge_block_array
					#endif
					#endif
					);
		//***********************************************************************************************

		//***********************************************************************************************// delete and crumple in
		#ifdef EN_CRUMPLEINONDELETE
		deleteandcrumplein_unit(
			writebackunitcmd,
			findreport,
			edge,
			edge_block_array_m,
			edge_block_array_c,
			#ifdef EN_LLGDS
			ll_edge_block_array,
			#endif
			edgeblock_parentinfo,
			xvtx_id,
			wblkmargin,
			subblkmargin,
			geni
			#ifdef EN_CRUMPLEINONDELETE
			,deleteandcrumpleincmd
			,svs
			,freed_edgeblock_list
			#endif
			);
		#endif
		//***********************************************************************************************
	
		//***********************************************************************************************// GraphTinkerLL
		#ifdef EN_LLGDS
		ll_unit(
			llgdsunitcmd,
			&moduleparams,
			&insertparams,
			edge,
			edge_block_array_m,
			edge_block_array_c,
			geni
			#ifdef EN_LLGDS
			,ll_edge_block_array
			,ll_lva
			,&ll_eba_tracker
			#endif
			);
		#endif
		//***********************************************************************************************
		
		//***********************************************************************************************//Interval unit
		interval_unit_updateedge(			
					&moduleunitcmd,
					&moduleparams,
					&loadunitcmd,
					&insertparams, 
					&insertreport,		
					&findparams,
					&findreport,
					&writebackunitcmd,
					intervalunitcmd,				
					&wblkmargin,
					&subblkmargin,
					&start_wblkmargin,
					&first_wblkmargin,
					&xvtx_id,
					&hadjvtx_id,
					edge,
					edgeupdatecmd,
					&tripiteration_lcs,
					&geni,
					&quitstatus,
					infiniti
					#ifdef EN_CRUMPLEINONDELETE
					,&lastgenworkblockaddr
					#endif
					#ifdef EN_LLGDS	
					,&llgdsunitcmd
					#endif
					#ifdef EN_CRUMPLEINONDELETE
					,&deleteandcrumpleincmd
					#endif
					);
		
		//***********************************************************************************************
		
		if(quitstatus==1){ 
			#ifdef cpuem_l7
			cout<<endl<<"successful. exiting... exiting... (update_singleedge)"<<endl; 
			#endif 
			return;
		} 
		if(tripiteration_lcs>100){
			#ifdef cpuem_bugs_b1
			cout<<endl<<"bug! : trip iteration too much!, exiting..."<<endl; 
			#endif 
			return; 
		}
		if(geni>500000){
			#ifdef cpuem_bugs_b1
			cout<<"bug! : too many generations ("<<geni<<") spun!, exiting..."<<endl;  
			cout<<"searchreport.searchstop = "<<searchreport.searchstop<<endl;
			cout<<"searchreport.searchsuccessful = "<<searchreport.searchsuccessful<<endl;
			cout<<"insertreport.exittype = "<<insertreport.exittype<<endl;
			cout<<"moduleunitcmd.mode = "<<moduleunitcmd.mode<<endl;
			#endif
			return; 
		}
	}
	cout<<endl<<"bug! : infiniti exhausted : infiniti = "<<infiniti<<""<<endl;
	cout<<"searchreport.searchstop = "<<searchreport.searchstop<<endl;
	cout<<"searchreport.searchsuccessful = "<<searchreport.searchsuccessful<<endl;
	cout<<"insertreport.exittype = "<<insertreport.exittype<<endl;
	cout<<"moduleunitcmd.mode = "<<moduleunitcmd.mode<<endl;
	return; 
}

vertexid_t graphtinker::retrieve_edges(vertexid_t vid, vector<edge_tt> & edges){
	vector<clusterptr_t> clusterptrs;	
	vertexid_t basevid = vid;
	unsigned int _geni=1;
	
	// load edges
	clusterptrs.push_back(vid);
	unsigned int len = clusterptrs.size();	
	unsigned int wps = work_blocks_per_subblock;
	
	while(true){
		for(unsigned int i=0; i<len; i++){
			vid = clusterptrs.back();
			clusterptrs.pop_back();
			
			unsigned int ebaoffset = get_edgeblock_offset(vid);
			for(unsigned int t=0; t<work_blocks_per_page; t++){
				edge_nt edgeset;
				if(_geni==1){ edgeset = edge_block_array_m[(ebaoffset + t)]; }
				else { edgeset = edge_block_array_c[(ebaoffset + t)]; }
				
				for(unsigned int k=0; k<WORK_BLOCK_HEIGHT; k++){
					if(edgeset.edges[k].flag == VALID){
						edges.push_back(edgeset.edges[k]);
					}
				}
				
				if(((t%wps)==0) && (edgeset.clusterinfo.flag==VALID)){
					clusterptrs.push_back(edgeset.clusterinfo.data); 
				}
			}
		}
	
		len = clusterptrs.size();
		if(len==0){ break; } else{ _geni+=1; }
	}
	return basevid;
}

vector<edge_nt> & graphtinker::get_edge_block_array_m(){
	return edge_block_array_m;
}

vector<edge_nt> & graphtinker::get_edge_block_array_c(){
	return edge_block_array_c;
}

vector<ll_logicalvertexentity_t> & graphtinker::get_ll_logicalvertexentity(){
	return ll_lva;
}

vector<ll_edgeblock_t> & graphtinker::get_ll_edge_block_array(){
	return ll_edge_block_array;
}
		
unsigned int graphtinker::printv_edgecount(){
	unsigned int edgecount = 0;
	edgecount += graphtinker::get_edgecount(edge_block_array_m, get_edge_block_array_height(edge_block_array_m));
	edgecount += graphtinker::get_edgecount(edge_block_array_c, lvatracker.mark);
	return edgecount;
}

unsigned int graphtinker::get_edgecount(vector<edge_nt> edge_block_array_x, unsigned int height){
	unsigned int edgecount = 0;
	for(vertexid_t vid=0; vid<height; vid++){
		unsigned int offset = get_edgeblock_offset(vid);		
		for(unsigned int j=offset; j<(offset+work_blocks_per_page); j++){ 
			for(unsigned int k=0; k<WORK_BLOCK_HEIGHT; k++){
				if (edge_block_array_x[j].edges[k].flag == VALID){ edgecount += edge_block_array_x[j].edges[k].edge_weight; }
			}
		}
	}
	return edgecount;
}

unsigned int graphtinker::printv_uniqueedgecount(){
	unsigned int edgecount = 0;
	edgecount += graphtinker::get_uniqueedgecount(edge_block_array_m, get_edge_block_array_height(edge_block_array_m));
	edgecount += graphtinker::get_uniqueedgecount(edge_block_array_c, lvatracker.mark);
	return edgecount;
}

unsigned int graphtinker::get_uniqueedgecount(vector<edge_nt> edge_block_array_x, unsigned int height){
	unsigned int edgecount = 0;
	for(vertexid_t vid=0; vid<height; vid++){
		unsigned int offset = get_edgeblock_offset(vid);		
		for(unsigned int j=offset; j<(offset+work_blocks_per_page); j++){ 
			for(unsigned int k=0; k<WORK_BLOCK_HEIGHT; k++){
				if (edge_block_array_x[j].edges[k].flag == VALID){ edgecount += 1; }
			}
		}
	}
	return edgecount;
}

unsigned int graphtinker::printll_edgecount(){
	unsigned int uniqueedgecount = 0;
	uniqueedgecount += ll_countedges(ll_edge_block_array);
	return uniqueedgecount;
}

unsigned int graphtinker::ll_countedges(vector<ll_edgeblock_t> & ll_edge_block_array){
	unsigned int uniqueedgecount = 0;
	for(unsigned int i=0;i<ll_edge_block_array.size();i++){ //ll_edgeblock_array_size
		for(unsigned int j=0;j<LLEDGEBLOCKSIZE;j++){
			if(ll_edge_block_array[i].ll_edgeblock[j].flag==VALID){ uniqueedgecount += ll_edge_block_array[i].ll_edgeblock[j].edgew; }
		}
	}	
	return uniqueedgecount;
}

#ifdef EN_CRUMPLEINONDELETE	
unsigned int graphtinker::print_svs_size(){
	return svs.size();
}
#endif

#ifdef EN_CRUMPLEINONDELETE	
unsigned int graphtinker::print_freed_edgeblock_list_size(){
	return freed_edgeblock_list.size();
}
#endif

void graphtinker::initialize_lvas(){
	for(unsigned int i=0; i<ll_lva.size(); i++){	
		ll_lva[i].baseaddr=0;
		ll_lva[i].lastlocalbaseaddr=0;
		ll_lva[i].lastlocaladdr=0;
		ll_lva[i].totaledgecount=0;
		ll_lva[i].flag = INVALID;
	}
	return;
}

vertices & graphtinker::get_vertices_handler(){
	return vertices_handler;
}

unsigned int graphtinker::get_graphdirectiontype(){
	return graphdirectiontype;
}

translator & graphtinker::gettranslator(){
	return translator_handler;
}

unsigned int graphtinker::get_translator_tracker_mark(){
	return translator_handler.get_translator_tracker_mark();
}

unsigned int graphtinker::get_work_blocks_per_page(){
	return work_blocks_per_page;
}

unsigned int graphtinker::get_work_blocks_per_subblock(){
	return work_blocks_per_subblock;
}

void graphtinker::print_edgeblockarray(vertexid_t begin, vertexid_t end){
	vector<edge_tt> edges;
	
	for(unsigned int i=begin; i<end; i++){
		retrieve_edges(0, edges);
		for(unsigned int j=0; j<edges.size(); j++){
			cout<<"graphtinker::print_edgeblockarray : srcvid : "<<i<<", dstvid : "<<edges[j].xadjvtx_id<<", edgew : "<<edges[j].edge_weight<<endl;
		}
		edges.clear();
	}
	return;
}

unsigned int graphtinker::get_edge_block_array_height(vector<edge_nt> & edge_block_array){
	return (edge_block_array.size() / work_blocks_per_page);
}

void graphtinker::check_whether_to_resize_edgeblockarray_m(unsigned int vid){
	if(vid >= get_edge_block_array_height(edge_block_array_m)){
		unsigned int newsz = (vid + eba_m_expansion_addition_height) * work_blocks_per_page;
		edge_block_array_m.resize(newsz);
		cout<<"graphtinker::resize_edgeblockarray_m : resizing... : vid : "<<vid<<", new edge_block_array_m size : "<<edge_block_array_m.size()<<", new edge_block_array_m height : "<<get_edge_block_array_height(edge_block_array_m)<<endl;	
	}
	return;
}

unsigned int graphtinker::get_vertex_range(){
	return vertex_range;
}


