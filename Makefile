NAME		= philo

SRCS		= 	philo.c \
				initialise.c \
				seat_philos_at_table.c \
				start_the_feast.c \
				feasting.c \
				clean.c \
				print.c \
				time.c \

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -pthread

OBJS_DIR	= ./objs/
SRCS_DIR 	= ./srcs/
INCS_DIR 	= ./includes/

OBJS 		= $(SRCS:%.c=$(OBJS_DIR)%.o)

.SILENT:

all:			colour $(NAME)
				echo "\\n\033[32;1m the philosophers cracked the tome open and there upon the withering pages lay... \033[0m \\n"
				echo "\\n\033[32;1m the SECRET TO LIFE OF INFINITE DAY!!! \033[0m \\n"
				echo "\\n\033[32;1m a sacred ritual begotten to time in which each philosopher must brandish one fork but may only eat with two... \033[0m \\n"
				echo "\\n\033[32;1m they must slumber to avoid being slew and when awake think with all three eyes... \033[0m \\n"
				echo "\\n\033[32;1m take heed, beware, for if they fumble, their timing stumble, all shall greet the grim reaper humble. \033[0m \\n"
				echo "\\n\033[32;1m THE PHILOSOPHERS ARE READY FOR THE RITUAL \033[0m \\n"

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
				mkdir -p $(OBJS_DIR)
				$(CC) $(CFLAGS) -I $(INCS_DIR) -o $@ -c $<

$(NAME): $(OBJS)
				$(CC) $(OBJS) -o $(NAME)

colour:
				echo "\x1b[36m""\x1b[1A\x1b[M"

clean:
				rm -rf $(OBJS_DIR)
				echo "\\n\033[32;1m getting in the way back machine... \033[0m \\n"
				echo "\\n\033[32;1m done. history erased. \033[0m \\n"

fclean:			
				rm -rf $(OBJS_DIR)
				rm -rf $(NAME)
				echo "\\n\033[32;1m forgetting spell being cast... \033[0m \\n"
				echo "\\n\033[32;1m okay, now tell me what it was that you wanted me to do again? \033[0m \\n"

re:				fclean	all
				echo "\\n\033[32;1m take care when you tamper with time... rewriting history can be dangerous \033[0m \\n"