// **************************************************************** //
// position-lib - Position conversion and display utilities         // 
// Version 0.1.0                                                    //
// https://github.com/iontodirel/position-lib                       //
// Copyright (c) 2023 Ion Todirel                                   //
// **************************************************************** //
//
// position.hpp
// 
// MIT License
// 
// Copyright (c) 2023 Ion Todirel
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <string>
#include <tuple>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <type_traits>

#ifndef POSITION_LIB_NAMESPACE_BEGIN
#define POSITION_LIB_NAMESPACE_BEGIN namespace position {
#endif
#ifndef POSITION_LIB_NAMESPACE_END
#define POSITION_LIB_NAMESPACE_END }
#endif
#ifndef POSITION_LIB_INLINE
#define POSITION_LIB_INLINE inline
#endif
#ifndef POSITION_LIB_INLINE_NO_DISABLE
#define POSITION_LIB_INLINE_NO_DISABLE inline
#endif
#ifndef POSITION_LIB_DETAIL_NAMESPACE_BEGIN
#define POSITION_LIB_DETAIL_NAMESPACE_BEGIN namespace detail {
#endif
#ifndef POSITION_LIB_DETAIL_NAMESPACE_END
#define POSITION_LIB_DETAIL_NAMESPACE_END }
#endif
#ifndef POSITION_LIB_DETAIL_NAMESPACE_REFERENCE
#define POSITION_LIB_DETAIL_NAMESPACE_REFERENCE detail::
#endif

// **************************************************************** //
//                                                                  //
//                                                                  //
//                                                                  //
//                                                                  //
// POSITIONS AND COORDINATES                                        //
//                                                                  //
//                                                                  //
//                                                                  //
//                                                                  //
// **************************************************************** //

POSITION_LIB_NAMESPACE_BEGIN

struct position_string_formatter;
struct position_dd;
struct position_dms;
struct position_ddm;

struct position_dd
{
    double lat = 0.0;
    double lon = 0.0;

    position_dd() = default;
    position_dd(double, double);
    position_dd(const position_dms& p);
    position_dd& operator=(const position_dms& p);
    position_dd(const position_ddm&);
    position_dd& operator=(const position_ddm& p);
};

struct position_dms
{
    char lat = '\0';
    int lat_d = 0;
    int lat_m = 0;
    double lat_s = 0.0;
    char lon = '\0';
    int lon_d = 0;
    int lon_m = 0;
    double lon_s = 0.0;

    position_dms() = default;
    position_dms(const position_dd& p);
    position_dms& operator=(const position_dd& p);
    position_dms(const position_ddm& p);
    position_dms& operator=(const position_ddm& p);
};

struct position_ddm
{
    char lat = '\0';
    int lat_d = 0;
    double lat_m = 0.0;
    char lon = '\0';
    int lon_d = 0;
    double lon_m = 0.0;

    position_ddm() = default;
    position_ddm(const position_dd& p);
    position_ddm& operator=(const position_dd& p);
    position_ddm(const position_dms& p);
    position_ddm& operator=(const position_dms& p);
};

struct position_format
{
    std::string deg_symbol = "°";
    std::string min_symbol = "'";
    std::string sec_symbol = "\"";
    bool dir_indicator = true;
    std::string dir_indicator_spacer = " ";
    std::string dm_separator = " ";
    std::string ms_separator = " ";
    int lat_precision = 6;
    int lon_precision = 6;
    int min_precision = 4;
    int sec_precision = 2;
};

POSITION_LIB_INLINE_NO_DISABLE position_format position_dd_format {.deg_symbol = "", .dir_indicator = false };
POSITION_LIB_INLINE_NO_DISABLE position_format position_ddm_format {.dir_indicator_spacer = "", .dm_separator = "", .min_precision = 3 };
POSITION_LIB_INLINE_NO_DISABLE position_format position_dms_format {.dir_indicator_spacer = "", .dm_separator = "", .sec_precision = 2 };

struct position_display_string
{
    std::string lat;
    std::string lon;
};

POSITION_LIB_DETAIL_NAMESPACE_BEGIN

template<typename T, typename ... U>
concept IsAnyOf = (std::same_as<T, U> || ...);

POSITION_LIB_DETAIL_NAMESPACE_END

// **************************************************************** //
//                                                                  //
//                                                                  //
// FORWARD FUNCTION DECLARATIONS                                    //
//                                                                  //
//                                                                  //
// **************************************************************** //

// **************************************************************** //
// CONVERSIONS                                                      //
// **************************************************************** //

POSITION_LIB_DETAIL_NAMESPACE_BEGIN

POSITION_LIB_INLINE position_ddm dd_to_ddm(position_dd dd);
POSITION_LIB_INLINE position_dms dd_to_dms(position_dd dd);
POSITION_LIB_INLINE std::tuple<int, double> dd_to_ddm(double dd);
POSITION_LIB_INLINE std::tuple<int, int, double> dd_to_dms(double dd);
POSITION_LIB_INLINE position_dd dms_to_dd(position_dms dms);
POSITION_LIB_INLINE position_ddm dms_to_ddm(position_dms dms);
POSITION_LIB_INLINE position_dms ddm_to_dms(position_ddm ddm);
POSITION_LIB_INLINE position_dd ddm_to_dd(position_ddm ddm);

POSITION_LIB_DETAIL_NAMESPACE_END

// **************************************************************** //
// FORMATTING                                                       //
// **************************************************************** //

POSITION_LIB_INLINE double format_number(double n, int p = 2);
POSITION_LIB_INLINE std::string format_number_to_string(double n, int p = 2);

// **************************************************************** //
//                                                                  //
//                                                                  //
// TYPE IMPLEMENTATIONS                                             //
//                                                                  //
//                                                                  //
// **************************************************************** //

template <POSITION_LIB_DETAIL_NAMESPACE_REFERENCE IsAnyOf<position_dd, position_ddm, position_dms> T>
POSITION_LIB_INLINE_NO_DISABLE position_display_string format(const T& p, const position_format& format)
{
    position_display_string ps;

    if constexpr (std::is_same_v<T, position_dd>)
    {
        ps.lat = format_number_to_string(p.lat, format.lat_precision);        
        ps.lat.append(format.deg_symbol);
        ps.lon = format_number_to_string(p.lon, format.lon_precision);
        ps.lon.append(format.deg_symbol);
    }
    else if constexpr (std::is_same_v<T, position_ddm>)
    {
        ps.lat = std::to_string(p.lat_d);
        ps.lat.append(format.deg_symbol);
        ps.lat.append(format.dm_separator);
        ps.lat.append(format_number_to_string(p.lat_m, format.min_precision));
        ps.lat.append(format.min_symbol);
        if (format.dir_indicator)
        {
            ps.lat.append(format.dir_indicator_spacer);
            ps.lat.append(1, p.lat);
        }
        ps.lon = std::to_string(p.lon_d);
        ps.lon.append(format.deg_symbol);
        ps.lon.append(format.dm_separator);
        ps.lon.append(format_number_to_string(p.lon_m, format.min_precision));
        ps.lon.append(format.min_symbol);
        if (format.dir_indicator)
        {
            ps.lon.append(format.dir_indicator_spacer);
            ps.lon.append(1, p.lon);
        }
    }
    else if constexpr (std::is_same_v<T, position_dms>)
    {
        ps.lat = std::to_string(p.lat_d);
        ps.lat.append(format.deg_symbol);
        ps.lat.append(format.dm_separator);
        ps.lat.append(std::to_string(p.lat_m));
        ps.lat.append(format.min_symbol);
        ps.lat.append(format_number_to_string(p.lat_s, format.sec_precision));
        ps.lat.append(format.sec_symbol);
        if (format.dir_indicator)
        {
            ps.lat.append(format.dir_indicator_spacer);
            ps.lat.append(1, p.lat);
        }
        ps.lon = std::to_string(p.lon_d);
        ps.lon.append(format.deg_symbol);
        ps.lon.append(format.dm_separator);
        ps.lon.append(std::to_string(p.lon_m));
        ps.lon.append(format.min_symbol);
        ps.lon.append(format_number_to_string(p.lon_s, format.sec_precision));
        ps.lon.append(format.sec_symbol);
        if (format.dir_indicator)
        {
            ps.lon.append(format.dir_indicator_spacer);
            ps.lon.append(1, p.lon);
        }
    }

    return ps;
}

#ifndef POSITION_LIB_PUBLIC_FORWARD_DECLARATIONS_ONLY

POSITION_LIB_INLINE position_dd::position_dd(double lat, double lon)
{
    this->lat = lat;
    this->lon = lon;
}

POSITION_LIB_INLINE position_dd::position_dd(const position_dms& p)
{
    *this = p;
}

POSITION_LIB_INLINE position_dd& position_dd::operator=(const position_dms& dms)
{
    position_dd p = POSITION_LIB_DETAIL_NAMESPACE_REFERENCE dms_to_dd(dms);
    lat = p.lat;
    lon = p.lon;
    return *this;
}

POSITION_LIB_INLINE position_dd::position_dd(const position_ddm& p)
{
    *this = p;
}

POSITION_LIB_INLINE position_dd& position_dd::operator=(const position_ddm& ddm)
{
    position_dd p = POSITION_LIB_DETAIL_NAMESPACE_REFERENCE ddm_to_dd(ddm);
    lat = p.lat;
    lon = p.lon;
    return *this;
}

POSITION_LIB_INLINE position_dms::position_dms(const position_dd& p)
{
    *this = p;
}

POSITION_LIB_INLINE position_dms& position_dms::operator=(const position_dd& p)
{
    position_dms p_dms = POSITION_LIB_DETAIL_NAMESPACE_REFERENCE dd_to_dms(p);
    lat_d = p_dms.lat_d;
    lat_m = p_dms.lat_m;
    lat_s = p_dms.lat_s;
    lon_d = p_dms.lon_d;
    lon_m = p_dms.lon_m;
    lon_s = p_dms.lon_s;
    lat = p_dms.lat;
    lon = p_dms.lon;
    return *this;
}

POSITION_LIB_INLINE position_dms::position_dms(const position_ddm& p)
{
    *this = p;
}

POSITION_LIB_INLINE position_dms& position_dms::operator=(const position_ddm& p)
{
    position_dms p_dms = POSITION_LIB_DETAIL_NAMESPACE_REFERENCE ddm_to_dms(p);
    lat_d = p_dms.lat_d;
    lat_m = p_dms.lat_m;
    lat_s = p_dms.lat_s;
    lon_d = p_dms.lon_d;
    lon_m = p_dms.lon_m;
    lon_s = p_dms.lon_s;
    lat = p_dms.lat;
    lon = p_dms.lon;
    return *this;
}

POSITION_LIB_INLINE position_ddm::position_ddm(const position_dd& p)
{
    *this = p;
}

POSITION_LIB_INLINE position_ddm& position_ddm::operator=(const position_dd& p)
{
    position_ddm p_ddm = POSITION_LIB_DETAIL_NAMESPACE_REFERENCE dd_to_ddm(p);
    lat_d = p_ddm.lat_d;
    lat_m = p_ddm.lat_m;
    lon_d = p_ddm.lon_d;
    lon_m = p_ddm.lon_m;
    lat = p_ddm.lat;
    lon = p_ddm.lon;
    return *this;
}

POSITION_LIB_INLINE position_ddm::position_ddm(const position_dms& p)
{
    *this = p;
}

POSITION_LIB_INLINE position_ddm& position_ddm::operator=(const position_dms& p)
{
    position_ddm p_ddm = POSITION_LIB_DETAIL_NAMESPACE_REFERENCE dms_to_ddm(p);
    lat_d = p_ddm.lat_d;
    lat_m = p_ddm.lat_m;
    lon_d = p_ddm.lon_d;
    lon_m = p_ddm.lon_m;
    lat = p_ddm.lat;
    lon = p_ddm.lon;
    return *this;
}

// **************************************************************** //
//                                                                  //
// FORMATTING                                                       //
//                                                                  //
// **************************************************************** //

POSITION_LIB_INLINE std::string format_number_to_string(double number, int precision)
{
    std::string pretty_number_str;
    if (precision == 0)
    {
        double i;
        std::modf(number, &i);
        pretty_number_str = std::to_string((int)i);
    }
    else
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(precision) << number;
        pretty_number_str = ss.str();
    }
    return pretty_number_str;
}

POSITION_LIB_INLINE double format_number(double number, int precision)
{
    std::string s = format_number_to_string(number, precision);
    return std::stod(s);
}

// **************************************************************** //
//                                                                  //
//                                                                  //
// INTERNALS IMPLEMENTATION                                         //
//                                                                  //
//                                                                  //
// **************************************************************** //

POSITION_LIB_DETAIL_NAMESPACE_BEGIN

POSITION_LIB_INLINE position_ddm dms_to_ddm(position_dms dms)
{
    position_ddm ddm;
    ddm.lat = dms.lat;
    ddm.lat_d = dms.lat_d;
    ddm.lat_m = dms.lat_m + (dms.lat_s / 60.0);
    ddm.lon = dms.lon;
    ddm.lon_d = dms.lon_d;
    ddm.lon_m = dms.lon_m + (dms.lon_s / 60.0);
    return ddm;
}

POSITION_LIB_INLINE position_dms ddm_to_dms(position_ddm ddm)
{
    position_dms dms;  
    dms.lat = ddm.lat;
    dms.lat_d = ddm.lat_d;
    dms.lat_m = static_cast<int>(ddm.lat_m);
    dms.lat_s = (ddm.lat_m - dms.lat_m) * 60;
    dms.lon = ddm.lon;
    dms.lon_d = ddm.lon_d;
    dms.lon_m = static_cast<int>(ddm.lon_m);
    dms.lon_s = (ddm.lon_m - dms.lon_m) * 60;
    return dms;
}

POSITION_LIB_INLINE position_dd ddm_to_dd(position_ddm ddm)
{
    position_dd p;
    p.lat = ddm.lat_d + (ddm.lat_m / 60.0);
    p.lon = ddm.lon_d + (ddm.lon_m / 60.0);
    p.lat = ddm.lat == 'S' ? -p.lat : p.lat;
    p.lon = ddm.lon == 'W' ? -p.lon : p.lon;
    return p;
}

POSITION_LIB_INLINE position_dd dms_to_dd(position_dms dms)
{
    position_dd p;
    p.lat = dms.lat_d + (dms.lat_m / 60.0) + (dms.lat_s / 3600.0);
    p.lon = dms.lon_d + (dms.lon_m / 60.0) + (dms.lon_s / 3600.0);
    p.lat = dms.lat == 'S' ? -p.lat : p.lat;
    p.lon = dms.lon == 'W' ? -p.lon : p.lon;
    return p;
}

POSITION_LIB_INLINE position_ddm dd_to_ddm(position_dd dd)
{
    position_ddm ddm;
    std::tie(ddm.lat_d, ddm.lat_m) = dd_to_ddm(dd.lat);
    std::tie(ddm.lon_d, ddm.lon_m) = dd_to_ddm(dd.lon);
    ddm.lat = dd.lat > 0 ? 'N' : 'S';
    ddm.lon = dd.lon > 0 ? 'E' : 'W';
    return ddm;
}

POSITION_LIB_INLINE std::tuple<int, double> dd_to_ddm(double dd)
{
    int d, m;
    double s;
    std::tie(d, m, s) = dd_to_dms(dd);
    double m_s = m + (s / 60.0);
    return std::make_tuple(d, m_s);
}

POSITION_LIB_INLINE position_dms dd_to_dms(position_dd dd)
{
    position_dms dms;
    std::tie(dms.lat_d, dms.lat_m, dms.lat_s) = dd_to_dms(dd.lat);
    std::tie(dms.lon_d, dms.lon_m, dms.lon_s) = dd_to_dms(dd.lon);
    dms.lat = dd.lat > 0 ? 'N' : 'S';
    dms.lon = dd.lon > 0 ? 'E' : 'W';
    return dms;
}

POSITION_LIB_INLINE std::tuple<int, int, double> dd_to_dms(double dd)
{
    // Example algorithm:
    //
    // Input DD = 37.7749
    // 
    // D = integer part of 37.7749 = 37
    // DM = fractional part of 37.7749 * 60 = 0.7749 * 60 = 46.494
    // M = integer part of 46.494 = 46
    // S = fractional part of 46.494 * 60 = 0.494 * 60 = 29.64
    // 
    // Output DMS = 37° 46' 29.64"

    double d, dm, m, s;
    dd = std::abs(dd);
    dm = std::modf(dd, &d);
    dm = dm * 60.0;
    s = std::modf(dm, &m);
    s = s * 60.0;
    return std::make_tuple((int)d, (int)m, s);
}

POSITION_LIB_DETAIL_NAMESPACE_END

#endif

POSITION_LIB_NAMESPACE_END