import csv
import os

# Input CSV file path (corrected)
csv_file_path = r"C:\DSA-SEM-3\Search Engine Final Project\Reviews.csv"
# Output folder for text files
output_folder = "review_text"

def create_review_text_file(review):
    """Create a text file for a single review."""
    try:
        # Ensure output folder exists
        if not os.path.exists(output_folder):
            os.makedirs(output_folder)

        # File name for the review
        file_name = f"{output_folder}/review_{review['Id']}.txt"

        # Write review details to the text file
        with open(file_name, 'w', encoding='utf-8') as file:
            file.write(f"ProductId: {review.get('ProductId', 'N/A')}\n")
            file.write(f"UserId: {review.get('UserId', 'N/A')}\n")
            file.write(f"ProfileName: {review.get('ProfileName', 'N/A')}\n")
            file.write(f"HelpfulnessNumerator: {review.get('HelpfulnessNumerator', 'N/A')}\n")
            file.write(f"HelpfulnessDenominator: {review.get('HelpfulnessDenominator', 'N/A')}\n")
            file.write(f"Score: {review.get('Score', 'N/A')}\n")
            file.write(f"Time: {review.get('Time', 'N/A')}\n")
            file.write(f"Summary: {review.get('Summary', 'N/A')}\n")
            file.write(f"Text: {review.get('Text', 'N/A')}\n")
    except Exception as e:
        print(f"Error creating file for review ID {review.get('Id', 'Unknown')}: {e}")

def csv_to_text(csv_file_path):
    """Convert a CSV file of reviews into individual text files."""
    try:
        if not os.path.exists(csv_file_path):
            print(f"Error: CSV file '{csv_file_path}' does not exist.")
            return

        # Open and read the CSV file
        with open(csv_file_path, 'r', encoding='utf-8') as csv_file:
            reader = csv.DictReader(csv_file)

            # Track progress
            total_reviews = 0
            processed_reviews = 0

            for row in reader:
                total_reviews += 1
                try:
                    create_review_text_file(row)
                    processed_reviews += 1
                except Exception as e:
                    print(f"Failed to process row {row.get('Id', 'Unknown')}: {e}")

            print(f"Conversion complete. Processed {processed_reviews}/{total_reviews} reviews.")
    except Exception as e:
        print(f"Error processing CSV file: {e}")

if __name__ == "__main__":
    csv_to_text(csv_file_path)
