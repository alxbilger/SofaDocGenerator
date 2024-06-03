import sys
import re
import os

starting_pattern = r"^\d+_"


def starts_with_digits_and_underscore(text):
    """
    Checks if a string starts with digits followed by an underscore using regex.

    Args:
    text: The string to check.

    Returns:
    True if the string starts with digits and _, False otherwise.
    """
    return bool(re.match(starting_pattern, text))


def add_metadata(filepath):
    filename = os.path.basename(filepath)
    filename = os.path.splitext(filename)[0]
    match = re.search(starting_pattern, filename)
    title = filename[match.end():]
    title = title.replace("_", " ")
    header_text = "---\n"
    header_text += "title: " + title + '\n'
    header_text += "---\n\n"
    with open(filepath, "r+", encoding='utf-8') as file:
        content = file.read()
        if not content.startswith(header_text):
            file.seek(0)
            file.write(header_text + content)
            file.truncate()


def analyze_folder(folder_path):
    """
    Analyzes all files recursively in a folder, modifying files starting with digits and _.

    Args:
    folder_path: Path to the folder to analyze.
    header_text: The text to add as the header for matching files.
    """
    for root, _, files in os.walk(folder_path):
        for filename in files:
            if starts_with_digits_and_underscore(filename):
                filepath = os.path.join(root, filename)
                print(f"Adding meta-data to: {filepath}")
                add_metadata(filepath)



if __name__ == "__main__":
    input_directory = sys.argv[1]

    print(f"input_directory: {input_directory}")

    analyze_folder(input_directory)
