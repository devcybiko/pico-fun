CPPFLAGS = -D__LINUX__ # -g -Wall -std=c++11 -fpermissive -w 

OBJECTS = main.o Template.o GObj.o GList.o GMap.o GCronEntry.o GTimer.o GCron.o

main: $(OBJECTS)
	gcc -o main $(OBJECTS) $(CPPFLAGS)

# Clean up the build
clean:
	rm -f $(OBJECTS) main
