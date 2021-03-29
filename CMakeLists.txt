# CMake examples:
# https://mirkokiefer.com/cmake-by-example-f95eb47d45b1
# Using Rust Code in a C++ project with CMake:
# https://blog.devolutions.net/2018/06/insider-series-using-rust-code-in-a-cc-project-with-cmake
# https://users.rust-lang.org/t/issue-adding-a-rust-static-library-to-a-c-project-using-cmake/26478/3

cmake_minimum_required(VERSION 3.0)

project (stlthumbnail)

set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

# Find Qt modules
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS 
    Core    # QCommandLineParser, QStringLiteral
    Widgets # QApplication 
)

# Find KDE modules
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    KIO
)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
    
set(stlthumbnail_SRCS stlcreator.cpp)

add_library(stlthumbnail MODULE ${stlthumbnail_SRCS})

# Add stl-thumb rust library
#add_library(stl_thumb SHARED IMPORTED)
#set_property(TARGET stl_thumb PROPERTY IMPORTED_LOCATION
#    ../stl-thumb/target/release/libstl_thumb.so
#)
add_library(stl_thumb STATIC IMPORTED)
set_property(TARGET stl_thumb PROPERTY IMPORTED_LOCATION
    ../stl-thumb/target/release/libstl_thumb.a
)
set(CMAKE_STATIC_LINKER_FLAGS "-ldl -ldl -lutil -lutil -ldl -lrt -lpthread -lgcc_s -lc -lm -lrt -lpthread -lutil -lutil")

target_link_libraries(stlthumbnail
    Qt5::Widgets
    KF5::KIOWidgets
    stl_thumb
    # Dependencies from running `cargo rustc --lib -- --print native-static-libs`
    dl
    util
    rt
    pthread
    gcc_s
    c
    m
)

install(TARGETS stlthumbnail DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES stlthumbnail.desktop DESTINATION ${SERVICES_INSTALL_DIR})