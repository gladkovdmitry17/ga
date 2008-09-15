#ifndef MPI2_H
#define MPI2_H

#include <mpi.h>

#define MPI_SPAWN_DEBUG 0

#define MPI_SPAWN_ZEROCOPY /* enables zero-copy for large requests */

#ifdef MPI_SPAWN_ZEROCOPY
#  define MPI_USER_DEF_DATATYPE /* Enables MPI userdefined type for non-contig
                                 * data, if MPI_SPAWN_ZEROCOPY is enabled */
#endif

#define ARMCI_MPI_SPAWN_INIT_TAG   1000
#define ARMCI_MPI_SPAWN_TAG        2000
#define ARMCI_MPI_SPAWN_DATA_TAG   3000
#define ARMCI_MPI_SPAWN_VDATA_TAG  4000

#define GET_SEND_BUFFER   _armci_buf_get
#define FREE_SEND_BUFFER  _armci_buf_release

#define COMPLETE_HANDLE   _armci_buf_complete_nb_request
#define TEST_HANDLE       _armci_buf_test_nb_request

#define SEND 0
#define RECV 1

extern void armci_mpi_strided(int op, void *ptr, int stride_levels,
                              int stride_arr[],  int count[], int proc,
                              MPI_Comm comm);

#endif /* MPI2_H */