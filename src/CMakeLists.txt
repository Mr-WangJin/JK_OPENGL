

#FILE(GLOB common_src_files ./common/*.*)
#FILE(GLOB common_src_files ./common/*.cpp)
#SET(COMMON_LIST
#	${common_src_files}
#	${PROJECT_SOURCE_DIR}/src/common/jk_arcball.h
#	${PROJECT_SOURCE_DIR}/src/common/jk_arcball.cpp
#	${PROJECT_SOURCE_DIR}/src/common/jk_scene.h
#	${PROJECT_SOURCE_DIR}/src/common/tinycthread.h
#	${PROJECT_SOURCE_DIR}/src/common/tinycthread.c
#	${PROJECT_SOURCE_DIR}/src/common/jk_glsl_prog.h
#	${PROJECT_SOURCE_DIR}/src/common/jk_glsl_prog.cpp
#	${PROJECT_SOURCE_DIR}/src/common/jk_ogl.h
#)
#SOURCE_GROUP(common FILES ${COMMON_LIST})


INCLUDE_DIRECTORIES($ENV{GLM_HOME}/include)

IF(BUILD_DYNAMIC)

MACRO(START_EXAMPLE)

    INCLUDE_DIRECTORIES($ENV{GLFW_HOME}/include)
	LINK_DIRECTORIES($ENV{GLFW_HOME}/lib)
	INCLUDE_DIRECTORIES($ENV{GLEW_HOME}/include)
	LINK_DIRECTORIES($ENV{GLEW_HOME}/lib/Release/Win32)
	
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/ingredients)
	LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH}/Debug/)

	
	FILE(GLOB source_file_list ${PROJECT_NAME}/*.cpp)
	FILE(GLOB header_file_list ${PROJECT_NAME}/*.h)
	MESSAGE(STATUS  ${PROJECT_NAME}-"this is source file list: " ${source_file_list})
	
	SET(file_list 
	${source_file_list}
	${header_file_list}
	#${COMMON_LIST}
	)

	ADD_EXECUTABLE(${PROJECT_NAME} ${file_list})
IF(WIN32)
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
		debug glfw3.lib optimized glfw3.lib
		debug glew32s.lib optimized glew32s.lib
		debug opengl32.lib optimized opengl32.lib
		debug glu32.lib optimized glu32.lib
		debug ingredientsd.lib optimized ingredients.lib
	)
ENDIF(WIN32)
if(UNIX)
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
		debug glfw3.so optimized glfw3.so

	)
ENDIF(UNIX)

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shader DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
ENDMACRO(START_EXAMPLE)

#MESSAGE(STATUS "This is additionan include path" ${CMAKE_INCLUDE_PATH})

ADD_SUBDIRECTORY(ingredients)

SET(PROJECT_NAME "fire")
START_EXAMPLE()

#SET(PROJECT_NAME "cloud")
#START_EXAMPLE()

#SET(PROJECT_NAME "octree")
#START_EXAMPLE()

SET(PROJECT_NAME "temp")
START_EXAMPLE()

ENDIF()

