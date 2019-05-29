import serial

port = serial.Serial("/dev/ttyUSB0", baudrate=38400, timeout=5)

msg = "\x49\x41\x49\x10\x29\x23\xbe\x84\xe1\x6c\xd6\xae\x52\x90\x49\xf1\xf1\xbb\xe9\xeb"
port.write(msg)

resp = port.read(20)