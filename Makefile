.PHONY			: 			clean fclean re all

DEBUG				=				false
COMPIL			=				gcc

NORMAL			=				"\033[0m"
BOLD				=				"\033[1m"
UNBOLD			=				"\033[21m"
UNDERLINE		=				"\033[4m"
UNUNDERLINE	=				"\033[24m"
SURLIGNE		=				"\033[7m"
UNSURLIGNE	=				"\033[27m"

RED					=				"\033[31m"
GREEN				=				"\033[32m"
YELLOW			=				"\033[33m"
DARKBLUE		=				"\033[34m"
PINK				=				"\033[35m"
TEAL				=				"\033[36m"

SERVER 			=				zappy_server
CLIENT			=				zappy_ai
SPSRC				=				./srcServer/
CPSRC				=				./srcClient/
GRAPHIC			=				./graphic/
SSRC 				=				$(SPSRC)main.c \
										$(SPSRC)print.c \
										$(SPSRC)cmd.c \
										$(SPSRC)cmd_next.c \
										$(SPSRC)cmd_next_next.c \
										$(SPSRC)list.c \
										$(SPSRC)init_server.c \
										$(SPSRC)map.c \
										$(SPSRC)stack.c \
										$(SPSRC)vector.c \
										$(SPSRC)inventory.c \
										$(SPSRC)see.c \
										$(SPSRC)cmd_list.c \
										$(SPSRC)parsing_args.c \
										$(SPSRC)check_args.c \
										$(SPSRC)parse_squad.c \
										$(SPSRC)squad.c \
										$(SPSRC)time_management.c \
										$(SPSRC)life_management.c \
										$(SPSRC)egg.c \
										$(SPSRC)spawn_ressources.c \
										$(SPSRC)protocol_server.c \
										$(SPSRC)egg_stack.c \
										$(SPSRC)tablen.c \
										$(SPSRC)cmd_tmp.c \
										$(SPSRC)broadcast.c \
										$(SPSRC)cmd_next_next_next.c \
										$(SPSRC)expulse.c \
										$(SPSRC)see2.c
CSRC				=				$(CPSRC)client.c \
								$(CPSRC)cmd_elev.c \
								$(CPSRC)write_read.c \
								$(CPSRC)protocol_client.c \
								$(CPSRC)ia.c \
								$(CPSRC)ia_evolve.c \
								$(CPSRC)ia_search.c \
								$(CPSRC)ia_evolve_search.c \
								$(CPSRC)ia_action.c \
								$(CPSRC)ia_func.c \
								$(CPSRC)gotTo.c \
								$(CPSRC)parse_see.c \
								$(CPSRC)parse_obj.c \
								$(CPSRC)functions.c \
								$(CPSRC)verif_param.c
GRAPHICSRC	=				$(GRAPHIC)tile.cpp \
										$(GRAPHIC)extern.cpp \
										$(GRAPHIC)map.cpp \
										$(GRAPHIC)player.cpp \
										$(GRAPHIC)mineral.cpp

NBSRC				=				44

SOBJS				=				$(SSRC:.c=.o)
COBJS				=				$(CSRC:.c=.o)
GRAPHICOBJS	=				$(GRAPHICSRC:.cpp=.o)

ifeq 								($(COMPIL),gcc)
	C					=				gcc
	CXX 			=				g++
else
	C					=				clang-3.5
	CXX				=				clang-3.5
endif
ifeq 								($(DEBUG),true)
	CFLAGS			=				-Wall -Wextra -Werror -lm -lpthread -g3
else
	CFLAGS			=				-Wall -Wextra -Werror -lm -lpthread
endif
LFLAGS		  +=			-I ./inc/ -lsfml-graphics -lsfml-window -lsfml-system -lstdc++ -lGL


all					 : $(SERVER) $(CLIENT)
ifeq ($(DEBUG),true)
	@echo $(BOLD)$(RED)"COMPILED WITH DEBUG MODE"$(NORMAL)
else
	@echo $(BOLD)$(RED)"COMPILED WITHOUT DEBUG MODE"$(NORMAL)
endif

%.o				 :	%.cpp
								@$(eval compteur=$(shell echo $$(($(compteur)+1))))
								@$(eval pct=$(shell echo $$(($(compteur)*100/$(NBSRC)))))
								@$(CXX) -o $@ -c $< $(LFLAGS)
								@echo $(BOLD)"["$(GREEN)$(pct)$(NORMAL)" %]"$(BOLD)$(PINK)" [GENERATING]    "$(NORMAL)$@$(BOLD)$(YELLOW)" [FROM] "$(NORMAL)$<

%.o				 :  %.c
								@$(eval compteur=$(shell echo $$(($(compteur)+1))))
								@$(eval pct=$(shell echo $$(($(compteur)*100/$(NBSRC)))))
								@$(C) -o $@ -c $< $(LFLAGS)
								@echo $(BOLD)"["$(GREEN)$(pct)$(NORMAL)" %]"$(BOLD)$(PINK)" [GENERATING]    "$(NORMAL)$@$(BOLD)$(YELLOW)" [FROM] "$(NORMAL)$<

$(SERVER) 	 :  $(SOBJS) $(GRAPHICOBJS)
								@printf $(TEAL)$(BOLD)"[GENERATING]"$(NORMAL)
								@printf "%30s          " $@
								@printf $(NORMAL)"\n"
								@$(C) -o $(SERVER) $(SOBJS) $(GRAPHICOBJS) $(CFLAGS) $(LFLAGS)
								@echo	$(BOLD)$(GREEN)"#------------------------------------------------------#"
								@printf $(BOLD)$(GREEN)"[COMPILED EXEC]"$(NORMAL)
								@printf "%5s"$(SERVER)
								@printf "\n"
								@echo	$(BOLD)$(GREEN)"#------------------------------------------------------#"
								@printf "\n"

$(CLIENT)		 :	$(COBJS)
								@printf $(TEAL)$(BOLD)"[GENERATING]"$(NORMAL)
								@printf "%30s          " $@
								@printf $(NORMAL)"\n"
								@$(C) -o $(CLIENT) $(COBJS) $(CFLAGS) $(LFLAGS)
								@echo	$(BOLD)$(GREEN)"#------------------------------------------------------#"
								@printf $(BOLD)$(GREEN)"[COMPILED EXEC]"$(NORMAL)
								@printf "%5s"$(CLIENT)
								@printf "\n"
								@echo	$(BOLD)$(GREEN)"#------------------------------------------------------#"
								@printf "\n"

clean				 :
								@rm -rf $(SOBJS) $(COBJS)
								@echo $(BOLD)$(RED)"OBJECT FILES DELETED"$(NORMAL)

fclean			 :	clean
								@rm -rf $(SERVER) $(CLIENT)
								@echo $(BOLD)$(RED)"EXEC FILE DELETED\n"$(NORMAL)

re					 :	fclean all

.ONESHELL:
install			 :
								chmod 777 install_sdl.sh
								install_sdl.sh
