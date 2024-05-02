cmake_minimum_required(VERSION 3.28)

project(cudf_sandbox LANGUAGES CXX)

find_package(cudf REQUIRED COMPONENTS testing)
find_package(kvikio REQUIRED)

add_executable(cudf_gds_check.run main.cpp)
target_link_libraries(cudf_gds_check.run PRIVATE cudf::cudf cudf::cudftestutil kvikio::kvikio)
set_property(TARGET cudf_gds_check.run PROPERTY CXX_STANDARD 20)

add_executable(rmm_gds_check.run rmm.cpp)
target_link_libraries(rmm_gds_check.run PRIVATE rmm::rmm kvikio::kvikio)
set_property(TARGET rmm_gds_check.run PROPERTY CXX_STANDARD 20)
