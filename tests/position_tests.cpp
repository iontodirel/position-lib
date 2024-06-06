#include <gtest/gtest.h>

#include "../position.hpp"

#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>

using namespace position;

TEST(Position, DDMPositionConversions)
{
    position_dd dd_original(47.620500, -122.349300);
    position_ddm ddm = dd_original;

    position_dd dd = ddm;
    position_dms dms = ddm;
}

TEST(Position, DMSPositionConversions)
{
    position_dd dd_original(47.620500, -122.349300);
    position_dms dms = dd_original;

    position_dd dd = dms;
    position_ddm ddm = dms;
}

TEST(Position, DDPositionConversions)
{
    position_dd dd(47.620500, -122.349300);

    position_ddm ddm = dd;
    EXPECT_TRUE(ddm.lat == 'N');
    EXPECT_TRUE(ddm.lat_d == 47);
    EXPECT_TRUE(ddm.lat_m >= 37.2299999 && ddm.lat_m < 37.23);
    EXPECT_TRUE(ddm.lon == 'W');
    EXPECT_TRUE(ddm.lon_d == 122);
    EXPECT_TRUE(ddm.lon_m >= 20.957999 && ddm.lon_m < 20.958);

    position_dms dms = dd;
    EXPECT_TRUE(dms.lat == 'N');
    EXPECT_TRUE(dms.lat_d == 47);
    EXPECT_TRUE(dms.lat_m == 37);
    EXPECT_TRUE(dms.lat_s >= 13.7999999 && dms.lat_s <= 13.8);
    EXPECT_TRUE(dms.lon == 'W');
    EXPECT_TRUE(dms.lon_d == 122);
    EXPECT_TRUE(dms.lon_m == 20);
    EXPECT_TRUE(dms.lon_s >= 57.4799999 && dms.lon_s <= 57.48);
}

TEST(PositionDetail, pretty_number_str)
{
    std::string res;
    EXPECT_TRUE((res = format_number_to_string(12.3456789, 0)) == "12");
    EXPECT_TRUE((res = format_number_to_string(12.3456789, 1)) == "12.3");
    EXPECT_TRUE((res = format_number_to_string(12.3456789, 2)) == "12.35");
    EXPECT_TRUE((res = format_number_to_string(12.3456789, 3)) == "12.346");
    EXPECT_TRUE((res = format_number_to_string(12.3456789, 4)) == "12.3457");
    EXPECT_TRUE((res = format_number_to_string(12.3456789, 5)) == "12.34568");
    EXPECT_TRUE((res = format_number_to_string(12.3456789, 6)) == "12.345679");    
    EXPECT_TRUE((res = format_number_to_string(12.3456789, 7)) == "12.3456789");
    EXPECT_TRUE((res = format_number_to_string(12.3456789, 10)) == "12.3456789000");
}

TEST(Position, FormattingSpaceNeedle)
{
    position_dd dd(47.620500, -122.349300);
    position_ddm ddm = dd;
    position_dms dms = dd;

    position_display_string dd_fmt = format(dd, position_dd_format);
    EXPECT_TRUE(dd_fmt.lat == "47.620500");
    EXPECT_TRUE(dd_fmt.lon == "-122.349300");

    position_display_string ddm_fmt = format(ddm, position_ddm_format);
    EXPECT_TRUE(ddm_fmt.lat == "47°37.230'N");
    EXPECT_TRUE(ddm_fmt.lon == "122°20.958'W");

    position_display_string dms_fmt = format(dms, position_dms_format);
    EXPECT_TRUE(dms_fmt.lat == "47°37'13.80\"N");
    EXPECT_TRUE(dms_fmt.lon == "122°20'57.48\"W");
}

TEST(Position, FormattingMuseumOfFlight)
{
    position_dd dd(47.51863818403278, -122.29686387310251);
    position_ddm ddm = dd;
    position_dms dms = dd;

    position_display_string dd_fmt = format(dd, position_dd_format);
    EXPECT_TRUE(dd_fmt.lat == "47.518638");
    EXPECT_TRUE(dd_fmt.lon == "-122.296864");

    position_display_string ddm_fmt = format(ddm, position_ddm_format);
    EXPECT_TRUE(ddm_fmt.lat == "47°31.118'N");
    EXPECT_TRUE(ddm_fmt.lon == "122°17.812'W");

    position_display_string dms_fmt = format(dms, position_dms_format);
    EXPECT_TRUE(dms_fmt.lat == "47°31'7.10\"N");
    EXPECT_TRUE(dms_fmt.lon == "122°17'48.71\"W");
}

TEST(Position, FormattingEiffelTower)
{
    position_dd dd(48.858553598330445, 2.2944812975469286);
    position_ddm ddm = dd;
    position_dms dms = dd;

    position_display_string dd_fmt = format(dd, position_dd_format);
    EXPECT_TRUE(dd_fmt.lat == "48.858554");
    EXPECT_TRUE(dd_fmt.lon == "2.294481");

    position_display_string ddm_fmt = format(ddm, position_ddm_format);
    EXPECT_TRUE(ddm_fmt.lat == "48°51.513'N");
    EXPECT_TRUE(ddm_fmt.lon == "2°17.669'E");

    position_display_string ddm_short_fmt = format(ddm, position_ddm_short_format);
    EXPECT_TRUE(ddm_short_fmt.lat == "4851.51N");
    EXPECT_TRUE(ddm_short_fmt.lon == "217.67E");

    position_display_string dms_fmt = format(dms, position_dms_format);
    EXPECT_TRUE(dms_fmt.lat == "48°51'30.79\"N");
    EXPECT_TRUE(dms_fmt.lon == "2°17'40.13\"E");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
