import csv
import serial
import argparse

def main(file_name, port):
    baudrate = 115200
    serial_connection = serial.Serial(port, baudrate)

    with open(file_name, 'a') as file:
        writer = csv.writer(file)
        writer.writerow(["Test", "# Instructions", "# Clock Cycles", "", "Total Time Taken (mS)"])

        i = 0
        tests = ["Float addition", "Float Subtraction"]
        while True:
            line = serial_connection.readline().decode('utf-8').strip()
            if line == "End of benchmark":
                file.close()
                break
            #print(line)


            if "results" in line.lower():
                test = line.split("Results:")[0].strip()
                print(test)
            elif "time taken" in line.lower():
                time_taken = float(line.split(":")[1].strip().split()[0])
                print("Time taken: ", time_taken)
            elif "instructions" in line.lower():
                instructions = int(line.split(":")[1].strip().split()[0])
                print("Instructions: ", instructions)
            elif "clock cycles" in line.lower():
                clock_cycles = int(line.split(":")[1].strip().split()[0])
                print("Clock cycles: ", clock_cycles)
                print("")
                i += 1
                writer.writerow([test, instructions, clock_cycles, "", time_taken])


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Read from serial and save to a CSV file.')
    parser.add_argument('file_name', type=str, help='The CSV file to save data')
    parser.add_argument('port', type=str, help='The serial port to connect to')
    args = parser.parse_args()
    main(args.file_name, args.port)