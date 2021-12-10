#define DLL extern "C" __declspec(dllexport)
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <string>

#define ABS(X) ((X) < 0 ? -(X) : (X))
#define EPSILON 0.000001
using namespace std;

string possible(std::vector<double>& nums, double target) {
	int n = nums.size(), bf = 1 << n;
	vector<map<double, string>> bitfield(bf);

	for (int i = 1; i < bf; i++) {
		int msb = (int)floor(log2(i));
		if (i == (i & -i))
		{
			bitfield[i].insert(pair<double, string>(nums[msb], to_string((int)nums[msb])));
		}

		else {
			int l = 1 << msb;
			for (int j = 1; j < l; j++)
			{
				if (!(~i & j))
				{
					map<double, string> r;
					for (const auto& kv : bitfield[j]) {
						for (const auto& kv2 : bitfield[~j & i]) {
							double tempResult = kv.first + kv2.first;
							if (ABS(target - tempResult) < EPSILON)
							{
								return "(" + kv.second + ") + (" + kv2.second + ")";
							}
							r.insert(pair<double, string>(tempResult, "(" + kv.second + ")+(" + kv2.second + ")"));

							tempResult = kv.first - kv2.first;
							if (ABS(target - tempResult) < EPSILON)
							{
								return "(" + kv.second + ")-(" + kv2.second + ")";
							}
							r.insert(pair<double, string>(tempResult, "(" + kv.second + ")-(" + kv2.second + ")"));

							tempResult = kv2.first - kv.first;
							if (ABS(target - tempResult) < EPSILON)
							{
								return "(" + kv2.second + ")-(" + kv.second + ")";
							}
							r.insert(pair<double, string>(tempResult, "(" + kv2.second + ")-(" + kv.second + ")"));

							tempResult = kv.first * kv2.first;
							if (ABS(target - tempResult) < EPSILON)
							{
								return "(" + kv.second + ")*(" + kv2.second + ")";
							}
							r.insert(pair<double, string>(tempResult, "(" + kv.second + ")*(" + kv2.second + ")"));

							if (kv2.first != 0)
							{
								tempResult = kv.first / kv2.first;
								if (ABS(target - tempResult) < EPSILON)
								{
									return "(" + kv.second + ")/(" + kv2.second + ")";
								}
								r.insert(pair<double, string>(tempResult, "(" + kv.second + ")/(" + kv2.second + ")"));
							}

							if (kv.first != 0)
							{
								tempResult = kv2.first / kv.first;
								if (ABS(target - tempResult) < EPSILON)
								{
									return "(" + kv2.second + ")/(" + kv.second + ")";
								}
								r.insert(pair<double, string>(tempResult, "(" + kv2.second + ")/(" + kv.second + ")"));
							}

							bitfield[i] = r;
						}
					}
				}
			}
		}
	}
	return "no";

backtrack:
	return "success";
}


string equationFormat(const std::string& str)
{
	//r->Remove
	//s->Stay
	string resultStr = str;
	string checkStr = str;
	while (checkStr.find("(") != string::npos)
	{
		int a = checkStr.find_last_of("(");
		int b = (checkStr.substr(a + 1, checkStr.length() - a)).find(")") + a + 1;
		//cout << endl << checkStr << endl;
		//cout << "a : " << a << "  b : " << b << endl;
		//cout << checkStr.substr(a + 1, b - a - 1) << endl;
		if (b - a == 2)
		{
			resultStr.replace(a, 1, "r");
			resultStr.replace(b, 1, "r");
			string t(b - a + 1, '0');
			checkStr.replace(a, b - a + 1, t);
		}
		else
		{
			char d = '-';
			char c = '+';
			if (a != 0)
			{
				c = checkStr.at(a - 1);
			}
			if (b != checkStr.length() - 1)
			{
				d = checkStr.at(b + 1);
			}

			if (c == '+' && (d == '+' || d == '-'))
			{
				resultStr.replace(a, 1, "r");
				resultStr.replace(b, 1, "r");
				string t(b - a + 1, '0');
				checkStr.replace(a, b - a + 1, t);
			}
			else
			{
				string in = checkStr.substr(a + 1, b - a - 1);
				if (in.find("+") == string::npos && in.find("-") == string::npos)
				{
					resultStr.replace(a, 1, "r");
					resultStr.replace(b, 1, "r");
				}
				string t(b - a + 1, '0');
				checkStr.replace(a, b - a + 1, t);
			}
		}
	}

	int pos = 0;
	while ((pos = resultStr.find("r")) != string::npos)
	{
		resultStr.erase(pos, 1);
	}
	return resultStr;
}


DLL string guessAI(string listN, double guess)
{
	vector<double> dest ;
	while (listN.find(" ") != string::npos)
	{
		int t = listN.find(" ");
		dest.push_back(stof(listN.substr(0, t)));
		listN = listN.erase(0, t+1);
	}
	return equationFormat(possible(dest, guess));
}


