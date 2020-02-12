module MCLfortran

    implicit none

    private

    public :: MCL_prepare
    public :: MCL_Init
    public :: MCL_Send
    public :: MCL_receive
    public :: MCL_destroy

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

    contains

    subroutine MCL_prepare(communicator)
        use, intrinsic :: iso_c_binding
        use mpi_f08
        integer, intent(inout), target :: communicator
        class(*), pointer :: test

        call CMCL_prepare(c_loc(communicator))
    end subroutine MCL_prepare

    subroutine MCL_Init(paths, delimiter, is_server)
        use, intrinsic :: iso_c_binding
        !> paths to working folders of client codes (delimited string)
        character, intent(in) :: paths(*)
        !> delimiter for path string
        character, intent(in) :: delimiter
        !>
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

        call CMCL_init(path, c_delimiter, c_flag)
    end subroutine MCL_Init

    subroutine MCL_Send(buffer, count, data_type, destination)
        use iso_c_binding, only: c_ptr, c_int
        type(c_ptr), value :: buffer
        !> Pointer to the buffer to send data from
        integer(kind=c_int), value :: count
        !> Number of data entries
        integer(kind=c_int), value :: data_type
        !> Type of data to be sent
        integer(kind=c_int), value :: destination

        call CMCL_send(buffer, count, data_type, destination)
    end subroutine MCL_Send

    subroutine MCL_receive(buffer, count, data_type, source)
        use iso_c_binding, only: c_ptr, c_int
        !> pointer to the buffer to receive data
        type(c_ptr), value :: buffer
        !> number of data entries
        integer(kind=c_int), value :: count
        !> type of data to be received
        integer(kind=c_int), value :: data_type
        !> ID of the client to receive data from
        integer(kind=c_int), value :: source

        call CMCL_receive(buffer, count, data_type, source)
    end subroutine MCL_receive

    subroutine MCL_Destroy
        call CMCL_destroy
    end subroutine MCL_Destroy

end module MCLfortran