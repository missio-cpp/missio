@ECHO OFF

pushd %~DP0
SET BUILD_ROOT=%CD%
popd

CALL "%BUILD_ROOT%\build.bat" address-model=32 %*
