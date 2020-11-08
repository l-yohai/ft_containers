## PIMPED MAKEFILE ##

# COLORS #

# This is a minimal set of ANSI/VT100 color codes
END			=	\e[0m
BOLD		=	\e[1m
UNDER		=	\e[4m
REV			=	\e[7m

# Colors
GREY		=	\e[30m
RED			=	\e[31m
GREEN		=	\e[32m
YELLOW		=	\e[33m
BLUE		=	\e[34m
PURPLE		=	\e[35m
CYAN		=	\e[36m
WHITE		=	\e[37m

# Inverted, i.e. colored backgrounds
IGREY		=	\e[40m
IRED		=	\e[41m
IGREEN		=	\e[42m
IYELLOW		=	\e[43m
IBLUE		=	\e[44m
IPURPLE		=	\e[45m
ICYAN		=	\e[46m
IWHITE		=	\e[47m

# **************************************************************************** #

# COMPILATION #

CC			=	clang++
CC_FLAGS	=	-Wall -Wextra -Werror -std=c++11

# COMMANDS #

RM			=	rm -rf

# DIRECTORIES #

DIR_HEADERS =	./include/
DIR_SRCS	=	./srcs/
DIR_OBJS	=	./objs/

# FILES #

SRC			=	main.cpp
SRCS		=	$(SRC)

# COMPILED_SOURCES #

OBJS 		=	$(SRCS:%.cpp=$(DIR_OBJS)%.o)
NAME 		=	ft_containers

# **************************************************************************** #

## RULES ##

all:			$(NAME)

# VARIABLES RULES #

$(NAME):		$(OBJS)
				@printf "\033[2K\r$(GREEN) All files compiled into '$(DIR_OBJS)'. $(END)✅\n"
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) $(OBJS) -o $(NAME)
				@printf "$(GREEN) Executable '$(NAME)' created. $(END)✅\n"

# COMPILED_SOURCES RULES #

$(OBJS):		| $(DIR_OBJS)


$(DIR_OBJS)%.o: $(DIR_SRCS)%.cpp
				@$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -c $< -o $@
				@printf "\033[2K\r $(YELLOW)Compiling $< $(END)⌛"

$(DIR_OBJS):
				@mkdir -p $(DIR_OBJS)


# OBLIGATORY PART #

clean:
				@$(RM) $(DIR_OBJS)
				@printf "$(RED) '"$(DIR_OBJS)"' has been deleted. $(END)🗑️\n"

fclean:			clean
				@$(RM) $(NAME)
				@printf "$(RED) '"$(NAME)"' has been deleted. $(END)🗑️\n"

re:				fclean all

# BONUS #

bonus:			all

re_bonus:		fclean bonus

.PHONY:			all clean fclean re bonus re_bonus