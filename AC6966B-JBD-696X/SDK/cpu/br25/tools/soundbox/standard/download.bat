@echo off

cd %~dp0

copy ..\..\script.ver .
copy ..\..\uboot.boot .
copy ..\..\ota.bin .

..\..\isd_download.exe -tonorflash -dev br25 -boot 0x12000 -div8 -wait 300 -uboot uboot.boot -app app.bin cfg_tool.bin -res tone.cfg eq_cfg_hw.bin -uboot_compress -format all 
:: -format all
::-reboot 2500

  

@rem ɾ    ʱ ļ -format all
if exist *.mp3 del *.mp3 
if exist *.PIX del *.PIX
if exist *.TAB del *.TAB
if exist *.res del *.res
if exist *.sty del *.sty



@rem    ɹ̼      ļ 
..\..\fw_add.exe -noenc -fw jl_isd.fw  -add ota.bin -type 100 -out jl_isd.fw
@rem       ýű  İ汾  Ϣ   FW  ļ   
..\..\fw_add.exe -noenc -fw jl_isd.fw -add script.ver -out jl_isd.fw


..\..\ufw_maker.exe -fw_to_ufw jl_isd.fw
copy jl_isd.ufw update.ufw
del jl_isd.ufw


@REM          ļ      ļ 
::ufw_maker.exe -chip AC800X %ADD_KEY% -output config.ufw -res bt_cfg.cfg

::IF EXIST jl_696x.bin del jl_696x.bin 


@rem         ˵  
@rem -format vm        //    VM     
@rem -format cfg       //    BT CFG     
@rem -format 0x3f0-2   //  ʾ ӵ  0x3f0    sector   ʼ         2    sector(  һ      Ϊ16   ƻ 10   ƶ  ɣ  ڶ             10    )

ping /n 2 127.1>null
IF EXIST null del null
