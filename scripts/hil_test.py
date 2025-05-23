import serial
import time
import os

PORT = "COM3"  # Update if needed
BAUD = 9600

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
    # Create logs directory just in case (optional)
    os.makedirs("logs", exist_ok=True)

    print(f"[{timestamp()}] === HIL Test Session Started ===")

    send_command("START")
    time.sleep(2)

    send_command("STATUS")
    time.sleep(1)

    send_command("MEASURE_VOLTAGE")
    time.sleep(1)

    send_command("STOP")

    print(f"[{timestamp()}] === HIL Test Session Ended ===")

if __name__ == "__main__":
    main()
