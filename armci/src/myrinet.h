/*              
 * Copyright (c)  2000 Pacific Northwest National Laboratory
 * All rights reserved.
 *
 *      Author: Jialin Ju, PNNL
 */

/***
   NAME
     myrinet.h
   PURPOSE
     
   NOTES
     
   HISTORY
     jju - Mar 1, 2000: Created.
***/

#ifndef MYRINET_H
#define MYRINET_H

#include "mpi.h"
#include "gm.h"

#define FALSE  0
#define TRUE   1

/* below are two ports used by ARMCI and their boards */
#define ARMCI_GM_SERVER_RCV_PORT 5
#define ARMCI_GM_SERVER_RCV_DEV 0
#define ARMCI_GM_SERVER_SND_PORT 6
#define ARMCI_GM_SERVER_SND_DEV 0

#define ARMCI_GM_MIN_MESG_SIZE 1
#define ARMCI_GM_MAX_MESG_SIZE 20

/* call back */
#define ARMCI_GM_SENDING 0
#define ARMCI_GM_SENT    1
#define ARMCI_GM_FAILED  2

/* msg ack */
#define ARMCI_GM_CLEAR     0
#define ARMCI_GM_READY    -1
#define ARMCI_GM_COMPLETE -2
#define ARMCI_GM_ACK      -3

typedef struct {
    void *data_ptr;         /* pointer where the data should go */
    long ack;               /* header ack */
} msg_tag_t;

/* data structure of computing process */
typedef struct {
    int node_id;            /* my node id */
    int *node_map;          /* other's node id */
    
    struct gm_port *port;   /* my port */

    long *serv_ack_ptr;     /* keep the pointers of server ack buffer */

    long *serv_buf_ptr;     /* keep the pointers of server MessageRcvBuffer */
} armci_gm_proc_t;

/* data structure of server thread */
typedef struct {
    int node_id;            /* my node id */
    int *node_map;          /* other's node id */
    
    struct gm_port *rcv_port;   /* server receive port */
    struct gm_port *snd_port;   /* server receive port */
    int port_id;            /* my port id */
    int *port_map;          /* other's port id. server only */

    void *dma_buf[ARMCI_GM_MAX_MESG_SIZE+1]; /* dma memory for regular send */
    long  *ack_buf;          /* ack buf for each computing process */

    long *proc_buf_ptr;     /* keep the pointers of client MessageSndBuffer */
} armci_gm_serv_t;

/* context for callback routine */
typedef struct {
    int tag;
    volatile int done;
} armci_gm_context_t;

/* the port that mpi currently using */
extern struct gm_port *gmpi_gm_port;

extern armci_gm_proc_t *proc_gm;
extern armci_gm_serv_t *serv_gm;

extern void armci_gm_cleanup();
extern char *armci_ReadFromDirect(char *buf, int len);

#endif /* MYRINET_H */
