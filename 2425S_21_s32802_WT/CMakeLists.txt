cmake_minimum_required(VERSION 3.30)
project(project)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         11.0.2
)

FetchContent_MakeAvailable(fmt)

add_executable(project main.cpp
        FileInfo/printFileInfo.cpp
        FileInfo/printFileName.cpp
        FileInfo/printFilePermissions.cpp
        FileInfo/printFileSize.cpp
        FileInfo/printLastAccessTime.cpp
        FileInfo/printLastModificationTime.cpp
        FileInfo/printLastStatusChangeTime.cpp
        additional/displayHelp.cpp
        additional/checkFilePermissions.cpp
        additional/getFileSize.cpp
        additional/charToBinary.cpp
        additional/binaryToChar.cpp
        additional/trim.cpp
        PPM/readPPM.cpp
        PPM/writeMessageToPPM.cpp
        PPM/readMessageFromPPM.cpp
        canWriteMessage.cpp
        PPM/processPPM.cpp
        BMP/processBMP.cpp
        BMP/readMessageFromBMP.cpp
        BMP/writeMessageToBMP.cpp
        BMP/readBMPHeader.cpp

)
target_link_libraries(project fmt)

