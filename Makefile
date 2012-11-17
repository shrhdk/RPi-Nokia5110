Nokia5110_sample: Nokia5110_sample.o Nokia5110.o RPiGPIO.o RPiSPI.o
	cc -g -o Nokia5110_sample Nokia5110_sample.o Nokia5110.o RPiGPIO.o RPiSPI.o

Nokia5110_sample.o: Nokia5110_sample.c
Nokia5110.o: Nokia5110.c
RPiGPIO.o: RPiGPIO.c
RPiSPI.o: RPiSPI.c

.c.o:
	cc -g -c $<

clean:
	rm *.o
