import os

from conans import ConanFile, tools


class PssimplesafeintConan(ConanFile):
    name = "pssimplesafeint"
    version = "0.1"
    license = "MIT license"
    author = "Peter Sommerlad peter.cpp@sommerlad.ch"
    url = "https://github.com/PeterSommerlad/PSsimplesafeint"
    description = "A single header library for integers without UB (but wrapping)"
    topics = ("C++", "MISRA-C++ compliance", "Safe C++")
    no_copy_source = True
    exports_sources = "include/*"
    # No settings/options are necessary, this is header only

    def source(self):
         '''retrieval of the source code here. Remember you can also put the code
         in the folder and use exports instead of retrieving it with this
         source() method
         '''
         self.run("git clone https://github.com/PeterSommerlad/PSsimplesafeint.git") 

    def package(self):
        self.copy("*.h")

    def package_id(self):
        self.info.header_only()
