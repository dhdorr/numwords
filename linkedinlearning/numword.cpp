#include <format>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <iostream>


std::unordered_map<int, std::string> ones_to_words {
	{1, "one"},
	{2, "two"},
	{3, "three"},
	{4, "four"},
	{5, "five"},
	{6, "six"},
	{7, "seven"},
	{8, "eight"},
	{9, "nine"},
};

// if the tens place is a 1, look ahead a digit to get the ones and check this map
std::unordered_map<int, std::string> tens_to_words{
	{10, "ten"},
	{11, "eleven"},
	{12, "twelve"},
	{13, "thirteen"},
	{14, "forteen"},
	{15, "fifteen"},
	{16, "sixteen"},
	{17, "seventeen"},
	{18, "eighteen"},
	{19, "nineteen"},
};

std::unordered_map<int, std::string> dec_to_words{
	{2, "twenty"},
	{3, "thirty"},
	{4, "forty"},
	{5, "fifty"},
	{6, "sixty"},
	{7, "seventy"},
	{8, "eighty"},
	{9, "ninety"},
};

// map the number of digits to the proper suffix
std::unordered_map<int, std::string> num_suffixes{
	{3, " hundred "},
	{4, " thousand "},
	{7, " million "},
	{10, " billion "},
	{13, " trillion "},
	{16, " quadrillion "}
};

// 1000 :==> one thousand
// 1'120'429 :==> 
/*
* resolve the hundreds place first, then tens, then ones
* repeat for every three digits.
* ex) 123'456'789 :==> one hundred twenty three million, four hundred fifty six thousand seven hundred eighty nine
*/
int main() {
	int input_1{ 2212145 };

	// to get hundreds place: floor(input % 1000) / 100
	std::cout << std::format("test format1: {}\n", std::to_string(input_1)); // with the string i can iterate from the end to the begin to find the words
	std::vector<std::string> output_vector{};
	auto input_string{ std::to_string(input_1) };
	int count = 0;
	int triple_count = 0;
	for (auto n = input_string.rbegin(); n != input_string.rend(); ++n) {
		auto k{ *n };
		int num{ k - '0'};
		if (count == 2) {
			count = -1;
			++triple_count;
			if (num == 0) {
				continue;
			}
			output_vector.insert(output_vector.begin(), num_suffixes.find(3)->second);
			output_vector.insert(output_vector.begin(), ones_to_words.find(num)->second);
			/*test_output += ones_to_words.find(num)->second;
			test_output += num_suffixes.find(3)->second;*/
		}
		else if (count == 1) {
			if (num == 1) {
				// replace the ones not insert
				std::string idk_man{ k , *(n - 1) };
				output_vector[0] = tens_to_words.find(std::stoi(idk_man))->second;
				//output_vector.insert(output_vector.begin(), tens_to_words.find(std::stoi(idk_man))->second);
			}
			else {
				output_vector.insert(output_vector.begin(), dec_to_words.find(num)->second);
			}
			//test_output += dec_to_words.find(num)->second;
		}
		else if (count == 0) {
			if (ones_to_words.find(num) != ones_to_words.end()) {
				//test_output += ones_to_words.find(num)->second;
				output_vector.insert(output_vector.begin(), ones_to_words.find(num)->second);
			}
		}
		++count;
		if (triple_count == 1 && count == 0) {
			output_vector.insert(output_vector.begin(), num_suffixes.find(4)->second);
		}
		else if (triple_count == 2 && count == 0) {
			output_vector.insert(output_vector.begin(), num_suffixes.find(7)->second);
		}
		if (triple_count == 4 && count == 0) {
			output_vector.insert(output_vector.begin(), num_suffixes.find(10)->second);
		}
	}

	//output_vector.insert(output_vector.begin() + 1, num_suffixes.find(in_len)->second);
	std::cout << std::format("test format helpme: {}\n", output_vector);
	
}