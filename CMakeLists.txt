cmake_minimum_required(VERSION 3.16)
project(Progetto2Gruppo25 C)

set(CMAKE_C_STANDARD 99)

add_executable(Progetto2Gruppo25 main.c List/list.c List/list.h Queue/queue.c Queue/queue.h Input/inputReader.c Input/inputReader.h Graph/graph.c Graph/graph.h User/user.h User/user.c Util/util.c Util/util.h CheckMail/checkMail.c CheckMail/checkMail.h Booking/booking.c Booking/booking.h)
