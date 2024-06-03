#!/bin/bash

validation="[^A-Za-z0-9_-]"

read -p $'\e[38;2;168;212;255mThe project directory name:\e[0m ' ProjectName
while [[ "${ProjectName}" == '' || "${ProjectName}" =~ ${validation} ]]; do
    read -p $'\e[38;2;255;51;51mInvalid name (a-z, A-Z, 0-9, -, _)!:\e[0m ' ProjectName
done
mkdir -p ./${ProjectName}/src \
         ./${ProjectName}/build
echo -e "\e[38;2;181;255;168mThe project directory named \"${ProjectName}\" has been created. ✓\e[0m"

#--- CMake Project Name
read -p $'\e[38;2;168;212;255mCMake project name:\e[0m ' CMakeProjectName
while [[ "${CMakeProjectName}" == '' || "${CMakeProjectName}" =~ ${validation} ]]; do
    read -p $'\e[38;2;255;51;51mInvalid name (a-z, A-Z, 0-9, -, _)!:\e[0m ' CMakeProjectName
done

#--- Execute ouput file name
read -p $'\e[38;2;168;212;255mName the CMake executable file the same as the project name? (Y/n):\e[0m ' execute
if [[ ${execute} == 'y' ]] || [[ ${execute} == 'Y' ]] || [[ ${execute} == '' ]]; then
    execute=${CMakeProjectName}
elif [[ ${execute} == 'n' ]] || [[ ${execute} == 'N' ]]; then
    read -p $'\e[38;2;168;212;255mExecute file name : \e[0m ' execute
    while [[ "${execute}" =~ ${validation} ]]; do
        read -p $'\e[38;2;255;51;51mInvalid name (a-z, A-Z, 0-9, -, _)! :\e[0m ' execute
    done
fi
echo -e "\e[38;2;181;255;168mCMake executable file name: \"${execute}\" ✓\e[0m"

#--- C++ Standard
read -p $'\e[38;2;168;212;255mC++ Standard (Ex. 11, 14, 17, 20, 23):\e[0m ' getCPPstd 
CPPstd=(11 14 17 20 23)
if ! [[ "${CPPstd[*]}" =~ "${getCPPstd}" ]] || [[ "${getCPPstd}" == '' ]]; then
    getCPPstd=11
    echo -e "\e[38;2;181;255;168mC++ Standard : -std=c++${getCPPstd} (default) ✓\e[0m"
else
    echo -e "\e[38;2;181;255;168mC++ Standard : -std=c++${getCPPstd} ✓\e[0m"
fi

#--- CMakeLists.txt
cat << EOF > ./${ProjectName}/CMakeLists.txt
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(${CMakeProjectName} VERSION 1.0.0 LANGUAGES C CXX)

# compiler flags/options INTERFACE
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE \$<BUILD_LOCAL_INTERFACE:cxx_std_23>)
target_compile_options(compiler_flags BEFORE INTERFACE
    \$<BUILD_LOCAL_INTERFACE:-Wall;-Werror;-Wpedantic>
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "\${CMAKE_SOURCE_DIR}/")

find_package(wxWidgets REQUIRED)

# include UsewxWidgets.cmake file to set up necessary variables
include(\${wxWidgets_USE_FILE})

# include directory INTERFACE
add_library(include_interface INTERFACE)
target_include_directories(include_interface INTERFACE
    \$<BUILD_LOCAL_INTERFACE:\${CMAKE_SOURCE_DIR}/src>
)

#add_executable(${execute} WIN32)
add_executable(${execute})
target_sources(${execute} PRIVATE
    \${CMAKE_SOURCE_DIR}/src/${execute}.cpp
)

target_link_libraries(${execute} PRIVATE
    include_interface
    compiler_flags
    \${wxWidgets_LIBRARIES}
)

#message(STATUS "==========================================================")
#message(STATUS "\\\${wxWidgets_USE_FILE}:     \${wxWidgets_USE_FILE}")
#message(STATUS "\\\${wxWidgets_INCLUDE_DIRS}: \${wxWidgets_INCLUDE_DIRS}")
#message(STATUS "==========================================================")
EOF

#--- Add code simple
cat << 'EOF' > ./${ProjectName}/src/${execute}.cpp
// Start of wxWidgets "Hello World" Program
#include <wx/wx.h>
 
class MyApp : public wxApp {
public:
    bool OnInit() override;
};
 
wxIMPLEMENT_APP(MyApp);
 
class MyFrame : public wxFrame {
public:
    MyFrame();
 
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
 
enum {
    ID_Hello = 1
};
 
bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}
 
MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
 
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}
 
void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
 
void MyFrame::OnHello(wxCommandEvent& event) {
    wxLogMessage("Hello world from wxWidgets!");
}
EOF

#--- VSCode .vscode folders
#   c_cpp_properties.json
#   launch.json
#   tasks.json
#GCC_VERSION=$(g++ --version | head -n 1 | awk '{print $7}')

mkdir ./${ProjectName}/.vscode
cat << EOF > ./${ProjectName}/.vscode/c_cpp_properties.json
{
  "env": {
    "myDefaultIncludePath": [
      "\${workspaceFolder}/**"
    ],
    "myCompilerPath": "C:/msys64/ucrt64/bin/g++.exe"
  },
  "configurations": [
    {
      "name": "Win32",
      "includePath": [
        "\${workspaceFolder}/**",
        "\${myDefaultIncludePath}",
        "C:/msys64/ucrt64/include/**",
        "C:/msys64/ucrt64/lib/**"
      ],
      "defines": [
        "_DEBUG",
        "UNICODE",
        "_UNICODE"
      ],
      "compilerPath": "\${myCompilerPath}",
      "cStandard": "c23",
      "cppStandard": "c++${getCPPstd}",
      "intelliSenseMode": "windows-gcc-x64",
      "browse": {
        "path": [
          "\${workspaceFolder}",
          "C:/msys64/ucrt64/lib",
          "C:/msys64/ucrt64/x86_64-w64-mingw32"      
        ],
        "limitSymbolsToIncludedHeaders": true,
        "databaseFilename": ""
      }
    }
  ],
  "version": 4
}
EOF

cat << EOF > ./${ProjectName}/.vscode/launch.json
{
  // Use IntelliSense to learn about possible attributes.
  // Hover to view descriptions of existing attributes.
  // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
  "version": "0.2.0",
  "configurations": [
    {
      "name": "(gdb) Launch",
      "type": "cppdbg",
      "request": "launch",
      "program": "\${workspaceFolder}/${execute}.exe",
      "args": [],
      "stopAtEntry": false,
      "cwd": "\${workspaceFolder}/build",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "miDebuggerPath": "C:/msys64/ucrt64/bin/gdb.exe",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
      //"preLaunchTask": "Make"
    }
  ]
}
EOF

cat << 'EOF' > ./${ProjectName}/.vscode/tasks.json
{
  "version": "2.0.0",
  "options": {
    "cwd": "${workspaceFolder}"
  },
  "tasks": [
    {
      "label": "CMake --build",
      "type": "shell",
      "windows":{
        "command": "cmake --build ./build"
      },
      "linux":{
        "command": "cmake --build ./build"
      },
      "problemMatcher": [
        "$gcc"
      ]
    },
  ]
}
EOF

#--- Build CMake project
echo "-------------------------------"
cmake -S ./${ProjectName} -B ./${ProjectName}/build -G "MSYS Makefiles"

echo "-------------------------------"
tree ${ProjectName} -L 2
echo "-------------------------------"
