
	#FILE(GLOB source_file_list_CPP *.cpp)
	#FILE(GLOB source_file_list_C *.c)
	#FILE(GLOB header_file_list *.h)
set( ingredients_SOURCES
	vboteapotpatch.h
	vboteapot.h
	drawable.h 
	vbomeshadj.h 
	vbotorus.h 
	glutils.h 
	vbomesh.h 
	glslprogram.h 
	vbocube.h 
	vboplane.h 
    vbosphere.h
	bmpreader.h
	tgaio.h
	
	vboteapotpatch.cpp
	vboteapot.cpp
	drawable.cpp 
	vbomeshadj.cpp 
	vbotorus.cpp 
	glutils.cpp 
	vbomesh.cpp 
	glslprogram.cpp 
	vbocube.cpp 
	vboplane.cpp 
    vbosphere.cpp
	bmpreader.cpp
	tgaio.cpp
	#jk_arcball.cpp
	gl_core_4_4.c)

add_library( ingredients STATIC ${ingredients_SOURCES} )
