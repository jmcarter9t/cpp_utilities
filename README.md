# Use in Existing Project as a Submodule

$ cd <project git repository>
$ mkdir lib
$ cd lib
$ git submodule add https://github.com/jmcarter9t/cpp_utilities.cpp

# Add to CMakeLists.txt

```
# Specify where to look for headers.
target_include_directories( binary-search
    PUBLIC
    "${CMAKE_SOURCE_DIR}/inc"
    PRIVATE
    INTERFACE
    )
```


