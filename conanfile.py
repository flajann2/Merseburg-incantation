from conans import ConanFile, CMake, tools


class MerseburgincantationConan(ConanFile):
    name = "merseburg-incantation"
    version = "0.0.1"
    license = "MIT"
    author = "Fred Mitchell fred.mitchell@gmx.de"
    url = "https://github.com/flajann2/merseburg-incantation.git"
    description = "Merseburg process collections as theads across your cores"
    topics = ("concurrency", "threads", "workers", "cores")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"

    def source(self):
        self.run("git clone https://github.com/flajann2/merseburg-incantation.git")
        # This small hack might be useful to guarantee proper /MT /MD linkage
        # in MSVC if the packaged project doesn't have variables to set it
        # properly
        tools.replace_in_file("merseburg-incantation/CMakeLists.txt", "PROJECT(merseburg-incantation)",
                              '''PROJECT(merseburg-incantation)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()''')

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="merseburg-incantation")
        cmake.build()

        # Explicit way:
        # self.run('cmake %s/merseburg-incantation %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include", src="merseburg-incantation")

    def package_info(self):
        self.cpp_info.libs = ["merseburg-incantation"]

