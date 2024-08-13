cmake_minimum_required (VERSION 3.21)

project(IReflx
	VERSION 1.0.0
	DESCRIPTION "ISTAR Reflextor Library"
	LANGUAGES C CXX
)

# set the postfix "d" for the resulting .so or .dll files when building the
# library in debug mode
set(CMAKE_DEBUG_POSTFIX d)

add_library(IReflx STATIC)

# specify the C++ standard
target_compile_features(
    IReflx
    PUBLIC cxx_std_14
)

target_compile_definitions(IReflx PRIVATE QSIZE=100)

target_sources(IReflx
  PUBLIC
    include/IReflx/CommandLineParser.h
    include/IReflx/IStarReflextor.h
  PRIVATE
    src/BaseIOInterface.cpp
    src/BaseIOInterface.h
    src/BoundedBuffer.h
    src/CommandLineParser.cpp
    src/GmtiReader.cpp
    src/GmtiReader.h
    src/IStarReflextor.cpp
    src/IStarReflextor.h
    src/SourceReader.cpp
    src/SourceReader.h
    src/StdinReader.cpp
    src/StdinReader.h
    src/UdpData.cpp
    src/UdpData.h
    src/UdpListener.cpp
    src/UdpListener.h
    src/UdpSender.cpp
    src/UdpSender.h
    src/QueueType.h
)

if(WIN32)
  target_link_libraries(IReflx PUBLIC wsock32 ws2_32)
else()
  target_link_libraries(IReflx)
endif()

if(PERFCNTR)
  target_include_directories(IReflx PUBLIC ../../)
  target_link_libraries(IReflx PUBLIC IReflxPerfCntr)
  target_link_directories(IReflx PUBLIC ../../x64/Debug ../../x64/Release)
endif()

target_include_directories(IReflx
		PRIVATE src/IReflx
		PUBLIC include
)