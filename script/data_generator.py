import random

N = 1000*1000*100

def writeRecord(output):
    for i in range(5):
        output.write(random.randint(-10000, 10000).to_bytes(4, byteorder='little', signed=True))


output = open(f"D:/Studia/Struktury baz danych/input{N}.bin", "wb")

for i in range(N):
    writeRecord(output)
output.close()