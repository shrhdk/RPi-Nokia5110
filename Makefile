TARGET	= Nokia5110_sample

$(TARGET): example/Nokia5110_sample.o src/Nokia5110.o src/RPiGPIO.o src/RPiSPI.o
	cc -g $^ -o $@

Nokia5110_sample.o: example/Nokia5110_sample.c
Nokia5110.o: src/Nokia5110.c
RPiGPIO.o: src/RPiGPIO.c
RPiSPI.o: src/RPiSPI.c

.c.o:
	cc -g -o $@ -c $^

clean:
	rm src/*.o example/*.o
	rm $(TARGET)
