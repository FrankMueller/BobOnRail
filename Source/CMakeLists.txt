file (GLOB SOURCE_FILES "*.cpp")

add_executable(BobOnRails ${SOURCE_FILES})
set_target_properties(BobOnRails PROPERTIES
    OUTPUT_NAME "BobOnRails"
)

set(include_install_dir "include")
set(lib_install_dir "lib/")
set(bin_install_dir "bin/")

