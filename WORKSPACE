load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "raylib",
    urls = ["https://github.com/raysan5/raylib/releases/download/3.0.0/raylib-3.0.0-Win64-msvc15.zip"],
    sha256 = "0b4db4212f443d733dd165b034317c9dd7a36e7d6415a4185d1984a18dc2314f",
    build_file = "@//:raylib.BUILD",
    strip_prefix = "raylib-3.0.0-Win64-msvc15",
)

http_archive(
    name = "gtest",
    url = "https://github.com/google/googletest/archive/release-1.7.0.zip",
    sha256 = "b58cb7547a28b2c718d1e38aee18a3659c9e3ff52440297e965f5edffe34b6d0",
    build_file = "@//:gtest.BUILD",
    strip_prefix = "googletest-release-1.7.0",
)

http_archive(
    name = "glfw",
    url = "https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.bin.WIN64.zip",
    sha256 = "aa291d8dce27d9e6cd567dc56e3768dcefceb3ddb7a65fb4cc3ef35be2a7548c",
    build_file = "@//:glfw.BUILD",
    strip_prefix = "glfw-3.3.2.bin.WIN64",
)
