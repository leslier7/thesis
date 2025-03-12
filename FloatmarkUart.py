import csv
import serial
import argparse

def main(file_name):
    port = "/dev/cu.usbserial-0001"  # Change this to your serial connection. Will be OS dependent
    baudrate = 115200
    serial_connection = serial.Serial(port, baudrate)

    with open(file_name, 'a') as file:
        writer = csv.writer(file)
        writer.writerow(["Test", "# Instructions", "# Clock Cycles", "", "Total Time Taken (mS)"])


    while True:
        line = serial_connection.readline().decode('utf-8').strip()
        if line == "End of Floatmark":
            break
        print(line)






if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Read from serial and save to a CSV file.')
    parser.add_argument('file_name', type=str, help='The CSV file to save data')
    args = parser.parse_args()
    main(args.file_name)