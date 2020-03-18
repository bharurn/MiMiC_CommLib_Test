module MCL_send_recv

    use MCL_interface

    implicit none

    contains

    subroutine send_int(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        integer, target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_int

    subroutine send_int_array1d(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        integer, dimension(:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_int_array1d

    subroutine send_int_array2d(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        integer, dimension(:,:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_int_array2d

    subroutine send_int_array3d(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        integer, dimension(:,:,:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_int_array3d

    subroutine send_float(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real32), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_float

    subroutine send_float_array1d(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real32), dimension(*), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_float_array1d

    subroutine send_float_array2d(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real32), dimension(:,:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_float_array2d

    subroutine send_float_array3d(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real32), dimension(:,:,:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_float_array3d

    subroutine send_double(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real64), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_double

    subroutine send_double_array1d(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real64), dimension(:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_double_array1d

    subroutine send_double_array2d(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real64), dimension(:,:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_double_array2d

    subroutine send_double_array3d(data, count, dest)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real64), dimension(:,:,:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: dest

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_dest

        c_count = count
        c_dest = dest
        buffer = c_loc(data)

        call CMCL_send(buffer, c_count, data_type, c_dest)
    end subroutine send_double_array3d

    subroutine send_char(data, count, dest)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        character(len=*), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
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
        character(len=*), dimension(*), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
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

    subroutine recv_int(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        integer, target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_int

    subroutine recv_int_array1d(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        integer, dimension(:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_int_array1d

    subroutine recv_int_array2d(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        integer, dimension(:,:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_int_array2d

    subroutine recv_int_array3d(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        integer, dimension(:,:,:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 2
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_int_array3d

    subroutine recv_float(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real32), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_float

    subroutine recv_float_array1d(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real32), dimension(:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_float_array1d

    subroutine recv_float_array2d(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real32), dimension(:,:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_float_array2d

    subroutine recv_float_array3d(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real32
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real32), dimension(:,:,:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 4
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_float_array3d

    subroutine recv_double(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real64), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_double

    subroutine recv_double_array1d(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real64), dimension(:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_double_array1d

    subroutine recv_double_array2d(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real64), dimension(:,:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_double_array2d

    subroutine recv_double_array3d(data, count, source)
        use, intrinsic :: iso_fortran_env, only: real64
        use iso_c_binding, only: c_ptr, c_int, c_loc
        real(kind=real64), dimension(:,:,:), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
        integer :: source

        type(c_ptr) :: buffer
        integer(kind=c_int) :: c_count
        integer(kind=c_int), parameter :: data_type = 1
        integer(kind=c_int) :: c_source

        c_count = count
        c_source = source
        buffer = c_loc(data)

        call CMCL_receive(buffer, c_count, data_type, c_source)
    end subroutine recv_double_array3d

    subroutine recv_char(data, count, source)
        use iso_c_binding, only: c_ptr, c_int, c_loc
        character(len=*), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
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
        character(len=*), dimension(*), target :: data
        !> Pointer to the buffer to send data from
        integer :: count
        !> Type of data to be sent
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