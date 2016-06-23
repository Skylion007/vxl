# bbas/volm/CMakeLists.txt
# Volumetric Matching and 3-d indexing library

# volm depends on bkml and expat

include( ${VXL_CMAKE_DIR}/FindGEOTIFF.cmake)
if(HAS_GEOTIFF)

include( ${BRL_MODULE_PATH}/FindEXPAT.cmake )
if(EXPAT_FOUND)
  if(EXPATPP_FOUND)
    include_directories( ${BRL_INCLUDE_DIR} )
    include_directories( ${BRL_INCLUDE_DIR}/bbas/bpgl )
    include_directories( ${GEL_INCLUDE_DIR} )
    include_directories(${EXPAT_INCLUDE_DIRS} )
    include_directories(${EXPATPP_INCLUDE_DIRS} )

    set(bcon_sources 
      blah.h
      blah.cxx)

    #aux_source_directory(Templates volm_sources)

    vxl_add_library(LIBRARY_NAME bcon LIBRARY_SOURCES  ${bcon_sources})

    target_link_libraries(bcon vsph bpgl ${VXL_LIB_PREFIX}vgl ${VXL_LIB_PREFIX}vgl_algo ${VXL_LIB_PREFIX}vgl_io ${VXL_LIB_PREFIX}vil ${VXL_LIB_PREFIX}vil_io ${VXL_LIB_PREFIX}vil_algo ${VXL_LIB_PREFIX}vbl_io vsol bkml bvgl ${VXL_LIB_PREFIX}vbl ${VXL_LIB_PREFIX}vsl ${VXL_LIB_PREFIX}vul bvrml depth_map brad)
    target_link_libraries(bcon ${EXPAT_LIBRARIES})
    if(APPLE)
      target_link_libraries(bcon expat)
    endif()
    target_link_libraries(bcon ${EXPATPP_LIBRARIES})
    # Base matcher, Proximity matcher, Visibility matcher related
    #add_subdirectory(desc)

    # 2-d, 3-d Configurational matcher related
    #add_subdirectory(conf)

    #if(BUILD_TESTING)
    #  add_subdirectory(tests)
    #endif()

    #add_subdirectory(exe)

    add_subdirectory(pro)
  endif()
endif()
else()
  message(STATUS "Skipping contrib/brl/bbas/bconn: requires geotiff")
endif()
