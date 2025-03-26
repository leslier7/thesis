import csv
import argparse
import numpy as np
import os
import re

def process_file(file_name, output_folder):
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

        charge_file_name = os.path.join(output_folder, os.path.basename(file_name).replace('.csv', '_Charge.csv'))
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
                if index == len(instances):
                    print('')
            outputcsvfile.close()

def main(folder_path):
    output_folder = os.path.join(folder_path, 'Outputs')
    os.makedirs(output_folder, exist_ok=True)
    for file_name in os.listdir(folder_path):
        if file_name.endswith('.csv'):
            process_file(os.path.join(folder_path, file_name), output_folder)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Process all CSV files in a folder.')
    parser.add_argument('folder_path', type=str, help='The folder containing CSV files to process')
    args = parser.parse_args()
    main(args.folder_path)