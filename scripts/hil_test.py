import serial
import time
from datetime import datetime

PORT = 'COM3'  # Adjust this to your actual port
BAUD = 9600
LOGFILE = 'hil_test_output.log'

def log(msg):
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    entry = f"[{timestamp}] {msg}"
    print(entry)
    with open(LOGFILE, 'a') as f:
        f.write(entry + '\n')

def send_command(command):
    try:
        with serial.Serial(PORT, BAUD, timeout=2) as ser:
            time.sleep(2)  # Wait for Arduino to reset
            ser.write((command + '\n').encode())
            log(f"> Sent: {command}")
            response = ser.readline().decode().strip()
            log(f"< Received: {response}")
    except serial.SerialException as e:
        log(f"Serial error: {e}")

if __name__ == '__main__':
    log("=== HIL Test Session Started ===")

    send_command("START")
    time.sleep(3)

    send_command("STATUS")
    send_command("MEASURE_VOLTAGE")
    send_command("UPTIME")

    time.sleep(3)
    send_command("STOP")

    send_command("STATUS")
    send_command("UPTIME")

    log("=== HIL Test Session Ended ===")
