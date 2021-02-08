# OxTS Generic Aiding SDK

This project contains the OxTS GAD SDK, written in C++. This SDK is designed to allow users to encode aiding data to GAD packets and send them to an OxTS INS for use in the navigation solution. It also contains NCom decoder functionality, for those who wish to receive data from the unit.

## Requirements

The NCom decoding portion of this SDK can be used with any OxTS INS. Generic Aiding can only be used with a unit for which the appropriate Generic Aiding Feature Codes are enabled. RD files can be processed with Feature Codes they did not have at the time of recording, using NAVsolve. For internal users, blended can be run using the blended bypass code generator. 

The connection to the unit is expected to be UDP via ethernet.

CMake is required to build the code and examples from source. (Pre-built binaries TBC)

## Getting Started

The fastest way to get started with the SDK is to install the pre-built binaries from... (TBC)

## Building from source

Users can also build the SDK from source, using the following instructions:

1. Clone the repository onto the PC.
2. cd gad-sdk/build 
3. cmake ..
4. make

## Examples

The SDK contains a number of examples to demonstrate Generic Aiding and NCom decoding in action. 


...
