cmake_minimum_required(VERSION 3.6)
project(RTv1)

set(CMAKE_CXX_STANDARD 11)

include_directories(./includes ./libft/includes)

set(SOURCE_FILES
    libft/includes/get_next_line.h
    libft/includes/libft.h
    libft/ft_atoi.c
    libft/ft_bzero.c
    libft/ft_isalnum.c
    libft/ft_isalpha.c
    libft/ft_isascii.c
    libft/ft_isdigit.c
    libft/ft_isprint.c
    libft/ft_itoa.c
    libft/ft_list_reverse.c
    libft/ft_lstadd.c
    libft/ft_lstdel.c
    libft/ft_lstdelone.c
    libft/ft_lstiter.c
    libft/ft_lstmap.c
    libft/ft_lstnew.c
    libft/ft_map.c
    libft/ft_memalloc.c
    libft/ft_memccpy.c
    libft/ft_memchr.c
    libft/ft_memcmp.c
    libft/ft_memcpy.c
    libft/ft_memdel.c
    libft/ft_memmove.c
    libft/ft_memset.c
    libft/ft_putchar.c
    libft/ft_putchar_fd.c
    libft/ft_putendl.c
    libft/ft_putendl_fd.c
    libft/ft_putnbr.c
    libft/ft_putnbr_fd.c
    libft/ft_putstr.c
    libft/ft_putstr_fd.c
    libft/ft_strcapitalize.c
    libft/ft_strcat.c
    libft/ft_strchr.c
    libft/ft_strclr.c
    libft/ft_strcmp.c
    libft/ft_strcpy.c
    libft/ft_strdel.c
    libft/ft_strdup.c
    libft/ft_strequ.c
    libft/ft_striter.c
    libft/ft_striteri.c
    libft/ft_strjoin.c
    libft/ft_strlcat.c
    libft/ft_strlen.c
    libft/ft_strlowcase.c
    libft/ft_strmap.c
    libft/ft_strmapi.c
    libft/ft_strncat.c
    libft/ft_strncmp.c
    libft/ft_strncpy.c
    libft/ft_strnequ.c
    libft/ft_strnew.c
    libft/ft_strnstr.c
    libft/ft_strrchr.c
    libft/ft_strsplit.c
    libft/ft_strstr.c
    libft/ft_strsub.c
    libft/ft_strtrim.c
    libft/ft_strupcase.c
    libft/ft_tolower.c
    libft/ft_toupper.c
    libft/get_next_line.c
    author
    Makefile src/main.c src/common.c src/sphere.c src/plane.c src/cylinder.c src/cone.c src/vector_operations_1.c src/vector_operations_2.c src/composed.c src/object_parameters.c src/vector_count.c src/hooks.c src/matrix_func.c src/objects_intersection.c)

include_directories(.)
include_directories(includes)
include_directories(libft)
include_directories(src)

add_executable(RTv1 ${SOURCE_FILES})
target_link_libraries(RTv1 libmlx.a "-framework AppKit" "-framework OpenGl")