@echo off
cython.py cmodel.pyx
cl cmodel.c /LD /O2 /Ot /Ox /Fecmodel.pyd python27.lib opengl32.lib