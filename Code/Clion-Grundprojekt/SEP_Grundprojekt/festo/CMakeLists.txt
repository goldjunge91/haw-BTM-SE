cmake_minimum_required(VERSION 3.17)
project(Projekttest)

set(CMAKE_CXX_STANDARD 14)

## Compiler Defines hier mittels add_definition hinzufügen
#add_definitions(-DHOME -DSIMULATION) #Schaltet die Simulation an
add_definitions(-DSIM_SHOW_TIMESTAMP) #Gibt die in der Simulation vergangene Zeit aus
add_definitions(-DLONGRUN) #Führt den langen, ausführlichen Test aus.

## In der folgenden Zeile alle .cpp- und .h-Dateien aus diesem Verzeichnis ergänzen.
add_executable(Projekttest main.cpp)


## Die folgenden Zeilen nicht ändern
find_library(CBW_LIB cbw64 ./lib)
find_path (CBW_INCLUDES cbw.h ./lib)
include_directories(${CBW_INCLUDES})
if(${WIN32})
    add_definitions(-DWIN_SYS)
endif()

include_directories( src)
add_subdirectory(src)

IF(${WIN32})
    target_link_libraries(Projekttest src ${CBW_LIB})

ELSE()
    get_directory_property(MYDEFS COMPILE_DEFINITIONS)
    if(MYDEFS MATCHES "^HOME")
    else()
        message(WARNING "Compiling not on Windows. You can only use the Simulation here!")
    endif()
    target_link_libraries(Projekttest)

ENDIF()

