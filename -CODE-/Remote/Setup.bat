@echo off

echo [env:program_via_ArduinoISP]>.\platformio.ini
echo platform = atmelavr>>.\platformio.ini
echo board = 168pa16m>>.\platformio.ini
echo board_build.f_cpu = 16000000L>>.\platformio.ini
echo framework = arduino>>.\platformio.ini
echo.>>.\platformio.ini
echo.>>.\platformio.ini
echo upload_command = avrdude -C${PROJECT_DIR}/avrdude.conf -v -pm168p -cstk500v1 -P$UPLOAD_PORT -b19200 -Uflash:w:$SOURCE:i -Ulfuse:w:0xde:m -Uhfuse:w:0xdf:m -Uefuse:w:0xf9:m>>.\platformio.ini

echo programmer>.\avrdude.conf
echo   id    = "stk500v1";>>.\avrdude.conf
echo   desc  = "Atmel STK500 Version 1.x firmware";>>.\avrdude.conf
echo   type  = "stk500";>>.\avrdude.conf
echo   connection_type = serial;>>.\avrdude.conf
echo ;>>.\avrdude.conf
echo.>>.\avrdude.conf
echo #------------------------------------------------------------>>.\avrdude.conf
echo # ATmega168>>.\avrdude.conf
echo #------------------------------------------------------------>>.\avrdude.conf
echo.>>.\avrdude.conf
echo part>>.\avrdude.conf
echo     id              = "m168";>>.\avrdude.conf
echo     desc            = "ATmega168";>>.\avrdude.conf
echo      has_debugwire = yes;>>.\avrdude.conf
echo      flash_instr   = 0xB6, 0x01, 0x11;>>.\avrdude.conf
echo      eeprom_instr  = 0xBD, 0xF2, 0xBD, 0xE1, 0xBB, 0xCF, 0xB4, 0x00,>>.\avrdude.conf
echo 	             0xBE, 0x01, 0xB6, 0x01, 0xBC, 0x00, 0xBB, 0xBF,>>.\avrdude.conf
echo 	             0x99, 0xF9, 0xBB, 0xAF;>>.\avrdude.conf
echo     stk500_devcode  = 0x86;>>.\avrdude.conf
echo     # avr910_devcode = 0x;>>.\avrdude.conf
echo     signature       = 0x1e 0x94 0x06;>>.\avrdude.conf
echo     pagel           = 0xd7;>>.\avrdude.conf
echo     bs2             = 0xc2;>>.\avrdude.conf
echo     chip_erase_delay = 9000;>>.\avrdude.conf
echo     pgm_enable       = "1 0 1 0 1 1 0 0 0 1 0 1 0 0 1 1",>>.\avrdude.conf
echo                        "x x x x x x x x x x x x x x x x";>>.\avrdude.conf
echo.>>.\avrdude.conf
echo     chip_erase       = "1 0 1 0 1 1 0 0 1 0 0 x x x x x",>>.\avrdude.conf
echo                        "x x x x x x x x x x x x x x x x";>>.\avrdude.conf
echo.>>.\avrdude.conf
echo     timeout         = 200;>>.\avrdude.conf
echo     stabdelay       = 100;>>.\avrdude.conf
echo     cmdexedelay     = 25;>>.\avrdude.conf
echo     synchloops      = 32;>>.\avrdude.conf
echo     bytedelay       = 0;>>.\avrdude.conf
echo     pollindex       = 3;>>.\avrdude.conf
echo     pollvalue       = 0x53;>>.\avrdude.conf
echo     predelay        = 1;>>.\avrdude.conf
echo     postdelay       = 1;>>.\avrdude.conf
echo     pollmethod      = 1;>>.\avrdude.conf
echo.>>.\avrdude.conf
echo     pp_controlstack     =>>.\avrdude.conf
echo 	0x0E, 0x1E, 0x0F, 0x1F, 0x2E, 0x3E, 0x2F, 0x3F,>>.\avrdude.conf
echo 	0x4E, 0x5E, 0x4F, 0x5F, 0x6E, 0x7E, 0x6F, 0x7F,>>.\avrdude.conf
echo 	0x66, 0x76, 0x67, 0x77, 0x6A, 0x7A, 0x6B, 0x7B,>>.\avrdude.conf
echo 	0xBE, 0xFD, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00;>>.\avrdude.conf
echo     hventerstabdelay    = 100;>>.\avrdude.conf
echo     progmodedelay       = 0;>>.\avrdude.conf
echo     latchcycles         = 5;>>.\avrdude.conf
echo     togglevtg           = 1;>>.\avrdude.conf
echo     poweroffdelay       = 15;>>.\avrdude.conf
echo     resetdelayms        = 1;>>.\avrdude.conf
echo     resetdelayus        = 0;>>.\avrdude.conf
echo     hvleavestabdelay    = 15;>>.\avrdude.conf
echo     resetdelay          = 15;>>.\avrdude.conf
echo     chiperasepulsewidth = 0;>>.\avrdude.conf
echo     chiperasepolltimeout = 10;>>.\avrdude.conf
echo     programfusepulsewidth = 0;>>.\avrdude.conf
echo     programfusepolltimeout = 5;>>.\avrdude.conf
echo     programlockpulsewidth = 0;>>.\avrdude.conf
echo     programlockpolltimeout = 5;>>.\avrdude.conf
echo.>>.\avrdude.conf
echo     ocdrev              = 1;>>.\avrdude.conf
echo.>>.\avrdude.conf
echo     memory "eeprom">>.\avrdude.conf
echo         paged           = no;>>.\avrdude.conf
echo         page_size       = 4;>>.\avrdude.conf
echo         size            = 512;>>.\avrdude.conf
echo         min_write_delay = 3600;>>.\avrdude.conf
echo         max_write_delay = 3600;>>.\avrdude.conf
echo         readback_p1     = 0xff;>>.\avrdude.conf
echo         readback_p2     = 0xff;>>.\avrdude.conf
echo         read            = " 1 0 1 0 0 0 0 0",>>.\avrdude.conf
echo                           " 0 0 0 x x x x a8",>>.\avrdude.conf
echo                           " a7 a6 a5 a4 a3 a2 a1 a0",>>.\avrdude.conf
echo                           " o o o o o o o o";>>.\avrdude.conf
echo     >>.\avrdude.conf
echo         write           = " 1 1 0 0 0 0 0 0",>>.\avrdude.conf
echo                           " 0 0 0 x x x x a8",>>.\avrdude.conf
echo                           " a7 a6 a5 a4 a3 a2 a1 a0",>>.\avrdude.conf
echo                           " i i i i i i i i";>>.\avrdude.conf
echo.>>.\avrdude.conf
echo 	loadpage_lo	= "  1   1   0   0      0   0   0   1",>>.\avrdude.conf
echo 			  "  0   0   0   0      0   0   0   0",>>.\avrdude.conf
echo 			  "  0   0   0   0      0   0  a1  a0",>>.\avrdude.conf
echo 			  "  i   i   i   i      i   i   i   i";>>.\avrdude.conf
echo.>>.\avrdude.conf
echo 	writepage	= "  1   1   0   0      0   0   1   0",>>.\avrdude.conf
echo 			  "  0   0   x   x      x   x   x  a8",>>.\avrdude.conf
echo 			  " a7  a6  a5  a4     a3  a2   0   0",>>.\avrdude.conf
echo 			  "  x   x   x   x      x   x   x   x";>>.\avrdude.conf
echo.>>.\avrdude.conf
echo 	mode		= 0x41;>>.\avrdude.conf
echo 	delay		= 20;>>.\avrdude.conf
echo 	blocksize	= 4;>>.\avrdude.conf
echo 	readsize	= 256;>>.\avrdude.conf
echo         ;>>.\avrdude.conf
echo.>>.\avrdude.conf
echo     memory "flash">>.\avrdude.conf
echo         paged           = yes;>>.\avrdude.conf
echo         size            = 16384;>>.\avrdude.conf
echo         page_size       = 128;>>.\avrdude.conf
echo         num_pages       = 128;>>.\avrdude.conf
echo         min_write_delay = 4500;>>.\avrdude.conf
echo         max_write_delay = 4500;>>.\avrdude.conf
echo         readback_p1     = 0xff;>>.\avrdude.conf
echo         readback_p2     = 0xff;>>.\avrdude.conf
echo         read_lo         = " 0 0 1 0 0 0 0 0",>>.\avrdude.conf
echo                           " 0 0 0 a12 a11 a10 a9 a8",>>.\avrdude.conf
echo                           " a7 a6 a5 a4 a3 a2 a1 a0",>>.\avrdude.conf
echo                           " o o o o o o o o";>>.\avrdude.conf
echo         >>.\avrdude.conf
echo         read_hi          = " 0 0 1 0 1 0 0 0",>>.\avrdude.conf
echo                            " 0 0 0 a12 a11 a10 a9 a8",>>.\avrdude.conf
echo                            " a7 a6 a5 a4 a3 a2 a1 a0",>>.\avrdude.conf
echo                            " o o o o o o o o";>>.\avrdude.conf
echo         >>.\avrdude.conf
echo         loadpage_lo     = " 0 1 0 0 0 0 0 0",>>.\avrdude.conf
echo                           " 0 0 0 x x x x x",>>.\avrdude.conf
echo                           " x x a5 a4 a3 a2 a1 a0",>>.\avrdude.conf
echo                           " i i i i i i i i";>>.\avrdude.conf
echo         >>.\avrdude.conf
echo         loadpage_hi     = " 0 1 0 0 1 0 0 0",>>.\avrdude.conf
echo                           " 0 0 0 x x x x x",>>.\avrdude.conf
echo                           " x x a5 a4 a3 a2 a1 a0",>>.\avrdude.conf
echo                           " i i i i i i i i";>>.\avrdude.conf
echo         >>.\avrdude.conf
echo         writepage       = " 0 1 0 0 1 1 0 0",>>.\avrdude.conf
echo                           " 0 0 0 a12 a11 a10 a9 a8",>>.\avrdude.conf
echo                           " a7 a6 x x x x x x",>>.\avrdude.conf
echo                           " x x x x x x x x";>>.\avrdude.conf
echo.>>.\avrdude.conf
echo         mode        = 0x41;>>.\avrdude.conf
echo         delay       = 6;>>.\avrdude.conf
echo         blocksize   = 128;>>.\avrdude.conf
echo         readsize    = 256;>>.\avrdude.conf
echo.>>.\avrdude.conf
echo         ;>>.\avrdude.conf
echo         >>.\avrdude.conf
echo     memory "lfuse">>.\avrdude.conf
echo         size            = 1;>>.\avrdude.conf
echo         min_write_delay = 4500;>>.\avrdude.conf
echo         max_write_delay = 4500;>>.\avrdude.conf
echo         read            = "0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0",>>.\avrdude.conf
echo                           "x x x x x x x x o o o o o o o o";>>.\avrdude.conf
echo         >>.\avrdude.conf
echo         write           = "1 0 1 0 1 1 0 0 1 0 1 0 0 0 0 0",>>.\avrdude.conf
echo                           "x x x x x x x x i i i i i i i i";>>.\avrdude.conf
echo         ;>>.\avrdude.conf
echo     >>.\avrdude.conf
echo     memory "hfuse">>.\avrdude.conf
echo         size            = 1;>>.\avrdude.conf
echo         min_write_delay = 4500;>>.\avrdude.conf
echo         max_write_delay = 4500;>>.\avrdude.conf
echo         read            = "0 1 0 1 1 0 0 0 0 0 0 0 1 0 0 0",>>.\avrdude.conf
echo                           "x x x x x x x x o o o o o o o o";>>.\avrdude.conf
echo         >>.\avrdude.conf
echo         write           = "1 0 1 0 1 1 0 0 1 0 1 0 1 0 0 0",>>.\avrdude.conf
echo                           "x x x x x x x x i i i i i i i i";>>.\avrdude.conf
echo         ;>>.\avrdude.conf
echo     >>.\avrdude.conf
echo     memory "efuse">>.\avrdude.conf
echo         size            = 1;>>.\avrdude.conf
echo         min_write_delay = 4500;>>.\avrdude.conf
echo         max_write_delay = 4500;>>.\avrdude.conf
echo         read            = "0 1 0 1 0 0 0 0 0 0 0 0 1 0 0 0",>>.\avrdude.conf
echo                           "x x x x x x x x o o o o o o o o";>>.\avrdude.conf
echo         >>.\avrdude.conf
echo         write           = "1 0 1 0 1 1 0 0 1 0 1 0 0 1 0 0",>>.\avrdude.conf
echo                           "x x x x x x x x x x x x x i i i";>>.\avrdude.conf
echo         ;>>.\avrdude.conf
echo     >>.\avrdude.conf
echo     memory "lock">>.\avrdude.conf
echo         size            = 1;>>.\avrdude.conf
echo         min_write_delay = 4500;>>.\avrdude.conf
echo         max_write_delay = 4500;>>.\avrdude.conf
echo         read            = "0 1 0 1 1 0 0 0 0 0 0 0 0 0 0 0",>>.\avrdude.conf
echo                           "x x x x x x x x x x o o o o o o";>>.\avrdude.conf
echo         >>.\avrdude.conf
echo         write           = "1 0 1 0 1 1 0 0 1 1 1 x x x x x",>>.\avrdude.conf
echo                           "x x x x x x x x 1 1 i i i i i i";>>.\avrdude.conf
echo         ;>>.\avrdude.conf
echo     >>.\avrdude.conf
echo     memory "calibration">>.\avrdude.conf
echo         size            = 1;>>.\avrdude.conf
echo         read            = "0 0 1 1 1 0 0 0 0 0 0 x x x x x",>>.\avrdude.conf
echo                           "0 0 0 0 0 0 0 0 o o o o o o o o";>>.\avrdude.conf
echo         ;>>.\avrdude.conf
echo     >>.\avrdude.conf
echo     memory "signature">>.\avrdude.conf
echo         size            = 3;>>.\avrdude.conf
echo         read            = "0 0 1 1 0 0 0 0 0 0 0 x x x x x",>>.\avrdude.conf
echo                           "x x x x x x a1 a0 o o o o o o o o";>>.\avrdude.conf
echo         ;>>.\avrdude.conf
echo ;>>.\avrdude.conf
echo.>>.\avrdude.conf
echo #------------------------------------------------------------>>.\avrdude.conf
echo # ATmega168P>>.\avrdude.conf
echo #------------------------------------------------------------>>.\avrdude.conf
echo.>>.\avrdude.conf
echo part parent "m168">>.\avrdude.conf
echo     id              = "m168p";>>.\avrdude.conf
echo     desc            = "ATmega168P";>>.\avrdude.conf
echo     signature       = 0x1e 0x94 0x0b;>>.\avrdude.conf
echo.>>.\avrdude.conf
echo     ocdrev              = 1;>>.\avrdude.conf
echo ;>>.\avrdude.conf
