/* $NetBSD: token_for_exprs.c,v 1.2 2021/10/31 23:33:12 rillig Exp $ */
/* $FreeBSD$ */

/*
 * Test for 'for' loops.
 *
 * Most 'for' loops have 3 expressions in their head.  Each of these
 * expressions is optional though.
 *
 * When all 3 expressions are omitted, the 'for' loop is often called a
 * 'forever' loop.
 */

#indent input
void
function(void)
{
	for (int i = 0; i < 6; i++)
		print_char("hello\n"[i]);
	forever {
		stmt();
	}
}
#indent end

#indent run-equals-input


/*
 * Indent can cope with various syntax errors, which may be caused by
 * syntactic macros like 'forever' or 'foreach'.
 */
#indent input
#define forever for (;;)
#define foreach(list, it) for (it = list.first; it != NULL; it = it->next)

void
function(void)
{
	forever
		stmt();

	forever {
		stmt();
	}

/* $ No space after 'foreach' since it looks like a function name. */
	foreach(list, it)
		println(it->data);

/* $ No space after 'foreach' since it looks like a function name. */
	foreach(list, it) {
		println(it->data);
	}
}
#indent end

#indent run-equals-input


/*
 * Another variant of a 'for' loop, seen in sys/arch/arm/apple/apple_intc.c.
 */
#indent input
{
	for (CPU_INFO_FOREACH(cii, ci)) {
	}
}
#indent end

#indent run-equals-input
