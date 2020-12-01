/*****************************************************************
**                                                              **
**  syRF                                                        **
**  Copyright (C) 2019-2020 Francesco Urbani                    **
**                                                              **
******************************************************************
**  Author:    Francesco Urbani <https://urbanij.github.io/>    **
**  Date:      Tue Apr 21 10:28:31 CEST 2020                    **
**  File:           tests_regex.cpp                             **
**  Description:                                                **
**
**  g++ -std=c++17 tests_regex.cpp utils.cpp -lgtest -lgtest_main -pthread -o tests_regex && ./tests_regex
*****************************************************************/
#include <gtest/gtest.h>

#include "utils.h"



TEST(regex_param, Test1) {
    const std::string s = "MRF571, Vce=6 V, Ic=5 mA, f=200 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               200);
}

TEST(regex_param, Test2) {
    const std::string s = "MRF571, Vce=6 V, Ic=5 mA, f=500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               500);
}

TEST(regex_param, Test3) {
    const std::string s = "MRF571, Vce=6 V, Ic=5 mA, f=1000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               1000);
}

TEST(regex_param, Test4) {
    const std::string s = "MRF571, Vce=6 V, Ic=5 mA, f=1500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               1500);
}

TEST(regex_param, Test5) {
    const std::string s = "MRF571, Vce=6 V, Ic=5 mA, f=2000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               2000);
}

TEST(regex_param, Test6) {
    const std::string s = "MRF571, Vce=6 V, Ic=10 mA, f=200 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               200);
}

TEST(regex_param, Test7) {
    const std::string s = "MRF571, Vce=6 V, Ic=10 mA, f=500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               500);
}

TEST(regex_param, Test8) {
    const std::string s = "MRF571, Vce=6 V, Ic=10 mA, f=1000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               1000);
}

TEST(regex_param, Test9) {
    const std::string s = "MRF571, Vce=6 V, Ic=10 mA, f=1500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               1500);
}

TEST(regex_param, Test10) {
    const std::string s = "MRF571, Vce=6 V, Ic=10 mA, f=2000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               2000);
}

TEST(regex_param, Test11) {
    const std::string s = "MRF571, Vce=6 V, Ic=50 mA, f=200 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               200);
}

TEST(regex_param, Test12) {
    const std::string s = "MRF571, Vce=6 V, Ic=50 mA, f=500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               500);
}

TEST(regex_param, Test13) {
    const std::string s = "MRF571, Vce=6 V, Ic=50 mA, f=1000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               1000);
}

TEST(regex_param, Test14) {
    const std::string s = "MRF571, Vce=6 V, Ic=50 mA, f=1500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               1500);
}

TEST(regex_param, Test15) {
    const std::string s = "MRF571, Vce=6 V, Ic=50 mA, f=2000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               2000);
}

TEST(regex_param, Test16) {
    const std::string s = "MRF571, Vce=8 V, Ic=5 mA, f=200 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               200);
}

TEST(regex_param, Test17) {
    const std::string s = "MRF571, Vce=8 V, Ic=5 mA, f=500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               500);
}

TEST(regex_param, Test18) {
    const std::string s = "MRF571, Vce=8 V, Ic=5 mA, f=1000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               1000);
}

TEST(regex_param, Test19) {
    const std::string s = "MRF571, Vce=8 V, Ic=5 mA, f=1500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               1500);
}

TEST(regex_param, Test20) {
    const std::string s = "MRF571, Vce=8 V, Ic=5 mA, f=2000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               2000);
}

TEST(regex_param, Test21) {
    const std::string s = "MRF571, Vce=8 V, Ic=10 mA, f=200 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               200);
}

TEST(regex_param, Test22) {
    const std::string s = "MRF571, Vce=8 V, Ic=10 mA, f=500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               500);
}

TEST(regex_param, Test23) {
    const std::string s = "MRF571, Vce=8 V, Ic=10 mA, f=1000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               1000);
}

TEST(regex_param, Test24) {
    const std::string s = "MRF571, Vce=8 V, Ic=10 mA, f=1500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               1500);
}

TEST(regex_param, Test25) {
    const std::string s = "MRF571, Vce=8 V, Ic=10 mA, f=2000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               2000);
}

TEST(regex_param, Test26) {
    const std::string s = "MRF571, Vce=8 V, Ic=50 mA, f=200 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               200);
}

TEST(regex_param, Test27) {
    const std::string s = "MRF571, Vce=8 V, Ic=50 mA, f=500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               500);
}

TEST(regex_param, Test28) {
    const std::string s = "MRF571, Vce=8 V, Ic=50 mA, f=1000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               1000);
}

TEST(regex_param, Test29) {
    const std::string s = "MRF571, Vce=8 V, Ic=50 mA, f=1500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               1500);
}

TEST(regex_param, Test30) {
    const std::string s = "MRF571, Vce=8 V, Ic=50 mA, f=2000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF571");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               2000);
}

TEST(regex_param, Test31) {
    const std::string s = "MRF572, Vce=6 V, Ic=5 mA, f=200 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               200);
}

TEST(regex_param, Test32) {
    const std::string s = "MRF572, Vce=6 V, Ic=5 mA, f=500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               500);
}

TEST(regex_param, Test33) {
    const std::string s = "MRF572, Vce=6 V, Ic=5 mA, f=1000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               1000);
}

TEST(regex_param, Test34) {
    const std::string s = "MRF572, Vce=6 V, Ic=5 mA, f=1500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               1500);
}

TEST(regex_param, Test35) {
    const std::string s = "MRF572, Vce=6 V, Ic=5 mA, f=2000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               2000);
}

TEST(regex_param, Test36) {
    const std::string s = "MRF572, Vce=6 V, Ic=10 mA, f=200 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               200);
}

TEST(regex_param, Test37) {
    const std::string s = "MRF572, Vce=6 V, Ic=10 mA, f=500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               500);
}

TEST(regex_param, Test38) {
    const std::string s = "MRF572, Vce=6 V, Ic=10 mA, f=1000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               1000);
}

TEST(regex_param, Test39) {
    const std::string s = "MRF572, Vce=6 V, Ic=10 mA, f=1500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               1500);
}

TEST(regex_param, Test40) {
    const std::string s = "MRF572, Vce=6 V, Ic=10 mA, f=2000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               2000);
}

TEST(regex_param, Test41) {
    const std::string s = "MRF572, Vce=6 V, Ic=50 mA, f=200 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               200);
}

TEST(regex_param, Test42) {
    const std::string s = "MRF572, Vce=6 V, Ic=50 mA, f=500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               500);
}

TEST(regex_param, Test43) {
    const std::string s = "MRF572, Vce=6 V, Ic=50 mA, f=1000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               1000);
}

TEST(regex_param, Test44) {
    const std::string s = "MRF572, Vce=6 V, Ic=50 mA, f=1500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               1500);
}

TEST(regex_param, Test45) {
    const std::string s = "MRF572, Vce=6 V, Ic=50 mA, f=2000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              6);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               2000);
}

TEST(regex_param, Test46) {
    const std::string s = "MRF572, Vce=8 V, Ic=5 mA, f=200 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               200);
}

TEST(regex_param, Test47) {
    const std::string s = "MRF572, Vce=8 V, Ic=5 mA, f=500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               500);
}

TEST(regex_param, Test48) {
    const std::string s = "MRF572, Vce=8 V, Ic=5 mA, f=1000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               1000);
}

TEST(regex_param, Test49) {
    const std::string s = "MRF572, Vce=8 V, Ic=5 mA, f=1500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               1500);
}

TEST(regex_param, Test50) {
    const std::string s = "MRF572, Vce=8 V, Ic=5 mA, f=2000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               5);
    EXPECT_EQ(f0,               2000);
}

TEST(regex_param, Test51) {
    const std::string s = "MRF572, Vce=8 V, Ic=10 mA, f=200 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               200);
}

TEST(regex_param, Test52) {
    const std::string s = "MRF572, Vce=8 V, Ic=10 mA, f=500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               500);
}

TEST(regex_param, Test53) {
    const std::string s = "MRF572, Vce=8 V, Ic=10 mA, f=1000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               1000);
}

TEST(regex_param, Tes54) {
    const std::string s = "MRF572, Vce=8 V, Ic=10 mA, f=1500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               1500);
}

TEST(regex_param, Test55) {
    const std::string s = "MRF572, Vce=8 V, Ic=10 mA, f=2000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               10);
    EXPECT_EQ(f0,               2000);
}

TEST(regex_param, Test56) {
    const std::string s = "MRF572, Vce=8 V, Ic=50 mA, f=200 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               200);
}

TEST(regex_param, Test57) {
    const std::string s = "MRF572, Vce=8 V, Ic=50 mA, f=500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               500);
}

TEST(regex_param, Test58) {
    const std::string s = "MRF572, Vce=8 V, Ic=50 mA, f=1000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               1000);
}

TEST(regex_param, Test59) {
    const std::string s = "MRF572, Vce=8 V, Ic=50 mA, f=1500 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               1500);
}

TEST(regex_param, Test60) {
    const std::string s = "MRF572, Vce=8 V, Ic=50 mA, f=2000 MHz";
    std::string transistor_name;
    int Vce, Ic, f0;
    filter_S_transistor_bias_settings(s, transistor_name, Vce, Ic, f0);
    EXPECT_EQ(transistor_name, "MRF572");
    EXPECT_EQ(Vce,              8);
    EXPECT_EQ(Ic,               50);
    EXPECT_EQ(f0,               2000);
}


int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
