//
// Created by Viacheslav Bolnykh on 12.02.20.
//

#ifndef MIMICCOMMLIB_MCLF2C_H
#define MIMICCOMMLIB_MCLF2C_H

#ifdef MCL_MPMD
extern "C"
int MCL_prepare_wrap(int *fcomm);
#else
extern "C"
int MCL_prepare_wrap(void *fcomm);
#endif

#endif //MIMICCOMMLIB_MCLF2C_H
