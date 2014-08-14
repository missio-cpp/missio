@ECHO OFF

pushd %~DP0\..\..
SET MISSIO_ROOT=%CD%
popd

:: Check if BOOST_ROOT is set
IF NOT DEFINED BOOST_ROOT (
    ECHO Required environment variable BOOST_ROOT is not set
    ECHO Please set it to point to the root of BOOST distribution
    EXIT /B 1
)

:: Remove quotes
SET BOOST_ROOT=%BOOST_ROOT:"=%

:: Remove trailing backslash
IF "%BOOST_ROOT:~-1%" == "\" (
    SET BOOST_ROOT=%BOOST_ROOT:~0,-1%
)

ECHO MISSIO_ROOT = %MISSIO_ROOT%
ECHO BOOST_ROOT = %BOOST_ROOT%

IF NOT EXIST "%MISSIO_ROOT%\Jamroot" (
    ECHO Could not find Jamroot file required to build missio
    EXIT /B 1
)

IF NOT EXIST "%BOOST_ROOT%\boost-build.jam" (
    ECHO Environment variable BOOST_ROOT does not point to a BOOST distribution
    EXIT /B 1
)

SET BOOST_JAM=%BOOST_ROOT%\bjam.exe
SET BOOST_JAM_LOG=%BOOST_ROOT%\bjam.log
SET BOOST_BUILD_PATH=%BOOST_ROOT%\tools\build\v2

IF NOT EXIST "%BOOST_JAM%" (
    IF NOT EXIST "%BOOST_ROOT%\bootstrap.bat" (
        ECHO Could not find file bootstrap.bat required to build Boost.Jam build engine
        EXIT /B 1
    )

    pushd "%BOOST_ROOT%"

    ECHO Building Boost.Jam build engine
    CALL bootstrap.bat > NUL

    popd

    IF ERRORLEVEL 1 (
        ECHO Error building Boost.Jam build engine.
        ECHO See %BOOST_JAM_LOG% for details.
        EXIT /B 1
    )
)

pushd "%MISSIO_ROOT%"

SET JOBS_NUM=%NUMBER_OF_PROCESSORS%

IF %JOBS_NUM% LEQ 0 (
    SET JOBS_NUM=2
)

SET BOOST_ROOT="%BOOST_ROOT%"
SET BOOST_BUILD_PATH="%BOOST_BUILD_PATH%"

ECHO Starting build of missio
"%BOOST_JAM%" -q -j%JOBS_NUM% %*

popd
