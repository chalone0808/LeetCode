#include "pch.h"
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

template <typename T> void print(const T& v) {
	for (auto& x : v) cout << x << endl;
}

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
	
};

class Solution {
public:
	/*----------------------------------------------------------                 000                 ----------------------------------------------------------*/
	vector<int> twoSum(vector<int>& nums, int target);							// 001 Two Sum (Using Vector)
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);						// 002 Add Two Numbers (Using Link List)
	int lengthOfLongestSubstring(string s);										// 003 Longest Substring Without Repeating Characters
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);		// 004 Median of Two Sorted Arrays
	string longestPalindrome(string s);											// 005 Longest Palindromic Substring
	string convert(string s, int numRows);										// 006 ZigZag Conversion
	int reverse(int x);															// 007 Reverse Integer
	int myAtoi(string str);														// 008 String to Integer
	bool isPalindrome(int x);													// 009 Palindrome Number
	/*----------------------------------------------------------                 010                 ----------------------------------------------------------*/
	bool isMatch(string s, string p);											// 010 Regular Expression Matching
	int maxArea(vector<int>& height);											// 011 Container With Most Water
	string intToRoman(int num);													// 012 Integer to Roman
	int romanToInt(string s);													// 013 Roman to Integer
	string longestCommonPrefix(vector<string>& strs);							// 014 Longest Common Prefix
	vector<vector<int>> threeSum(vector<int>& nums);							// 015 3Sum
	int threeSumClosest(vector<int>& nums, int target);							// 016 3Sum closest

	int divide(int dividend, int divisor);										// 029 Divide Two Integers

	int numJewelsInStones(string J, string S);									// 771 Jewels and Stones
	int rotatedDigits(int N);													// 788 Rotated Digits
	string customSortString(string S, string T);								// 791 Custom Sort String
};

int main() {
	Solution S;
	string s("PAYPALISHIRING");
	string::iterator i = s.end() - 1;
	cout << *i;
	
}

/*----------------------------------------------------------                 000                 ----------------------------------------------------------*/
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

// 004 Median of Two Sorted Arrays
double Solution::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
	size_t size = nums1.size() + nums2.size();
	if (size == 0) return 0.0;
	size_t mid = size / 2;
	//防止越界
	nums1.push_back(INT_MAX);
	nums2.push_back(INT_MAX);
	vector<int>::iterator n1 = nums1.begin(), n2 = nums2.begin();
	int res = 0;
	// 如下可以简化，但是为了看得清楚，不简化
	if (size % 2) {
		for (int i = 0; i <= mid; ++i) {
			if (i == mid) { 
				res = (*n1 < *n2) ? *n1 : *n2; 
				return (double)res;
			}
			(*n1 < *n2) ? ++n1 : ++n2;
		}
	}
	else {
		for (int i = 0; i <= mid; ++i) {
			if (i == mid - 1) res += (*n1 < *n2) ? *n1 : *n2;
			if (i == mid) { 
				res += (*n1 < *n2) ? *n1 : *n2; 
				return (double)res / 2;
			}
			(*n1 < *n2) ? ++n1 : ++n2;
		}
	}	
}

// 005 Longest Palindromic Substring
string Solution::longestPalindrome(string s)
{
	string::iterator a = s.begin(), b = s.end();

	return string();
}

// 006 ZigZag Conversion
string Solution::convert(string s, int numRows) {
	if (numRows >= s.size() || numRows == 1) return s;
	string res;

	// initiate a 2-d vector with the first element in it
	vector<vector<char>> t;
	for (int i = 0; i < numRows; ++i) {
		vector<char> v = { s[i] };
		t.push_back(v);
	}

	/** the sorting goes like:
	 * 1,2,...,numRows,numRows-1,...1,2,...,numRows.......
	 */
	int going_up = 1;
	int nowRow = numRows - 1;
	for (int i = numRows; i < s.size(); ++i) {
		if (going_up) {
			t[--nowRow].push_back(s[i]);
			if (nowRow == 0) { 
				going_up = 0; 
				continue;
			}
		}
		if (!going_up) {
			t[++nowRow].push_back(s[i]);
			if (nowRow == numRows - 1) {
				going_up = 1;
				continue;
			}
		}
	}
	for (auto& x : t) {
		for (auto& y : x) {
			cout << y;
		}
		cout << endl;
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

/*----------------------------------------------------------                 010                 ----------------------------------------------------------*/
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

// 013 Roman to Integer
int Solution::romanToInt(string s)
{
	unordered_map<char, int> T = {	{'I',1},	
									{'V',5}, 
									{'X',10},
									{'L',50},
									{'C',100},
									{'D',500},
									{'M',1000} };
	int sum = T[s.back()];
	for (int i = s.length() - 2; i >= 0; i--) {
		if (T[s[i]] < T[s[i + 1]]) sum -= T[s[i]];
		else sum += T[s[i]];
	}
	return sum;
}

// 014 Longest Common Prefix
string Solution::longestCommonPrefix(vector<string>& strs)
{
	if (strs.size() == 0) return "";
	string prefix = strs[0];
	for (int i = 1; i < strs.size(); ++i) {
		if (prefix.size() == 0) return "";
		int len = prefix.size() < strs[i].size() ? prefix.size() : strs[i].size();
		// 先做一个长度的截断
		prefix = prefix.substr(0, len);
		for (int k = 0; k < len; ++k) {
			if (prefix[k] != strs[i][k]) prefix = prefix.substr(0, k);
		}
	}
	return prefix;
}

// 015 3Sum
vector<vector<int>> Solution::threeSum(vector<int>& nums)
{
	vector<vector<int>> res;
	sort(nums.begin(), nums.end());
	for (int k = 0; k < nums.size(); ++k) {
		if (nums[k] > 0) break;
		// skip duplicated first number
		if (k > 0 && nums[k] == nums[k - 1]) continue;
		int target = 0 - nums[k];
		int i = k + 1, j = nums.size() - 1;
		while (i < j)
		{
			// Found Target
			if (nums[i] + nums[j] == target) {
				res.push_back({ nums[k],nums[i],nums[j] });
				// Skip duplicated elements
				while (i < j && nums[i] == nums[i + 1]) ++i;
				while (i < j && nums[j] == nums[j - 1]) --j;
				// thank u, next
				++i; --j;
			}
			// number on the left is too small
			else if (nums[i] + nums[j] < target) {
				++i;				
			}
			// number on the right is too large
			else {
				--j;
			}
		}
	}
	return res;
}

// 016 3Sum closest
int Solution::threeSumClosest(vector<int>& nums, int target)
{
	int res = 0;
	if (nums.size() == 3) {
		for (auto&x : nums) res += x;
		return res;
	}

	for (auto& x : nums) {
		x -= target;
	}
	sort(nums.begin(), nums.end());
	// compare with zero
	for (int i = 0; i < nums.size() - 2; ++i) {

	}
	return 0;
}

/*----------------------------------------------------------                 020                 ----------------------------------------------------------*/
// 029 Divide Two Integers
int Solution::divide(int dividend, int divisor)
{
	int flag = 0;
	if (dividend < 0 && divisor < 0) { dividend = -dividend; divisor = -divisor; }
	if (dividend < 0 && divisor > 0) { flag = 1; dividend = -dividend; }
	if (dividend > 0 && divisor < 0) { flag = 1; divisor = -divisor; }
	return 0;
}

// 771 Jewels and Stones
int Solution::numJewelsInStones(string J, string S)
{
	int Sint[256] = { 0 };
	for (int i = 0; i < S.size(); ++i) {
		Sint[S[i]] += 1;
	}
	int res = 0;
	for (int i = 0; i < J.size(); ++i) {
		res += Sint[J[i]];
	}
	return res;
}

// 788 Rotated Digits
int Solution::rotatedDigits(int N)
{
	int n[5], times = 0;
	int flag = 0;
	for (int i = 0; i <= N; ++i) {
		flag = 0;
		int temp = i, sep[5];
		for (int j = 0; j < 5; ++j) {
			int judge = temp % 10;
			if (judge == 3 || judge == 4 || judge == 7) {
				flag = 1;
				break;
			}
			switch (judge)
			{
			case 0: sep[5 - j - 1] = 0; break;
			case 1: sep[5 - j - 1] = 1; break;
			case 2: sep[5 - j - 1] = 5; break;
			case 5: sep[5 - j - 1] = 2; break;
			case 6: sep[5 - j - 1] = 9; break;
			case 8: sep[5 - j - 1] = 8; break;
			case 9: sep[5 - j - 1] = 6; break;
			}
			temp /= 10;
		}
		if (flag == 1) continue;
		int comp = 10000 * sep[0] + 1000 * sep[1] + 100 * sep[2] + 10 * sep[3] + sep[4];
		if (comp != i) times++;
	}
	return times;
}

// 791 Custom Sort String
string Solution::customSortString(string S, string T)
{
	int t[26] = { 0 }, s[26] = { 0 };
	for (auto&x : S) s[x - 'a']++;
	for (auto& x : T) {
		if (s[x - 'a']) t[x - 'a']++;
	}
	string res;
	for (auto& x : S) {
		if (!t[x - 'a']) continue;
		int times = t[x - 'a'];
		while (times) {
			res += x;
			times--;
		}
	}
	for (auto&x : T) {
		if (t[x - 'a'] == 0) res += x;
	}
	return res;
}



