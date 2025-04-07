# CMakeList.txt: projekt CMake dla elementu Overloading, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#
cmake_minimum_required (VERSION 3.8)

project ("Overloading")

# Włącz przeładowywanie kodu XAML na gorąco dla kompilatorów MSVC, jeśli jest to obsługiwane.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_PREFIX_PATH "C:/Users/nowak/OneDrive/Pulpit/C++/wxWidgets")
find_package(wxWidgets REQUIRED)
include_directories(${wxWidgets_INCLUDE_DIRS})
include_directories("C:/Users/nowak/source/repos/Overloading/out/source/candidate")
include_directories("C:/Users/nowak/source/repos/Overloading/out/source/major")


# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (Overloading "out/source/wxWidgets/main.cpp" "out/source/candidate/candidate.h" "out/source/candidate/candidate.cpp" "out/source/wxWidgets/admissionApp.h" "out/source/wxWidgets/admissionApp.cpp" "out/source/major/major.h" "out/source/major/major.cpp" "out/source/wxWidgets/mainFrame.h" "out/source/wxWidgets/mainFrame.cpp")

target_link_libraries(Overloading ${wxWidgets_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Overloading PROPERTY CXX_STANDARD 20)
endif()

set_target_properties(Overloading PROPERTIES WIN32_EXECUTABLE TRUE)

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
