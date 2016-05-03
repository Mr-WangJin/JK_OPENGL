SET(PROJECT_NAME "wave")

	INCLUDE_DIRECTORIES($ENV{GLFW_HOME}/include)
	LINK_DIRECTORIES($ENV{GLFW_HOME}/lib)
	INCLUDE_DIRECTORIES($ENV{GLEW_HOME}/include)
	LINK_DIRECTORIES($ENV{GLEW_HOME}/lib/Release/Win32)
	
	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/ingredients)
	LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH}/Debug/)

	SET(COMMON_LIST
	gerstner.cpp
	gerstner.h
	)
	SOURCE_GROUP(Gerstner FILES ${COMMON_LIST})
	
	FILE(GLOB source_file_list *.cpp)
	FILE(GLOB header_file_list *.h)
	MESSAGE(STATUS  ${PROJECT_NAME}-"this is source file list: " ${source_file_list})
	
	SET(file_list 
	${source_file_list}
	${header_file_list}
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
