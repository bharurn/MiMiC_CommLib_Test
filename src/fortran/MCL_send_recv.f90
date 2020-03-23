!
!    MCL: MiMiC Communication Library
!    Copyright (C) 2015-2020  Viacheslav Bolnykh,
!                             Jógvan Magnus Haugaard Olsen,
!                             Simone Meloni,
!                             Emiliano Ippoliti,
!                             Paolo Carloni
!                             and Ursula Röthlisberger.
!
!    This file is part of MCL.
!
!    MCL is free software: you can redistribute it and/or modify
!    it under the terms of the GNU Lesser General Public License as
!    published by the Free Software Foundation, either version 3 of
!    the License, or (at your option) any later version.
!
!    MCL is distributed in the hope that it will be useful, but
!    WITHOUT ANY WARRANTY; without even the implied warranty of
!    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
!    GNU Lesser General Public License for more details.
!
!    You should have received a copy of the GNU Lesser General Public License
!    along with this program.  If not, see <http://www.gnu.org/licenses/>.

module MCL_send_recv

    use MCL_interface

    implicit none

    contains

    subroutine send_int32(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int32
        !> Pointer to the buffer to send data from
        integer(kind=int32), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_int32

    subroutine send_int32_array1d(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int32
        !> Pointer to the buffer to send data from
        integer(kind=int32), dimension(:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_int32_array1d

    subroutine send_int32_array2d(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int32
        !> Pointer to the buffer to send data from
        integer(kind=int32), dimension(:,:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_int32_array2d

    subroutine send_int32_array3d(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int32
        !> Pointer to the buffer to send data from
        integer(kind=int32), dimension(:,:,:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_int32_array3d

    subroutine send_int64(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int64
        !> Pointer to the buffer to send data from
        integer(kind=int64), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 5
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_int64

    subroutine send_int64_array1d(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int64
        !> Pointer to the buffer to send data from
        integer(kind=int64), dimension(:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 5
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_int64_array1d

    subroutine send_int64_array2d(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int64
        !> Pointer to the buffer to send data from
        integer(kind=int64), dimension(:,:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 5
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_int64_array2d

    subroutine send_int64_array3d(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int64
        !> Pointer to the buffer to send data from
        integer(kind=int64), dimension(:,:,:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 5
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_int64_array3d

    subroutine send_float32(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to send data from
        real(kind=real32), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_float32

    subroutine send_float32_array1d(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to send data from
        real(kind=real32), dimension(:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_float32_array1d

    subroutine send_float32_array2d(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to send data from
        real(kind=real32), dimension(:,:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_float32_array2d

    subroutine send_float32_array3d(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to send data from
        real(kind=real32), dimension(:,:,:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_float32_array3d

    subroutine send_float64(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to send data from
        real(kind=real64), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_float64

    subroutine send_float64_array1d(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to send data from
        real(kind=real64), dimension(:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_float64_array1d

    subroutine send_float64_array2d(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to send data from
        real(kind=real64), dimension(:,:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_float64_array2d

    subroutine send_float64_array3d(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to send data from
        real(kind=real64), dimension(:,:,:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_float64_array3d

    subroutine send_char(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to send data from
        character(len=*), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 3
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_char

    subroutine send_char_array(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to send data from
        character(len=*), dimension(:), target :: data
        !> Type of data to be sent
        integer :: count
        !> ID of the client to send data to
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 3
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_char_array

    subroutine recv_int32(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int32
        !> Pointer to the buffer to put data to
        integer(kind=int32), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_int32

    subroutine recv_int32_array1d(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int32
        !> Pointer to the buffer to put data to
        integer(kind=int32), dimension(:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_int32_array1d

    subroutine recv_int32_array2d(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int32
        !> Pointer to the buffer to put data to
        integer(kind=int32), dimension(:,:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_int32_array2d

    subroutine recv_int32_array3d(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int32
        !> Pointer to the buffer to put data to
        integer(kind=int32), dimension(:,:,:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_int32_array3d

    subroutine recv_int64(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int64
        !> Pointer to the buffer to put data to
        integer(kind=int64), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 5
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_int64

    subroutine recv_int64_array1d(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int64
        !> Pointer to the buffer to put data to
        integer(kind=int64), dimension(:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 5
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_int64_array1d

    subroutine recv_int64_array2d(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int64
        !> Pointer to the buffer to put data to
        integer(kind=int64), dimension(:,:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 5
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_int64_array2d

    subroutine recv_int64_array3d(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        use, intrinsic :: iso_fortran_env, only: int64
        !> Pointer to the buffer to put data to
        integer(kind=int64), dimension(:,:,:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 5
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_int64_array3d

    subroutine recv_float32(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to put data to
        real(kind=real32), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_float32

    subroutine recv_float32_array1d(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to put data to
        real(kind=real32), dimension(:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_float32_array1d

    subroutine recv_float32_array2d(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to put data to
        real(kind=real32), dimension(:,:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_float32_array2d

    subroutine recv_float32_array3d(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to put data to
        real(kind=real32), dimension(:,:,:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_float32_array3d

    subroutine recv_float64(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to put data to
        real(kind=real64), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_float64

    subroutine recv_float64_array1d(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to put data to
        real(kind=real64), dimension(:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_float64_array1d

    subroutine recv_float64_array2d(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to put data to
        real(kind=real64), dimension(:,:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_float64_array2d

    subroutine recv_float64_array3d(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to put data to
        real(kind=real64), dimension(:,:,:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_float64_array3d

    subroutine recv_char(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to put data to
        character(len=*), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 3
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_char

    subroutine recv_char_array(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        !> Pointer to the buffer to put data to
        character(len=*), dimension(:), target :: data
        !> Type of data to be received
        integer :: count
        !> ID of the source of the data
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 3
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_char_array

end module MCL_send_recv