@ECHO Remnants of Storied Encounters Windows Code Update
@ECHO WIP by Umbrella Wizard

@ECHO Refer to the included readme for useful information.
@PAUSE

@IF EXIST %SYSTEMDRIVE%\dsbackup\lib\log\* (
   IF EXIST %SYSTEMDRIVE%\dsbackup\lib\save\* (
      IF EXIST %SYSTEMDRIVE%\dsbackup\lib\secure\save\* (
         IF EXIST %SYSTEMDRIVE%\dsbackup\lib\estates\* (
                  rmdir /S/Q %SYSTEMDRIVE%\ds\lib\estates\
                  rmdir /S/Q %SYSTEMDRIVE%\ds\lib\secure\save\
                  rmdir /S/Q %SYSTEMDRIVE%\ds\lib\save\
                  rmdir /S/Q %SYSTEMDRIVE%\ds\lib\profiles\
                  rmdir /S/Q %SYSTEMDRIVE%\ds\lib\log\

                  xcopy /Y %SYSTEMDRIVE%\dsbackup\lib\estates\* %SYSTEMDRIVE%\ds\lib\estates\ /E/R/H
                  xcopy /Y %SYSTEMDRIVE%\dsbackup\lib\secure\save\* %SYSTEMDRIVE%\ds\lib\secure\save\ /E/R/H
                  xcopy /Y %SYSTEMDRIVE%\dsbackup\lib\save\* %SYSTEMDRIVE%\ds\lib\save\ /E/R/H
                  xcopy /Y %SYSTEMDRIVE%\dsbackup\lib\log\* %SYSTEMDRIVE%\ds\lib\log\ /E/R/H
         )
      )
   )

)

xcopy /Y lib\* %SYSTEMDRIVE%\ds\lib\* /E/R/H
