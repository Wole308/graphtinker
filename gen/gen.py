import argparse
import xml.etree.ElementTree as ET
import os
from jinja2 import Environment, FileSystemLoader
import math
import sys

context = {}
print('number of arguments : ' + str(len(sys.argv)))

#### system variables
context['NUM_CORES'] = int(sys.argv[1])
context['LLFULLDB'] = sys.argv[2]
context['CRUMPLEINONDELETE'] = sys.argv[3]
context['WORK_BLOCK_HEIGHT'] = int(sys.argv[4])

print ('GraphTinker configured parameters (Courtesy: Jinja 2.0)...')
print ('NUM_CORES: ' + str(context['NUM_CORES']))
print ('LLFULLDB: ' + str(context['LLFULLDB']))
print ('CRUMPLEINONDELETE: ' + str(context['CRUMPLEINONDELETE']))
print ('WORK_BLOCK_HEIGHT: ' + str(context['WORK_BLOCK_HEIGHT']))
	
#================================
o_path0="../tests/updates_test.cpp"
o_path1="../tests/updates_test.cpp"
o_path2="../tests/updates_test.cpp"
o_path3="../tests/updates_test.cpp"

o_path10="../vertices/vertices.cpp"
o_path11="../vertices/vertices.h"
o_path12="../vertices/vertices.cpp"
o_path13="../vertices/vertices.cpp"

o_path20="../common/common.h"
o_path21="../vertices/vertices.cpp"
o_path22="../vertices/vertices.cpp"
o_path23="../vertices/vertices.cpp"
o_path24="../vertices/vertices.cpp"
o_path25="../vertices/vertices.cpp" 
o_path26="../vertices/vertices.cpp"
o_path27="../vertices/vertices.cpp"
o_path28="../vertices/vertices.cpp"

o_path30="../graphtinker/compute_unit.cpp"
o_path31="../graphtinker/find_margin.cpp" 
o_path32="../graphtinker/find_unit.cpp" 
o_path33="../graphtinker/graphtinker.cpp" 
o_path34="../graphtinker/hash_gen.cpp"
o_path35="../graphtinker/inference_unit.cpp" 
o_path36="../graphtinker/init.cpp" 
o_path37="../graphtinker/insert_unit.cpp" 
o_path38="../graphtinker/interval_unit.cpp"
o_path39="../graphtinker/ll_functions.cpp" 
o_path40="../graphtinker/load_params.cpp" 
o_path41="../graphtinker/load_unit.cpp" 
o_path42="../graphtinker/print.cpp" 
o_path43="../graphtinker/supervs.cpp" 
o_path44="../graphtinker/utility.cpp" 
o_path45="../graphtinker/writeback_unit.cpp"
o_path46="../graphtinker/deleteandcrumplein_unit.cpp" 
o_path47="../graphtinker/ll_unit.cpp" 

o_path200="../graphtinker/graphtinker.h" 
o_path201="../graphtinker/graphtinker.h" 
o_path202="../graphtinker/graphtinker.h"

out_path0=os.path.abspath(o_path0)
out_path1=os.path.abspath(o_path1)
out_path2=os.path.abspath(o_path2)
out_path3=os.path.abspath(o_path3)

out_path10=os.path.abspath(o_path10)
out_path11=os.path.abspath(o_path11)
out_path12=os.path.abspath(o_path12)
out_path13=os.path.abspath(o_path13)

out_path20=os.path.abspath(o_path20)
out_path21=os.path.abspath(o_path21)
out_path22=os.path.abspath(o_path22)
out_path23=os.path.abspath(o_path23)
out_path24=os.path.abspath(o_path24)
out_path25=os.path.abspath(o_path25)
out_path26=os.path.abspath(o_path26)
out_path27=os.path.abspath(o_path27)
out_path28=os.path.abspath(o_path28)

out_path30=os.path.abspath(o_path30)
out_path31=os.path.abspath(o_path31)
out_path32=os.path.abspath(o_path32)
out_path33=os.path.abspath(o_path33)
out_path34=os.path.abspath(o_path34)
out_path35=os.path.abspath(o_path35)
out_path36=os.path.abspath(o_path36)
out_path37=os.path.abspath(o_path37)
out_path38=os.path.abspath(o_path38)
out_path39=os.path.abspath(o_path39)
out_path40=os.path.abspath(o_path40)
out_path41=os.path.abspath(o_path41)
out_path42=os.path.abspath(o_path42)
out_path43=os.path.abspath(o_path43)
out_path44=os.path.abspath(o_path44)
out_path45=os.path.abspath(o_path45)
out_path46=os.path.abspath(o_path46)
out_path47=os.path.abspath(o_path47)

out_path200=os.path.abspath(o_path200)
out_path201=os.path.abspath(o_path201)
out_path202=os.path.abspath(o_path202)

templ_path0="../tests/"
templ_path1="../tests/"
templ_path2="../tests/"
templ_path3="../tests/"

templ_path10="../vertices/" 
templ_path11="../vertices/" 
templ_path12="../vertices/" 
templ_path13="../vertices/" 

templ_path20="../common/"
templ_path21="../vertices/"
templ_path22="../vertices/"
templ_path23="../vertices/"
templ_path24="../vertices/" 
templ_path25="../vertices/" 
templ_path26="../vertices/"
templ_path27="../vertices"
templ_path28="../vertices/"

templ_path30="../graphtinker/" 
templ_path31="../graphtinker/" 
templ_path32="../graphtinker/" 
templ_path33="../graphtinker/" 
templ_path34="../graphtinker/"
templ_path35="../graphtinker/" 
templ_path36="../graphtinker/" 
templ_path37="../graphtinker/" 
templ_path38="../graphtinker/"
templ_path39="../graphtinker/" 
templ_path40="../graphtinker/" 
templ_path41="../graphtinker/" 
templ_path42="../graphtinker/" 
templ_path43="../graphtinker/" 
templ_path44="../graphtinker/" 
templ_path45="../graphtinker/" 
templ_path46="../graphtinker/" 
templ_path47="../graphtinker/" 

templ_path200="../graphtinker/" 
templ_path201="../graphtinker/" 
templ_path202="../graphtinker/"

#####################
### System parameters (gds main)

#####################
### System parameters (gds LL)
context['LVACOARSENESSWIDTH'] = 2048
context['LLEDGEBLOCKSIZE'] = 512
		
#####################
### Sequencers
context['NUM_CORES_seq'] = []
for i in range (1,(context['NUM_CORES']+1)):
		context['NUM_CORES_seq'].append(i)

#=========================
#=== all templates ===
env0 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path0)), trim_blocks=True, lstrip_blocks=True)
env1 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path1)), trim_blocks=True, lstrip_blocks=True)
env2 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path2)), trim_blocks=True, lstrip_blocks=True)
env3 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path3)), trim_blocks=True, lstrip_blocks=True)

env10 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path10)), trim_blocks=True, lstrip_blocks=True)
env11 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path11)), trim_blocks=True, lstrip_blocks=True)
env12 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path12)), trim_blocks=True, lstrip_blocks=True)
env13 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path13)), trim_blocks=True, lstrip_blocks=True)

env20 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path20)), trim_blocks=True, lstrip_blocks=True)
env21 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path21)), trim_blocks=True, lstrip_blocks=True)
env22 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path22)), trim_blocks=True, lstrip_blocks=True)
env23 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path23)), trim_blocks=True, lstrip_blocks=True)
env24 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path24)), trim_blocks=True, lstrip_blocks=True)
env25 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path25)), trim_blocks=True, lstrip_blocks=True)
env26 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path26)), trim_blocks=True, lstrip_blocks=True)
env27 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path27)), trim_blocks=True, lstrip_blocks=True)
env28 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path28)), trim_blocks=True, lstrip_blocks=True)

env30 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path30)), trim_blocks=True, lstrip_blocks=True)
env31 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path31)), trim_blocks=True, lstrip_blocks=True)
env32 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path32)), trim_blocks=True, lstrip_blocks=True)
env33 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path33)), trim_blocks=True, lstrip_blocks=True)
env34 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path34)), trim_blocks=True, lstrip_blocks=True)
env35 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path35)), trim_blocks=True, lstrip_blocks=True)
env36 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path36)), trim_blocks=True, lstrip_blocks=True)
env37 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path37)), trim_blocks=True, lstrip_blocks=True)
env38 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path38)), trim_blocks=True, lstrip_blocks=True)
env39 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path39)), trim_blocks=True, lstrip_blocks=True)
env40 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path40)), trim_blocks=True, lstrip_blocks=True)
env41 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path41)), trim_blocks=True, lstrip_blocks=True)
env42 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path42)), trim_blocks=True, lstrip_blocks=True)
env43 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path43)), trim_blocks=True, lstrip_blocks=True)
env44 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path44)), trim_blocks=True, lstrip_blocks=True)
env45 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path45)), trim_blocks=True, lstrip_blocks=True)
env46 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path46)), trim_blocks=True, lstrip_blocks=True)
env47 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path47)), trim_blocks=True, lstrip_blocks=True)

env200 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path200)), trim_blocks=True, lstrip_blocks=True)
env201 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path201)), trim_blocks=True, lstrip_blocks=True)
env202 = Environment(loader=FileSystemLoader(os.path.abspath(templ_path202)), trim_blocks=True, lstrip_blocks=True)

env0.globals.update(zip=zip)
env1.globals.update(zip=zip)
env2.globals.update(zip=zip)
env3.globals.update(zip=zip)

env10.globals.update(zip=zip)
env11.globals.update(zip=zip)
env12.globals.update(zip=zip)
env13.globals.update(zip=zip)

env20.globals.update(zip=zip)
env21.globals.update(zip=zip)
env22.globals.update(zip=zip)
env23.globals.update(zip=zip)
env24.globals.update(zip=zip)
env25.globals.update(zip=zip)
env26.globals.update(zip=zip)
env27.globals.update(zip=zip)
env28.globals.update(zip=zip)

env30.globals.update(zip=zip)
env31.globals.update(zip=zip)
env32.globals.update(zip=zip)
env33.globals.update(zip=zip)
env34.globals.update(zip=zip)
env35.globals.update(zip=zip)
env36.globals.update(zip=zip)
env37.globals.update(zip=zip)
env38.globals.update(zip=zip)
env39.globals.update(zip=zip)
env40.globals.update(zip=zip)
env41.globals.update(zip=zip)
env42.globals.update(zip=zip)
env43.globals.update(zip=zip)
env44.globals.update(zip=zip)
env45.globals.update(zip=zip)
env46.globals.update(zip=zip)
env47.globals.update(zip=zip)

env200.globals.update(zip=zip)
env201.globals.update(zip=zip)
env202.globals.update(zip=zip)

template0 = env0.get_template('updates_test.template')
template1 = env1.get_template('updates_test.template')
template2 = env2.get_template('updates_test.template')
template3 = env3.get_template('updates_test.template')

template10 = env10.get_template('vertices.template') 
template11 = env11.get_template('vertices_h.template') 
template12 = env12.get_template('vertices.template') 
template13 = env13.get_template('vertices.template') 

template20 = env20.get_template('common_h.template')
template21 = env21.get_template('vertices.template')
template22 = env22.get_template('vertices.template')
template23 = env23.get_template('vertices.template') 
template24 = env24.get_template('vertices.template') 
template25 = env25.get_template('vertices.template')
template26 = env26.get_template('vertices.template')
template27 = env27.get_template('vertices.template')
template28 = env28.get_template('vertices.template')

template30 = env30.get_template('compute_unit.template') 
template31 = env31.get_template('find_margin.template') 
template32 = env32.get_template('find_unit.template') 
template33 = env33.get_template('graphtinker.template') 
template34 = env34.get_template('hash_gen.template')
template35 = env35.get_template('inference_unit.template') 
template36 = env36.get_template('init.template') 
template37 = env37.get_template('insert_unit.template') 
template38 = env38.get_template('interval_unit.template')
template39 = env39.get_template('ll_functions.template') 
template40 = env40.get_template('load_params.template') 
template41 = env41.get_template('load_unit.template') 
template42 = env42.get_template('print.template') 
template43 = env43.get_template('supervs.template') 
template44 = env44.get_template('utility.template') 
template45 = env45.get_template('writeback_unit.template') 
template46 = env46.get_template('deleteandcrumplein_unit.template')
template47 = env47.get_template('ll_unit.template')

template200 = env200.get_template('graphtinker_h.template') 
template201 = env201.get_template('graphtinker_h.template') 
template202 = env202.get_template('graphtinker_h.template')

# Render the template for the output file.
rendered_file0 = template0.render(context=context)
rendered_file1 = template1.render(context=context)
rendered_file2 = template2.render(context=context)
rendered_file3 = template3.render(context=context)

rendered_file10 = template10.render(context=context)
rendered_file11 = template11.render(context=context)
rendered_file12 = template12.render(context=context)
rendered_file13 = template13.render(context=context)

rendered_file20 = template20.render(context=context)
rendered_file21 = template21.render(context=context)
rendered_file22 = template22.render(context=context)
rendered_file23 = template23.render(context=context)
rendered_file24 = template24.render(context=context)
rendered_file25 = template25.render(context=context)
rendered_file26 = template26.render(context=context)
rendered_file27 = template27.render(context=context)
rendered_file28 = template28.render(context=context)

rendered_file30 = template30.render(context=context)
rendered_file31 = template31.render(context=context)
rendered_file32 = template32.render(context=context)
rendered_file33 = template33.render(context=context)
rendered_file34 = template34.render(context=context)
rendered_file35 = template35.render(context=context)
rendered_file36 = template36.render(context=context)
rendered_file37 = template37.render(context=context)
rendered_file38 = template38.render(context=context)
rendered_file39 = template39.render(context=context)
rendered_file40 = template40.render(context=context)
rendered_file41 = template41.render(context=context)
rendered_file42 = template42.render(context=context)
rendered_file43 = template43.render(context=context)
rendered_file44 = template44.render(context=context)
rendered_file45 = template45.render(context=context)
rendered_file46 = template46.render(context=context)
rendered_file47 = template47.render(context=context)

rendered_file200 = template200.render(context=context)
rendered_file201 = template201.render(context=context)
rendered_file202 = template202.render(context=context)

# Write output file
with open(out_path0, 'w') as outFile0:
	outFile0.write(rendered_file0)
with open(out_path1, 'w') as outFile1:
	outFile1.write(rendered_file1)
with open(out_path2, 'w') as outFile2:
	outFile2.write(rendered_file2)
with open(out_path3, 'w') as outFile3:
	outFile3.write(rendered_file3)
	
with open(out_path10, 'w') as outFile10:
	outFile10.write(rendered_file10)
with open(out_path11, 'w') as outFile11:
	outFile11.write(rendered_file11)
with open(out_path12, 'w') as outFile12:
	outFile12.write(rendered_file12)
with open(out_path13, 'w') as outFile13:
	outFile13.write(rendered_file13)
	
with open(out_path20, 'w') as outFile20:
	outFile20.write(rendered_file20)
with open(out_path21, 'w') as outFile21:
	outFile21.write(rendered_file21)
with open(out_path22, 'w') as outFile22:
	outFile22.write(rendered_file22)
with open(out_path23, 'w') as outFile23:
	outFile23.write(rendered_file23)
with open(out_path24, 'w') as outFile24:
	outFile24.write(rendered_file24)
with open(out_path25, 'w') as outFile25:
	outFile25.write(rendered_file25)
with open(out_path26, 'w') as outFile26:
	outFile26.write(rendered_file26)
with open(out_path27, 'w') as outFile27:
	outFile27.write(rendered_file27)
with open(out_path28, 'w') as outFile28:
	outFile28.write(rendered_file28)
	
with open(out_path30, 'w') as outFile30:
	outFile30.write(rendered_file30)
with open(out_path31, 'w') as outFile31:
	outFile31.write(rendered_file31)
with open(out_path32, 'w') as outFile32:
	outFile32.write(rendered_file32)
with open(out_path33, 'w') as outFile33:
	outFile33.write(rendered_file33)
with open(out_path34, 'w') as outFile34:
	outFile34.write(rendered_file34)
with open(out_path35, 'w') as outFile35:
	outFile35.write(rendered_file35)
with open(out_path36, 'w') as outFile36:
	outFile36.write(rendered_file36)
with open(out_path37, 'w') as outFile37:
	outFile37.write(rendered_file37)
with open(out_path38, 'w') as outFile38:
	outFile38.write(rendered_file38)
with open(out_path39, 'w') as outFile39:
	outFile39.write(rendered_file39)	
with open(out_path40, 'w') as outFile40:
	outFile40.write(rendered_file40)
with open(out_path41, 'w') as outFile41:
	outFile41.write(rendered_file41)
with open(out_path42, 'w') as outFile42:
	outFile42.write(rendered_file42)
with open(out_path43, 'w') as outFile43:
	outFile43.write(rendered_file43)
with open(out_path44, 'w') as outFile44:
	outFile44.write(rendered_file44)
with open(out_path45, 'w') as outFile45:
	outFile45.write(rendered_file45)
with open(out_path46, 'w') as outFile46:
	outFile46.write(rendered_file46)
with open(out_path47, 'w') as outFile47:
	outFile47.write(rendered_file47)
	
with open(out_path200, 'w') as outFile200:
	outFile200.write(rendered_file200)
with open(out_path201, 'w') as outFile201:
	outFile201.write(rendered_file201)
with open(out_path202, 'w') as outFile202:
	outFile202.write(rendered_file202)

print ("successful!")
print ("...")


