/* Fajar Dwi Darmanto (fajardwidarm@gmail.com) */

#include "base64.h"

const char base64_index_table[64] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
	'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

const unsigned char base64_inverse_table[128] = { 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0,
	0, 63,
	
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
	
	0, 0, 0, 0, 0, 0, 0,
	
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	20, 21, 22, 23, 24, 25,
	
	0, 0, 0, 0, 0, 0,
	
	26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 
	43, 44, 45, 46, 47, 48, 49, 50, 51,
	
	0, 0, 0, 0, 0
};

size_t 
base64_encode (const unsigned char *in, char *out, size_t sz)
{
	size_t x = 0;
	
	if (!in || !out) {
		return 0;
	}
	
	for (int i = 0; i < sz; i+=3) {
		out[x++] = base64_index_table[in[i] >> 2];
		if ((i+1) >= sz) {
			out[x++] = base64_index_table[(in[i] & 0x02) << 4];
			out[x++] = '=';
			out[x++] = '=';
			break;
		} else {
			out[x++] = base64_index_table[((in[i+1] & 0xf0) >> 4) | ((in[i] & 0x03) << 4)];
			if ((i+2) >= sz) {
				out[x++] = base64_index_table[(in[i+1] & 0x0f) << 2];
				out[x++] = '=';
				break;
			} else {
				out[x++] = base64_index_table[((in[i+2] & 0xc0) >> 6) | ((in[i+1] & 0x0f) << 2)];
				out[x++] = base64_index_table[in[i+2] & 0x3f];
			}
		}
	}
	out[x] = 0;
	return x;
}

size_t
base64_decode (const char *in, unsigned char *out, size_t sz)
{
	size_t x = 0;
	
	if (!in || !out) {
		return 0;
	}
	
	for (int i = 0;; i+=4) {
		if ((i+4) <= sz) {
			out[x++] = (base64_inverse_table[in[i]] << 2) | (base64_inverse_table[in[i+1]] >> 4);
			if (in[i+2] != '=') {
				out[x++] = (base64_inverse_table[in[i+2]] >> 2) | (base64_inverse_table[in[i+1]] << 4);
				if (in[i+3] != '=') {
					out[x++] = base64_inverse_table[in[i+3]] | (base64_inverse_table[in[i+2]] << 6);
				} else {
					break;
				}
			} else {
				break;
			}
		} else {
			break;
		}
	}
	out[x] = 0;
	return x;
}
