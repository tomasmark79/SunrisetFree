import os, json, uuid
from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, CMakeDeps
from conan.tools.system import package_manager
from conan.tools.files import copy

# DO NOT use cmake_layout(self) in the recipe.
# ----------------------------------------- --
    # DotNameCpp is using self layout       --
    # to define build ouput layout!         --
    # ├── Build                             --
    #     ├── Artefacts - tarballs          --
    #     ├── Install - final installation  --
    #     ├── Library - library build       --
    #     └── Standalone - standalone build --
# ----------------------------------------- --

class DotNameCppRecipe(ConanFile):
    name = "sunrisetlib"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    def generate(self): 
        cmake_toolchain = CMakeToolchain(self)
    
        # Dynamic change of names of CMakePresets.json
        preset_file = "CMakePresets.json"
        if os.path.exists(preset_file):
            with open(preset_file, "r", encoding="utf-8") as f:
                data = json.load(f)
            build_suffix = f"{self.settings.arch}-{uuid.uuid4().hex[:8]}"
            name_mapping = {}
            for preset in data.get("configurePresets", []):
                old_name = preset["name"]
                new_name = f"{old_name}-{build_suffix}"
                preset["name"] = new_name
                preset["displayName"] = f"{preset['displayName']} ({build_suffix})"
                name_mapping[old_name] = new_name  # Uložení pro reference
            for preset in data.get("buildPresets", []):
                if preset["configurePreset"] in name_mapping:
                    preset["name"] = name_mapping[preset["configurePreset"]]
                    preset["configurePreset"] = name_mapping[preset["configurePreset"]]
            for preset in data.get("testPresets", []):
                if preset["configurePreset"] in name_mapping:
                    preset["name"] = name_mapping[preset["configurePreset"]]
                    preset["configurePreset"] = name_mapping[preset["configurePreset"]]
            with open(preset_file, "w", encoding="utf-8") as f:
                json.dump(data, f, indent=4)

    # Consuming recipe
    def configure(self):
        self.options["*"].shared = False # this replaced shared flag from SolutionController.py and works

    def requirements(self):
        self.requires("fmt/[~11.1]") # required by cpm package
        # self.requires("zlib/[~1.3]")
        # self.requires("nlohmann_json/[~3.11]")
        # self.requires("yaml-cpp/0.8.0")

    def build_requirements(self):
        self.tool_requires("cmake/[>3.14]")

    def imports(self):
        self.copy("license*", dst="licenses", folder=True, ignore_case=True)

    # def system_requirements(self):
        # dnf = package_manager.Dnf(self)
        # dnf.install("SDL2-devel")
        # apt = package_manager.Apt(self)
        # apt.install(["libsdl2-dev"])
        # yum = package_manager.Yum(self)
        # yum.install("SDL2-devel")
        # brew = package_manager.Brew(self)
        # brew.install("sdl2")

    # TO DO 
    # # ----------------------------------------------------------    
    # # Creating basic library recipe
    # # ----------------------------------------------------------
    
    # # Optional metadata
    # license = "<Put the package license here>"
    # author = "<Put your name here> <And your email here>"
    # url = "<Package recipe repository url here, for issues about the package>"
    # description = "<Description of hello package here>"
    # topics = ("<Put some tag here>", "<here>", "<and here>")
   
    # # Sources are located in the same place as this recipe, copy them to the recipe
    # exports_sources = "CMakeLists.txt", "src/*", "include/*", "cmake/*", "LICENSE", "README.md"
    
    # def config_options(self):
    #     if self.settings.os == "Windows":
    #         del self.options.fPIC

    # def build(self):
    #     cmake = CMake(self)
    #     cmake.configure()
    #     cmake.build()

    # def package(self):
    #     cmake = CMake(self)
    #     cmake.install()

    # def package_info(self):
    #     self.cpp_info.libs = ["sunrisetlib"]
