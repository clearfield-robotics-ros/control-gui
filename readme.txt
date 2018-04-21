Ros Gui Template
================

This package is designed to get you started creating GUIs in ROS with C++.
If you want to use Python, check out the ROS tutorials.

Basic instructions:
==================
Put the ros_gui_template folder in the src folder of whatever package you want
to add a gui to.  For instance, you could put it inside of
~/nimbus_asctec/src/nimbus_asctec/ along with all the other packages in 
there.

Now go back to ~/nimbus_asctec (or whatever your root catkin workspace is)
and run catkin_make.  If you've already built you project once, then you'll
probably just see it build the ros_gui_template.  Once that's done, you should
be able to run the following: 
roslaunch ros_gui_template ros_gui_template.launch

You should eventually see a window pop open that has a label across the top
that says "Ros Gui Template."  If you do, then success!  Now the fun begins.

Obviously, you want your code in there.  With your file names and so on.  
So you'll need to make some changes to the files in your project.  Basically,
you're going to replace any instances of "ros_gui_template" and 
"RosGuiTemplate" with your own project name.  For tutorial purposes, we'll
use "your_project" and "YourProject."

Start with the folder that you just placed inside you project.  Rename it 
to your_project.  Now go into "your_project" and make the the following 
changes to the following files:

In the base directory where you see the CMakeLists.txt, package.xml,
plugin.xml, and so on...

CMakeLists.txt
===============
-Find and replace all instances of "ros_gui_template" with "your_project"

package.xml
===========
-Find and replace all instances of "ros_gui_template" with "your_project"
-Change the other tags as/if required.  Remember, ROS stuff will probably
change here as your project progresses.

plugin.xml
==========
-Change path="lib/libros_gui_template" to path="lib/libyour_project"
-Change class name="ros_gui_template/RosGuiTemplate" to class name="your_project/YourProject"
-Change type="ros_gui_template::RosGuiTemplate" to type="your_project::YourProject"
-Change the other stuff as/if needed

Rename ros_gui_template.launch to whatever-you-want.launch
==========================================================
-Find and replace all instances of "ros_gui_template" with "your_project"


In the include folder, rename "ros_gui_template.h" to "your_project.h"

your_project.h
==============
-Change the #ifndef and #define lines as you see fit
-Find and replace all instances of "ros_gui_template" with "your_project"
-Find and replace all instances of "RosGuiTemplate" with "YourProject"


In the src folder, rename "ros_gui_template.cpp" to "your_project.cpp"

your_project.cpp
================
-Find and replace all instances of "ros_gui_template" with "your_project"
-Find and replace all instances of "RosGuiTemplate" with "YourProject"

In the resource folder, rename "ros_gui_template.ui" to "your_project.ui"

your_project.ui
===============
-Find and replace all instances of "RosGuiTemplate" with "YourProject"

In the scripts folder, rename "ros_gui_template.py" to "your_project.py"
(make sure this file stays executable)

your_project.py
===============
-Find and replace all instances of "ros_gui_template" with "your_project"

Now go back to the root of your workspace and run catkin_make.  Hopefully,
everything will build and you'll be able to test your project with
roslaunch your_project whatever-you-want.launch

After you get that working, you'll be ready to use Qtcreator to get in there
and edit your UI and whatever else you need to do.  Remember, you need to 
source your deve/setup.bash and THEN launch qtcreator from that same command
line.  From there, you open a project and choose the CMakeLists.txt file in
your_project's directory (when package.xml is and so on).

If you're not a Qt expert, there are plenty of awesome tutorials on youtube
that will take you through the basics of creating buttons, assigning functions
to those buttons and so on.

Let me know if you need any help or if I should add stuff to this file.

--Adam
aplowcha@gmail.com


