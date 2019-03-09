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

Override the default C++ compiler:

    $ CXX=g++-7 make

Test the build:

    $ make test

Run analytics on our hybrid engine (e.g. BFS):

    $ .... (not yet added)


Quick Notes
-------------

Jinja first generates the source code that corresponds to your given input parameters, before the compiler compiles the project to give the binary executable.


Features
-----------------------

+ delete-only mechanism, where edges are deleted without crumpling-in the data structure
+ delete-and-crumple-in mechanism, where edges are deleted and the data structure is crumpled in for each deletion. From our paper (GraphTinker), this feature has low overhead and allows minimum performance degradation when many edges are deleted
+ coarsed


How to Cite
-----------

Please cite this code by the benchmark specification:

(not yet added)
