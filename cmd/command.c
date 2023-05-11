
#line 1 "command.rl"
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
    
#line 2 ".\\cmd\\command.c"
static const int command_start = 1;
static const int command_first_final = 24;
static const int command_error = 0;

static const int command_en_main = 1;


#line 18 "command.rl"

	
#line 8 ".\\cmd\\command.c"
	{
	cs = command_start;
	}

#line 11 ".\\cmd\\command.c"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	if ( (*p) == 58 )
		goto st2;
	goto st0;
tr2:
#line 41 "command.rl"
	{Serial.println("not a command") ;}
	goto st0;
tr10:
#line 40 "command.rl"
	{Serial.println("not hex digit");}
	goto st0;
#line 26 ".\\cmd\\command.c"
st0:
cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	switch( (*p) ) {
		case 66: goto tr3;
		case 68: goto tr4;
		case 70: goto tr6;
		case 71: goto tr7;
		case 77: goto tr5;
		case 86: goto tr7;
		case 88: goto tr8;
		case 109: goto tr4;
		case 113: goto tr5;
		case 115: goto tr4;
		case 122: goto tr6;
	}
	if ( (*p) < 79 ) {
		if ( (*p) > 73 ) {
			if ( 74 <= (*p) && (*p) <= 76 )
				goto tr6;
		} else if ( (*p) >= 69 )
			goto tr5;
	} else if ( (*p) > 80 ) {
		if ( (*p) > 85 ) {
			if ( 97 <= (*p) && (*p) <= 107 )
				goto tr4;
		} else if ( (*p) >= 83 )
			goto tr5;
	} else
		goto tr3;
	goto tr2;
tr3:
#line 23 "command.rl"
	{cmd=(*p);}
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 68 ".\\cmd\\command.c"
	if ( 49 <= (*p) && (*p) <= 51 )
		goto tr9;
	goto tr2;
tr9:
#line 24 "command.rl"
	{chan=(*p)-'0';}
	goto st4;
tr24:
#line 25 "command.rl"
	{lHex[n++]=(*p);lHex[n]=0;}
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 81 ".\\cmd\\command.c"
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 70 )
			goto tr11;
	} else if ( (*p) >= 48 )
		goto tr11;
	goto tr10;
tr11:
#line 25 "command.rl"
	{lHex[n++]=(*p);lHex[n]=0;}
#line 38 "command.rl"
	{	value = (uint32_t)strtoul(lHex, NULL, 16);}
	goto st5;
tr21:
#line 25 "command.rl"
	{lHex[n++]=(*p);lHex[n]=0;}
#line 26 "command.rl"
	{uint16_t* swap =(uint16_t*) lHex;
					uint16_t tmp=*(swap);
					*swap =*(swap+2);
					*(swap+2)=tmp;
					value = (uint32_t)strtoul(lHex, NULL, 16);
					//Serial.println(lHex);
					}
	goto st5;
tr29:
#line 25 "command.rl"
	{lHex[n++]=(*p);lHex[n]=0;}
#line 33 "command.rl"
	{uint16_t* swap =(uint16_t*) lHex;
					uint16_t tmp=*(swap);
					*swap =*(swap+1);
					*(swap+1)=tmp;
					value = (uint32_t)strtoul(lHex, NULL, 16);}
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 113 ".\\cmd\\command.c"
	if ( (*p) == 13 )
		goto tr12;
	goto tr10;
tr12:
#line 21 "command.rl"
	{setcommand(cmd,chan,value);}
	goto st24;
tr14:
#line 22 "command.rl"
	{getcommand(cmd,chan);}
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 126 ".\\cmd\\command.c"
	goto st0;
tr4:
#line 23 "command.rl"
	{cmd=(*p);}
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 134 ".\\cmd\\command.c"
	if ( 49 <= (*p) && (*p) <= 51 )
		goto tr13;
	goto tr2;
tr13:
#line 24 "command.rl"
	{chan=(*p)-'0';}
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 144 ".\\cmd\\command.c"
	if ( (*p) == 13 )
		goto tr14;
	goto st0;
tr5:
#line 23 "command.rl"
	{cmd=(*p);}
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 154 ".\\cmd\\command.c"
	if ( 49 <= (*p) && (*p) <= 51 )
		goto tr15;
	goto tr2;
tr15:
#line 24 "command.rl"
	{chan=(*p)-'0';}
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 164 ".\\cmd\\command.c"
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 70 )
			goto tr16;
	} else if ( (*p) >= 48 )
		goto tr16;
	goto tr10;
tr16:
#line 25 "command.rl"
	{lHex[n++]=(*p);lHex[n]=0;}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 177 ".\\cmd\\command.c"
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 70 )
			goto tr17;
	} else if ( (*p) >= 48 )
		goto tr17;
	goto tr10;
tr17:
#line 25 "command.rl"
	{lHex[n++]=(*p);lHex[n]=0;}
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 190 ".\\cmd\\command.c"
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 70 )
			goto tr18;
	} else if ( (*p) >= 48 )
		goto tr18;
	goto tr10;
tr18:
#line 25 "command.rl"
	{lHex[n++]=(*p);lHex[n]=0;}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 203 ".\\cmd\\command.c"
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 70 )
			goto tr19;
	} else if ( (*p) >= 48 )
		goto tr19;
	goto tr10;
tr19:
#line 25 "command.rl"
	{lHex[n++]=(*p);lHex[n]=0;}
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 216 ".\\cmd\\command.c"
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 70 )
			goto tr20;
	} else if ( (*p) >= 48 )
		goto tr20;
	goto tr10;
tr20:
#line 25 "command.rl"
	{lHex[n++]=(*p);lHex[n]=0;}
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 229 ".\\cmd\\command.c"
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 70 )
			goto tr21;
	} else if ( (*p) >= 48 )
		goto tr21;
	goto tr10;
tr6:
#line 23 "command.rl"
	{cmd=(*p);}
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 242 ".\\cmd\\command.c"
	if ( 49 <= (*p) && (*p) <= 51 )
		goto tr22;
	goto tr2;
tr22:
#line 24 "command.rl"
	{chan=(*p)-'0';}
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 252 ".\\cmd\\command.c"
	if ( (*p) == 13 )
		goto tr12;
	goto st0;
tr7:
#line 23 "command.rl"
	{cmd=(*p);}
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 262 ".\\cmd\\command.c"
	if ( 49 <= (*p) && (*p) <= 51 )
		goto tr23;
	goto tr2;
tr23:
#line 24 "command.rl"
	{chan=(*p)-'0';}
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 272 ".\\cmd\\command.c"
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 70 )
			goto tr24;
	} else if ( (*p) >= 48 )
		goto tr24;
	goto tr10;
tr8:
#line 23 "command.rl"
	{cmd=(*p);}
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 285 ".\\cmd\\command.c"
	if ( 49 <= (*p) && (*p) <= 51 )
		goto tr25;
	goto tr2;
tr25:
#line 24 "command.rl"
	{chan=(*p)-'0';}
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 295 ".\\cmd\\command.c"
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 70 )
			goto tr26;
	} else if ( (*p) >= 48 )
		goto tr26;
	goto tr10;
tr26:
#line 25 "command.rl"
	{lHex[n++]=(*p);lHex[n]=0;}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 308 ".\\cmd\\command.c"
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 70 )
			goto tr27;
	} else if ( (*p) >= 48 )
		goto tr27;
	goto tr10;
tr27:
#line 25 "command.rl"
	{lHex[n++]=(*p);lHex[n]=0;}
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
#line 321 ".\\cmd\\command.c"
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 70 )
			goto tr28;
	} else if ( (*p) >= 48 )
		goto tr28;
	goto tr10;
tr28:
#line 25 "command.rl"
	{lHex[n++]=(*p);lHex[n]=0;}
	goto st23;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
#line 334 ".\\cmd\\command.c"
	if ( (*p) > 57 ) {
		if ( 65 <= (*p) && (*p) <= 70 )
			goto tr29;
	} else if ( (*p) >= 48 )
		goto tr29;
	goto tr10;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof24: cs = 24; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 4: 
	case 5: 
	case 9: 
	case 10: 
	case 11: 
	case 12: 
	case 13: 
	case 14: 
	case 18: 
	case 20: 
	case 21: 
	case 22: 
	case 23: 
#line 40 "command.rl"
	{Serial.println("not hex digit");}
	break;
	case 2: 
	case 3: 
	case 6: 
	case 8: 
	case 15: 
	case 17: 
	case 19: 
#line 41 "command.rl"
	{Serial.println("not a command") ;}
	break;
#line 393 ".\\cmd\\command.c"
	}
	}

	_out: {}
	}

#line 65 "command.rl"

	    if ( cs < command_first_final )
        	return 1;else//fprintf( stderr, " command:  error\n" );

        return  0;
}
	
