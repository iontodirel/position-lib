# Header only coordinate representation, conversion and formatting utilities

## Usage example

In the example below, we store coordinates in Decimal Degrees format, convert them to DDM and to DMS, then use a string formatter to convert coordinates as strings.

`position_dd dd(47.51863818403278, -122.29686387310251);` \
`position_ddm ddm = dd;` \
`position_dms dms = dd;`

`position_display_string dd_fmt = format(dd, position_dd_format);` \
`assert(dd_fmt.lat == "47.518638");` \
`assert(dd_fmt.lon == "-122.296864");`

`position_display_string ddm_fmt = format(ddm, position_ddm_format);` \
`assert(ddm_fmt.lat == "47°31.118'N");` \
`assert(ddm_fmt.lon == "122°17.812'W");` 

`position_display_string dms_fmt = format(dms, position_dms_format);` \
`assert(dms_fmt.lat == "47°31'7.10\"N");` \
`assert(dms_fmt.lon == "122°17'48.71\"W");`

## Tests

Tests are stored in `./tests/position_tests.cpp` and are run automatically via a github action, on Ubuntu and Windows using the MSVC and GCC compilers.

## Integration with CMake

As this is a header only library, you can simple download the header and use it:

`file(DOWNLOAD
    https://raw.githubusercontent.com/iontodirel/position-lib/main/position.hpp
    ${CMAKE_SOURCE_DIR}/external/position.hpp
)`

Include the header:

`#include "external/position.hpp"`
