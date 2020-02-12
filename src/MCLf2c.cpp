//
// Created by Viacheslav Bolnykh on 12.02.20.
//

#include "mpi.h"
#include "MCLf2c.h"
#include "MessageApi.h"

#ifdef MCL_MPMD
int MCL_prepare_wrap(int *fcomm) {
    MPI_Comm ccomm = MPI_Comm_f2c(*fcomm);
    MCL_prepare(&ccomm);
    *fcomm = MPI_Comm_c2f(ccomm);
    return 0;
}
#else
int MCL_prepare_wrap(void *fcomm) {
    MCL_prepare(fcomm);
    return 0;
}
#endif