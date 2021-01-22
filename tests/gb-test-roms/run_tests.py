import os
import sys
import socket
import subprocess
import select
import threading
import time

base_port = 10800
S_IFMT = 0o170000
S_IFDIR = 0o40000

results = {}
threads = []

def getEmuTestResult(sock):
	buffer = []
	timeSpent = 0
	while True:
		ready = select.select([sock.fileno()], [], [], 0.25)[0]
		if not ready and ("Passed" in "".join(buffer) or "Failed" in "".join(buffer)):
			return buffer
		if not ready:
			if len([r for r in "".join(buffer).split('\n') if r]) > 1:
				timeSpent += 0.25
				if timeSpent > 10:
					return buffer
			continue
		else:
			timeSpent = 0
		d = sock.recv(8)
		if not d:
			return buffer
		if d[0] == 104:
			buffer.append(chr(d[1]))
			sock.send(bytes([105, 0, 0x80, 0, 0, 0, 0, 0]))


def executeTest(romPath, port):
	times = 0
	sock = socket.socket()
	args = [emuPath, "--no-error", "--no-bootrom", "--no-audio", "--no-display", "--max-speed", "--listen", str(port), romPath]
	#args = [emuPath, "-nrabml", str(port), romPath]
	process = subprocess.Popen(args, 0, emuPath, subprocess.DEVNULL, subprocess.DEVNULL)
	while True:
		times += 1
		try:
			sock.connect(("localhost", port))
			break
		except ConnectionRefusedError:
			time.sleep(0.1)
		if times >= 30:
			results[romPath.replace("/", "_").replace(" ", "_")] = "Cannot connect to emulator"
			print("Cannot connect to emulator......")
			return
	sock.send(bytes([1, 1, 4, 0, 0, 0, 0, 0]))
	try:
		buffer = getEmuTestResult(sock)
	except BrokenPipeError:
		buffer = "BrokenPipeError"
	sock.close()
	process.terminate()
	old = buffer
	buffer = []
	count = 0
	while count < len(old):
		if count + 1 < len(old) and old[count] == old[count + 1] and (old[count] == ' ' or old[count] == '\n'):
			while count + 1 < len(old) and old[count] == old[count + 1]:
				count += 1
			buffer.append('\n')
		else:
			buffer.append(old[count])
		count += 1
	results[romPath.replace("/", "_").replace(" ", "_")] = "".join(buffer)


class TestThread(threading.Thread):
	def __init__(self, path, port):
		super().__init__(None, None)
		self.path = path
		self.port = port

	def run(self):
		executeTest(self.path, self.port)


def executeTestSuite(directory):
	global base_port
	for rom in sorted(os.listdir(directory)):
		if rom[-3:].lower() == ".gb" or rom[-4:].lower() == ".gbc":
			port = base_port
			thread = TestThread(directory + "/" + rom, port)
			thread.start()
			threads.append(thread)
			base_port += 1


def testEmulator(path):
	expected = "Usage: " + path + " rom.gb [-dnrmba] [-l <port>] [-c <ip:port>]"
	f = os.popen(path, "r")
	if f.read(len(expected)) != expected:
		print(path + ": GBEmulator didn't return the proper help message")
		exit(1)
	f.close()
	print(path + " seems ok")


if len(sys.argv) != 2:
	print("Usage:", sys.argv[0], "<GBEmulator executable>", sep=" ")
	exit(1)


emuPath = sys.argv[1]
testEmulator(emuPath)
for elem in sorted(os.listdir()):
	if (os.stat(elem).st_mode & S_IFMT) == S_IFDIR:
		executeTestSuite(elem)

for thread in threads:
	thread.join()

passed = 0
failed = 0
for name, result in sorted(results.items(), key=lambda a: a[0]):
	if "Passed" in result:
		passed += 1
		print(name + ": \033[32mPassed\033[0m")
	else:
		failed += 1
		print(name + ": \033[31mFailed\033[0m. Rom output:")
		print(result)

print("Total:", passed, "\033[32mPassed\033[0m,", failed, "\033[31mFailed\033[0m")