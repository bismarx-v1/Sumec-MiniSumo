import socket


#localIp = "192.168.4.2"		# Local IP here.
localIp = socket.gethostbyname(socket.gethostname())		# Local IP here.
localPort = 2038
local = (localIp, localPort)


remoteIp = "192.168.4.1"
remotePort = 2038
remote = (remoteIp, remotePort)


socketObj = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
#socketObj = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
#socketObj = socket.socket(family=socket.AF_INET, type=socket.SOCK_RAW)
socketObj.bind(local)
socketObj.connect(remote)

message = "nya :3"
bufferTx = str.encode(message)
socketObj.sendto(bufferTx, remote)
print('Sent: ', repr(bufferTx))

bufferRxLen = 1024
while 1:
	bufferRx = socketObj.recv(bufferRxLen)
	print('Received: ', repr(bufferRx))
