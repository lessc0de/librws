/*
 *   Copyright (c) 2014 - 2016 Kulykov Oleh <info@resident.name>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */


#ifndef __FRAME_H__
#define __FRAME_H__ 1

#include "../librws.h"
#include "common.h"

typedef enum _rws_opcode
{
	rws_opcode_continuation = 0x0, // %x0 denotes a continuation frame
	rws_opcode_text_frame = 0x1, // %x1 denotes a text frame
	rws_opcode_binary_frame = 0x2, // %x2 denotes a binary frame
	rws_opcode_connection_close = 0x8, // %x8 denotes a connection close
	rws_opcode_ping = 0x9, // %x9 denotes a ping
	rws_opcode_pong = 0xA // %xA denotes a pong
} rws_opcode;

typedef struct _rws_frame_struct
{
	void * data;
	size_t data_size;
	size_t expected_size;
	rws_opcode opcode;
	unsigned char mask[4];
	rws_bool is_masked;
	rws_bool is_finished;
	unsigned char header_size;
} _rws_frame;

_rws_frame * rws_frame_create_with_recv_data(const void * data, const size_t data_size);

// data - should be null, and setted by newly created. 'data' & 'data_size' can be null
void rws_frame_fill_with_send_data(_rws_frame * f, const void * data, const size_t data_size);

_rws_frame * rws_frame_create(void);

void rws_frame_delete(_rws_frame * f);

void rws_frame_delete_clean(_rws_frame ** f);

#endif 
