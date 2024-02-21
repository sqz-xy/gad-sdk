This utility is supported by OxTS. If you require assistance, please contact OxTS support at [https://support.oxts.com/hc/en-us/requests/new]

# OxTS Generic Aiding SDK

For more information on OxTS Generic Aiding Solutions, see [here](https://www.oxts.com/what-is-generic-aiding/)

This project contains the OxTS GAD SDK, written in C++. This SDK is designed to allow users to encode aiding data to GAD packets and send them to an OxTS INS for use in the navigation solution. Alternatively, the SDK can be instructed to create a CSV style file which can be used as an aiding source when post-processing with the INS data.

In addition, the C++ SDK has been wrapped in Python using PyBind11.

The SDK also contains NCom decoder functionality, for those who wish to receive data from the unit.

The OxTS GAD SDK is compliant with the Motor Industry Software Reliability Association (MISRA) coding standards.

Find the full code documentation for this project at: [https://oxfordtechnicalsolutions.github.io/index.html](https://oxfordtechnicalsolutions.github.io/index.html)

## Requirements

- Navsuite 3.9 or newer. Or Blended 230817 or newer.
- OxTS INS with firmware version 231017 or newer. Contact OxTS [support](https://support.oxts.com/hc/en-us/requests/new) for help with firmware.
- CMake >3.1 (Last version tested 3.24)
- Generic Aiding Feature Codes.
- Ethernet connection to an OxTS INS, for real-time aiding.
- C/C++ Compiler (Easiest option is to install Visual Studio Professional 2019 on Windows, Linux GCC)
- Python > 3.7 (Optional, for Python SDK and building documentation.)
- Boost 1.82 (Optional, for unit testing only).

### Installing requirements on Linux and Unix

To Install cmake on Linux and Unix operating systems, use the following:
```
sudo apt-get install cmake
```

If required, Boost can be installed with the following command:
```
sudo apt-get install libboost-all-dev
```

### Installing requirements on Windows 

- Download and install [CMake](https://cmake.org/download/) (the latest msi installer should be sufficient)

If unit testing is required, install Boost:
- Download [Boost](https://www.boost.org/users/download/)
  - Extract the files to a sensible location such as C:\Libs. Note you do not need to create an extra containing folder. The full path to the boost libraries should resemble C:\Libs\boost_1_77_0.
  - In a command prompt navigate to the boost directory and run ``` bootstrap.bat ``` - Then run ```b2.exe link=shared``` to install boost.
  - Edit your environment variables and add the variable ```BOOST_ROOT``` with value equal to the path to your boost library. In this example the value would be ```C:\Libs\boost_1_77_0```

## Building from source

Users can build the SDK from source, using the following instructions:

1. Clone the repository onto the PC. Note: Clone this repository with the --recursive option to ensure pybind11 is available. 

   ```git clone https://github.com/OxfordTechnicalSolutions/gad-sdk.git --recursive```

	Note the `--recursive` command.

2. Navigate to the root directory of the repository.

3. (Optional) Edit the CMakeLists.txt file in the root of the repository to configure options, such as enabling building of examples and documentation. See the Build Options sections for more details.

4. Execute the following commands:

```
mkdir _build
cd _build 
cmake ..
cmake --build . --target install
```
This will build the SDK and install it to your machine.

Your machine may report an error from the INSTALL that permission to copy a file has been denied. 

* For Linux or Unix the last command again, but add `sudo` to the start. 

* For Windows, run CMD or Powershell as an administrator.

This should provide the correct access rights to install files to the correct location. 

Once this is complete, other CMake projects on the machine can link to the libraries using:

```
find_package(oxts-sdk-gal-cpp REQUIRED)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        oxts-sdk-gal-cpp
)
```
in their CMakeLists.txt.
 
Header files can then be included your .cpp source code using 
`#include "oxts/<oxts-sdk-module>/<filename>.hpp". For an example of this usage, see  [https://oxfordtechnicalsolutions.github.io/longform/example-my-first-gad.html](here.)


### Build options

The CMakeLists.txt file in the root of the repository contains some options for building the SDK.

| Option | Description | Default |
|-------------|---------------|----|
|OXTS_SDK_BUILD_DOCS|Build SDK documentation.| OFF |
|OXTS_SDK_BUILD_TESTS|Enable unit test targets. (Boost must be installed)| OFF |
|OXTS_SDK_BUILD_EXAMPLES|Build examples shown in documentation.| ON |
|OXTS_SDK_BUILD_PYTHON|Build SDK Python wrapper.| OFF |


### Building the docs

The documentation for this project can be found [here](https://oxfordtechnicalsolutions.github.io/index.html)_.

It is not necessary to build the documentation, however for reference, this can be generated using the following tools: Doxygen, Sphinx, and Breathe. 

To build:


1. Install Doxygen. Installation instructions can be found [here](https://www.doxygen.nl/manual/install.html)_.

2. Install Sphinx and Breathe using pip install (python 3.7 also required):
```
  pip install -U sphinx
  pip install sphinx-tabs
  pip3 install sphinx-rtd-theme
  pip3 install breathe
  pip3 install sphinx-sitemap
  pip3 install sphinx-toolbox

```
3. Navigate to the `docs_sphinx\source` directory and run the command:
```
  sphinx-build -b html . public
```

## Running

See the extended documentation for using the SDK.  If built using Visual Studio all code with examples and unit tests are available in the solution (oxts-sdk.sln) in the build folder.  This automatically links to the source files in each specific folder in the root directory.

	## stuff

## Python GAD SDK (Windows and Linux)

Note: As of PIP 21.3 pip creates build files locally in a folder called build instead of a temporary folder.

The C++ SDK has been wrapped in Python using PyBind11.

Note: To include the PyBind11 in your GAD SDK installation, the repository should be cloned with the –-recursive option. If this option was not included in the initial clone, the PyBind11 can be cloned afterwards with the following commands:
```
git submodule sync 
git submodule update --init --recursive
```

Information on Python SDK can be found within the main SDK documentation. In addition, a list of bindings to the C++ can be found in the documentation or here `oxts-sdk-py/gal-py-bindings.cpp`. Also, there are examples here `examples/python/my-first-gad.py`.

To install the package, navigate to the repository folder and use `pip install . `. After that, it can be imported using `import oxts_sdk`.

Note: You may need to install or update the Ninja package when installing the Python SDK.

