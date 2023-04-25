@echo off

@REM set firmware-bin=".\firmware.bin"
@REM set partitions-bin=".\partitions.bin"
set firmware-bin="..\.pio\build\GoWannaGo\firmware.bin"
set partitions-bin="..\.pio\build\GoWannaGo\partitions.bin"
set COM=COM5

echo Uploading %firmware-bin% and %partitions-bin% to esp32 with COM port: %COM%

@REM set /p COM="Enter comport number of the microcontroller: "
@REM set COM=COM%COM%
@REM echo Com port entered: %COM%


.\esptool.exe --chip esp32 --port %COM% --baud 1500000 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 .\boot_app0.bin 0x1000 .\bootloader_dio_80m.bin 0x10000 %firmware-bin% 0x8000 %partitions-bin%

:End
cmd /k
