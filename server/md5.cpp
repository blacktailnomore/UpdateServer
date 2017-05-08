#include "md5.h"
#include <cstdio>
//using namespace std;

const string MD5_Key = "blacktail";
const byte MD5::PADDING[64] = { 0x80 };
const char MD5::HEX[16] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'a', 'b',
	'c', 'd', 'e', 'f'
};


/* Default construct. */
MD5::MD5() {
	reset();
}

/* Construct a MD5 object with a input buffer. */
MD5::MD5(const void* input, size_t length) {
	reset();
	update(input, length);
}

/* Construct a MD5 object with a string. */
MD5::MD5(const string& str) {
	reset();
	update(str);
}

/* Construct a MD5 object with a file. */
MD5::MD5(ifstream& in) {
	reset();
	update(in);
}

/* Return the message-digest */
const byte* MD5::digest() {

	if (!_finished) {
		_finished = true;
		final();
	}
	return _digest;
}

/* Reset the calculate state */
void MD5::reset() {

	_finished = false;
	/* reset number of bits. */
	_count[0] = _count[1] = 0;
	/* Load magic initialization constants. */
	_state[0] = state[0];
	_state[1] = state[1];
	_state[2] = state[2];
	_state[3] = state[3];
}

/* Updating the context with a input buffer. */
void MD5::update(const void* input, size_t length) {
	update((const byte*)input, length);
}

/* Updating the context with a string. */
void MD5::update(const string& str) {
	update((const byte*)str.c_str(), str.length());
}

/* Updating the context with a file. cpp*/
void MD5::update(ifstream& in) {

	if (!in) {
		return;
	}

	std::streamsize length;
	char buffer[BUFFER_SIZE];
	while (!in.eof()) {
		in.read(buffer, BUFFER_SIZE);
		length = in.gcount();
		if (length > 0) {
			update(buffer, length);
		}
	}
	in.close();
}

/* Updating the context with a file. c */
void MD5::update(FILE* fp){
    if(!fp)
        return;

    int length;
    char buffer[BUFFER_SIZE];
    while((length=fread(buffer,1,BUFFER_SIZE,fp))>0){
        if(length>0)
            update(buffer,length);
    }
}


/* MD5 block update operation. Continues an MD5 message-digest
operation, processing another message block, and updating the
context.
*/
void MD5::update(const byte* input, size_t length) {

	uint32 i, index, partLen;

	_finished = false;

	/* Compute number of bytes mod 64 */
	index = (uint32)((_count[0] >> 3) & 0x3f);

	/* update number of bits */
	if ((_count[0] += ((uint32)length << 3)) < ((uint32)length << 3)) {
		++_count[1];
	}
	_count[1] += ((uint32)length >> 29);

	partLen = 64 - index;

	/* transform as many times as possible. */
	if (length >= partLen) {

		memcpy(&_buffer[index], input, partLen);
		transform(_buffer);

		for (i = partLen; i + 63 < length; i += 64) {
			transform(&input[i]);
		}
		index = 0;

	}
	else {
		i = 0;
	}

	/* Buffer remaining input */
	memcpy(&_buffer[index], &input[i], length - i);
}

/* MD5 finalization. Ends an MD5 message-_digest operation, writing the
the message _digest and zeroizing the context.
*/
void MD5::final() {

	byte bits[8];
	uint32 oldState[4];
	uint32 oldCount[2];
	uint32 index, padLen;

	/* Save current state and count. */
	memcpy(oldState, _state, 16);
	memcpy(oldCount, _count, 8);

	/* Save number of bits */
	encode(_count, bits, 8);

	/* Pad out to 56 mod 64. */
	index = (uint32)((_count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	update(PADDING, padLen);

	/* Append length (before padding) */
	update(bits, 8);

	/* Store state in digest */
	encode(_state, _digest, 16);

	/* Restore current state and count. */
	memcpy(_state, oldState, 16);
	memcpy(_count, oldCount, 8);
}

/* MD5 basic transformation. Transforms _state based on block. */
void MD5::transform(const byte block[64]) {

	uint32 a = _state[0], b = _state[1], c = _state[2], d = _state[3], x[16];

	decode(block, x, 64);

	/* Round 1 */
	FF(a, b, c, d, x[0], S11, MD5_T[0]); /* 1 */
	FF(d, a, b, c, x[1], S12, MD5_T[1]); /* 2 */
	FF(c, d, a, b, x[2], S13, MD5_T[2]); /* 3 */
	FF(b, c, d, a, x[3], S14, MD5_T[3]); /* 4 */
	FF(a, b, c, d, x[4], S11, MD5_T[4]); /* 5 */
	FF(d, a, b, c, x[5], S12, MD5_T[5]); /* 6 */
	FF(c, d, a, b, x[6], S13, MD5_T[6]); /* 7 */
	FF(b, c, d, a, x[7], S14, MD5_T[7]); /* 8 */
	FF(a, b, c, d, x[8], S11, MD5_T[8]); /* 9 */
	FF(d, a, b, c, x[9], S12, MD5_T[9]); /* 10 */
	FF(c, d, a, b, x[10], S13, MD5_T[10]); /* 11 */
	FF(b, c, d, a, x[11], S14, MD5_T[11]); /* 12 */
	FF(a, b, c, d, x[12], S11, MD5_T[12]); /* 13 */
	FF(d, a, b, c, x[13], S12, MD5_T[13]); /* 14 */
	FF(c, d, a, b, x[14], S13, MD5_T[14]); /* 15 */
	FF(b, c, d, a, x[15], S14, MD5_T[15]); /* 16 */

											/* Round 2 */
	GG(a, b, c, d, x[1], S21, MD5_T[16]); /* 17 */
	GG(d, a, b, c, x[6], S22, MD5_T[17]); /* 18 */
	GG(c, d, a, b, x[11], S23, MD5_T[18]); /* 19 */
	GG(b, c, d, a, x[0], S24, MD5_T[19]); /* 20 */
	GG(a, b, c, d, x[5], S21, MD5_T[20]); /* 21 */
	GG(d, a, b, c, x[10], S22, MD5_T[21]); /* 22 */
	GG(c, d, a, b, x[15], S23, MD5_T[22]); /* 23 */
	GG(b, c, d, a, x[4], S24, MD5_T[23]); /* 24 */
	GG(a, b, c, d, x[9], S21, MD5_T[24]); /* 25 */
	GG(d, a, b, c, x[14], S22, MD5_T[25]); /* 26 */
	GG(c, d, a, b, x[3], S23, MD5_T[26]); /* 27 */
	GG(b, c, d, a, x[8], S24, MD5_T[27]); /* 28 */
	GG(a, b, c, d, x[13], S21, MD5_T[28]); /* 29 */
	GG(d, a, b, c, x[2], S22, MD5_T[29]); /* 30 */
	GG(c, d, a, b, x[7], S23, MD5_T[30]); /* 31 */
	GG(b, c, d, a, x[12], S24, MD5_T[31]); /* 32 */

											/* Round 3 */
	HH(a, b, c, d, x[5], S31, MD5_T[32]); /* 33 */
	HH(d, a, b, c, x[8], S32, MD5_T[33]); /* 34 */
	HH(c, d, a, b, x[11], S33, MD5_T[34]); /* 35 */
	HH(b, c, d, a, x[14], S34, MD5_T[35]); /* 36 */
	HH(a, b, c, d, x[1], S31, MD5_T[36]); /* 37 */
	HH(d, a, b, c, x[4], S32, MD5_T[37]); /* 38 */
	HH(c, d, a, b, x[7], S33, MD5_T[38]); /* 39 */
	HH(b, c, d, a, x[10], S34, MD5_T[39]); /* 40 */
	HH(a, b, c, d, x[13], S31, MD5_T[40]); /* 41 */
	HH(d, a, b, c, x[0], S32, MD5_T[41]); /* 42 */
	HH(c, d, a, b, x[3], S33, MD5_T[42]); /* 43 */
	HH(b, c, d, a, x[6], S34, MD5_T[43]); /* 44 */
	HH(a, b, c, d, x[9], S31, MD5_T[44]); /* 45 */
	HH(d, a, b, c, x[12], S32, MD5_T[45]); /* 46 */
	HH(c, d, a, b, x[15], S33, MD5_T[46]); /* 47 */
	HH(b, c, d, a, x[2], S34, MD5_T[47]); /* 48 */

										   /* Round 4 */
	II(a, b, c, d, x[0], S41, MD5_T[48]); /* 49 */
	II(d, a, b, c, x[7], S42, MD5_T[49]); /* 50 */
	II(c, d, a, b, x[14], S43, MD5_T[50]); /* 51 */
	II(b, c, d, a, x[5], S44, MD5_T[51]); /* 52 */
	II(a, b, c, d, x[12], S41, MD5_T[52]); /* 53 */
	II(d, a, b, c, x[3], S42, MD5_T[53]); /* 54 */
	II(c, d, a, b, x[10], S43, MD5_T[54]); /* 55 */
	II(b, c, d, a, x[1], S44, MD5_T[55]); /* 56 */
	II(a, b, c, d, x[8], S41, MD5_T[56]); /* 57 */
	II(d, a, b, c, x[15], S42, MD5_T[57]); /* 58 */
	II(c, d, a, b, x[6], S43, MD5_T[58]); /* 59 */
	II(b, c, d, a, x[13], S44, MD5_T[59]); /* 60 */
	II(a, b, c, d, x[4], S41, MD5_T[60]); /* 61 */
	II(d, a, b, c, x[11], S42, MD5_T[61]); /* 62 */
	II(c, d, a, b, x[2], S43, MD5_T[62]); /* 63 */
	II(b, c, d, a, x[9], S44, MD5_T[63]); /* 64 */

	_state[0] += a;
	_state[1] += b;
	_state[2] += c;
	_state[3] += d;
}

/* Encodes input (ulong) into output (byte). Assumes length is
a multiple of 4.
*/
void MD5::encode(const uint32* input, byte* output, size_t length) {

	for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
		output[j] = (byte)(input[i] & 0xff);
		output[j + 1] = (byte)((input[i] >> 8) & 0xff);
		output[j + 2] = (byte)((input[i] >> 16) & 0xff);
		output[j + 3] = (byte)((input[i] >> 24) & 0xff);
	}
}

/* Decodes input (byte) into output (ulong). Assumes length is
a multiple of 4.
*/
void MD5::decode(const byte* input, uint32* output, size_t length) {

	for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
		output[i] = ((uint32)input[j]) | (((uint32)input[j + 1]) << 8) |
			(((uint32)input[j + 2]) << 16) | (((uint32)input[j + 3]) << 24);
	}
}

/* Convert byte array to hex string. */
string MD5::bytesToHexString(const byte* input, size_t length) {

	string str;
	str.reserve(length << 1);
	for (size_t i = 0; i < length; ++i) {
		int t = input[i];
		int a = t / 16;
		int b = t % 16;
		str.append(1, HEX[a]);
		str.append(1, HEX[b]);
	}
	return str;
}

/* Convert digest to string value */
string MD5::toString() {
	return bytesToHexString(digest(), 16);
}

string MD5::ToMD5(const string& str) //MD5加密，其中密钥key=xyf，密钥需加在加密之前
{
	const string str_word = str + MD5_Key;
	reset();
	update(str_word);
	return toString();
}
