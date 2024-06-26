add_library(EventBuilderCore STATIC)
target_include_directories(EventBuilderCore SYSTEM PUBLIC ../../vendor/spdlog/include ${ROOT_INCLUDE_DIRS} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_precompile_headers(EventBuilderCore PRIVATE ../EventBuilder.h)

target_sources(EventBuilderCore PRIVATE
    ChannelMap.cpp
    CompassRun.h
    FlagHandler.cpp
    MassLookup.h
    SFPAnalyzer.h
    Stopwatch.cpp
    ChannelMap.h
    CutHandler.cpp
    FlagHandler.h
    OrderChecker.cpp
    SFPPlotter.cpp
    Stopwatch.h
    CutHandler.h
    FP_kinematics.cpp
    OrderChecker.h
    SFPPlotter.h
    CompassFile.cpp
    EVBApp.cpp
    FP_kinematics.h
    ProgressCallback.h
    ShiftMap.cpp
    CompassFile.h
    EVBApp.h
    Logger.cpp
    RunCollector.cpp
    ShiftMap.h
    CompassHit.h
    FastSort.cpp
    Logger.h
    RunCollector.h
    SlowSort.cpp
    CompassRun.cpp
    FastSort.h
    MassLookup.cpp
    SFPAnalyzer.cpp
    SlowSort.h
)

target_link_libraries(EventBuilderCore PUBLIC
    SPSDict
    ${ROOT_LIBRARIES}
)

set_target_properties(EventBuilderCore PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${EVB_LIBRARY_DIR})