NAME	= philo
CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -pthread $(INCLUDES) 
INCLUDES = -I inc -I ${LIBFT_DIR}

LIBFT_DIR		= inc/libft
LIBFT_LIB		= libft.a

PHILO_SRCS	=	error.c init_data.c launcher.c philo.c utils.c routine.c
PHILO_SRCS_DIR	= src/
PHILO_OBJS = $(addprefix $(PHILO_SRCS_DIR), $(PHILO_SRCS:.c=.o))

all: ${NAME}

${LIBFT_DIR}/${LIBFT_LIB}:
	@echo "Compilling libft"
	@make -C ${LIBFT_DIR}

${NAME}:	${LIBFT_DIR}/${LIBFT_LIB} ${PHILO_OBJS} 
	@echo "Compiling philosopher dining problem"
	${CC} ${CFLAGS} ${PHILO_OBJS} -o ${NAME} -L${LIBFT_DIR} -lft

clean:
	@echo "cleaning files"
	@make clean -C ${LIBFT_DIR}
	@rm -rf ${PHILO_OBJS}

fclean: clean
	@make fclean -C ${LIBFT_DIR}
	@rm -rf $(NAME)

re: clean all

.PHONY:	all clean fclean re 