CC=gcc

TARGET_SRV=file_server
TARGET_CLN=file_client

LDFLAGS=

all : $(TARGET_SRV) $(TARGET_CLN)

$(TARGET_SRV):$(TARGET_SRV).o
	$(CC) -o $@ $< $(LDFLAGS)

$(TARGET_CLN):$(TARGET_CLN).o
	$(CC) -o $@ $< $(LDFLAGS)

%.o:%.c
	$(CC) -c -o $@ $<

clean:
	rm -f *.o $(TARGET_SRV) $(TARGET_CLN)
