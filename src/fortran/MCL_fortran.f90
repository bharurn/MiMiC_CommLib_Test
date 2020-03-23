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

module MCL_fortran

    use MCL_interface
    use MCL_send_recv

    implicit none

    private

    public :: MCL_Init
    public :: MCL_Handshake
    public :: MCL_Send
    public :: MCL_Receive
    public :: MCL_Destroy

    !> Send data to specified client
    interface MCL_Send
        module procedure send_int32, send_int32_array1d, &
                send_int32_array2d, send_int32_array3d, &
                send_int64, send_int64_array1d, &
                send_int64_array2d, send_int64_array3d, &
                send_float32, send_float32_array1d, &
                send_float32_array2d, send_float32_array3d, &
                send_float64, send_float64_array1d, &
                send_float64_array2d, send_float64_array3d, &
                send_char, send_char_array
    end interface MCL_Send

    !> Receive data from a specified client
    interface MCL_Receive
        module procedure recv_int32, recv_int32_array1d, &
                recv_int32_array2d, recv_int32_array3d, &
                recv_int64, recv_int64_array1d, &
                recv_int64_array2d, recv_int64_array3d, &
                recv_float32, recv_float32_array1d, &
                recv_float32_array2d, recv_float32_array3d, &
                recv_float64, recv_float64_array1d, &
                recv_float64_array2d, recv_float64_array3d, &
                recv_char, recv_char_array
    end interface MCL_Receive

    contains

    !> Initialize communicator. SHOULD BE CALLED AFTER MPI_INIT!!!
    subroutine MCL_Init(communicator)
        use, intrinsic :: iso_c_binding
        use mpi_f08
        !> MPI communicator that is used by the host code
        integer, intent(inout), target :: communicator

        call CMCL_init(c_loc(communicator))
    end subroutine MCL_Init

    !> Handshake function used for both server and client
    subroutine MCL_Handshake(paths, delimiter, is_server)
        use, intrinsic :: iso_c_binding
        !> paths to working folders of client codes (delimited string)
        character, intent(in) :: paths(*)
        !> delimiter for path string
        character, intent(in) :: delimiter
        !> flag, indicating whether the caller is a server or a client
        logical, intent(in) :: is_server

        integer :: n_client
        character(kind=c_char) :: c_delimiter
        character(kind=c_char), allocatable :: path (:)
        integer(kind=c_int) :: c_flag = 0
        integer :: n_char, i

        n_char = len(paths)
        allocate(path(n_char + 1))

        path = ""

        do i = 1, len(paths)
            path(i) = paths(i)
        end do
        path(n_char + 1) = C_NULL_CHAR
        c_delimiter = delimiter
        if (is_server) then
            c_flag = 1
        else
            c_flag = 0
        end if

        call CMCL_handshake(path, c_delimiter, c_flag)
    end subroutine MCL_Handshake

    !> Destroy the endpoint
    subroutine MCL_Destroy
        call CMCL_destroy
    end subroutine MCL_Destroy

end module MCL_fortran