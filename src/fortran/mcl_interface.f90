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

module mcl_interface

    implicit none

    !> interface of the communication library
    interface
        !> initialize the server endpoint
        subroutine cmcl_init(args) bind(c, name="MCL_init_wrap")
            use, intrinsic :: iso_c_binding, only: c_ptr
            !> paths to working folders of client codes (delimited string)
            type(c_ptr), value :: args
        end subroutine cmcl_init

        !> initialize the server endpoint
        subroutine cmcl_handshake(paths, delimiter, is_server) bind(c, name="MCL_handshake")
            use, intrinsic :: iso_c_binding, only: c_char, c_int
            !> paths to working folders of client codes (delimited string)
            character(kind=c_char), dimension(*) :: paths
            !> delimiter for path string
            character(kind=c_char) :: delimiter
            !> 0 - indicates a client, 1 - indicates a server
            integer(kind=c_int), value :: is_server
        end subroutine cmcl_handshake

        !> deinitialize the communication layer
        subroutine cmcl_destroy() bind(c, name="MCL_destroy")
        end subroutine cmcl_destroy

        !> request data (analogous to mpi_recv)
        subroutine cmcl_receive(buffer, count, data_type, source) bind(c, name="MCL_receive")
            use iso_c_binding, only: c_ptr, c_int
            !> pointer to the buffer to receive data
            type(c_ptr), value :: buffer
            !> number of data entries
            integer(kind=c_int), value :: count
            !> type of data to be received
            integer(kind=c_int), value :: data_type
            !> id of the client to receive data from
            integer(kind=c_int), value :: source
        end subroutine cmcl_receive

        !> routine to send data (analogous to mpi_send)
        subroutine cmcl_send(buffer, count, data_type, destination) bind(c, name="MCL_send")
            use iso_c_binding, only: c_ptr, c_int
            !> pointer to the buffer to send data from
            type(c_ptr), value :: buffer
            !> number of data entries
            integer(kind=c_int), value :: count
            !> type of data to be sent
            integer(kind=c_int), value :: data_type
            !> id of the client to receive data
            integer(kind=c_int), value :: destination
        end subroutine cmcl_send
    end interface

end module mcl_interface