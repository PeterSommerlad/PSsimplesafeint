import os

from conans import ConanFile, CMake, tools


class PssimplesafeintTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    def build(self):
        cmake = CMake(self, set_cmake_flags=True)
        # Current dir is "test_package/build/<build_id>" and CMakeLists.txt is
        # in "test_package"
        myargs = ["-DCMAKE_CXX_COMPILER=g++-10"]
        cmake.configure(args=myargs)
        cmake.build()

    def imports(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy('*.so*', dst='bin', src='lib')

    def test(self):
        if not tools.cross_building(self):
            os.chdir("bin")
            self.run(".%sexample" % os.sep)
