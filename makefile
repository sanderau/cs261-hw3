default: skipList

skipList: skipList.c skipList.h 
	gcc -Wall -ansi skipList.c skipList.h -o run	
		
clean:
	rm run
