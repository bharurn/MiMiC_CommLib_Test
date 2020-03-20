//
//    MCL: MiMiC Communication Library
//    Copyright (C) 2015-2020  Viacheslav Bolnykh,
//                             Jógvan Magnus Haugaard Olsen,
//                             Simone Meloni,
//                             Emiliano Ippoliti,
//                             Paolo Carloni
//                             and Ursula Röthlisberger.
//
//    This file is part of MCL.
//
//    MCL is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Lesser General Public License as
//    published by the Free Software Foundation, either version 3 of
//    the License, or (at your option) any later version.
//
//    MCL is distributed in the hope that it will be useful, but
//    WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef MIMICCOMMLIB_MCLF2C_H
#define MIMICCOMMLIB_MCLF2C_H

#ifdef MCL_MPMD
extern "C"
int MCL_init_wrap(int *fcomm);
#else
extern "C"
int MCL_init_wrap(void *fcomm);
#endif

#endif //MIMICCOMMLIB_MCLF2C_H
