/*	$NetBSD: msg_012.c,v 1.3 2021/08/26 19:23:25 rillig Exp $	*/
# 3 "msg_012.c"

// Test for message: compiler takes size of function [12]
/* This message is not used. */

unsigned long
example(void)
{
	/* expect+1: error: cannot take size/alignment of function [144] */
	return sizeof(example);
}
