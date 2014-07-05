all:clean $(exe) run

$(exe):$(objs)
	$(LINK) -o $@ $< $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(objs) $(exe) *.heap

