"""Build rules for AdicViz."""

load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "adicviz",
    srcs = [
        "main.cpp",
        "Comp.cpp",
        "Comp.h",
        "Svg.cpp",
        "Svg.h",
        "Settings.cpp",
        "Settings.h",
        "Integers.cpp",
        "Integers.h",
        "Fractions.cpp",
        "Fractions.h",
        "BarChart.cpp",
        "BarChart.h",
    ],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["/std:c++11"],
        "//conditions:default": ["-std=c++11"],
    }),
)
