# cmake/Unix.cmake

list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)

# === Dependency library ===
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost REQUIRED COMPONENTS filesystem thread)
find_package(OpenSSL REQUIRED)
find_package(simdjson REQUIRED)
find_package(mimalloc CONFIG REQUIRED)
find_package(absl REQUIRED)
find_package(benchmark REQUIRED)
find_package(GTest REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(flatbuffers REQUIRED)
find_package(PQXX REQUIRED)
set(BLA_VENDOR OpenBLAS) 
find_package(OpenBLAS REQUIRED)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

# ==============
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
# Executable
add_executable(
  tutorial
  ${SRC_FILES}
)
# ==============

# Include directories
target_include_directories(
  tutorial
  PRIVATE
      ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(tutorial
  PRIVATE 
    # Memory & Performance
    mimalloc
    simdjson::simdjson
    flatbuffers::flatbuffers
    
    # Utilities & Logic
    Boost::thread 
    Boost::filesystem
    Boost::headers
    absl::base 
    absl::strings 
    absl::numeric
    
    # Math & Science
    Eigen3::Eigen
    BLAS::BLAS 
    LAPACK::LAPACK
    # Note: OpenBLAS is usually wrapped by BLAS::BLAS if BLA_VENDOR is set
    
    # Security & Database
    OpenSSL::SSL 
    OpenSSL::Crypto
    pqxx::pqxx
    
    # Testing & Benchmarking
    GTest::gtest 
    GTest::gtest_main
    benchmark::benchmark
)
