import serial
import time

PORT = 'COM3'  # Adjust as needed
BAUD = 9600

def send_command(command):
    try:
        with serial.Serial(PORT, BAUD, timeout=2) as ser:
            time.sleep(2)  # Give Arduino time to reset on COM open
            ser.write((command + '\n').encode())
            print(f"> Sent: {command}")
            response = ser.readline().decode().strip()
            print(f"< Received: {response}")
    except serial.SerialException as e:
        print(f"Serial error: {e}")

if __name__ == '__main__':
    print("Sending START command...")
    send_command("START")
    time.sleep(10)  # Simulate wait time during test
    print("Sending STOP command...")
    send_command("STOP")
