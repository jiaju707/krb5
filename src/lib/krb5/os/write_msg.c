/*
 * lib/krb5/os/write_msg.c
 *
 * Copyright 1991 by the Massachusetts Institute of Technology.
 * All Rights Reserved.
 *
 * Export of this software from the United States of America may
 *   require a specific license from the United States Government.
 *   It is the responsibility of any person or organization contemplating
 *   export to obtain such a license before exporting.
 * 
 * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation, and that
 * the name of M.I.T. not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.  M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 * 
 *
 * convenience sendauth/recvauth functions
 */

#define NEED_SOCKETS
#include "k5-int.h"
#include <errno.h>
#ifndef _WINSOCKAPI_
#include <netinet/in.h>
#endif

krb5_error_code INTERFACE
krb5_write_message(context, fdp, outbuf)
    krb5_context context;
	krb5_pointer	fdp;
	krb5_data	*outbuf;
{
	krb5_int32	len;
	int		fd = *( (int *) fdp);

	len = htonl(outbuf->length);
	if (krb5_net_write(context, fd, (char *)&len, 4) < 0) {
		return(errno);
	}
	if (len && (krb5_net_write(context, fd, outbuf->data, outbuf->length) < 0)) {
		return(errno);
	}
	return(0);
}




