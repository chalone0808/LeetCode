// LeetCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

#include <Windows.h>
#include <sql.h>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
	
};

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target);		// 001 Two Sum (Using Vector)
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);	// 002 Add Two Numbers (Using Link List)
	int lengthOfLongestSubstring(string s);					// 003 Longest Substring Without Repeating Characters

	string convert(string s, int numRows);					// 006 ZigZag Conversion
	int reverse(int x);										// 007 Reverse Integer
	int myAtoi(string str);									// 008 String to Integer
	bool isPalindrome(int x);								// 009 Palindrome Number
	bool isMatch(string s, string p);						// 010 Regular Expression Matching
	int maxArea(vector<int>& height);						// 011 Container With Most Water
	string intToRoman(int num);								// 012 Integer to Roman
	int romanToInt(string s);								// 013 Roman to Integer
};

// 001 Two Sum (Using Vector)
vector<int> Solution::twoSum(vector<int>& nums, int target) {
	vector<int> res;
	for (vector<int>::iterator i = nums.begin(); i != nums.end() - 1; ++i) {
		vector<int>::iterator j = find(nums.begin(), i, target - *i);
		if ((j - nums.begin()) == nums.size()) {
			j = find(i, nums.end(), target - *i);
		}
		res.push_back(i - nums.begin());
		res.push_back(j - nums.begin());
	}
	return res;
}

// 002 Add Two Numbers (Using Link List)
ListNode* Solution::addTwoNumbers(ListNode* l1, ListNode* l2) {
	// 给结果分配内存空间
	ListNode* res = new ListNode(0);
	// 创建l1, l2 和 结果的 指针
	ListNode* p = l1;
	ListNode* q = l2;
	ListNode* curr = res;
	// 进位符号
	int carry = 0;

	while (p != NULL || q != NULL) {
		int x = (p != NULL) ? p->val : 0;
		int y = (q != NULL) ? q->val : 0;
		int sum = carry + x + y;
		carry = sum / 10;
		curr->next = new ListNode(sum % 10);
		curr = curr->next;
		if (p != NULL) p = p->next;
		if (q != NULL) q = q->next;
	}
	if (carry > 0) {
		curr->next = new ListNode(carry);
	}
	return res->next;
}

// 003 Longest Substring Without Repeating Characters
int Solution::lengthOfLongestSubstring(string s) {

	int m[256] = { 0 }, res = 0, left = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (m[s[i]] == 0 || m[s[i]] < left) {
			res = max(res, i - left + 1);
		}
		else {
			left = m[s[i]];
		}
		m[s[i]] = i + 1;
	}
	return res;
}

// 006 ZigZag Conversion
string Solution::convert(string s, int numRows) {
	// Initiate a 2D vector
	vector<vector<char>> t;
	for (int i = 0; i < numRows; ++i) {
		vector<char> v;
		t.push_back(v);
	}
	int down = 1;
	int p = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (down == 1) {
			t[p++].push_back(s[i]);
			if (p == numRows) {
				p--;
				down = 0;
				continue;
			}
		}
		if (down == 0) {
			t[p--].push_back(s[i]);
			if (p == -1) {
				p++;
				p++;
				down = 1;
				continue;
			}
		}
	}
	string res;
	for (int i = 0; i < numRows; ++i) {
		for (auto &x : t[i]) {
			res += x;
		}
	}
	return res;
}

// 007 Reverse Integer
int Solution::reverse(int x) {
	int res = 0;
	while (x != 0) {
		int t = res * 10 + x % 10;
		if (t / 10 != res) return 0;
		res = t;
		x /= 10;
	}
	return res;
	/*if ((x > 0 && (x + 1) < 0) || (x < 0 && (x - 1) > 0)) return 0;
	int sign = 0;
	if (x < 0) {
		sign = 1;
		x = -x;
	}
	deque<int> d;
	while (x) {
		d.push_back(x % 10);
		x /= 10;
	}
	int zero = 1;
	for (auto& i : d) {
		if (zero && i == 0) {
			d.pop_front();
			zero = 0;
		}
		if (d[0] != 0) { zero = 0; }
	}
	for (auto& i : d) cout << i << endl;
	int index = 1;
	long long res = 0;
	for (auto& i : d) {
		res += i * pow(10, d.size() - index++);
	}
	if (res > INT_MAX) return 0;
	if (sign) return -res;
	return res;*/
}

// 008 String to Integer
int Solution::myAtoi(string str)
{
	int flag_char = 0;
	int res = 0;
	int flag_neg = 1;
	for (auto& x : str) {
		if (x == ' ' && flag_char == 0) {
			continue;
		}
		if (x == '+' && flag_char == 0) {
			flag_char = 1;
			continue;
		}
		if (x == '-' && flag_char == 0) {
			flag_char = 1;
			flag_neg = -1;
			continue;
		}
		if (x < '0' || x > '9') {
			flag_char = 1;
			return res * flag_neg;
		}
		res = res * 10 + (int)(x - '0');
		flag_char = 1;
		if ((res % 10) != (x - '0')) {
			if (flag_neg == 1) return INT_MAX;
			if (flag_neg == -1) return INT_MIN;
		}
	}
	return res * flag_neg;
}

// 009 Palindrome Number
bool Solution::isPalindrome(int x)
{
	string s = to_string(x);
	for (string::iterator head = s.begin(), tail = s.end() - 1; head <= tail; ++head, --tail) {
		if (*head != *tail) return false;
	}
	return true;
}

// 010 Regular Expression Matching
bool Solution::isMatch(string s, string p)
{
	if (p.empty()) return s.empty();
	if (p.size() > 1 && p[1] == '*') {
		// p第二个字母是'*'
		// s非空，p首为'.'或者p和s首一致，去s首，比较子串和p
		return isMatch(s, p.substr(2)) || (!s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p));
	}
	else {
		return !s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));	// p首为'.'或者p和s首一致的时候，直接去首字母，比较字串
	}
}

// 011 Container With Most Water
int Solution::maxArea(vector<int>& height)
{
	int maxarea = 0;
	for (vector<int>::iterator begin = height.begin(), end = height.end() - 1; begin < end; ) {
		int nowarea = (end - begin) * (*begin < *end ? *begin : *end);
		maxarea = maxarea < nowarea ? nowarea : maxarea;
		if (*begin <= *end) {
			++begin;
		}
		else {
			--end;
		}
	}
	return maxarea;
}

// 012 Integer to Roman
string Solution::intToRoman(int num)
{
	// input from 1 to 3999
	//					1,	5,	10,	50,	100,500,1000
	vector<char> roman{ 'I','V','X','L','C','D','M' };
	string res("");
	vector<int> val{ 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
	vector<string> str{ "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
	for (int i = 0; i < val.size(); ++i) {
		while (num >= val[i]) {
			num -= val[i];
			res += str[i];
		}
	}

	return res;
}

int main() {
	string s = "123456";
	cout << s.substr(3);
}

