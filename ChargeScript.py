import csv
import argparse
import numpy as np

def main(file_name):
    with open(file_name, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        instances = []
        current_instance = {'time': [], 'current': []}
        for row in reader:
            timestamp = float(row['Timestamp(ms)'])
            current = float(row['Current(uA)'])
            if row['D0'] == '1':
                if not current_instance['time']:
                    current_instance['start_time'] = timestamp
                current_instance['time'].append(timestamp)
                current_instance['current'].append(current)
            else:
                if current_instance['time']:
                    instances.append(current_instance)
                    current_instance = {'time': [], 'current': []}
        if current_instance['time']:
            instances.append(current_instance)

        charge_file_name = file_name.replace('.csv', '_Charge.csv')
        with open(charge_file_name, 'w', newline='') as outputcsvfile:
            writer = csv.writer(outputcsvfile)
            writer.writerow(['Instance', 'Charge (uC)'])
            total_time = 0
            total_current = 0
            total_charge = 0
            for index, instance in enumerate(instances, start=1):
                time = instance['time']
                current = instance['current']
                time_diff = time[-1] - time[0]
                total_time += time_diff
                total_current += sum(current)
                charge = np.trapezoid(current, time) / 1000
                total_charge += charge
                writer.writerow([index, total_charge])
                print(f'Instance {index} time: {time_diff} ms')
                print(f'Instance current: {sum(current)} uA')
                print(f'Instance charge: {charge} uC')
                print('-------------------')



if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Process a CSV file.')
    parser.add_argument('file_name', type=str, help='The CSV file to process')
    args = parser.parse_args()
    main(args.file_name)