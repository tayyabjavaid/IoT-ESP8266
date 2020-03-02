

/*
 * Convert a string to an integer.
 */

#include <stdlib.h>
#include <string.h>
//#include <stdio.h>
#include <stdbool.h>


#line 14 "lexer.c"
static const char _get_IP_addr_actions[] = {
	0, 1, 2, 2, 2, 0, 2, 2, 
	1, 2, 2, 6, 2, 3, 2, 2, 
	4, 2, 2, 5, 2
};

static const char _get_IP_addr_key_offsets[] = {
	0, 6, 6, 8, 11, 13, 16, 18, 
	21, 23, 26, 28, 30, 32, 34, 36, 
	37, 41, 43, 45, 47, 49, 50, 53, 
	55, 56, 60, 62, 64, 66, 68, 70, 
	72
};

static const char _get_IP_addr_trans_keys[] = {
	34, 43, 65, 83, 97, 115, 48, 57, 
	46, 48, 57, 48, 57, 46, 48, 57, 
	48, 57, 46, 48, 57, 48, 57, 34, 
	48, 57, 67, 99, 73, 105, 70, 102, 
	83, 115, 82, 114, 58, 34, 43, 83, 
	115, 84, 116, 65, 97, 73, 105, 80, 
	112, 44, 34, 83, 115, 84, 116, 43, 
	67, 71, 99, 103, 87, 119, 77, 109, 
	79, 111, 68, 100, 69, 101, 77, 109, 
	82, 114, 0
};

static const char _get_IP_addr_single_lengths[] = {
	6, 0, 0, 1, 0, 1, 0, 1, 
	0, 1, 2, 2, 2, 2, 2, 1, 
	4, 2, 2, 2, 2, 1, 3, 2, 
	1, 4, 2, 2, 2, 2, 2, 2, 
	2
};

static const char _get_IP_addr_range_lengths[] = {
	0, 0, 1, 1, 1, 1, 1, 1, 
	1, 1, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0
};

static const unsigned char _get_IP_addr_index_offsets[] = {
	0, 7, 8, 10, 13, 15, 18, 20, 
	23, 25, 28, 31, 34, 37, 40, 43, 
	45, 50, 53, 56, 59, 62, 64, 68, 
	71, 73, 78, 81, 84, 87, 90, 93, 
	96
};

static const char _get_IP_addr_indicies[] = {
	1, 2, 3, 4, 3, 4, 0, 0, 
	5, 0, 6, 5, 0, 7, 0, 8, 
	7, 0, 9, 0, 10, 9, 0, 11, 
	0, 12, 11, 0, 13, 13, 0, 14, 
	14, 0, 15, 15, 0, 16, 16, 0, 
	17, 17, 0, 18, 0, 1, 2, 4, 
	4, 0, 19, 19, 0, 20, 20, 0, 
	21, 21, 0, 22, 22, 0, 23, 0, 
	1, 4, 4, 0, 24, 24, 0, 25, 
	0, 27, 28, 27, 28, 26, 29, 29, 
	0, 30, 30, 0, 31, 31, 0, 32, 
	32, 0, 33, 33, 0, 34, 34, 0, 
	35, 35, 0, 0
};

static const char _get_IP_addr_trans_targs[] = {
	1, 2, 10, 23, 17, 3, 4, 5, 
	6, 7, 8, 9, 1, 11, 12, 13, 
	14, 15, 16, 18, 19, 20, 21, 22, 
	24, 25, 1, 26, 31, 27, 28, 29, 
	30, 1, 32, 1
};

static const char _get_IP_addr_trans_actions[] = {
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 18, 1, 1, 1, 
	1, 1, 12, 1, 1, 1, 1, 15, 
	1, 1, 3, 1, 1, 1, 1, 1, 
	1, 6, 1, 9
};

static const int get_IP_addr_start = 0;
static const int get_IP_addr_first_final = 0;
static const int get_IP_addr_error = -1;

static const int get_IP_addr_en_atParse = 0;


#line 13 "lexer.c"


static void get_IP_addr( char *str, char *ptr )
{
	char *p = str, *pe = str + strlen( str ), *startP = 0, *endP = 0;
	int cs, iplen = 0;
	long long val = 0;
	bool neg = false;
	char *ip = 0;
    

	
#line 117 "lexer.c"
	{
	cs = get_IP_addr_start;
	}

#line 122 "lexer.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
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
#line 32 "lexer.c"
	{
			memcpy(ptr, "AT Command is found\r\n", 23);
		}
	break;
	case 1:
#line 35 "lexer.c"
	{
			ptr = "AT+CWMODE Command is found\n";
		}
	break;
	case 2:
#line 38 "lexer.c"
	{
			//printf("multicars found\n");
		}
	break;
	case 3:
#line 41 "lexer.c"
	{
			memcpy(ptr, "+CIFSR command found\n", 25);
		}
	break;
	case 4:
#line 44 "lexer.c"
	{
			ptr = ("STAIP found\n");
			startP = p+1;

		}
	break;
	case 5:
#line 49 "lexer.c"
	{
			endP = p+1;
			iplen = endP - startP;
			ip = malloc(iplen);
			memcpy(ip, startP, iplen);
			ptr = ("ip_addr is: %s \n");
		}
	break;
	case 6:
#line 56 "lexer.c"
	{
		    ptr = ("AT+GMR is found\n");
		}
	break;
#line 242 "lexer.c"
		}
	}

_again:
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	}

#line 85 "lexer.c"


};

void get_IP_addr1( char *str, char *ptr )
{
    get_IP_addr( str, ptr);
}


