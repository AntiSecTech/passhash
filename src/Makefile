CC = gcc
CFLAGS = 
TARGET = passhash
SRC = passhash.c
BINDIR = /bin
MANDIR = /usr/share/man/man1

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

install: $(TARGET)
	cp $(TARGET) $(BINDIR)/$(TARGET)
	if [ -f $(TARGET).1 ]; then \
		cp $(TARGET).1 $(MANDIR)/$(TARGET).1; \
	fi

uninstall:
	rm -f $(BINDIR)/$(TARGET)
	rm -f $(MANDIR)/$(TARGET).1

clean:
	rm -f $(TARGET)

.PHONY: all install uninstall clean
