# OxTS Generic Aiding SDK

This project contains the OxTS GAD SDK, written in C++. This SDK is designed to allow users to encode aiding data to GAD packets and send them to an OxTS INS for use in the navigation solution. It also contains NCom decoder functionality, for those who wish to receive data from the unit.

Find the full code documentation for this project at: [https://oxts.gitlab.io/navigation/generic-aiding/gad-sdk/](https://oxts.gitlab.io/navigation/generic-aiding/gad-sdk/)

## Requirements

- CMake 3.1
- Boost 1.71 (requirement can be disabled, though this will remove UDP functionality)
- Generic Aiding Feature Codes.
- Ethernet connection to an OxTS INS, for real-time aiding.

### Installing requirements on Linux

```
sudo apt-get install cmake
sudo apt-get install libboost-all-dev
```

## Getting Started

Install the pre-built binaries from... (TBC). Will require some form of deployment.

## Building from source

Users can also build the SDK from source, using the following instructions:

1. Clone the repository onto the PC.
2. Navigate to the root directory of the repository
3. (Optional) Edit the CMakeLists.txt file in the root of the repository to 
   configure options, such as enabling building of examples and documentation.
4. Execute the commands:

```
mkdir _build && cd _build 
cmake ..
cmake --build . --target install
```

This will build the SDK and install it to your machine. Once this is complete, 
other CMake projects on the machine can link to the libraries using:

```
find_package(oxts-sdk-gal-cpp REQUIRED)
find_package(Boost COMPONENTS system thread regex)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        oxts-sdk-gal-cpp
)
```
in their CMakeLists.txt. 
Header files can then be included in code files using 
`#include "oxts/<oxts-sdk-module>/<filename>.hpp".

### Build options

The CMakeLists.txt file in the root of the repository contains some options for building the SDK.

| Option | Description | Default |
|-------------|---------------|----|
<!-- |OXTS_SDK_BUILD_DOCS|Build SDK documentation.| OFF | -->
|OXTS_SDK_BUILD_EXAMPLES|Enable examples targets.| ON |
|OXTS_SDK_DISABLE_BOOST|Use Boost library when building. Note that not using boost will limit UDP functionality, which will need to be replaced by the user in order to send GAD to an INS.| OFF |

### Building the docs

The documentation for this project is generated using a few tools: Doxygen, Breathe, and Sphinx. 

1. Install requirements (python 3.7 also required):
```
  pip install -U sphinx
  pip3 install sphinx-rtd-theme
  pip3 install sphinx-sitemap
  pip3 install breathe

```
2. Navigate to the `docs_sphinx` directory and run the command:
```
  sphinx-build -b html . public
```

