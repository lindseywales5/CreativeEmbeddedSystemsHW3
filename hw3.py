import socket
from datetime import datetime

UDP_IP = "192.168.1.29" # The IP that is printed in the serial monitor from the ESP32
SHARED_UDP_PORT = 4210
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Internet  # UDP
sock.connect((UDP_IP, SHARED_UDP_PORT))
total_cals = 0
max_cals = 400


def loop():
    now = datetime.now().time()	
    hour = int(now.strftime("%H"))
    time = now.strftime("%H:%M:%S")
    if hour < 9:
        total_cals = 0
    elif hour >= 9 and hour < 18:
        total_cals = 190
    else:
        total_cals = 380
    
    while True:   
        now = datetime.now().time()	
        time = now.strftime("%H:%M:%S")
        data = sock.recv(2048)
        if int(data)<25:
            if total_cals < max_cals:
                sock.send('servo'.encode())
                total_cals += 5 
                print("At " + time + " Chewy had a treat, bringing his total calories for the day to ", total_cals)
            else:
                print("At " + time + " Chewy wanted a treat but had already surpassed his daily calorie limit :( ")    

if __name__ == "__main__":
    sock.send('Hello ESP32'.encode())
    loop()
