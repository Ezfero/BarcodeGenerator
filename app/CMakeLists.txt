cmake_minimum_required(VERSION 3.4.1)
add_library( barcodegenerator-lib SHARED

             src/main/cpp/common/BarcodeGenerator.cpp
             src/main/cpp/common/code128/CharacterSet.cpp
             src/main/cpp/common/code128/CharacterRow.cpp
             src/main/cpp/common/json/json11.cpp
             src/main/cpp/android/AndroidBarcodeGenerator.cpp

             src/main/cpp/common/QRCodeGenerator.cpp
             src/main/cpp/common/ResourceLoader.cpp
             src/main/cpp/common/qr/Version.cpp
             src/main/cpp/common/qr/VersionFactory.cpp
             src/main/cpp/common/qr/util/MatrixUtil.cpp
             src/main/cpp/common/qr/encoders/Encoder.cpp
             src/main/cpp/common/qr/encoders/NumericEncoder.cpp
             src/main/cpp/common/qr/encoders/AlphanumericEncoder.cpp
             src/main/cpp/common/qr/encoders/ByteEncoder.cpp
             src/main/cpp/common/qr/encoders/EncoderFactory.cpp
             src/main/cpp/common/qr/errorCorrection/ErrorCorrector.cpp
             src/main/cpp/common/qr/errorCorrection/Polynomial.cpp
             src/main/cpp/common/qr/errorCorrection/LogAntilogTable.cpp
             src/main/cpp/common/qr/masking/MatrixMasker.cpp
             src/main/cpp/common/qr/masking/MaskersFactory.cpp

             src/main/cpp/android/AssetLoader.cpp
             src/main/cpp/android/AndroidQRCodeGenerator.cpp

             src/main/cpp/barcodegenerator-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       barcodegenerator-lib
                       android

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib})
