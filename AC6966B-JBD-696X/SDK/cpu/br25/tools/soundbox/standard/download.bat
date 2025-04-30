@echo off

cd %~dp0

copy ..\..\script.ver .
copy ..\..\uboot.boot .
copy ..\..\ota.bin .

..\..\isd_download.exe -tonorflash -dev br25 -boot 0x12000 -div8 -wait 300 -uboot uboot.boot -app app.bin cfg_tool.bin -res tone.cfg eq_cfg_hw.bin -uboot_compress -format all
:: -format all
::-reboot 2500

  

@rem ??????  
if exist *.mp3 del *.mp3 
if exist *.PIX del *.PIX
if exist *.TAB del *.TAB
if exist *.res del *.res
if exist *.sty del *.sty

@rem ??????  
..\..\fw_add.exe -noenc -fw jl_isd.fw  -add ota.bin -type 100 -out jl_isd.fw  
@rem ??????  
..\..\fw_add.exe -noenc -fw jl_isd.fw -add script.ver -out jl_isd.fw

@rem ??? UFW  
..\..\ufw_maker.exe -fw_to_ufw jl_isd.fw  
copy jl_isd.ufw update.ufw  
del jl_isd.ufw

@rem ????  
ping /n 2 127.0.0.1 >nul
