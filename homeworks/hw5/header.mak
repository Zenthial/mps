# 
# Programs in this directory include the object_list.h interface file

CFLAGS = -ggdb -std=c99 -Wall -Wextra -pedantic -I/home/course/csci243/pub/homeworks/05/include

# 
# Programs in this directory link to the libobject_list.a library

CLIBFLAGS =	-lm -L/home/course/csci243/pub/homeworks/05/lib/ -lobject_list
