/* $NetBSD: opt_cd.c,v 1.2 2021/11/19 22:24:29 rillig Exp $ */
/* $FreeBSD$ */

#indent input
int aflag; /* Apply to all files. */
#indent end

#indent run -cd49
int		aflag;				/* Apply to all files. */
#indent end

/* If '-cd' is not given, it falls back to '-c'. */
#indent run-equals-prev-output -c49
