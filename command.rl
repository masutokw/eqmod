#include <string.h>
#include <stdio.h>

long command(char *str)
{ 
char *p = str, *pe = str + strlen( str );
    int cs;
	uint32_t value;
	uint8_t chan=0;
	char cmd=' ';
	char lHex[15]="0000000";
	int n=0;
	char *eof = pe;
	uint16 *swap ;
    %%{
        machine command;
        write data;
    }%%
	%%{
#Actions
	action set_command{setcommand(cmd,chan,value);}
	action get_command{getcommand(cmd,chan);}
	action getcmd {cmd=fc;}
	action set_channel{chan=fc-'0';}
	action addstr {lHex[n++]=fc;lHex[n]=0;}
	action hexcal6 {uint16_t* swap =(uint16_t*) lHex;
					uint16_t tmp=*(swap);
					*swap =*(swap+2);
					*(swap+2)=tmp;
					value = (uint32_t)strtoul(lHex, NULL, 16);
					//Serial.println(lHex);
					}
	action hexcal4 {uint16_t* swap =(uint16_t*) lHex;
					uint16_t tmp=*(swap);
					*swap =*(swap+1);
					*(swap+1)=tmp;
					value = (uint32_t)strtoul(lHex, NULL, 16);}
	action hexcal {	value = (uint32_t)strtoul(lHex, NULL, 16);}			
					
	action hexerror {Serial.println("not hex digit");}
	action error_code {Serial.println("not a command") ;}

	Hex1=((([0-9]|[A-F]))@addstr)$err(hexerror);
	Hex_1 = Hex1 @hexcal;
	Hex_2 = Hex1{2}@hexcal;
	Hex_4 = Hex1{4}@hexcal4;
	Hex_6 = Hex1{6}@hexcal6;
    Axis=[1-3]@set_channel;
	Run_Boot_Loader_Mode =  'Q'@getcmd Axis Hex_4 %set_command;
	SetCmd = (
			(('E'|'H'|'M'|'S'|'T'|'U'|'q'|'I')$err(error_code)@getcmd Axis Hex_6)|
			(('G'|'V')$err(error_code)@getcmd Axis Hex_2)|
			(('X')$err(error_code)@getcmd Axis Hex_4)|			
			(('O'|'P'|'B'|'P')$err(error_code)@getcmd Axis Hex_1)|
			(('J'|'K'|'L'|'F'|'z')$err(error_code)@getcmd Axis ))
			%set_command; 
			
	get_char=('a'|'b'|'c'|'h'|'i'|'j'|'k'|'m'|'f'|'g'|'D'|'d'|'e'|'s')$err(error_code);			
	GetCmd	= get_char @getcmd	Axis %get_command;

	main:=':' (SetCmd | GetCmd ) 0x0D;
	
	 write init;
     write exec;
	}%%
	    if ( cs < command_first_final )
        	return 1;else//fprintf( stderr, " command:  error\n" );

        return  0;
}
	
