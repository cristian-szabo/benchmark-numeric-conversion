cmake_minimum_required(VERSION 3.15)

AddProject(
    EXECUTABLE FOLDER_EXCLUDE
    TARGET_NAME NumConvPerf
    SOURCE_DIRS Fixtures Datasets Benchmarks
    DEPENDEES Test CommandLine Profiler)
