#ifndef ONSEI_S_H
#define ONSEI_S_H

#include <stdlib.h>
#include <stddef.h>

/*
 * NMNxNMNQN4NDN6N-
 */
typedef struct {
	int16_t onsei_procno;		/* N=NhNMN}NHNVN9Nf */
	int16_t onsei_usetankan;		/* NCN1N4NAN;NzN<N-N=NqN;NHNMNQN%NUN%NiN%N0 (0,1) */
	int16_t onsei_kouseisystem;	/* N9N;N@N5N%N7N%N9N%NFN%N`N%NbN!N<N%NIN%NUN%NiN%N0 (0,1) */
	int16_t onsei_crlfexist;		/* NFN~NNNONJN8N;NzNNNsN$N,N2N~N9NTN$NGN=N*NNN;N$N7N$NFN$N$N$Nk (0,1) */
	int16_t onsei_readcrlf;		/* N2N~N9NTN#NrN#NeN#NaN#NdN%NUN%NiN%N0 (0,1) */

	uint8_t* onsei_inert;		/* NJNQN4N9N$N9N$NkN2N>NLN>N4NAN;NzN8NrN$N8N$NjNJN8N$NrN3NJNGN<N$N7N$N^N$N9N!N#
							 * NJN8N;NzN<NoN$NON!N"N#NJN#NIN#NSN%N3N!N<N%NIN$NGNAN4N3NQNJN8N;NzN$NNN$N_N!N#
							 */
	uint8_t* onsei_omega;		/* NJNQN4N9N7NkN2NLN$NNNJN8N;NzNNNsN$NrN3NJNGN<N$N7N$N^N$N9N!N#
							 *
							 * N@NhNFN,N$NNN#N2N%NPN%N$N%NHN$NON!N"NGNoN?NtN!N#
							 *
							 * N#N3N%NPN%N$N%NHNLN\N$N+N$Ni
							 *		NBNhN#N1NGNoN$NNNHN/N2N;N%N3N!N<N%NI
							 *		NBNhN#N1NGNoN$NNN%NbN!N<N%NiN>NpNJNs
							 *		NBNhN#N1NGNoN$NNNAN0N$NNN%N]N!N<N%N:NNNL
							 *		NBNhN#N2NGNoN$NNNHN/N2N;N%N3N!N<N%NI
							 *		NBNhN#N2NGNoN$NNN%NbN!N<N%NiN>NpNJNs
							 *		NBNhN#N2NGNoN$NNNAN0N$NNN%N]N!N<N%N:NNNL
							 *         ....
							 * N$NHN$N$N$N&N$NhN$N&N$NKN3NJNGN<N$N5N$NlN$N^N$N9N!N#
							 *
							 * NCN"N$N7N!N"N%NbN!N<N%NiN>NpNJNsN$NN
							 *	N#N1N%NSN%NCN%NHNLN\N$NONLN5N@N<N2N=N%NUN%NiN%N0N!N"
							 *	N#N2N%NSN%NCN%NHNLN\N$NONJN8N@NaN$NNN@NhNFN,N%NUN%NiN%N0N!N"
							 *	N2N<N0NLN#N4N%NSN%NCN%NHN$NON%N"N%N/N%N;N%NsN%NHN$NNN9NbN$N5N!N#
							 *	N%N"N%N/N%N;N%NsN%NHN$NNN9NbN$N5N$NON<N!N$NNN#N3N<NoNNN`
							 *		N#N1	NDNcN$N$NGNo
							 *		N#N2	N9NbN$N$NGNo
							 *		N#N9	N5N?NLNdNDN4N$NNN9NbN$N$NGNo
							 */
	uint8_t* onsei_speak;		/* NIN=N2N;N%NGN!N<N%N?N$NNNJN8N;NzNNNsN$NrN3NJNGN<N$N7N$N^N$N9N!N#
							 *
							 * N$N3N$NNNJN8N;NzNNNsN$NrN$N=N$NNN$N^N$N^NHN/N@N<NANuNCNVN$NKNANwN$NkN$NHN!N"
							 * NCN}N$NiN$N;N$NkN$N3N$NHN$N,N=NPNMNhN$N^N$N9N!N#
							 */
	uint16_t* onsei_sent;		/* NJNQN4N9N7NkN2NLN$NNNJN8N@NaN>NpNJNsN$NrN3NJNGN<N$N7N$N^N$N9N!N#
							 *
							 * N3NFNJN8N@NaN$NKNBNPN1N~N$N9N$NkNFN~N=NPNNNONJN8N;NzN$NNN0NLNCNVN$N,N3NJNGN<N$N5N$NlN$N^N$N9N!N#
							 * N#N1N%N*N%NjN%N8N%NsN$NGN3NJNGN<N!N#
							 * N@NhNFN,N$N+N$NiNBNhN#N1NJN8N@NaN$NNNFN~NNNON$NNN=N*N$NoN$NjN$NNNJN8N;NzN0NLNCNV
							 *         NBNhN#N1NJN8N@NaN$NNN=NPNNNON$NNN=N*N$NoN$NjN$NNNJN8N;NzN0NLNCNV
							 *         NBNhN#N2NJN8N@NaN$NNNFN~NNNON$NNN=N*N$NoN$NjN$NNNJN8N;NzN0NLNCNV
							 *         NBNhN#N2NJN8N@NaN$NNN=NPNNNON$NNN=N*N$NoN$NjN$NNNJN8N;NzN0NLNCNV
							 *         ....
							 * N$NHN$N$N$N&N$NhN$N&N$NKNJN8N;NzN0NLNCNVN$N,NFN~N$NjN$N^N$N9N!N#
							 */
/*
 * N!NJNNNcN!NK	N!NVN;NdN$NON1NvNLNnN$NGN$N9N!NW
 *
 *		onsei_inert	  onsei_sent	  onsei_omega
 *
 *										09 00
 *		1	N;Nd	  +----	02 04 -----+	68 41 00	}N\  |1 <-- NJN8N@NaN@NhNFN,
 *      2   N$NO <--+ +--	06 09 ---+ |	20 02 00    }N@  |2
 *      3   N1Nv		|		     | |	19 02 00	}N<  |3	
 *      4   NLNn		|		     | +--> 68 02 00    }N\  |4
 *      5   N$NG		|		     |      19 42 00    }N<  |5 <-- NJN8N@NaN@NhNFN,
 *      6   N$N9 <----+            |      04 01 00    }N5  |6
 *                               |      3C 01 00    }NI  |7
 *                               |      93 01 00    }NCN^ |8
 *                               +---->	12 81 00    }N=  |9 <-- NLN5N@N<N2N=N$N9N$Nk
 *
 *			N!NVN;NdN$NON!N"N1NvNLNnN$NGN$N9N!N#N!NW
 *
 *		onsei_inert	  onsei_sent	  onsei_omega
 *
 *										B0 00
 *		1	N;Nd	  +----	03 05 -----+	68 41 00	}N\  |1 <-- NJN8N@NaN@NhNFN,	 
 *      2   N$NO	  | +--	08 0B ---+ |	20 02 00    }N@  |2
 *      3   N!N" <--+ |            | |	19 02 00    }N<  |3
 *      4   N1Nv		|            | |    68 02 00    }N\  |4
 *      5   NLNn		|            | +--> FF 00 00    }N$  |5 <-- FFN$NONFNCN<NlNJN8N;NzN$NKNBNPN1N~
 *      6   N$NG		|            |      19 42 08    }N<  |6 <-- NJN8N@NaN@NhNFN,N$NGNDN>NAN0N$NKN%N]N!N<N%N:
 *      7   N$N9		|            |      04 01 00    }N5  |7	 	
 *      8   N!N# <----+            |      3C 01 00    }NI  |8
 *								 |      93 01 00    }NCN^ |9
 *								 |      12 81 00    }N=  |A <-- NLN5N@N<N2N=N$N9N$Nk
 *                               +---->	FF 00 00    }N!  |B <-- FFN$NONFNCN<NlNJN8N;NzN$NKNBNPN1N~
 *
 */
	int16_t onsei_ninert;/* NFN~NNNONJN8N;NzN?NtN$NrN<N(N$N7N$N^N$N9N!N#*/
	int16_t onsei_sentno;/* NJNQN4N9N7NkN2NLN$NNNJN8N@NaN?NtN$NrN<N(N$N7N$N^N$N9N!N#*/
	int16_t onsei_wsno;	/* NCNmNLN\N$N7N$NFN$N$N$NkNJN8N@NaNHNVN9NfN$NrN<N(N$N7N$N^N$N9N!N#
							 * N=NiN2NsNJNQN4N9N8NeN$NON!N"N>NoN$NKN#N1N$NGN$N9N!N#
							 */
	int16_t onsei_acctype;/* NJNQN4N9N7NkN2NLN$NNN@NhNFN,NMNWNANGN$NNN%N"N%N/N%N;N%NsN%NHN0NLNCNVN$NrN<N(N$N7N$N^N$N9N!N#*/
	int16_t onsei_status;/* N%N(N%NiN!N<N%N3N!N<N%NIN!N#N#N0N$NJN$NiN!N"N@N5N>NoN=N*NNN;N!N#*/

    int (*onsei_stop)(void*);		/* NCNfNCNGNHN=NDNjN4NXN?Nt */
    int (*onsei_alloc)(void** addr, size_t size);	/* NNNNN0NhN3NNNJN]N4NXN?Nt */
    int (*onsei_read)(int page, size_t size, void* addr);		/* NJN*NMN}NFN~NNNON4NXN?Nt */
    int (*onsei_write)(int page, size_t size, void* addr); /* NJN*NMN}N=NPNNNON4NXN?Nt */
    void (*onsei_dealloc)(void** addr);	/* call to free memory allocated by onsei_alloc */
} STRUCT_ONSEI;

#endif /* ONSEI_S_H */

/* End of onsei_s.h */
