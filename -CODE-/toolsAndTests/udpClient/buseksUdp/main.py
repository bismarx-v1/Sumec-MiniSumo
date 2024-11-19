# Imports
import sys
import socket
import pygame
import threading
import struct

def gui():
    pygame.init()
    fps = 60
    fpsClock = pygame.time.Clock()
    width, height = 640, 480
    screen = pygame.display.set_mode((width, height))
    while True:
        screen.fill((20, 20, 20))
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_1:
                    bytesToSend = b'\x01'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_2:
                    bytesToSend = b'\x02'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_3:
                    bytesToSend = b'\x03'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_4:
                    bytesToSend = b'\x04'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_5:
                    bytesToSend = b'\x05'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_6:
                    bytesToSend = b'\x06'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_7:
                    bytesToSend = b'\x07'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_0:
                    bytesToSend = b'\x00'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_o:
                    print("ON")
                    bytesToSend = b'\xEE'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_f:
                    print("OFF")
                    bytesToSend = b'\xFF'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_z:
                    bytesToSend = b'\xCC'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_a:
                    bytesToSend = b'\xAA'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_d:
                    bytesToSend = b'\xDD'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_LSHIFT:
                    bytesToSend = b'\xB0'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
                if event.key == pygame.K_RSHIFT:
                    bytesToSend = b'\xB1'
                    UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))
        keys = pygame.key.get_pressed()
        if keys[pygame.K_w]:
            print('W Pressed')

        pygame.display.flip()
        fpsClock.tick(fps)

def recv(file, lock):
    try:
        while(True):
            
            bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
            message = bytesAddressPair[0]

            # parse variables from message
            
            time = int.from_bytes(message[0:4], byteorder='little', signed=False)
            [position] = struct.unpack('f', message[4:8])
            [phi] = struct.unpack('f', message[8:12])
            [theta] = struct.unpack('<f', message[12:16])
            [motor] = struct.unpack('<f', message[16:20])
            [servo] = struct.unpack('<f', message[20:24])
            
            #motor = int.from_bytes(message[16:20], byteorder='little', signed=False)
            #servo = int.from_bytes(message[20:24], byteorder='little', signed=False)
            
            #address = bytesAddressPair[1]
            
    #        with lock:
            file.write("%d,%.6f,%.6f,%.6f,%.6f,%.6f\n" % (time, position, phi, theta, motor, servo))
            file.flush()

            print("%d\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f" % (time, position, phi, theta, motor, servo))
    except:
        file.close()

localIP = "192.168.4.2"
localPort = 2038
bufferSize  = 128
UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
UDPServerSocket.bind((localIP, localPort))

msgFromServer = "init"
bytesToSend = str.encode(msgFromServer)
UDPServerSocket.sendto(bytesToSend, ("192.168.4.1", localPort))

lock = threading.Lock()
file = open("data.txt", 'a')

# initialize threads

gui_thread = threading.Thread(target=gui)
recv_thread = threading.Thread(target=recv, args=(file, lock))

# start threads

gui_thread.start()
recv_thread.start()
