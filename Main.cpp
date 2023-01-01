#include<iostream>
#include<string>

using namespace std;

string getSign(string s);
void getNums(string s, float arr[]);
void replace(string& s, string before, string after);
void remove(float arr[], int index);
bool contains(string s, string boi);
float reccursiveCalculate(string input);

int main() {
	string input;
	getline(cin, input);
	//input = "32.5 - (65 + 22) / 3 + (1 / 13)";

	cout << reccursiveCalculate(input) << endl;
	//cout << input.length();

	return 0;
}

float reccursiveCalculate(string input) {
	while (contains(input, "(")) {
		if (not contains(input, ")")) return 0;

		// finds the corresponding closed bracket for the first open bracket
		int bracketCounter = 1;
		int firstBracket = input.find("(");
		int lastBracket = firstBracket;
		for (int i = firstBracket + 1; i < input.length(); i++) {
			if (input[i] == '(') bracketCounter++;
			else if (input[i] == ')') {
				bracketCounter--;
				if (bracketCounter <= 0) {
					lastBracket = i;
					break;
				}
			}
		}

		int bracketLength = lastBracket - firstBracket + 1;
		// string containing the bracket
		string bracket = input.substr(firstBracket, bracketLength);
		// string containing the insides of the above bracket
		string nextInput = input.substr(firstBracket + 1, bracketLength - 2);

		// replaces the bracket with the sum/product of the things inside
		replace(input, bracket, to_string(reccursiveCalculate(nextInput)));
		//std::cout << input << std::endl;
	}

	// string containing just the operations from the input string (3 for + or -, 2 for *, and 3 for /)
	string op = getSign(input);

	float arr[30];
	for (int i = 0; i < 30; i++) {
		arr[i] = -12000;
	}
	// array containing just the numbers from the input string
	getNums(input, arr);

	while (contains(op, "3")) {
		int i = op.find("3");
		arr[i] = arr[i] / arr[i + 1];
		remove(arr, i + 1);
		op.replace(i, 1, "");
	}
	while (contains(op, "2")) {
		int i = op.find("2");
		arr[i] = arr[i] * arr[i + 1];
		remove(arr, i + 1);
		op.replace(i, 1, "");
	}
	while (contains(op, "1")) {
		int i = op.find("1");
		arr[i] = arr[i] + arr[i + 1];
		remove(arr, i + 1);
		op.replace(i, 1, "");
	}

	return arr[0];
}

string getSign(string input) {
	// returns a string containing just the operations from the input string (3 for + or -, 2 for *, and 3 for /)
	int l = input.length();
	string o = "";
	int i = 0;

	while (i < l) {
		if (input[i] == '+' || input[i] == '-') {
			o.append("1");
		}
		else if (input[i] == '*') {
			o.append("2");
		}
		else if (input[i] == '/') {
			o.append("3");
		}
		i++;
	}
	return o;
}

void getNums(string s, float arr[]) {
	// places just the numbers from the input string into the array arr
	int l = s.length();
	int i = 0, last = 0, count = 0;
	bool nextNeg = false;
	string b;

	while (i <= l) {
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || i == l) {
			b = s.substr(last, i - last);
			replace(b, " ", "");
			if (nextNeg) {
				arr[count] = -stof(b);
				nextNeg = false;
			}
			else {
				arr[count] = stof(b);
			}
			last = i + 1;
			count++;
		}
		if (s[i] == '-') {
			nextNeg = true;
		}
		i++;
	}
}

void replace(string& s, string before, string after) {
	// replaces every instance of the before string with the after string inside string s
	int l = s.length(), lb = before.length(), la = after.length();
	int i = 0;
	int diff = la - lb;

	while (i < l) {
		if (s[i] == before[0] && s.substr(i, lb) == before) {
			s.replace(i, lb, after);
			l += diff;
			i += diff;
		}
		i++;
	}
}

void remove(float arr[], int index) {
	// removes number from array
	// in this program I use -12000 to indicate an empty spot in the array
	// I am not sure if there is a better way of doing it... by default it's 0 which was problematic in this case
	int i = index;
	while (arr[i] != -12000) {
		arr[i] = arr[i + 1];
		i++;
	}
}

bool contains(string s, string boi) {
	// checks if the string s contains the string boi
	int l = s.length(), lb = boi.length();
	if (lb > l) return false;

	for (int i = 0; i <= l; i++) {
		if (s[i] == boi[0] && s.substr(i, lb) == boi) {
			return true;
		}
	}
	return false;
}