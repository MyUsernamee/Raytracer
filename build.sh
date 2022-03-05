# First we are going to check if the user has all of the things we need like
#     vcpkg
#     cmake
#     ninja

if ! command -v vcpkg &> /dev/null
then
    echo "vcpkg is not installed"
    exit 1
fi
if ! command -v cmake &> /dev/null
then
    echo "cmake is not installed"
    exit 1
fi
if ! command -v ninja &> /dev/null
then
    echo "ninja is not installed"
    exit 1
fi
if [ ! -v VCPKG_ROOT ]
then
    echo "VCPKG_ROOT is not set"
    echo "User \"./vcpkg integrate install\" in the vcpkg directory to set it"
    exit 1
fi

echo "All dependencies are installed"

vcpkg install pngpp
vcpkg install glm

mkdir build
cd build
cmake ../ -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=release -DCMAKE_MAKE_PROGRAM=ninja -G Ninja
ninja

echo "Build complete"

