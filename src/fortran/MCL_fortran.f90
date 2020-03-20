module MCL_fortran

    use MCL_interface
    use MCL_send_recv

    implicit none

    private

    public :: MCL_Prepare
    public :: MCL_Init
    public :: MCL_Send
    public :: MCL_Receive
    public :: MCL_Destroy

    interface MCL_Send
        module procedure send_int, send_int_array1d, &
                send_int_array2d, send_int_array3d, &
                send_float, send_float_array1d, &
                send_float_array2d, send_float_array3d, &
                send_double, send_double_array1d, &
                send_double_array2d, send_double_array3d, &
                send_char, send_char_array
    end interface MCL_Send

    interface MCL_Receive
        module procedure recv_int, recv_int_array1d, &
                recv_int_array2d, recv_int_array3d, &
                recv_float, recv_float_array1d, &
                recv_float_array2d, recv_float_array3d, &
                recv_double, recv_double_array1d, &
                recv_double_array2d, recv_double_array3d, &
                recv_char, recv_char_array
    end interface MCL_Receive

    contains

    subroutine MCL_Prepare(communicator)
        use, intrinsic :: iso_c_binding
        use mpi_f08
        integer, intent(inout), target :: communicator
        class(*), pointer :: test

        call CMCL_prepare(c_loc(communicator))
    end subroutine MCL_Prepare

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

    subroutine MCL_Destroy
        call CMCL_destroy
    end subroutine MCL_Destroy

end module MCL_fortran