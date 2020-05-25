cmake_minimum_required(VERSION 3.15)

AddProject(
    STATIC FOLDER_EXCLUDE
    TARGET_NAME Test
    SOURCE_DIRS Datasets
    DEPENDEES Core Profiler)
