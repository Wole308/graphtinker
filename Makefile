export OMP_NUM_THREADS=1
NUM_CORES=1

ON=1
OFF=0
rmat_500k_8M=ON
rmat_1M_10M=OFF
rmat_1M_16M=OFF 
rmat_2M_32M=OFF 
hollywood=OFF 
kron=OFF

LL=ON
VUPDATE=OFF

DELETIONTYPE=DELETEEDGE
INSERTIONRATE=1
DELETIONRATE=0

GDSARG1=vertices/vertices.cpp
GDSARG2=graphtinker/commonutility.cpp 
GDSARG3=graphtinker/compute_unit.cpp 
GDSARG4=graphtinker/eba_manager.cpp 
GDSARG5=graphtinker/find_margin.cpp 
GDSARG6=graphtinker/find_unit.cpp 
GDSARG7=graphtinker/gds_utility.cpp 
GDSARG8=graphtinker/graphtinker.cpp 
GDSARG9=graphtinker/hash_gen.cpp
GDSARG10=graphtinker/inference_unit.cpp 
GDSARG11=graphtinker/init.cpp 
GDSARG12=graphtinker/insert_unit.cpp 
GDSARG13=graphtinker/interval_unit.cpp 
GDSARG14=graphtinker/intervalunit_funcs.cpp 
GDSARG15=graphtinker/ll_functions.cpp 
GDSARG16=graphtinker/load_params.cpp 
GDSARG17=graphtinker/load_unit.cpp 
GDSARG18=graphtinker/print.cpp
GDSARG19=graphtinker/supervs.cpp
GDSARG20=graphtinker/utility.cpp
GDSARG21=graphtinker/writeback_unit.cpp
GDSARG22=graphtinker/deleteandcrumplein_unit.cpp
GDSARG23=graphtinker/ll_unit.cpp
TESTARG1=tests/updates_test.cpp

TESTARG=$(TESTARG1)
GDSARG=$(GDSARG1) $(GDSARG2) $(GDSARG3) $(GDSARG4) $(GDSARG5) $(GDSARG6) $(GDSARG7) $(GDSARG8) $(GDSARG9) $(GDSARG10) $(GDSARG11) $(GDSARG12) $(GDSARG13) $(GDSARG14) $(GDSARG15) $(GDSARG16) $(GDSARG17) $(GDSARG18) $(GDSARG19) $(GDSARG20) $(GDSARG21) $(GDSARG22) $(GDSARG23)
	
$(info echo *** started! ***)

all: clean system_config generate_src gt

test: clean system_config generate_src gt run

system_config:
ifeq ($(rmat_500k_8M), ON)
PYARG=$(NUM_CORES) $(LL) $(VUPDATE) 4 8 64 1048576
endif
ifeq ($(rmat_1M_10M), ON)
PYARG=$(NUM_CORES) $(LL) $(VUPDATE) 4 8 64 1048576
endif
ifeq ($(rmat_1M_16M), ON)
PYARG=$(NUM_CORES) $(LL) $(VUPDATE) 4 8 64 1048576
endif
ifeq ($(rmat_2M_32M), ON)
PYARG=$(NUM_CORES) $(LL) $(VUPDATE) 4 8 64 1048576
endif
ifeq ($(hollywood), ON)
PYARG=$(NUM_CORES) $(LL) $(VUPDATE) 4 8 64 1048576
endif
ifeq ($(kron), ON)
PYARG=$(NUM_CORES) $(LL) $(VUPDATE) 4 8 64 1048576
endif
	
generate_src:
	cd gen; python gen.py $(PYARG)

gt:
	g++ -O3 -std=c++11 $(TESTARG) $(GDSARG) -fopenmp -o gt.exe
	
run:
	./gt.exe
	
clean:
	rm -rf gt.exe
	$(info clean successful)