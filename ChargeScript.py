import csv
import argparse
import numpy as np
import os
import re

def process_file(file_name, output_folder):
    with open(file_name, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        runs = []
        current_runs = []
        current_test = {'time': [], 'current': []}
        for row in reader:
            timestamp = float(row['Timestamp(ms)'])
            current = float(row['Current(uA)'])
            if row['D1'] == '1':
                if row['D0'] == '1':
                    if not current_test['time']:
                        current_test['start_time'] = timestamp
                    current_test['time'].append(timestamp)
                    current_test['current'].append(current)
                else:
                    if current_test['time']:
                        current_runs.append(current_test)
                        current_test = {'time': [], 'current': []}
            else:
                if current_runs:
                    runs.append(current_runs)
                    current_runs = []
        if current_test['time']:
            current_runs.append(current_test)
        if current_runs:
            runs.append(current_runs)

        charge_file_name = os.path.join(output_folder, os.path.basename(file_name).replace('.csv', '_Charge.csv'))
        with open(charge_file_name, 'w', newline='') as outputcsvfile:
            writer = csv.writer(outputcsvfile)
            writer.writerow(['Test', 'Run', 'Charge (uC)', 'Time (ms)'])

            test_dict = {}
            for run_index, run in enumerate(runs, start=1):
                for test_index, test in enumerate(run, start=1):
                    if test_index not in test_dict:
                        test_dict[test_index] = []
                    test_dict[test_index].append((run_index, test))

            for test_index, tests in test_dict.items():
                for run_index, test in tests:
                    time = test['time']
                    current = test['current']
                    time_diff = time[-1] - time[0]
                    charge = np.trapezoid(current, time) / 1000
                    writer.writerow([test_index, run_index, charge, time_diff])
                    print(f'Test {test_index} Run {run_index} time: {time_diff} ms')
                    print(f'Test {test_index} Run {run_index} charge: {charge} uC')
                writer.writerow([]) # Add a spacer row
                print('-------------------')

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