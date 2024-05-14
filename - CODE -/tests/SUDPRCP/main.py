'''
import socket

BUFFER_LEN = 32

def SendUDP(UDP_IP, UDP_PORT, message, bufferLen=32):
	message = message[:bufferLen]
	so = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	try:
		so.sendto(message.encode(), (UDP_IP, UDP_PORT))
	finally:
		so.close()


message = "012345678901234567890123456789012345678901234567890123456789"  # send the message via socket



SendUDP("192.168.1.22", 1984, message, BUFFER_LEN)

SendUDP("192.168.1.22", 1984, "message", BUFFER_LEN)
'''


'''
import socket

localIP = "192.168.1.22"
localPort = 1984
bufferSize = 64

UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
UDPServerSocket.bind((localIP, localPort))

while(1):
	bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)
	message = bytesAddressPair[0]
	
	address = bytesAddressPair[1]
	clientMsg = "Msg: {}".format(message.decode())
	clientIP = "IP: {}".format(address)
	
	print(clientMsg)
	print(clientIP)
	
'''

#=============================================

# !/usr/bin/python3
# -*-coding:Utf-8 -*
"""
Created on Thu Nov 17 16:59:13 2022

@author: X.Wiedmer

AC windows
Define the application window
"""

import sys, os
# from PyQt5.QtWidgets import *
# from PyQt5.QtCore import *
# from PyQt5.QtGui import *
from PySide2.QtWidgets import *
from PySide2.QtCore import *
from PySide2.QtGui import *

pyqtSignal = Signal  # translate pyqt to Pyside

import socket
import time

"""
App configuration
"""
__title__ = "ACTerminal"
__version__ = "v0.1"

HOST = '192.168.1.67'
PORT = 8888


# Ethernet connection
class EthModel(QThread):
	"""Handle Ethernet connexion with remote device and connect to interface EthInterface"""
	debugSignal = pyqtSignal(str)  # define debug signal
	
	def __init__(self):
		super(EthModel, self).__init__()
		self.quit_flag = False
		self.msgToEmit = ""
	
	def run(self):
		while True:
			if not self.quit_flag:
				self.read()
			# time.sleep(1)
			else:
				self.close()
				break
		
		self.quit()
		self.exit()
	
	# self.wait()
	
	def connec(self, addr='192.168.1.10', port=7):
		# Create a UDP/IP socket
		self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # worls with esp8266 udp client
		self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
		self.sock.bind((addr, port))
		# Listen for incoming connections
		# self.sock.listen(1) #stream
		
		print('starting up on {} port {}'.format(addr, port))
		self.debugSignal.emit('starting up on {} port {}'.format(addr, port))
		self.quit_flag = False
		self._isRunning = True
	
	def read(self):
		while self._isRunning:
			# data = self.sock.recv(1024)
			try:
				data, addr = self.sock.recvfrom(1024)
				print(data)
			except:
				print("socket closed")
				data = False
			
			if not data:
				print("no data &gt; break loop")
				break
			# self.sock.sendto("received OK".encode('utf-8'),addr)
			if self.msgToEmit != "":
				self.sock.sendto(self.msgToEmit.encode('utf-8'), addr)
				self.msgToEmit = ""  # clear message
			self.debugSignal.emit(str(data))
	
	def write(self, msg):
		self.msgToEmit = msg
	
	def close(self):
		self._isRunning = False
		self.sock.close()


# define GUI
class EthernetInterface(QFrame):
	debugSignal = pyqtSignal(str)  # define debug signal
	
	def __init__(self, parent=None):
		super(EthernetInterface, self).__init__(parent)
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		self.defineWidgets()
		self.model = EthModel()  # self.model=None
		self.model.debugSignal.connect(self.read)
	
	def defineWidgets(self):
		# self.setStyleSheet("""QGroupBox{backgrornd-color:white;border: 1px solid green;border-radius: 4px;}
		# QGroupBox::title {padding:1 5px;}""")
		
		# groorpbox widget container
		self.grp = QGroupBox(self)
		self.grp.setTitle("Connection Configuration")
		
		self.fields = QGridLayout()
		self.grp.setLayout(self.fields)
		self.grid.addWidget(self.grp, 0, 0)
		
		# Define widget UI
		# validator
		ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])"  # Part of the regular expression
		# Regulare expression
		ipRegex = QRegExp("^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\." + ipRange + "$")
		ipValidator = QRegExpValidator(ipRegex, self)
		
		# label
		self.selectlbl = QLabel("IP Address:")
		self.typeBox = QLineEdit(HOST)
		# self.typeBox.setInputMask("0.0.0.0");
		self.typeBox.setValidator(ipValidator);
		
		self.baudlbl = QLabel("Port:")
		self.baudBox = QLineEdit("{}".format(PORT))
		
		# btn
		self.button = QPushButton("Connect")
		self.button.clicked.connect(self.clicked)
		self.button.clicked.connect(self.connec)
		
		sendBtn = QPushButton("send")
		sendBtn.clicked.connect(self.clicked)
		sendBtn.clicked.connect(self.send)
		
		titlelbl = QLabel("Enter")
		self.edit = QLineEdit("")
		sentlbl = QLabel("Sent")
		self.sent = QTextEdit("")
		desclbl = QLabel("Console")
		self.desc = QTextEdit("")
		
		# row, column[, rowSpan=1[, columnSpan=1[
		self.fields.addWidget(self.selectlbl, 0, 0, 1, 1)
		self.fields.addWidget(self.typeBox, 0, 1, 1, 1)
		self.fields.addWidget(self.baudlbl, 0, 2, 1, 1)
		self.fields.addWidget(self.baudBox, 0, 3, 1, 1)
		
		self.fields.addWidget(self.button, 0, 4, 1, 1)
		
		self.fields.addWidget(titlelbl, 1, 0, 1, 1)
		self.fields.addWidget(self.edit, 1, 1, 1, 3)
		self.fields.addWidget(sendBtn, 1, 4, 1, 1)
		
		self.fields.addWidget(sentlbl, 2, 0, 1, 1, Qt.AlignTop)  # Qt.AlignmentFlag.AlignTop)
		self.fields.addWidget(self.sent, 2, 1, 1, 3)
		self.fields.addWidget(desclbl, 3, 0, 1, 1, Qt.AlignTop)  # Qt.AlignmentFlag.AlignTop)
		self.fields.addWidget(self.desc, 3, 1, 1, 3)
	
	def debug(self, msg):
		sender = self.sender()
		self.debugSignal.emit(sender.__class__.__name__ + " : " + msg)
	
	def clicked(self):
		sender = self.sender()
		if sender.__class__.__name__ == "QPushButton":
			self.debugSignal.emit(sender.text() + " clicked")
		if sender.__class__.__name__ == "QComboBox":
			self.debugSignal.emit(sender.currentText() + " selected")
	
	def connec(self):
		# self.desc.setText("")
		self.desc.clear()
		if self.model is not None:
			if self.button.text() == "Connect":
				self.desc.setText(
					"&gt;&gt; trying to connect to address {} on port {} ...\n".format(self.typeBox.text(),
																					   self.baudBox.text()))
				
				print("Started")
				self.button.setText("Stop")
				self.model.connec(self.typeBox.text(), int(self.baudBox.text()))
				self.model.start()
			else:
				self.model.quit_flag = True
				print("Stop sent")
				self.model.close()  # self.model.wait()
				print("Stopped")
				self.button.setText("Connect")
				self.desc.setText(
					"&gt;&gt; deconnect address {} on port {} ...".format(self.typeBox.text(), self.baudBox.text()))
	
	def read(self, msg):
		self.desc.setText(self.desc.toPlainText() + msg + "\n")
		self.desc.verticalScrollBar().setValue(self.desc.verticalScrollBar().maximum());
	
	def send(self):
		if self.edit.text() != "":
			self.sent.setText(self.sent.toPlainText() + self.edit.text() + "\n")
			
			if self.model is not None:
				self.model.write(self.edit.text())


# Generic app container
class AcApp(QMainWindow):
	
	def __init__(self, title='AcApp', mainFrame=QFrame):
		super().__init__()
		self.title = title
		self.mainFrame = mainFrame()
		self.initUI()
	
	def initUI(self):
		self.setCentralWidget(self.mainFrame)
		
		# connect signals
		self.mainFrame.debugSignal.connect(self.debugMsg)
		
		# General configuration
		# self.resize(self.width, self.height)
		self.setWindowTitle(self.title)
		self.setGeometry(300, 300, 850, 450)
		# self.setWindowIcon(QIcon(__icon__))
		
		# Debug bar
		self.statusBar()
		self.statusBar().showMessage('Display debug messages')
		
		self.show()
	
	def debugMsg(self, val):
		self.statusBar().showMessage(val)


def main():
	app = QApplication(sys.argv)
	app.setQuitOnLastWindowClosed(True)
	# app.setStyleSheet(open("style.txt").read()); #set style according to file
	# ex = AcApp(__title__)
	ex = AcApp(__title__, EthernetInterface)
	app.quit()
	sys.exit(app.exec_())


if __name__ == '__main__':
	main()