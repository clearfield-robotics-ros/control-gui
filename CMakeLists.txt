cmake_minimum_required(VERSION 2.8.3)
project(control_gui)

if("$ENV{ROS_DISTRO}" STRGREATER "jade")
  set(USE_QT5 true)
else()
  set(USE_QT5 false)
endif()

find_package(catkin REQUIRED COMPONENTS roscpp rqt_gui rqt_gui_cpp image_transport cv_bridge std_msgs)
find_package(OpenCV REQUIRED)


if(${USE_QT5})
  # Autogenerate the MOC files
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOINC ON)

  # Tell catkin where to look for the moc files
  set(CMAKE_INCLUDE_CURRENT_DIR ON)

  # Get the Qt components
  find_package(Qt5Widgets REQUIRED Core Widgets)
  set(QT_LIBRARIES Qt5::Widgets)
else()
  find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
  include(${QT_USE_FILE})
endif()

set(control_gui_SRCS
  src/control_gui.cpp
  src/clicklabel.cpp
)

set(control_gui_HDRS
  include/control_gui.h
  include/clicklabel.h
)

set(control_gui_UIS
  resource/control_gui.ui
)

set(control_gui_INCLUDE_DIRECTORIES
  include
  ${CMAKE_CURRENT_BINARY_DIR}
)

catkin_package(
  INCLUDE_DIRS ${control_gui_INCLUDE_DIRECTORIES}
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp rqt_gui rqt_gui_cpp  std_msgs
)

if(${USE_QT5})
  qt5_wrap_cpp(control_gui_MOCS ${control_gui_HDRS})
  qt5_wrap_ui(control_gui_UIS_H ${control_gui_UIS})
  qt5_add_resources(control_gui_RESOURCE resource/mc_resources.qrc)
  include_directories(
    ${control_gui_INCLUDE_DIRECTORIES}
    ${catkin_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDES}
    ${OpenCV_INCLUDE_DIRS})
  add_definitions(${Qt5Widgets_DEFINITIONS})
else()
  qt4_wrap_cpp(control_gui_MOCS ${control_gui_HDRS})
  qt4_wrap_ui(control_gui_UIS_H ${control_gui_UIS})
  qt4_add_resources(control_gui_RESOURCE resource/mc_resources.qrc)
  include_directories(
    ${control_gui_INCLUDE_DIRECTORIES}
    ${catkin_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS})
endif()

add_library(
  ${PROJECT_NAME}
  ${control_gui_SRCS}
  ${control_gui_MOCS}
  ${control_gui_UIS_H}
  ${control_gui_RESOURCE}
)


if(${USE_QT5})

  target_link_libraries(
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${QT_QTCORE_LIBRARY}
    ${QT_LIBRARIES}
    ${OpenCV_LIBRARIES})
else()
  target_link_libraries(
    ${PROJECT_NAME}
    ${catkin_LIBRARIES}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${OpenCV_LIBRARIES})
endif()

add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})

find_package(class_loader)
class_loader_hide_library_symbols(${PROJECT_NAME}) 

install(FILES plugin.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

set_target_properties(
  control_gui
    PROPERTIES
    COMPILE_FLAGS
      "-std=c++11")
