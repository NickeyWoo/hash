

TARGET := hash

all: $(TARGET)

clean:
	rm -f $(TARGET)

$(TARGET): main.cpp ../url/misc.o
	g++ -o $@ $^ -I../url -I../../project/cityhash-1.0.3/src -I../../project/commlib64/baselib -L../../project/commlib64/baselib/ -L../../project/cityhash-1.0.3/src/ -L/usr/local/x84_64-linux-gnu/ -lcityhash -lcomm_oi -lcrypto


