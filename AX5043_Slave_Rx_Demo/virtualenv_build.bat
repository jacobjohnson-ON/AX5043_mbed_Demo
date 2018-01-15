@ECHO OFF

cd C:\virtualenvs\mbed\Scripts 
call activate 

cd C:\Users\ffwxjw\Documents\GitHub\AX5043_Slave_Rx_Demo
@ECHO ON

::set PATH = %PATH%;C:\Keil_v5\ARM\ARMCC\bin

::mbed compile -m NCS36510 -t GCC_ARM -f --profile mbed-os/tools/profiles/debug.json
::mbed compile -m NCS36510 -t GCC_ARM -f -c --profile mbed-os/tools/profiles/debug.json

::mbed compile -m NCS36510 -t IAR -f --profile mbed-os/tools/profiles/debug.json
::mbed compile -m NCS36510 -t IAR -f -c --profile mbed-os/tools/profiles/debug.json

::mbed compile -m NCS36510 -t ARM -f -c --profile mbed-os/tools/profiles/debug.json

::mbed compile -m K64F -t GCC_ARM -f -c --profile mbed-os/tools/profiles/debug.json
mbed compile -m K64F -t GCC_ARM -f --profile mbed-os/tools/profiles/debug.json

::mbed compile -m K64F -t GCC_ARM -c
::mbed compile -m NCS36510 -t GCC_ARM -c

