#include <iostream>
#include <string>

using namespace std;

// Function to check if a character is a digit
bool is_digit(char c) {
  return isdigit(c);
}

// Function to validate card number length
bool is_valid_length(const string& card_number) {
  string clean_number = remove_non_digits(card_number);
  return clean_number.length() > 1;
}

// Function to remove non-numeric characters from a string
string remove_non_digits(const string& str) {
  string clean_str;
  for (char c : str) {
    if (is_digit(c)) {
      clean_str += c;
    }
  }
  return clean_str;
}

// Function to extract the check digit from a string
char get_check_digit(const string& card_number) {
  string clean_number = remove_non_digits(card_number);
  return clean_number.back();
}

// Function to separate card digits from the check digit
pair<string, char> separate_digits_and_check_digit(const string& card_number) {
  string clean_number = remove_non_digits(card_number);
  char check_digit = clean_number.back();
  clean_number.pop_back();
  return {clean_number, check_digit};
}

// Function to double every other digit, starting from the second-to-last
string double_alternate_digits(const string& digits) {
  string doubled_digits;
  for (int i = digits.length() - 1; i >= 0; --i) {
    int digit = digits[i] - '0';
    doubled_digits += ((i % 2 == 1) ? (digit * 2) : digit) + '0';
  }
  return doubled_digits;
}

// Function to calculate the sum of digits (including sum of digits from doubling)
int sum_digits(const string& digits) {
  int sum = 0;
  for (char c : digits) {
    sum += (c - '0') % 10 + (c - '0') / 10;
  }
  return sum;
}

// Function to check if the card number is valid using Luhn's algorithm
bool is_valid_card(const string& card_number) {
  if (!is_valid_length(card_number)) {
    return false;
  }

  pair<string, char> digits_and_check_digit = separate_digits_and_check_digit(card_number);
  string clean_digits = digits_and_check_digit.first;
  char check_digit = digits_and_check_digit.second;

  string doubled_digits = double_alternate_digits(clean_digits);
  int sum_of_all_digits = sum_digits(doubled_digits);

  return check_digit == ((sum_of_all_digits % 10) == 0 ? '0' : ('0' + (sum_of_all_digits % 10)));
}

int main() {
  string card_number;
  cout << "Enter your credit card number: ";
  getline(cin, card_number);

  if (is_valid_card(card_number)) {
    cout << "Valid card number." << endl;
  } else {
    cout << "Invalid card number." << endl;
  }

  return 0;
}
