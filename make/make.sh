#!/bin/bash
#!/bin/bash
#SBATCH --job-name=all_runs      # Job name		
#SBATCH --cpus-per-task=1            # Number of CPU cores per task
#SBATCH --error="all_runs.err"                    # Where to write std err
#SBATCH --output=all_runs.log     # Standard output and error log
#SBATCH --nodelist=slurm1

set -e # Courtesy : Jinja 2.0

rm -rf bmrktest.exe
export OMP_NUM_THREADS=1
NUM_CORES=1

ON=1
OFF=0
rmat_500k_8M=1
rmat_1M_10M=0
rmat_1M_16M=0 
rmat_2M_32M=0 
hollywood=0
kron=0

GDSARG1="../vertices/vertices.cpp"
GDSARG2="../graphtinker/commonutility.cpp" 
GDSARG3="../graphtinker/compute_unit.cpp" 
GDSARG4="../graphtinker/eba_manager.cpp" 
GDSARG5="../graphtinker/find_margin.cpp" 
GDSARG6="../graphtinker/find_unit.cpp" 
GDSARG7="../graphtinker/gds_utility.cpp" 
GDSARG8="../graphtinker/graphtinker.cpp" 
GDSARG9="../graphtinker/hash_gen.cpp"
GDSARG10="../graphtinker/inference_unit.cpp" 
GDSARG11="../graphtinker/init.cpp" 
GDSARG12="../graphtinker/insert_unit.cpp" 
GDSARG13="../graphtinker/interval_unit.cpp" 
GDSARG14="../graphtinker/intervalunit_funcs.cpp" 
GDSARG15="../graphtinker/ll_functions.cpp" 
GDSARG16="../graphtinker/load_params.cpp" 
GDSARG17="../graphtinker/load_unit.cpp" 
GDSARG18="../graphtinker/print.cpp"
GDSARG19="../graphtinker/supervs.cpp"
GDSARG20="../graphtinker/utility.cpp"
GDSARG21="../graphtinker/writeback_unit.cpp"
GDSARG22="../graphtinker/deleteandcrumplein_unit.cpp"
GDSARG23="../graphtinker/ll_unit.cpp"

TESTARG1="../tests/updates_test.cpp"

TESTARG="$TESTARG1"
GDSARG="$GDSARG1 $GDSARG2 $GDSARG3 $GDSARG4 $GDSARG5 $GDSARG6 $GDSARG7 $GDSARG8 $GDSARG9 $GDSARG10 $GDSARG11 $GDSARG12 $GDSARG13 $GDSARG14 $GDSARG15 $GDSARG16 $GDSARG17 $GDSARG18 $GDSARG19 $GDSARG20 $GDSARG21 $GDSARG22 $GDSARG23"

if [ $rmat_500k_8M == $ON ] 
then 
	echo '*** started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES ON ON OFF rmat16_524288_8380000.edges DIRECTEDGRAPH 524288 8380000 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	cd ../gen
	python gen.py $PYARG_BFS
	cd ../make
	g++ -O3 -std=c++11 $TESTARG $GDSARG -fopenmp -o bmrktest.exe
	time ./bmrktest.exe #> rmat_500k_8M/ll_on.log
	wait
	echo '*** finished! ***'
	rm -rf bmrktest.exe
	
	echo '*** started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES OFF ON OFF rmat16_524288_8380000.edges DIRECTEDGRAPH 524288 8380000 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	cd ../gen
	python gen.py $PYARG_BFS
	cd ../make
	g++ -O3 -std=c++11 $TESTARG $GDSARG -fopenmp -o bmrktest.exe
	time ./bmrktest.exe #> rmat_500k_8M/ll_off.log
	wait
	echo '*** finished! ***'
	rm -rf bmrktest.exe
	exit 0
	
	echo '*** started! ***'
	PYARG_BFS_FULLPROC="$NUM_CORES OFF OFF OFF rmat16_524288_8380000.edges DIRECTEDGRAPH 524288 8380000 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	cd ../../stinger-master/stinger-master/build
	make -j6
	./bin/stinger_rmat_graph_generator -s 19 -e 16 -n 8380000 > ../../../graphtinker/make_cpu/rmat_500k_8M/st.log 2>&1 &
	RUN_ME_PID1A=$!
	echo "stinger_rmat_graph_generator process called : PID=$RUN_ME_PID1A"
	wait $RUN_ME_PID1A
	./bin/stinger_insert_remove_benchmark -n 8 -b 1048576 g.19.16.bin a.19.16.8380000.bin > ../../../graphtinker/make_cpu/rmat_500k_8M/stb.log 2>&1 &
	RUN_ME_PID2A=$!
	echo "stinger_insert_remove_benchmark process called : PID=$RUN_ME_PID2A"
	wait $RUN_ME_PID2A
	echo '*** finished! ***'
fi

if [ $rmat_1M_10M == $ON ] 
then
	echo '*** started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES ON ON OFF rmat64_1000192_10000000.edges DIRECTEDGRAPH 1000192 10000000 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	g++ -O3 -std=c++11 $TESTARG $GDSARG -fopenmp -o bmrktest.exe
	time ./bmrktest.exe > rmat_1M_10M/ll_on.log
	wait
	echo '*** finished! ***'
	rm -rf bmrktest.exe
	
	echo '*** started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES OFF ON OFF rmat64_1000192_10000000.edges DIRECTEDGRAPH 1000192 10000000 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	g++ -O3 -std=c++11 $TESTARG $GDSARG -fopenmp -o bmrktest.exe
	time ./bmrktest.exe > rmat_1M_10M/ll_off.log
	wait
	echo '*** finished! ***'
	rm -rf bmrktest.exe
	
	echo '*** started! ***'
	PYARG_BFS_FULLPROC="$NUM_CORES OFF OFF OFF rmat64_1000192_10000000.edges DIRECTEDGRAPH 1000192 10000000 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	cd ../../stinger-master/stinger-master/build
	make -j6
	./bin/stinger_rmat_graph_generator -s 20 -e 10 -n 10000000 > ../../../graphtinker/make_cpu/rmat_1M_10M/st.log 2>&1 &
	RUN_ME_PID1A=$!
	echo "stinger_rmat_graph_generator process called : PID=$RUN_ME_PID1A"
	wait $RUN_ME_PID1A
	./bin/stinger_insert_remove_benchmark -n 10 -b 1048576 g.20.10.bin a.20.10.10000000.bin > ../../../graphtinker/make_cpu/rmat_1M_10M/stb.log 2>&1 &
	RUN_ME_PID2A=$!
	echo "stinger_insert_remove_benchmark process called : PID=$RUN_ME_PID2A"
	wait $RUN_ME_PID2A
	echo '*** finished! ***'
fi

if [ $rmat_1M_16M == $ON ] 
then 
	echo '*** started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES ON ON OFF rmat16_1048576_15700000.edges DIRECTEDGRAPH 1048576 15700000 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	g++ -O3 -std=c++11 $TESTARG $GDSARG -fopenmp -o bmrktest.exe
	time ./bmrktest.exe > rmat_1M_16M/ll_on.log
	wait
	echo '*** finished! ***'
	rm -rf bmrktest.exe
	
	echo '*** started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES OFF ON OFF rmat16_1048576_15700000.edges DIRECTEDGRAPH 1048576 15700000 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	g++ -O3 -std=c++11 $TESTARG $GDSARG -fopenmp -o bmrktest.exe
	time ./bmrktest.exe > rmat_1M_16M/ll_off.log
	wait
	echo '*** finished! ***'
	rm -rf bmrktest.exe
	
	echo '*** started! ***'
	PYARG_BFS_FULLPROC="$NUM_CORES OFF OFF OFF rmat16_1048576_15700000.edges DIRECTEDGRAPH 1048576 15700000 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	cd ../../stinger-master/stinger-master/build
	make -j6
	./bin/stinger_rmat_graph_generator -s 20 -e 16 -n 16777216 > ../../../graphtinker/make_cpu/rmat_1M_16M/st.log 2>&1 &
	RUN_ME_PID1A=$!
	echo "stinger_rmat_graph_generator process called : PID=$RUN_ME_PID1A"
	wait $RUN_ME_PID1A
	./bin/stinger_insert_remove_benchmark -n 16 -b 1048576 g.20.16.bin a.20.16.16777216.bin > ../../../graphtinker/make_cpu/rmat_1M_16M/stb.log 2>&1 &
	RUN_ME_PID2A=$!
	echo "stinger_insert_remove_benchmark process called : PID=$RUN_ME_PID2A"
	wait $RUN_ME_PID2A
	echo '*** finished! ***'
fi

if [ $rmat_2M_32M == $ON ] 
then 
	echo '*** started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES ON ON OFF rmat16_2097152_31770000.edges DIRECTEDGRAPH 2097152 31770000 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	g++ -O3 -std=c++11 $TESTARG $GDSARG -fopenmp -o bmrktest.exe
	time ./bmrktest.exe > rmat_2M_32M/ll_on.log
	wait
	echo '*** finished! ***'
	rm -rf bmrktest.exe
	
	echo '*** started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES OFF ON OFF rmat16_2097152_31770000.edges DIRECTEDGRAPH 2097152 31770000 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	g++ -O3 -std=c++11 $TESTARG $GDSARG -fopenmp -o bmrktest.exe
	time ./bmrktest.exe > rmat_2M_32M/ll_off.log
	wait
	echo '*** finished! ***'
	rm -rf bmrktest.exe
	
	echo '*** deletion rate 0 - started! ***'
	PYARG_BFS_FULLPROC="$NUM_CORES OFF OFF OFF rmat16_2097152_31770000.edges DIRECTEDGRAPH 2097152 31770000 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	cd ../../stinger-master/stinger-master/build
	make -j6
	./bin/stinger_rmat_graph_generator -s 21 -e 16 -n 33554432 > ../../../graphtinker/make_cpu/rmat_2M_32M/st.log 2>&1 &
	RUN_ME_PID1A=$!
	echo "stinger_rmat_graph_generator process called : PID=$RUN_ME_PID1A"
	wait $RUN_ME_PID1A
	./bin/stinger_insert_remove_benchmark -n 32 -b 1048576 g.21.16.bin a.21.16.33554432.bin > ../../../graphtinker/make_cpu/rmat_2M_32M/stb.log 2>&1 &
	RUN_ME_PID2A=$!
	echo "stinger_insert_remove_benchmark process called : PID=$RUN_ME_PID2A"
	wait $RUN_ME_PID2A
	echo '*** deletion rate 0 - successful! ***'
fi

if [ $hollywood == $ON ] 
then 
	echo '*** started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES ON ON OFF hollywood-2009.edges UNDIRECTEDGRAPH 1139905 57515616 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	g++ -O3 -std=c++11 $TESTARG $GDSARG -fopenmp -o bmrktest.exe
	time ./bmrktest.exe > hollywood/ll_on.log
	wait
	echo '*** finished! ***'
	rm -rf bmrktest.exe
	
	echo '*** started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES OFF ON OFF hollywood-2009.edges UNDIRECTEDGRAPH 1139905 57515616 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	g++ -O3 -std=c++11 $TESTARG $GDSARG -fopenmp -o bmrktest.exe
	time ./bmrktest.exe > hollywood/ll_off.log
	wait
	echo '*** finished! ***'
	rm -rf bmrktest.exe
	
	echo '*** stinger started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES OFF OFF OFF hollywood-2009.edges UNDIRECTEDGRAPH 1139905 57515616 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	cd ../../stinger-master/stinger-master/build
	make -j6
	./bin/stinger_rmat_graph_generator -s 21 -e 28 -n 58720256 > ../../../graphtinker/make_cpu/hollywood/st.log 2>&1 &
	RUN_ME_PID1A=$!
	echo "stinger_rmat_graph_generator process called : PID=$RUN_ME_PID1A"
	wait $RUN_ME_PID1A
	./bin/stinger_insert_remove_benchmark -n 58 -b 1048576 g.21.28.bin a.21.28.58720256.bin > ../../../graphtinker/make_cpu/hollywood/stb.log 2>&1 &
	RUN_ME_PID2A=$!
	echo "stinger_insert_remove_benchmark process called : PID=$RUN_ME_PID2A"
	wait $RUN_ME_PID2A
	echo '*** stinger finished! ***'	
fi

if [ $kron == $ON ] 
then 
	echo '*** started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES ON ON OFF kron_g500-logn21.edges UNDIRECTEDGRAPH 2097153 91042010 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	g++ -O3 -std=c++11 $TESTARG $GDSARG -fopenmp -o bmrktest.exe
	time ./bmrktest.exe > kron/ll_on.log
	wait
	echo '*** finished! ***'
	rm -rf bmrktest.exe
	
	echo '*** started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES OFF ON OFF kron_g500-logn21.edges UNDIRECTEDGRAPH 2097153 91042010 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	g++ -O3 -std=c++11 $TESTARG $GDSARG -fopenmp -o bmrktest.exe
	time ./bmrktest.exe > kron/ll_off.log
	wait
	echo '*** finished! ***'
	rm -rf bmrktest.exe
	
	echo '*** stinger started! ***'
	INSERTIONRATE="1"
	DELETIONRATE="0"
	DELETIONTYPE="DELETEEDGE"
	PYARG_BFS_FULLPROC="$NUM_CORES OFF OFF OFF kron_g500-logn21.edges UNDIRECTEDGRAPH 2097153 91042010 4 8 64 1048576 $INSERTIONRATE $DELETIONTYPE $DELETIONRATE 0 0"
	PYARG_BFS=$PYARG_BFS_FULLPROC
	python gen.py $PYARG_BFS
	cd ../../stinger-master/stinger-master/build
	make -j6
	./bin/stinger_rmat_graph_generator -s 21 -e 45 -n 94371840 > ../../../graphtinker/make_cpu/kron/st.log 2>&1 &
	RUN_ME_PID1A=$!
	echo "stinger_rmat_graph_generator process called : PID=$RUN_ME_PID1A"
	wait $RUN_ME_PID1A
	./bin/stinger_insert_remove_benchmark -n 94 -b 1048576 g.21.45.bin a.21.45.94371840.bin > ../../../graphtinker/make_cpu/kron/stb.log 2>&1 &
	RUN_ME_PID2A=$!
	echo "stinger_insert_remove_benchmark process called : PID=$RUN_ME_PID2A"
	wait $RUN_ME_PID2A
	echo '*** stinger finished! ***'
fi
