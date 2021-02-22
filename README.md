# OxTS Generic Aiding SDK

This project contains the OxTS GAD SDK, written in C++. This SDK is designed to allow users to encode aiding data to GAD packets and send them to an OxTS INS for use in the navigation solution. It also contains NCom decoder functionality, for those who wish to receive data from the unit.

## Requirements

The NCom decoding portion of this SDK can be used with any OxTS INS. Generic Aiding can only be used with a unit for which the appropriate Generic Aiding Feature Codes are enabled. RD files can be processed with Feature Codes they did not have at the time of recording, using NAVsolve. For internal users, blended can be run using the blended bypass code generator. 

The connection to the unit is expected to be UDP via ethernet.

CMake is required to build the code and examples from source. (Pre-built binaries TBC)

## Getting Started

The fastest way to get started with the SDK is to install the pre-built binaries from... (TBC). Will require some form of deployment.

## Building from source

Users can also build the SDK from source, using the following instructions:

1. Clone the repository onto the PC.
2. Navigate to the root directory of the repository
3. (Optional) Edit the CMakeLists.txt file in the root of the repository to 
   configure options, such as enabling building of examples.
4. Execute the commands:

```
mkdir _build && cd _build 
cmake ..
cmake --build . --target install
```

This will build the SDK and install it to your machine. Once this is complete, 
other CMake projects on the machine can link to the libraries using... (not 
functional yet. Can only be included in example projects within the repo.)

## Examples

The SDK contains a number of examples to demonstrate Generic Aiding and NCom 
decoding in action. These are contained in the /examples directory. To build 
the examples, ensure that the option OXTS_SDK_BUILD_EXAMPLES is enabled in the
CMakeLists.txt file at the root of the repository.

### GAL

#### Static Aiding

This is one of the simplest Generic Aiding examples, ideal for getting to grips 
with the interface without leaving your desk.

Static position and attitude measurements are created alongside zero velocity 
updates, all of which are sent to the INS.
