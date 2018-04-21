#!/usr/bin/python

#Automatically rename this project
#to what you want
#
#Adam Plowcha
#28 Feb 2017

import sys
import os
import fileinput
import shutil

if (len(sys.argv) != 3):
	print 'Usage: ./create_gui.py <your_project> <YourClass>'
	print '-------'
	print 'Example: ./create_gui.py spinning_flyer SpinningFlyer'
else:
	#go through and rename directories, files, and change file contents
	newProj = str(sys.argv[1])
	newClass = str(sys.argv[2])
	currentDir = os.getcwd()

	print ' '
	print 'Creating project: ', newProj
	print 'with class: ', newClass
	print '================================='
	print ' '

	# CMakeLists.txt
	# ==============
	print 'Opening CMakeLists.txt...'

	with open('CMakeLists.txt', 'r') as file:
		filedata = file.read()
	filedata = filedata.replace('ros_gui_template', newProj)
	with open('CMakeLists.txt', 'w') as file:
		file.write(filedata)

	print 'Replaced all instances of ros_gui_template with ', newProj
	print ' '

	# package.xml
	# ===========
	print 'Opening package.xml...'

	with open('package.xml', 'r') as file:
		filedata = file.read()
	filedata = filedata.replace('ros_gui_template', newProj)
	with open('package.xml', 'w') as file:
		file.write(filedata)

	print 'Replaced all instances of ros_gui_template with ', newProj
	print ' '

	# plugin.xml
	# ===========
	print 'Opening plugin.xml...'

	with open('plugin.xml', 'r') as file:
		filedata = file.read()
	filedata = filedata.replace('ros_gui_template', newProj)
	filedata = filedata.replace('RosGuiTemplate', newClass)
	with open('plugin.xml', 'w') as file:
		file.write(filedata)

	print 'Replaced all instances of ros_gui_template with ', newProj
	print 'Replaced all instances of RosGuiTemplate with ', newClass
	print ' '

	# ros_gui_template.launch
	# =======================
	os.rename('ros_gui_template.launch', newProj + '.launch')
	print 'Renamed ros_gui_template.launch to ', newProj + '.launch'

	print 'Opening ', newProj+'.launch'
	with open(newProj+'.launch', 'r') as file:
		filedata = file.read()
	filedata = filedata.replace('ros_gui_template', newProj)
	with open(newProj+'.launch', 'w') as file:
		file.write(filedata)

	print 'Replaced all instances of ros_gui_template with ', newProj
	
	print ' '

	# include/ros_gui_template.h
	# =======================
	os.rename('include/ros_gui_template.h', 'include/' + newProj + '.h')
	print 'Renamed include/ros_gui_template.h to include/' + newProj + '.h'

	print 'Opening include/' + newProj + '.h...'

	with open('include/'+ newProj + '.h', 'r') as file:
		filedata = file.read()
	filedata = filedata.replace('ros_gui_template', newProj)
	filedata = filedata.replace('RosGuiTemplate', newClass)
	with open('include/'+ newProj + '.h', 'w') as file:
		file.write(filedata)

	print 'Replaced all instances of ros_gui_template with ', newProj
	print 'Replaced all instances of RosGuiTemplate with ', newClass
	print ' '

	# src/ros_gui_template.cpp
	# ========================
	os.rename('src/ros_gui_template.cpp', 'src/' + newProj + '.cpp')
	print 'Renamed include/ros_gui_template.h to ', 'include/' + newProj + '.h'

	print 'Opening src/' + newProj + '.cpp...'

	with open('src/' + newProj + '.cpp', 'r') as file:
		filedata = file.read()
	filedata = filedata.replace('ros_gui_template', newProj)
	filedata = filedata.replace('RosGuiTemplate', newClass)
	with open('src/' + newProj + '.cpp', 'w') as file:
		file.write(filedata)

	print 'Replaced all instances of ros_gui_template with ', newProj
	print 'Replaced all instances of RosGuiTemplate with ', newClass
	print ' '

	# resource/ros_gui_template.ui
	# ============================
	os.rename('resource/ros_gui_template.ui', 'resource/' + newProj + '.ui')
	print 'Renamed resource/ros_gui_template.ui to resource/' + newProj + '.ui'

	print 'Opening resource/'+newProj+'.ui...'

	with open('resource/' + newProj + '.ui', 'r') as file:
		filedata = file.read()
	filedata = filedata.replace('RosGuiTemplate', newClass)
	with open('resource/' + newProj + '.ui', 'w') as file:
		file.write(filedata)

	print 'Replaced all instances of RosGuiTemplate with ', newClass
	print ' '

	# scripts/ros_gui_template.py
	# ============================
	os.rename('scripts/ros_gui_template.py', 'scripts/' + newProj + '.py')
	print 'Renamed scripts/ros_gui_template.py to scripts/' + newProj + '.py'

	print 'Opening scripts/' + newProj + '.py...'

	with open('scripts/' + newProj + '.py', 'r') as file:
		filedata = file.read()
	filedata = filedata.replace('ros_gui_template', newProj)
	with open('scripts/' + newProj + '.py', 'w') as file:
		file.write(filedata)

	print 'Replaced all instances of ros_gui_template with ', newProj
	print ' '

	# Remove subversion info
	if (os.path.isfile('CMakeLists.txt')): #verify we're in right dir
		shutil.rmtree('.svn', ignore_errors=True)
		print 'Removed Subversion info.'
		print ' '

	print 'Project created.'
	print '================================'
	print ' '
	
		



