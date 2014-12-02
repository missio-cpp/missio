@ECHO OFF

pushd %~DP0\build
SET BUILD_ROOT=%CD%
popd

IF /I "%PROCESSOR_ARCHITECTURE%" == "amd64" (
    ECHO Detected 64-bit operating system
    CALL "%BUILD_ROOT%/win/build.bat" address-model=64 %*
) ELSE IF /I "%PROCESSOR_ARCHITECTURE%" == "x86" (
    ECHO Detected 32-bit operating system
    CALL "%BUILD_ROOT%/win/build.bat" address-model=32 %*
) ELSE (
    ECHO Current operating system is not supported
    EXIT /B 1
)
