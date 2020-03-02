
#line 1 "urc_parse.rl"
/*
 * Convert a string to an integer.
 */

#include <stdlib.h>
#include <string.h>
//#include <stdio.h>
#include <stdbool.h>

#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"
#include "at_layer.h"


#line 18 "urc_parse.c"
static const char _get_IP_addr_actions[] = {
	0, 1, 0, 1, 1, 1, 2
};

static const char _get_IP_addr_key_offsets[] = {
	0, 0, 2, 5, 7, 10, 12, 15, 
	17, 20, 22, 24, 26, 28, 30, 31, 
	35, 37, 39, 41, 43, 44, 47, 51
};

static const char _get_IP_addr_trans_keys[] = {
	48, 57, 46, 48, 57, 48, 57, 46, 
	48, 57, 48, 57, 46, 48, 57, 48, 
	57, 34, 48, 57, 67, 99, 73, 105, 
	70, 102, 83, 115, 82, 114, 58, 34, 
	43, 83, 115, 84, 116, 65, 97, 73, 
	105, 80, 112, 44, 34, 83, 115, 34, 
	43, 83, 115, 0
};

static const char _get_IP_addr_single_lengths[] = {
	0, 0, 1, 0, 1, 0, 1, 0, 
	1, 2, 2, 2, 2, 2, 1, 4, 
	2, 2, 2, 2, 1, 3, 4, 0
};

static const char _get_IP_addr_range_lengths[] = {
	0, 1, 1, 1, 1, 1, 1, 1, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0
};

static const char _get_IP_addr_index_offsets[] = {
	0, 0, 2, 5, 7, 10, 12, 15, 
	17, 20, 23, 26, 29, 32, 35, 37, 
	42, 45, 48, 51, 54, 56, 60, 65
};

static const char _get_IP_addr_indicies[] = {
	0, 1, 2, 0, 1, 3, 1, 4, 
	3, 1, 5, 1, 6, 5, 1, 7, 
	1, 8, 7, 1, 9, 9, 1, 10, 
	10, 1, 11, 11, 1, 12, 12, 1, 
	13, 13, 1, 14, 1, 15, 16, 17, 
	17, 1, 18, 18, 1, 19, 19, 1, 
	20, 20, 1, 21, 21, 1, 22, 1, 
	15, 17, 17, 1, 15, 16, 17, 17, 
	1, 1, 0
};

static const char _get_IP_addr_trans_targs[] = {
	2, 0, 3, 4, 5, 6, 7, 8, 
	23, 10, 11, 12, 13, 14, 15, 1, 
	9, 16, 17, 18, 19, 20, 21
};

static const char _get_IP_addr_trans_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	5, 0, 0, 0, 0, 0, 1, 0, 
	0, 0, 0, 0, 0, 0, 3
};

static const int get_IP_addr_start = 22;
static const int get_IP_addr_first_final = 22;
static const int get_IP_addr_error = 0;

static const int get_IP_addr_en_atParse = 22;


#line 17 "urc_parse.rl"


void get_IP_addr(UART_HandleTypeDef *huart, char *str )
{
	char *p = str, *pe = str + strlen( str ), *startP = 0, *endP = 0;
	int cs, iplen = 0;
	char *ip = 0;

	
#line 98 "urc_parse.c"
	{
	cs = get_IP_addr_start;
	}

#line 103 "urc_parse.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _get_IP_addr_trans_keys + _get_IP_addr_key_offsets[cs];
	_trans = _get_IP_addr_index_offsets[cs];

	_klen = _get_IP_addr_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _get_IP_addr_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _get_IP_addr_indicies[_trans];
	cs = _get_IP_addr_trans_targs[_trans];

	if ( _get_IP_addr_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _get_IP_addr_actions + _get_IP_addr_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 26 "urc_parse.rl"
	{
			//printf("+CIFSR command found\n");
			send_AT_command(huart, "+CIFSR command found\r\n", 1000);
		}
	break;
	case 1:
#line 30 "urc_parse.rl"
	{
			//printf("STAIP found\n");
			send_AT_command(huart, "STAIP found\r\n", 1000);
			startP = p+1;

		}
	break;
	case 2:
#line 36 "urc_parse.rl"
	{
			endP = p+1;
			iplen = endP - startP;
			ip = malloc(iplen);
			memcpy(ip, startP, iplen);
			//printf("STAIP is: %s \n", ip);
			send_AT_command(huart, "STAIP is: ", 1000);
			send_AT_command(huart, ip, 1000);
			send_AT_command(huart, "\r\n", 1000);
		}
	break;
#line 206 "urc_parse.c"
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	_out: {}
	}

#line 60 "urc_parse.rl"

};



