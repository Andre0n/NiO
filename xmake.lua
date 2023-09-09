add_rules("mode.debug", "mode.release")

target("nio")
    set_kind("binary")
    add_files("src/*.cpp")
    set_warnings("all", "error")
    set_languages("c++20")
    add_includedirs("include")
    set_toolset("cxx", "clang++")

