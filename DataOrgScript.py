import csv
from collections import defaultdict
import os
import argparse

def reorganize_csv(input_file, output_file):
    # Read the CSV file into a list
    with open(input_file, newline='', encoding='utf-8') as csvfile:
        reader = csv.reader(csvfile)
        headers = next(reader)  # Read the header row
        rows = [row for row in reader if any(row)]  # Remove completely empty rows

    # Identify column indexes
    run_idx = headers.index("Run")
    test_idx = headers.index("Test")

    # Remove rows where "Run" or "Test" are missing
    rows = [row for row in rows if row[run_idx] and row[test_idx]]

    # Maintain original test order as they first appear
    seen_tests = []
    test_groups = {}

    for row in rows:
        test_name = row[test_idx]
        if test_name not in seen_tests:
            seen_tests.append(test_name)
        test_groups.setdefault(test_name, []).append(row)

    # Write the reorganized data to a new CSV file
    with open(output_file, mode="w", newline='', encoding='utf-8') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(headers)  # Write header row

        for i, test_name in enumerate(seen_tests):
            if i > 0:
                writer.writerow([""] * len(headers))  # Add a spacer row
            writer.writerows(test_groups[test_name])

    print(f"Reorganized file saved as: {output_file}")


def main(folder_path):
    output_folder = os.path.join(folder_path, 'Outputs')
    os.makedirs(output_folder, exist_ok=True)
    for file_name in os.listdir(folder_path):
        if file_name.endswith('.csv'):
            input_file_path = os.path.join(folder_path, file_name)
            output_file_path = os.path.join(output_folder, file_name.replace('.csv', '_reorganized.csv'))
            reorganize_csv(input_file_path, output_file_path)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Process all CSV files in a folder.')
    parser.add_argument('folder_path', type=str, help='The folder containing CSV files to process')
    args = parser.parse_args()
    main(args.folder_path)
