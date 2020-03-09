/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "../../include/libeggnogg_rpc.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <signal.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

namespace LibEggnogg
{
	static void
	libeggnogg_rpc_3(struct svc_req *rqstp, register SVCXPRT *transp)
	{
		union {
			u_long set_speed_3_arg;
		} argument;
		char *result;
		xdrproc_t _xdr_argument, _xdr_result;
		char *(*local)(char *, struct svc_req *);

		switch (rqstp->rq_proc) {
		case NULLPROC:
			(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
			return;

		case set_speed:
			_xdr_argument = (xdrproc_t) xdr_u_long;
			_xdr_result = (xdrproc_t) xdr_void;
			local = (char *(*)(char *, struct svc_req *)) set_speed_3_svc;
			break;

		case get_speed:
			_xdr_argument = (xdrproc_t) xdr_void;
			_xdr_result = (xdrproc_t) xdr_u_long;
			local = (char *(*)(char *, struct svc_req *)) get_speed_3_svc;
			break;

		case get_roomdef:
			_xdr_argument = (xdrproc_t) xdr_void;
			_xdr_result = (xdrproc_t) xdr_wrapstring;
			local = (char *(*)(char *, struct svc_req *)) get_roomdef_3_svc;
			break;

		default:
			svcerr_noproc (transp);
			return;
		}
		memset ((char *)&argument, 0, sizeof (argument));
		if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
			svcerr_decode (transp);
			return;
		}
		result = (*local)((char *)&argument, rqstp);
		if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
			svcerr_systemerr (transp);
		}
		if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
			fprintf (stderr, "%s", "unable to free arguments");
			exit (1);
		}
		return;
	}

	void exit_libeggnogg_rpc_serv()
	{
		svc_exit();
		pmap_unset(LibEggnogg_RPC , Stable);
		puts("[+] Closing RPC !");
	}

	void init_libeggnogg_rpc_serv()
	{
		register SVCXPRT *transp;

		pmap_unset (LibEggnogg_RPC, Stable);

		transp = svcudp_create(RPC_ANYSOCK);
		if (transp == NULL) {
			fprintf (stderr, "%s", "cannot create udp service.");
			exit(1);
		}
		if (!svc_register(transp, LibEggnogg_RPC, Stable, libeggnogg_rpc_3, IPPROTO_UDP)) {
			fprintf (stderr, "%s", "unable to register (LibEggnogg_RPC, Stable, udp).");
			exit(1);
		}

		transp = svctcp_create(RPC_ANYSOCK, 0, 0);
		if (transp == NULL) {
			fprintf (stderr, "%s", "cannot create tcp service.");
			exit(1);
		}
		if (!svc_register(transp, LibEggnogg_RPC, Stable, libeggnogg_rpc_3, IPPROTO_TCP)) {
			fprintf (stderr, "%s", "unable to register (LibEggnogg_RPC, Stable, tcp).");
			exit(1);
		}
		
		svc_run();
		exit(1);
	}
}
