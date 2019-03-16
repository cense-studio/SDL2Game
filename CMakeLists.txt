cmake_minimum_required (VERSION 3.0)

# 设置项目名称
project (Game)	
MESSAGE( STATUS "项目名称: " ${PROJECT_NAME} )

include(CheckCXXCompilerFlag)
if(CHECK_CXX_COMPILER_USED1)
elseif("${CMAKE_CXX_COMPILER_ID}x" STREQUAL "MSVCx")    # 使用　Visual Studio C++
elseif("${CMAKE_CXX_COMPILER_ID}x" STREQUAL "Intelx")   # 使用　Intel C++
else(CHECK_CXX_COMPILER_USED1)
    # GCC or Clang
    # At least C++11
    CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
    CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
    CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
    CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    if(COMPILER_SUPPORTS_CXX17)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    elseif(COMPILER_SUPPORTS_CXX1Z)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
    elseif(COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    elseif(COMPILER_SUPPORTS_CXX1Y)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
    elseif(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        else(COMPILER_SUPPORTS_CXX17)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif(COMPILER_SUPPORTS_CXX17)
 
    if(CHECK_CXX_COMPILER_USED2)
    elseif("${CMAKE_CXX_COMPILER_ID}x" MATCHES "Clangx")
        # 使用 Clang
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-global-constructors")
    elseif("${CMAKE_CXX_COMPILER_ID}x" STREQUAL "GNUx")
        # 使用 GCC
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    endif(CHECK_CXX_COMPILER_USED2)
endif(CHECK_CXX_COMPILER_USED1)
MESSAGE( STATUS "当前编译器：" ${CMAKE_CXX_COMPILER_ID} )
 
# 设置版本号
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
MESSAGE( STATUS "项目版本: " ${PROJECT_VERSION_MAJOR} "."  ${PROJECT_VERSION_MINOR})

# 设置平台
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
	if(CMAKE_CL_64)
		set(PLATFORM x64)
    else()
		set(PLATFORM x86)
    endif()
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib/win32/${PLATFORM} )
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/lib/win32/${PLATFORM} )
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../bin )
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../bin)
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)
endif()


# 在非Windows平台下设置RPATH
if(WINDOWS)
else()
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    MESSAGE( STATUS "CMAKE_INSTALL_RPATH: " "${CMAKE_INSTALL_PREFIX}/lib" )
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

if(WINDOWS) #Windows下区分32位和64位
	link_directories( ${PROJECT_SOURCE_DIR}/lib/win32/${PLATFORM} )
elseif(LINUX)
    link_directories( ${PROJECT_SOURCE_DIR}/Libs/linux ) 
elseif(MACOS)
    link_directories( ${PROJECT_SOURCE_DIR}/Libs/macos ) 
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
set(CMAKE_DEBUG 1)
else()
set(CMAKE_DEBUG 0)
endif()

if(CMAKE_DEBUG)
MESSAGE( STATUS "当前项目构建模式: Debug" )
else()
MESSAGE( STATUS "当前项目构建模式: Release" )
endif()

configure_file(
    ${PROJECT_SOURCE_DIR}/src/Config.hc
    ${PROJECT_SOURCE_DIR}/src/Config.h
    LF
)

include_directories(
    ./include
)

# 游戏源代码
file(GLOB_RECURSE SRC
    ./src/*.h
    ./src/*.cpp
    ./src/*/*.h
    ./src/*/*.cpp
  )
# 添加游戏可执行文件
add_executable(${PROJECT_NAME} ${SRC})
# 链接静态动态库
target_link_libraries (${PROJECT_NAME} SDL2 SDL2_image SDL2_mixer SDL2_ttf)

if(WINDOWS)
set(DLL_DIR ${PROJECT_SOURCE_DIR}/lib/win32/${PLATFORM})
set(DLL_FILES
		${DLL_DIR}/SDL2.dll
		${DLL_DIR}/SDL2_image.dll
        ${DLL_DIR}/libjpeg-9.dll
        ${DLL_DIR}/libpng16-16.dll
        ${DLL_DIR}/zlib1.dll         
        ${DLL_DIR}/SDL2_mixer.dll
        ${DLL_DIR}/libmpg123-0.dll
        ${DLL_DIR}/SDL2_ttf.dll             
        ${DLL_DIR}/libfreetype-6.dll
        ${DLL_DIR}/sqlite3.dll )

    # 复制DLL文件到输出目录
	#add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD 
    #    COMMAND ${CMAKE_COMMAND} -E copy_if_different
	#	${DLL_FILES}
	#	$<TARGET_FILE_DIR:${PROJECT_NAME}>)

	# 其它的一些文件复制
#    add_custom_command(TARGET OLGame POST_BUILD 
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        "${PROJECT_SOURCE_DIR}/templates"       
#        $<TARGET_FILE_DIR:OLGame>/"templates" )

	# 设置安装目录
    #set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
    #install (FILES ${DLL_FILES} DESTINATION  ${PROJECT_SOURCE_DIR})
	#install (TARGETS OLGame DESTINATION  ${PROJECT_SOURCE_DIR})
endif()