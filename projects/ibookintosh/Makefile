#
# to be used for local compilation (not delivered to Pico)
#

CPPFLAGS = -D__LINUX__ -I../gtos # -g -Wall -std=c++11 -fpermissive -w 

GTOS_OBJECTS = ../gtos/Template.o ../gtos/GObj.o ../gtos/GList.o ../gtos/GMap.o ../gtos/GCronEntry.o ../gtos/GTimer.o ../gtos/GCron.o

OBJECTS = main.o

main: $(OBJECTS)
	gcc -o main $(OBJECTS) $(GTOS_OBJECTS) $(CPPFLAGS)

# Clean up the build
clean:
	rm -f $(OBJECTS) main
