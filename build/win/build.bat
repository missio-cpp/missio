@ECHO OFF

pushd %~DP0\..\..
SET MISSIO_ROOT=%CD%
popd

ECHO MISSIO_ROOT = %MISSIO_ROOT%

IF NOT EXIST "%MISSIO_ROOT%\Jamroot" (
    ECHO Could not find file "Jamroot" required to build missio
    EXIT /B 1
)

:: Check if BOOST_ROOT is set
IF DEFINED BOOST_ROOT (
    :: Remove quotes
    SET BOOST_ROOT=%BOOST_ROOT:"=%

    :: Remove trailing backslash
    IF "%BOOST_ROOT:~-1%" == "\" (
        SET BOOST_ROOT=%BOOST_ROOT:~0,-1%
    )

    ECHO BOOST_ROOT = %BOOST_ROOT%

    IF NOT EXIST "%BOOST_ROOT%\boost-build.jam" (
        ECHO Environment variable BOOST_ROOT does not point to a BOOST distribution
        EXIT /B 1
    )

    SET BOOST_JAM=%BOOST_ROOT%\bjam.exe
    SET BOOST_JAM_LOG=%BOOST_ROOT%\bjam.log
    SET BOOST_BUILD_PATH=%BOOST_ROOT%\tools\build\v2

    IF NOT EXIST "%BOOST_JAM%" (
        IF NOT EXIST "%BOOST_ROOT%\bootstrap.bat" (
            ECHO Could not find file "bootstrap.bat" required to build Boost.Jam build engine
            EXIT /B 1
        )

        pushd "%BOOST_ROOT%"

        ECHO Building Boost.Jam build engine
        CALL bootstrap.bat > NUL

        popd

        IF ERRORLEVEL 1 (
            ECHO Error building Boost.Jam build engine
            ECHO See %BOOST_JAM_LOG% for details
            EXIT /B 1
        )
    )
) ELSE (
    SET BOOST_JAM=bjam.exe
)

IF NOT EXIST "%BOOST_JAM%" (
    ECHO Could not find file "%BOOST_JAM%" required to build missio
    EXIT /B 1
)

pushd "%MISSIO_ROOT%"

ECHO Starting build of missio
"%BOOST_JAM%" -q %*

IF ERRORLEVEL 1 (
    ECHO Error building missio
    EXIT /B 1
)

popd
