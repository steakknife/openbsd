/* $OpenBSD$ */
/* Public Domain <marc@snafu.org> */

#if defined(LIBC_SCCS) && !defined(lint)
static char *rcsid = "$OpenBSD$";
#endif /* LIBC_SCCS and not lint */

#include <errno.h>
#include <limits.h>
#include <string.h>

extern char *__strerror(int, char *);

int
strerror_r(int errnum, char *strerrbuf, size_t buflen)
{
	int save_errno;
	int ret_errno;
	char buf[NL_TEXTMAX];

	save_errno = errno;
	errno = 0;
	__strerror(errnum, buf);
	if (strlcpy(strerrbuf, buf, buflen) >= buflen)
		errno = ERANGE;
	ret_errno = errno;
	errno = save_errno;

	return (ret_errno);
}
