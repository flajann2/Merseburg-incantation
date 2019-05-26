from conans import ConanFile, CMake, tools


class MerseburgincantationConan(ConanFile):
    name = "merseburg-incantation"
    version = "0.0.1"
    license = "MIT"
    author = "Fred Mitchell fred.mitchell@gmx.de"
    url = "https://github.com/flajann2/merseburg-incantation.git"
    description = "Merseburg process collections as theads across your cores"
    topics = ("concurrency", "threads", "workers", "cores")
    exports_sources = "include/*"
    no_copy_source = True

    def package(self):
        self.copy("*.h", dst="include", src="merseburg-incantation")

    def package_info(self):
        self.cpp_info.libs = ["merseburg-incantation"]

