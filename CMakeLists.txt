# CMake examples:
# https://mirkokiefer.com/cmake-by-example-f95eb47d45b1
# Using Rust Code in a C++ project with CMake:
# https://blog.devolutions.net/2018/06/insider-series-using-rust-code-in-a-cc-project-with-cmake
# https://users.rust-lang.org/t/issue-adding-a-rust-static-library-to-a-c-project-using-cmake/26478/3

cmake_minimum_required(VERSION 3.10)

project(stl-thumb-kde
	#VERSION 0.5.0
	DESCRIPTION "Fast lightweight STL file thumbnail generator for KDE"
	#HOMEPAGE_URL "https://github.com/unlimitedbacon/stl-thumb-kde"	# Doesn't work with CMake 3.10
	)

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

# Use local stl-thumb lib instead of system-wide lib
# Dynamic
#add_library(stl_thumb SHARED IMPORTED)
#set_property(TARGET stl_thumb PROPERTY IMPORTED_LOCATION
#    ../stl-thumb/target/release/libstl_thumb.so
#)
# Static
#add_library(stl_thumb STATIC IMPORTED)
#set_property(TARGET stl_thumb PROPERTY IMPORTED_LOCATION
#    ../stl-thumb/target/release/libstl_thumb.a
#)

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

# This path works on Arch
#install(TARGETS stlthumbnail DESTINATION ${PLUGIN_INSTALL_DIR})
# This path works on Debian / Ubuntu
install(TARGETS stlthumbnail DESTINATION ${LIB_INSTALL_DIR}/qt5/plugins/)
install(FILES stlthumbnail.desktop DESTINATION ${SERVICES_INSTALL_DIR})

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 5)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Tyler Anderson <unlimitedbacon@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/unlimitedbacon/stl-thumb-kde")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgl1, libc6, libgcc1, libosmesa6-dev, kio, stl-thumb")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

include(CPack)
