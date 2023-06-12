#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

using namespace std;

int main()
{
	string input, output;
	getline(cin, input);
	vector<string> sentence;
	bool isFirstSentence = true;

	int lastword = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == ' ')
		{
			if (lastword != i)
			{
				sentence.push_back(input.substr(lastword, i - lastword));
			}
			
			lastword = i + 1;
		}

		if (input[i] == '.' || input[i] == '?' || input[i] == '!' || i == input.length() - 1)
		{
			if (i == input.length() - 1 && input[i] != '.' && input[i] != '?' && input[i] != '!')
			{
				sentence.push_back(input.substr(lastword, i + 1 - lastword));
			}
			else
			{
				sentence.push_back(input.substr(lastword, i - lastword));
				lastword = i;
			}
			
			auto rng = default_random_engine { random_device{}() };
			shuffle(begin(sentence), end(sentence), rng);

			for (int i = 0; i < sentence.size(); i++)
			{
				if (i == 0)
				{
					if (!isFirstSentence)
					{
						output.append(1, ' ');
					}

					output.append(sentence[i]);
				}
				else
				{
					output.append(1, ' ');
					output.append(sentence[i]);
				}
			}

			isFirstSentence = false;
			sentence.clear();
			if (input[i] == '.' || input[i] == '?' || input[i] == '!')
			{
				output.append(1, input[i]);
				lastword = i + 1;
			}
		}
	}

	cout << output << endl;
}
