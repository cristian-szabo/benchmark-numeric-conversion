cmake_minimum_required(VERSION 3.15)

AddProject(
    STATIC FOLDER_EXCLUDE
    TARGET_NAME CommandLine
    SOURCE_DIRS Options
    DEPENDEES Core)
