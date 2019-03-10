GraphTinker : A Data Structure for Dynamic Graph Processing
===================

This project is designed to be used with dynamic graph frameworks.

Dependencies
----------------
+ Jinja 2.0 (template generator engine)

Quick Start
-----------

Build the project:

    $ make

Test the build:

    $ make test

Run analytics on our hybrid engine (e.g. BFS):

    $ .... (not yet added)


Quick Notes
-------------

Jinja first generates the source code that corresponds to your given input parameters, before the compiler compiles the project to give the binary executable.


Features
-----------------------

+ Coarsed Adjacency List (CAL) - this maintains a highly compacted form of the graph for use in the hybrid mode of our hybrid engine (can be switched on or off in the makefile)
+ Scatter-Gather Hashing (SGH) - this allows hashing of edges before updating the underlying dynamic graph. This is to maintain a compact data structure in every stage of the dynamic graph's lifetime (can be switched on or off in the makefile)
+ Delete-only mechanism, where edges are deleted without crumpling-in the data structure
+ Delete-and-crumple-in mechanism, where edges are deleted and the data structure is crumpled in for each deletion. From our paper (GraphTinker), this feature has low overhead and allows minimum performance degradation when many edges are deleted
+ Other adjustable parameters of GraphTinker are WORKBLOCK size, SUBBLOCK size and PAGEWIDTH. Feel free to adjust this to suit your data structure requirements. Our paper shows a WORKBLOCK size, SUBBLOCK size and PAGEWIDTH of 4, 8 and 64 allow optimal updates/analytics performance


How to Cite
-----------

Please cite this code by the benchmark specification:

(not yet added)
