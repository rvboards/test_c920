CC=riscv64-unknown-linux-gnu-gcc

CFLAGS= -O3 -march=rv64imafdcv0p7_zfh_xtheadc -mabi=lp64d -mtune=c920

TARGET=test
all=$(TARGET)

$(TARGET):test.c
	$(CC) -static $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

run:$(TARGET)
	qemu-riscv64 -cpu c920 ./$(TARGET)
