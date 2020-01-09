cmake_minimum_required (VERSION 3.8)

project ("rdcfswatcherexample")

add_executable (rdcfswatcherexample "main.cpp" "rdc_fs_watcher.cpp" "rdc_fs_watcher.h")
set_property(TARGET rdcfswatcherexample PROPERTY CXX_STANDARD 17)