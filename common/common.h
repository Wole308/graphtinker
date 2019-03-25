#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
using namespace std;

#define CPU 0

#define cpuem_bugs_b1 0
#define EN_BUGCHECK 0
#define EN_PROCESSLOWERGENCLUSTERS 0 //don't turn off!!!
#define EN_INITVPROPERTYARRAY 0

#define WORK_BLOCK_HEIGHT 4 
#define BATCH_SIZE 1048576

#define DIRECTEDGRAPH 0
#define UNDIRECTEDGRAPH 1

#define ZERO 0
#define NA 999999999 //not applicable
#define NAv 555555555 //not available
#define NULLL 888
#define NONE 666
#define FIRST 111

#define LOADEDINTOEMPTYBUCKET 0
#define FOUNDANDUPDATEDITSELF 1
#define PASSEDTHROUGH 2
#define PASSEDTHROUGHANDSWAPPEDATSOMEPOINT 3

#define SOMESMALLNO 10
#define SOMELARGENO 100000000

#define VALID 5
#define INVALID 6
#define METAVALID 7
#define DELETED 8

#define SUCCESSFUL 1
#define UNSUCCESSFUL 0

#define NO 0
#define YES 1

#define OFF 0
#define ON 1

#define READ 5 
#define WRITE 6
#define NEITHER_READ_NOR_WRITE 7

#define FINDONLYMODE 0
#define INSERTONLYMODE 1

#define GRAPHGEN_TOTAL_VERTEX_COUNT 10
#define GRAPHGEN_NO_OF_DSTV_PER_SRCV 10

#define OCCUPIED 989898989
#define UNOCCUPIED 898989898

#define MAXUNSIGNEDINT 18446744073709551615
#define INFINITI 184467443

#define ENSearch_SearchValid_SearchStopped_SearchUnsuccessful_ENInsert_InsertValid_PassedThroughandSwappedatsomePoint_AllMode_X 0
#define ENSearch_SearchValid_SearchStopped_SearchUnsuccessful_ENInsert_InsertValid_LoadedIntoEmptyBucket_AllMode_X 1
#define ENSearch_SearchValid_SearchStopped_SearchUnsuccessful_ENInsert_InsertValid_FoundandUpdatedItself_AllMode_X 2
#define ENSearch_SearchValid_SearchStopped_SearchUnsuccessful_ENInsert_InsertValid_PassedThrough_AllMode_X 3
#define ENSearch_SearchValid_SearchNotStopped_SearchUnsuccessful_ENInsert_InsertValid_X_AllModes_X 4
#define ENSearch_SearchValid_SearchStopped_SearchSuccessful_ENInsert_InsertValid_X_AllModes_X 5

#define ENSearch_SearchValid_SearchNotstopped_SearchUnsuccessfull_X_X_X_SearchOnlyMode_NotLastWorkblock 6
#define ENSearch_SearchValid_SearchNotstopped_SearchUnsuccessfull_ENInsert_X_X_SearchOnlyMode_LastWorkblock 7
#define ENSearch_SearchValid_SearchNotstopped_SearchUnsuccessfull_UNENInsert_X_X_SearchOnlyMode_LastWorkblock 8
#define ENSearch_SearchValid_Searchstopped_SearchUnsuccessfull_ENInsert_X_X_SearchOnlyMode_X 9
#define ENSearch_SearchValid_Searchstopped_SearchUnsuccessfull_UNENInsert_X_X_SearchOnlyMode_X 10
#define ENSearch_SearchValid_Searchstopped_SearchSuccessfull_X_X_X_SearchOnlyMode_X 11

#define X_X_X_X_ENInsert_InsertValid_PassedThroughandSwappedatsomePoint_InsertOnlyMode_NotLastWorkblock 12
#define X_X_X_X_ENInsert_InsertValid_PassedThroughandSwappedatsomePoint_InsertOnlyMode_LastWorkblock 13
#define X_X_X_X_ENInsert_InsertValid_LoadedIntoEmptyBucket_InsertOnlyMode_X 14
#define X_X_X_X_ENInsert_InsertValid_FoundandUpdatedItself_InsertOnlyMode_X 15
#define X_X_X_X_ENInsert_InsertValid_PassedThrough_InsertOnlyMode_NotLastWorkblock 16
#define X_X_X_X_ENInsert_InsertValid_PassedThrough_InsertOnlyMode_LastWorkblock 17

#define CONTINUE_FROM_FIRST_GENERATION 0
#define CONTINUE_IN_LOWER_GENERATION 1
#define CONTINUE_IN_CURRENT_GENERATION 2
#define QUIT_TO_NEXT_EDGE 3

#define EXIT 6

#define PRINTTYPE_VALIDEDGESONLY 0
#define PRINTTYPE_EDGECOUNT 1
#define PRINTTYPE_CLUSTERINFOONLY 2
#define PRINTTYPE_ALLINFOS 3
#define PRINTTYPE_VALIDEDGESANDCLUSTERINFOONLY 4
#define PRINTTYPE_VALIDEDGESONLY_PRESENTATIONVIEW 5
#define PRINTTYPE_UNIQUEEDGECOUNT 6
#define PRINTTYPE_VALIDHEBAANDLLEDGES 7

#define INITTYPE_ALLZEROS 0
#define INITTYPE_ALLINFINITY 1

#define RUN_SUMMARY_ARRAY_SIZE 

#define LLEDGEBLOCKSIZE 512
#define LVACOARSENESSWIDTH 2048 //should be a power of 2

// ll commands
#define NOCMD 0
#define INSERTCMD 5 
#define UPDATECMD 6
#define DELETECMD 7
#define DELETEANDCRUMPLEINCMD 8
#define UPDATEEDGEPTRSCMD 9

// dci (deleteandcrumplein commands)
#define DCI_NOCMD 5
#define DCI_JUSTQUITCMD 6
#define DCI_CRUMPLEINCMD 7 

#define NO_OF_VERTEX_PARTITIONS  //8
#define MAX_INDEX_FINDABLE_IN_A_PARTITION 
#define SIZE_OF_EACH_VERTEX_PARTITION 
#define SIZE_OF_EACH_VERTEX_SUBPARTITION 

#define SRC_DST 5
#define DST_SRC 6

#define INEDGE 5
#define OUTEDGE 6
#define NOEDGE 7

#define HEBAEXPANSIONADDITIONHEIGTH 100

#define INSERTEDGE 5
#define DELETEEDGE 6

#define HIGH_DEGREE_VERTEX 5
#define LOW_DEGREE_VERTEX 6

#define SELF 1
#define OTHER 2

typedef unsigned int vertexid_t;
typedef unsigned int vertexid_t;
typedef unsigned int bucket_t;
typedef unsigned int edgeweight_t;
typedef unsigned int flag_t;
typedef double vertexdata_t;
typedef unsigned int clusterptr_t;
typedef unsigned int id_t;

/// struct declarations

typedef struct {
	string path;
	unsigned int min_vertex;
	unsigned int max_vertex;
    unsigned int num_vertices;
	unsigned int num_edges;
} dataset_t;

typedef struct {
	vertexid_t xadjvtx_id;
	bucket_t initialbucket;
	edgeweight_t edge_weight;
    flag_t flag;
	#ifdef EN_LLGDS
	vertexid_t ll_localbaseaddrptr;
	vertexid_t ll_localaddrptr;
	#endif
} edge_tt;

/** sv_ptr : pointer to a supervertex
NB: many subblocks can (and should) have the same sv_ptr. means they all are 1st borns in a descendancy tree */
typedef struct {
	clusterptr_t data;
	flag_t flag;
	unsigned int sv_ptr;
} clusterinfo_t;

typedef struct {
	flag_t flag; 
} edgeinfo_t;

typedef struct {
	edgeinfo_t edgeinfo;
	clusterinfo_t clusterinfo;
	edge_tt edges[WORK_BLOCK_HEIGHT];
} edge_nt;

typedef struct {
	unsigned int subblockid;
	flag_t flag;
} edgeblock_parentinfo_t;

typedef struct {
	vertexid_t xvtx_id;
	vertexid_t xadjvtx_id;
	edgeweight_t edgew;
	flag_t flag;
	#ifdef EN_LLGDS
	int heba_hvtx_id;
	int heba_workblockid;
	int heba_loffset;
	#endif
} edge_t;

typedef struct {
	unsigned int mode;
} moduleunitcmd_t;

typedef struct {
	unsigned int rolledover;  //Y/N // traversal info
	unsigned int clustered; //Y/N // cluster info
    int cptr;	
	vertexid_t xadjvtx_id; // edge info
	edgeweight_t edge_weight;
	#ifdef EN_LLGDS
	vertexid_t ll_localbaseaddrptr_x;
	vertexid_t ll_localaddrptr_x;
	#endif	
} moduleparams_t;

typedef struct {
	unsigned int load;
} loadunitcmd_t;

typedef struct {
	unsigned int verdict;
} llgdsunitcmd_t;

typedef struct {
	unsigned int verdict;
} deleteandcrumpleincmd_t;

typedef struct {
	vertexid_t xadjvtx_id; // edge info
	bucket_t initialbucket_x;
	edgeweight_t edge_weight;
	flag_t isstartblk; // additional info	
} insertparams_t;

typedef struct {
	unsigned int exittype;
	bucket_t validbuckets_incr;
	bucket_t overflowbkt;
	bucket_t lastbktloadedinto;
} insertreport_t;

typedef struct {	
	vertexid_t xadjvtx_id; // edge info
	bucket_t initialbucket_x;
	edgeweight_t edge_weight;	
	flag_t isstartblk; // additional info
} findparams_t;

typedef struct {
	bucket_t localoffset;
	flag_t entryfound;
	flag_t entrydeleted;
	flag_t maxprobelengthreached;
    flag_t foundemptybkt;
} findreport_t;

typedef struct {
	unsigned int writeback;
	unsigned int addr;
	unsigned int markasclustered;
	unsigned int subblockid;
	unsigned int workblockid;
} writebackunitcmd_t;

typedef struct {
	unsigned int verdict;
} intervalunitcmd_t;

typedef struct {
	bucket_t top;
	bucket_t bottom;
} margin_t;

typedef struct {
	unsigned int searchstop;
	unsigned int searchsuccessful;
} searchreport_t;

typedef struct {
	unsigned int search;
	unsigned int insert;
} encontrol_t;

/// trackers
typedef struct {
	unsigned int mark;
} tracker_t;

typedef struct {
	unsigned int marker;
} markertracker_t;

/// profiling

typedef struct {
	vertexid_t A;
	vertexid_t B;
} tuple_vid_t;

typedef struct {
	unsigned int A;
	unsigned int B;
} tuple_t;

typedef struct {
	vertexid_t A;
	vertexid_t B;
	vertexid_t C;
} triple_vid_t; 

typedef struct {
	vertexid_t globalvid;
	vertexid_t localvid;
	flag_t flag;
	flag_t lflag;
} vertex_translator_t;

/// LL data structures
typedef struct {
	unsigned int edgecount;
	unsigned int nextcptr;
	unsigned int currcptr;
	unsigned int prevcptr;
} ll_edgeblockmetadata_t;

typedef struct {
	edge_t ll_edgeblock[LLEDGEBLOCKSIZE];
	ll_edgeblockmetadata_t metadata;
} ll_edgeblock_t;

typedef struct {
	unsigned int ptraddr;
} ll_eba_tracker_t;

typedef struct {
	unsigned int baseaddr;
	unsigned int lastlocalbaseaddr;
	unsigned int lastlocaladdr;
	unsigned int totaledgecount;
	unsigned int flag;
} ll_logicalvertexentity_t;

typedef struct {	
	unsigned int indegree;
	unsigned int outdegree;
	vertexdata_t data;
	flag_t flag;
} vertexproperty_t;

/** 
- except stated otherwise, when used, the array of this struct is indexed by the *** raw local vertex ids ***  
- hvtx_id is a hashed vertex id value (calculated from the raw local vertex id) AND (w.r.t the given cluster!) ...
- ... this is done like this because each cluster exist as its own independent EdgeblockArray ...
- ... so the hvtx_id is just like that used in GT
- ... therefore, multiple entries in the *vertexlink_t can have the same hvtx_id, but these entry's cluster id (cid) must be all different
- status (VALID/INVALID) indicates whether or not this struct entry is valid and points to an edge cluster
- vprop is the property of the vertexlink */
typedef struct {
	vertexid_t hvtx_id; 
	unsigned int cid;
	flag_t status;
	vertexproperty_t vprop;
} vertexlink_t;

/** 
- vertexid iteratior type : used by powergraph in GTC
- a cluster of edges is retiieved
- says what vertices own these edges, and the offsets of their ownerships
unsigned int offset; // offset from beginning of list
unsigned int size; // length of vertex's edges
unsigned int lvid; // vertex value */
typedef struct {
	unsigned int offset; 
	unsigned int size; 
	unsigned int lvid; 
} vid_it_t; 

/** used in the crumpling-in deletion functionality
hvtx_id specifies an index to an edgeblock in the EdgeblockArray */
typedef struct {
	vector<unsigned int> hvtx_ids;
	unsigned int geni_ofparentsubblock;
} supervertex_t;
#endif








