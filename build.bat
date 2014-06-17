@ECHO OFF

pushd %~DP0\build
SET BUILD_ROOT=%CD%
popd

IF /I "%PROCESSOR_ARCHITECTURE%" == "amd64" (
    ECHO Detected 64-bit Windows operating system
    CALL "%BUILD_ROOT%/windows/build64.bat" %*
) ELSE IF /I "%PROCESSOR_ARCHITECTURE%" == "x86" (
    ECHO Detected 32-bit Windows operating system
    CALL "%BUILD_ROOT%/windows/build32.bat" %*
) ELSE (
    ECHO Current operating system is not supported
    EXIT /B 1
)
