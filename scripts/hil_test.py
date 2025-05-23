import serial
import time
import os

PORT = "COM3"  # Update if needed
BAUD = 9600
LOG_FILE = "logs/hil_test_output.log"

def send_command(command):
    try:
        with serial.Serial(PORT, BAUD, timeout=2) as ser:
            time.sleep(2)  # Wait for Arduino reset
            ser.write((command + '\n').encode())
            print(f"[{timestamp()}] > Sent: {command}")
            response = ser.readline().decode(errors='replace').strip()
            print(f"[{timestamp()}] < Received: {response}")
            return response
    except serial.SerialException as e:
        print(f"[{timestamp()}] Serial error: {e}")
        return None

def timestamp():
    return time.strftime("%Y-%m-%d %H:%M:%S")

def main():
    os.makedirs("logs", exist_ok=True)

    with open(LOG_FILE, "w") as log:
        def log_print(msg):
            print(msg)
            log.write(msg + "\n")

        log_print(f"[{timestamp()}] === HIL Test Session Started ===")

        response = send_command("START")
        time.sleep(2)

        response = send_command("STATUS")
        time.sleep(1)

        response = send_command("MEASURE_VOLTAGE")
        time.sleep(1)

        response = send_command("STOP")

        log_print(f"[{timestamp()}] === HIL Test Session Ended ===")

if __name__ == "__main__":
    main()
