# cmake/FindPQXX.cmake

# 1. Look for the header file
find_path(PQXX_INCLUDE_DIR 
    NAMES pqxx/pqxx
    PATHS /usr/include /usr/local/include /opt/homebrew/include
)

# 2. Look for the compiled library file (.a, .so, or .dylib)
find_library(PQXX_LIBRARY 
    NAMES pqxx
    PATHS /usr/lib /usr/local/lib /opt/homebrew/lib
)

# 3. Use standard CMake module to verify both were found
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(PQXX DEFAULT_MSG PQXX_LIBRARY PQXX_INCLUDE_DIR)

# 4. Create a Modern CMake Target for your project to link against
if(PQXX_FOUND AND NOT TARGET pqxx::pqxx)
    add_library(pqxx::pqxx UNKNOWN IMPORTED)
    set_target_properties(pqxx::pqxx PROPERTIES
        IMPORTED_LOCATION "${PQXX_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${PQXX_INCLUDE_DIR}"
    )
endif()
