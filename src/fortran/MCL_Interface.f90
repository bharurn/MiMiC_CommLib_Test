module MCL_interface

    implicit none

    !> interface of the communication library
    interface
        !> initialize the server endpoint
        subroutine CMCL_prepare(args) bind(C, name="MCL_prepare_wrap")
            use, intrinsic :: iso_c_binding, only: c_ptr
            !> paths to working folders of client codes (delimited string)
            type(c_ptr), value :: args
        end subroutine CMCL_prepare

        !> initialize the server endpoint
        subroutine CMCL_init(paths, delimiter, is_server) bind(C, name="MCL_init")
            use, intrinsic :: iso_c_binding, only: c_char, c_int
            !> paths to working folders of client codes (delimited string)
            character(kind=c_char) :: paths (*)
            !> delimiter for path string
            character(kind=c_char) :: delimiter
            !> 0 - indicates a client, 1 - indicates a server
            integer(kind=c_int), value :: is_server
        end subroutine CMCL_init

        !> deinitialize the communication layer
        subroutine CMCL_destroy() bind(C, name="MCL_destroy")
        end subroutine CMCL_destroy

        !> request data (analogous to MPI_Recv)
        subroutine CMCL_receive(buffer, count, data_type, source) bind(C, name="MCL_receive")
            use iso_c_binding, only: c_ptr, c_int
            !> pointer to the buffer to receive data
            type(c_ptr), value :: buffer
            !> number of data entries
            integer(kind=c_int), value :: count
            !> type of data to be received
            integer(kind=c_int), value :: data_type
            !> ID of the client to receive data from
            integer(kind=c_int), value :: source
        end subroutine CMCL_receive

        subroutine CMCL_send(buffer, count, data_type, destination) bind(C, name="MCL_send")
            !> Routine to send data (analogica to MPI_Send)
            use iso_c_binding, only: c_ptr, c_int
            type(c_ptr), value :: buffer
            !> Pointer to the buffer to send data from
            integer(kind=c_int), value :: count
            !> Number of data entries
            integer(kind=c_int), value :: data_type
            !> Type of data to be sent
            integer(kind=c_int), value :: destination
            !> ID of the client to receive data
        end subroutine CMCL_send
    end interface

end module MCL_interface