build: 
	gcc -std=gnu99 -o tema1 fctLG.c fctTABH.c main.c
run:
	./tema1
clean:
	rm -rf tema1