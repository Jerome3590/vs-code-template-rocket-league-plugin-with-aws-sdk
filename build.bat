mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_GENERATOR_PLATFORM=x64 -DVCPKG_TARGET_TRIPLET=x64-windows-static -DCMAKE_TOOLCHAIN_FILE=D:/Rocket_League_Plugin_with_AWS_SDK/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
cd ..