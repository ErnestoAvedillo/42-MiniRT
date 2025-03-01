NAME	=	libft.a

CFLAGS =  -Wall -Wextra -Werror -g3
XFLAGS	= #-fsanitize=address  -D

AR		= ar -rcs
RM		= rm -f
MD		= mkdir -p
CP		= cp -f
CLEAN_CAR	=	\033[2K\r

SRC_DIR	= src/
OBJ_DIR	= obj/
INC_DIR	= inc/

EXTRA_DIR = extra/

INCLUDE	= -I $(INC_DIR)

LIBFT_SRC	= ft_strlcat.c ft_substr.c ft_atoi.c ft_strdup.c \
			ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isprint.c ft_strlen.c ft_memset.c ft_isascii.c \
			ft_bzero.c ft_memcpy.c ft_toupper.c ft_tolower.c \
			ft_strchr.c ft_memcmp.c ft_memchr.c ft_isdigit.c \
			ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strjoin.c \
			ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_memmove.c \
			ft_split.c ft_strnstr.c ft_substr.c ft_lstnew.c ft_lstadd_front.c \
			ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
			ft_lstiter.c ft_lstmap.c

LIBFT_EXTRA = ft_array_size.c ft_array_free.c ft_substr_free.c ft_strlwr.c ft_strjoin_free.c ft_putstr.c \
				ft_atol.c ft_atoll.c ft_isnumeric.c ft_strcmp.c ft_isstralnum.c ft_isupper.c ft_isstrupper.c \
				ft_strpbrk.c ft_isstrprint.c ft_isspace.c ft_isstrspace.c ft_isallspace.c get_next_line.c \
				ft_print_array.c ft_atof.c ft_split_spaces.c ft_isstrarray.c ft_check_extension.c ft_isallalpha.c

SRCS	+=	$(addprefix $(SRC_DIR), $(LIBFT_SRC))
SRCS	+=	$(addprefix $(EXTRA_DIR), $(LIBFT_EXTRA))
OBJS	=	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEPS	=	$(addsuffix .d, $(basename $(OBJS)))

$(OBJ_DIR)%.o: %.c Makefile
		@$(MD) $(dir $@)
		@printf "$(OK_COLOR)$(CLEAN_CAR)[libft Compiling] $(BLUE_COLOR):$(WARN_COLOR) $<$(NO_COLOR)"
		@$(CC) -MT $@ -MMD $(CFLAGS) $(INCLUDE) -c $< -o $@
		
#echo "$(WARN_COLOR)Compiling: $<$(NO_COLOR)"

all:		$(NAME) 


$(NAME):	$(OBJS)
			@$(AR) $(NAME) $(OBJS)
			@sleep 0.2
			@echo "$(OK_COLOR)$(CLEAN_CAR)Libft Compiled!$(NO_COLOR)"

clean:
			@$(RM) -r $(OBJ_DIR) 
			@echo "$(ERROR_COLOR)Dependencies and objects removed$(NO_COLOR)"

fclean:		clean  
			@$(RM) $(NAME)
			@echo "$(ERROR_COLOR)Libft.a removed$(NO_COLOR)"

re:			fclean all

-include $(DEPS)

.PHONY: all clean fclean re

#●○●○●○●○●○●○●○●○●○●●○●○●○●○●○●○●○●○●○●●○●○●○●○●○●○●○●○●○●●○●○●○●○●○●○●○●○●○●#
#•❅──────✧❅✦❅✧──────❅••❅──────✧❅✦❅✧─COLOR──✧❅✦❅✧──────❅••❅──────✧❅✦❅✧──────❅•#
#●○●○●○●○●○●○●○●○●○●●○●○●○●○●○●○●○●○●○●●○●○●○●○●○●○●○●○●○●●○●○●○●○●○●○●○●○●○●#

NO_COLOR		=	\033[1;97m
OK_COLOR		=	\033[1;92m
ERROR_COLOR		=	\033[1;91m
WARN_COLOR		=	\033[1;93m
BLUE_COLOR		=	\033[1;94m

OK_STRING		=	$(OK_COLOR)[OK]$(NO_COLOR)
ERROR_STRING	=	$(ERROR_COLOR)[ERRORS]$(NO_COLOR)
WARN_STRING		=	$(WARN_COLOR)[WARNINGS]$(NO_COLOR)
