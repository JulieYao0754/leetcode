#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
using namespace std;

struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };


class Solution {
public:
    //  724. Find Pivot Index
    //  https://leetcode.com/problems/find-pivot-index/
    int pivotIndex(vector<int>& nums) {
        int ls = 0, rs = 0;
        for (int u: nums) rs += u;

        for (int i; i < nums.size(); i++) {
            rs -= nums[i];
            if (ls == rs) return i;
            ls += nums[i];
        } 
        return -1;  
    }

    // 747. Largest Number At Least Twice of Others
    // https://leetcode.com/problems/largest-number-at-least-twice-of-others/
    int dominantIndex(vector<int>& nums) {
        int *fl, *sl; // Init largest number and second largest number
        int size = nums.size(); 
        if (size == 0) return -1;
        if (size == 1) return 0;
        if (nums[0] > nums[1]) {
            fl = &nums[0];
            sl = &nums[1];
        }
        else {
            fl = &nums[1];
            sl = &nums[0];
        }
        for (int i = 2; i < size; i++) {
            if (nums[i] > *sl) sl = &nums[i];
            if (*sl > *fl) {
                int *tmp = fl;
                fl = sl; 
                sl = tmp;
            }
        }
        if (*fl >= 2 * *sl) {
            return fl - &nums[0];
        }
        return -1;
    }

    // 66. Plus One
    // https://leetcode.com/problems/plus-one/
    vector<int> plusOne(vector<int>& digits) {
        int tmp = digits.back();
        digits.pop_back();
        vector<int> out;
        out.push_back((tmp + 1) % 10);
        int carry = (tmp + 1) / 10;
        while (!digits.empty())
        {
            tmp = digits.back();
            out.insert(out.begin(), (tmp + carry) % 10);
            carry = (tmp + carry) / 10;
            digits.pop_back();
        }
        if (carry > 0) {
            out.insert(out.begin(), carry);
        }
        return out;
    }

    // 498. Diagonal Traverse
    // https://leetcode.com/problems/diagonal-traverse/
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        vector<int> out;

        int M = matrix.size();
        if (M == 0) return out;
        int N = matrix[0].size();
        if (N == 0) return out;

        out.resize(M * N);
        int total = M + N - 1;
        int min = std::min(M, N);
        int max = std::max(M, N);
        int start = 0;
        int cur;

        for (int i = 0; i < total; i++) {
            if (i < min) cur = i + 1;
            else if (i < max) cur = min;
            else cur = min - i + max - 1;

            if (i % 2 == 0) {
                int x = i >= M ? (M - 1) : i;
                int y = i >= M ? (i - M + 1) : 0;
                for (int j = 0; j < cur; j++) {
                    out[start+j] = matrix[x--][y++];
                }
            }
            else {
                int x = i >= N ? (i - N + 1) : 0;
                int y = i >= N ? (N - 1) : i;
                for (int j = 0; j < cur; j++) {
                    out[start+j] = matrix[x++][y--];
                }
            }
            start += cur;
        }
        return out;
    }

    // 54. Spiral Matrix
    // https://leetcode.com/problems/spiral-matrix/
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> out;
        
        int M = matrix.size();
        if (M == 0) return out;
        int N = matrix[0].size();
        if (N == 0) return out;

        int count = M * N;
        int inside = 0;
        if (M > 2 && N > 2) inside = (M - 2) * (N - 2);
        
        vector<int> visited(count, 0);     
        int x = 0;
        int y = 0;

        while (count > 0)
        {
            out.push_back(matrix[x][y]);
            visited[x * N + y] = 1;
            count--;
            if (count == inside) break;
            if (x == 0 && y < N - 1) y++;
            else if (y == N - 1 && x < M - 1) x++;
            else if (x == M - 1 && y > 0) y--;
            else if (y == 0 && x > 1) x--;
        }
        
        while (count > 0)
        {
            if (visited[x * N + y + 1] == 0 && visited[(x - 1) * N + y + 1] == 1) y++;
            else if (visited[(x + 1) * N + y] == 0 && visited[(x + 1) * N + y + 1] == 1) x++;
            else if (x < M - 1 && visited[x * N + y - 1] == 0 && visited[(x + 1) * N + y - 1] == 1) y--;
            else if (visited[(x - 1) * N + y] == 0 && visited[(x - 1) * N + y - 1] == 1) x--;
            out.push_back(matrix[x][y]);
            visited[x * N + y] = 1;
            count--;
        }
        return out;
    }

    // 118. Pascal's Triangle
    // https://leetcode.com/problems/pascals-triangle/
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> out;
        int curn = 1;
        while(numRows > 0) {
            vector<int> cur(curn, 1);
            for(int i = 1; i < curn - 1; i++) {
                cur[i] = out[curn - 2][i-1] + out[curn - 2][i];
            }
            out.push_back(cur);
            curn++;
            numRows--;
        }
        return out;
    }

    // 67. Add Binary
    // https://leetcode.com/problems/add-binary/
    string addBinary(string a, string b) {
        string out;
        int cur = 0, la = a.length() - 1, lb = b.length() - 1;
        while (la >= 0 || lb >= 0 || cur > 0) {
            if (la >= 0) {
                cur += a[la--] - '0';
            }
            if (lb >= 0) {
                cur += b[lb--] - '0';
            }
            out += (cur % 2) + '0';
            cur /= 2;
        }
        reverse(out.begin(), out.end());
        return out; 
    }

    // 28. Implement strStr()
    // https://leetcode.com/problems/implement-strstr/
    int strStr(string haystack, string needle) {
        int lh = haystack.size(), ln = needle.size(), out = -1;
        if (ln == 0) return 0;
        if (lh == 0) return -1;
        if (ln > lh) return -1;
        for (int i = 0; i <= lh - ln; i++) {
            if (haystack[i] == needle[0]) {
                for (int j = 0; j < ln; j++) {
                    if (haystack[i+j] != needle[j]) break;
                    if (j == ln - 1) out = i;
                }
            }
            if (out >= 0) break;
        }
        return out;
    }

    // 14. Longest Common Prefix
    // https://leetcode.com/problems/longest-common-prefix/
    string longestCommonPrefix(vector<string>& strs) {
         string result = "";
         int count = strs.size();
         if (count == 0) return "";
         int minlen = strs[0].size();
         for (int i = 1; i < count; i++) {
             if (strs[i].size() < minlen) minlen = strs[i].size();
         }
         char cur;
         bool diff = false;
         for (int j = 0; j < minlen; j++) {
             cur = strs[0][j];
             for (int i = 1; i < count; i++) {
                 if (cur != strs[i][j]) {
                     diff = true;
                     break;
                 }
             }
             if (diff == false) {
                 result += cur;
             }
             else break;
         }
         return result;
    }

    // 344. Reverse String
    // https://leetcode.com/problems/reverse-string/
    void reverseString(vector<char>& s) {
        char tmp;
        int max = s.size() - 1;
        for (int i = 0; i < (s.size() / 2); i++) {
            tmp = s[i];
            s[i] = s[max - i];
            s[max - i] = tmp;
        }
    }

    // 561. Array Partition I
    // https://leetcode.com/problems/array-partition-i/
    int arrayPairSum(vector<int>& nums) {
        int count = nums.size(), result = 0;
        vector<int> record(20001, 0);
        for (int i =0; i < count; i++) {
            ++record[nums[i]+10000];
        }
        bool flag = true;
        int cur = 0;
        while (count > 0) {
            if (record[cur] == 0) ++cur;
            else {
                if (flag) {
                    result += (cur - 10000);
                    flag = false;
                }
                else flag = true;
                --record[cur];
                --count;
            }
        }
        return result;
    }

    // 167. Two Sum II - Input array is sorted
    // https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
    vector<int> twoSumII(vector<int>& numbers, int target) {
        vector<int> result;
        int i = 0, j = numbers.size() - 1;
        while (numbers[i] + numbers[j] != target) {
            if (numbers[j] > target) j--;
            else if (numbers[i] + numbers[j] > target) j--;
            else i++;
        }
        result.push_back(i+1);
        result.push_back(j+1);
        return result;
    }

    // 27. Remove Element
    // https://leetcode.com/problems/remove-element/
    int removeElement(vector<int>& nums, int val) {
        int k = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[k++] = nums[i];
            }
        }
        return k;
    }

    // 485. Max Consecutive Ones
    // https://leetcode.com/problems/max-consecutive-ones/
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int output = 0;
        int k = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                output = output > (i - k - 1)? output: (i - k - 1);
                k = i;
            }
        }
        if (k != nums.size() - 1) output = output > (nums.size() - k - 1)? output: nums.size() - k - 1;
        return output;
    }

    // 209. Minimum Size Subarray Sum
    // https://leetcode.com/problems/minimum-size-subarray-sum/
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        int result = 0, cur_sum = 0, k = -1;
        for (int i = 0; i < n; i++) {
            cur_sum += nums[i];
            while (cur_sum >= s) {
                result = result > i - k || result == 0 ? i - k : result;
                cur_sum -= nums[++k];
            }
        }
        return result;
        /* Slower Solving.
        if (nums.size() == 0) return 0;
        for (int i = 0; i < nums.size(); i++) {
            cur_sum += nums[i];
            if (cur_sum >= s) {
                while (cur_sum >= s) {
                    result = result > i - k || result == 0 ? i - k : result;
                    cur_sum -= nums[++k];
                }
            }
            else if (result > 0 && result <= i - k) cur_sum -= nums[++k];
        } */
    }

    // 189. Rotate Array
    // https://leetcode.com/problems/rotate-array/
    void rotate(vector<int>& nums, int k) {
        int N = nums.size(), n = nums.size(), start = 0, mingap = k;
        k %= n;
        if (k == 0) return;
        while (true) {
            mingap = min(start + k, N);
            for (int i = start; i < mingap; i++) {
                swap(nums[i], nums[n - k + i]);
            }
            n -= k;
            start += k;
            k %= n;
            if (k == 0) break; 
        }
    }

    // 119. Pascal's Triangle II
    // https://leetcode.com/problems/pascals-triangle-ii/
    vector<int> getRow(int rowIndex) {
        vector<int> result(rowIndex+1, 0);
        result[0] = 1;
        for (int i = 1; i <= rowIndex; i++) {
            for (int j = i; j > 0; j--) {
                result[j] += result[j-1];
            }
        }
        return result;
    }

    // 151. Reverse Words in a String
    // https://leetcode.com/problems/reverse-words-in-a-string/
    string reverseWords(string s) {
        string result = "";
        int k = s.size();
        bool flag = false;
        for (int i = k - 1; i >= 0; i--) {
             if (!(s[i] - ' ')) {
                 if (flag) {
                     result.append(s.begin() + i + 1, s.begin() + k);
                     result.push_back(' ');
                     flag = false;
                 }
                 k = i;
             }
            else flag = true;
        }
        if (k > 0) result.append(s.begin(), s.begin() + k);
        else if (result.size() > 0) result.pop_back();
        return result;
    }

    // 557. Reverse Words in a String III
    // https://leetcode.com/problems/reverse-words-in-a-string-iii/
    string reverseWordsIII(string s) {
        string result = "", tmp;
        int k = -1, n = s.size();
        bool flag = false;
        for (int i = 0; i < n; i++) {
            if (!(s[i] - ' ')) {
                if (flag) {
                    tmp.assign(s.begin() + k + 1, s.begin() + i);
                    reverse(tmp.begin(), tmp.end());
                    result.append(tmp);
                    result += ' ';
                    flag = false;
                }
                k = i;
            }
            else flag = true;
        }
        if (k < n - 1) {
            tmp.assign(s.begin() + k + 1, s.end());
            reverse(tmp.begin(), tmp.end());
            result.append(tmp);
        }
        else if (result.size() > 0) result.pop_back();
        return result;      
    }

    // 26. Remove Duplicates from Sorted Array
    // https://leetcode.com/problems/remove-duplicates-from-sorted-array/
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return n;
        int result = 0, k = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i] != nums[k]) {
                nums[result++] = nums[k];
                k = i;
            }
        }
        nums[result++] = nums[k];
        return result;
    }

    // 283. Move Zeroes
    // https://leetcode.com/explore/learn/card/array-and-string/204/conclusion/1174/
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return;
        int k = -1;
        for (int i = 0; i < n; i++) {
            if (k == -1) {
                if (nums[i] == 0) k = i;
            }
            else {
                if (nums[i] != 0) swap(nums[i], nums[k++]);
            } 
        }
    }

    // 217. Contains Duplicate
    // https://leetcode.com/problems/contains-duplicate/
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> hs;
        for (int num: nums) {
            if (hs.count(num) > 0) return true;
            else hs.insert(num);
        }
        return false;
    }

    // 136. Single Number
    // https://leetcode.com/problems/single-number/
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int num: nums) result ^= num;
        return result;
    }

    // 349. Intersection of Two Arrays
    // https://leetcode.com/problems/intersection-of-two-arrays/
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        // unordered_set<int> ns(nums1.begin(), nums1.end());
        unordered_set<int> ns;
        vector<int> result;
        for(int num1: nums1) ns.insert(num1);
        for(int num2: nums2) {
            if (ns.count(num2) > 0) {
                result.emplace_back(num2);
                ns.erase(num2);
            }
        }
        return result;
    }

    // 202. Happy Number
    // https://leetcode.com/problems/happy-number/
    int replaceDigits(int n) {
        int out = 0;
        while (n) {
            out += pow(n % 10, 2);
            n /= 10;
        }
        return out;
    }
    bool isHappy(int n) {
        bool hasharray[1000] = {0};
        n = replaceDigits(n);
        while(!hasharray[n]) {
            hasharray[n] = true;
            if (n == 1) return true;
            n = replaceDigits(n);
        }
        return false;
    }

    // 1. Two Sum
    // https://leetcode.com/problems/two-sum/
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> dict;
        for (int i = 0; i < nums.size(); i++) {
            if (dict.count(target - nums[i]) > 0 && i != dict[target - nums[i]]) {
                return {i, dict[target - nums[i]]};
            }
            dict[nums[i]] = i;
        }
        return {};
    }

    // 205. Isomorphic Strings
    // https://leetcode.com/problems/isomorphic-strings/
    bool isIsomorphic(string s, string t) {
        int n = s.size();
        unordered_map<char, char> dict, revdict;
        for (int i = 0; i < n; i++) {
            if (dict.count(s[i]) > 0 && dict[s[i]] != t[i]) return false;
            if (revdict.count(t[i]) > 0 && revdict[t[i]] != s[i]) return false;
            dict[s[i]] = t[i];
            revdict[t[i]] = s[i];
        } 
        return true;
    }

    // 599. Minimum Index Sum of Two Lists
    // https://leetcode.com/problems/minimum-index-sum-of-two-lists/
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        int l1 = list1.size(), l2 = list2.size(), sum = INT32_MAX;
        unordered_map<string, int> dict;
        vector<string> max;
        for (int i = 0; i < l1; i++) dict[list1[i]] = i;
        for (int i = 0; i < l2; i++) {
            if (dict.count(list2[i]) > 0) {
                int tmp = dict[list2[i]] + i;
                if (tmp < sum) {
                    sum = tmp;
                    max = {list2[i]};
                }
                else if (tmp == sum) max.push_back(list2[i]);
            }
        }
        return max;
    }

    // 387. First Unique Character in a String
    // https://leetcode.com/problems/first-unique-character-in-a-string/
    int firstUniqChar(string s) {
        if (s == "") return -1;
        unordered_map<char, pair<int, int>> dict;
        for (int i = 0; i < s.size(); i++) {
            dict[s[i]].first = i;
            dict[s[i]].second++;
        }
        int min = INT32_MAX;
        for (auto it = dict.begin(); it != dict.end(); it++) {
            if (it->second.second == 1 && it->second.first < min) min = it -> second.first;
        }
        return min < INT32_MAX ? min : -1;
    }

    // 350. Intersection of Two Arrays II
    // https://leetcode.com/problems/intersection-of-two-arrays-ii/
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> dict;
        vector<int> result;
        for (int ele: nums1) dict[ele]++;
        for (int ele: nums2) {
            if (dict.count(ele) != 0) {
                dict[ele]--;
                if (dict[ele] == 0) dict.erase(ele);
                result.push_back(ele);
            }
        }
        return result;
    }

    // 219. Contains Duplicate II
    // https://leetcode.com/problems/contains-duplicate-ii/
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> dict;
        for (int i = 0; i < nums.size(); i++) {
            if (dict.count(nums[i]) != 0 && i - dict[nums[i]] <= k) return true;
            dict[nums[i]] = i;
        }
        return false;
    }

    // 49. Group Anagrams
    // https://leetcode.com/problems/group-anagrams/
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> out;
        for (string str: strs) out[keyofAna(str)].push_back(str);
        // for (auto it: out) result.push_back(it.second);  Slower(?)
        for (auto it = out.begin(); it != out.end(); it++) result.push_back({it->second.begin(), it->second.end()});
        return result;
    }
    string keyofAna(string word) {
        int count[26] = {0};
        string output;
        for (char c: word) count[c - 'a']++;
        for (int num: count) output += num;
        return output;
    }

    // 36. Valid Sudoku
    // https://leetcode.com/problems/valid-sudoku/
    bool isValidSudoku(vector<vector<char>>& board) {
        for (vector<char> row: board) {
            if (!keyofRow(row)) {
                cout<< "row" << endl;
                return false;
            }
        }
        for (int i = 0; i < 9; i++) {
            if (!keyofColumn(board, i)) {
                cout<< "column" << endl;
                return false;
            }
            if (!keyofBox(board, i)) {
                cout<< "box" << endl;
                return false;
            }
        }
        return true;
    }
    bool keyofRow(vector<char>& row) {
        int count[10] = {0};
        for (char num: row) {
            if (num == '.') continue;
            if (count[num - '0'] != 0) return false;
            count[num - '0'] ++;
        }
        return true;
    }
    bool keyofColumn(vector<vector<char>>& board, int& i) {
        int counts[10] = {0};
        for (int x = 0; x < 9; x++) {
            if (board[x][i] == '.') continue;
            if (counts[board[x][i] - '0'] != 0) return false;
            counts[board[x][i] - '0'] ++;
        }
        return true;
    }
    bool keyofBox(vector<vector<char>>& board, int& i) {
        int startX = i/3 * 3, startY = i%3 * 3;
        int counts[10] = {0};
        for (int count = 0; count < 9; count++) {
            if (board[startX + count/3][startY + count%3] == '.') continue;
            if (counts[board[startX + count/3][startY + count%3] - '0'] != 0) return false;
            counts[board[startX + count/3][startY + count%3] - '0'] ++;
        }
        return true;
    }

    // 652. Find Duplicate Subtrees
    // https://leetcode.com/problems/find-duplicate-subtrees/
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, vector<TreeNode*>> dict;
        vector<TreeNode*> result;
        generate_link(root, dict);
        for (auto it = dict.begin(); it != dict.end(); it++) {
            if (it -> second.size() > 1) result.push_back(it -> second[0]);
        }
        return result;
    }
    string generate_link(TreeNode*& node, unordered_map<string, vector<TreeNode*>>& dict) {
        if (!node) return "";
        string s = "(" + generate_link(node->left, dict) + to_string(node->val) + generate_link(node->right, dict) + ")";
        dict[s].push_back(node);
        return s;
    }

    // 771. Jewels and Stones
    // https://leetcode.com/problems/jewels-and-stones/
    int numJewelsInStones(string J, string S) {
        unordered_set<char> dict(begin(J), end(J));
        int result = 0;
        for (char s: S) {
            if (dict.count(s) != 0) result++;
        }
        return result;
    }

    // 3. Longest Substring Without Repeating Characters
    // https://leetcode.com/problems/longest-substring-without-repeating-characters/
    int lengthOfLongestSubstring(string s) {
        int result = 0, i = 0, k = 0;
        unordered_set<char> dict;
        while(i < s.size()) {
            if (dict.count(s[i]) > 0) { 
                result = result < (i - k) ? (i - k) : result;
                dict.erase(s[k++]);
            }
            else {
                dict.insert(s[i]);
                i++;
            }
        }
        return result < (i - k) ? (i - k) : result; 
    }

    // 454. 4Sum II
    // https://leetcode.com/problems/4sum-ii/
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        unordered_map<int, int> absum;
        int result = 0;
        for (int a: A) {
            for (int b: B) ++absum[a+b];
        }
        for (int c: C) {
            for (int d: D) {
                if (absum.count(0 - c - d) > 0) result += absum[0 - c - d];
            }
        }
        return result;
    }

    // 347. Top K Frequent Elements
    // https://leetcode.com/problems/top-k-frequent-elements/
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> dict;
        unordered_map<int, vector<int>> revdict;
        vector<int> result;
        for (int num: nums) dict[num]++;
        for (auto it = dict.begin(); it != dict.end(); it++) revdict[it->second].push_back(it->first);
        for (int i = nums.size(); i > 0; i--) {
            if (revdict.count(i) != 0) {
                result.insert(result.end(), revdict[i].begin(), revdict[i].end());
                k -= revdict[i].size();
            }
            if (k == 0) break;
        }
        return result;
    }

    // 144. Binary Tree Preorder Traversal
    // https://leetcode.com/problems/binary-tree-preorder-traversal/
    // Recursion
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == NULL) return {};
        vector<int> result = {root -> val};
        
        vector<int> left = preorderTraversal(root -> left);
        result.insert(result.end(), left.begin(), left.end());

        vector<int> right = preorderTraversal(root -> right);
        result.insert(result.end(), right.begin(), right.end());

        return result;
    }
    // Iteration
    vector<int> preorderTraversalIter(TreeNode* root) {
        if (root == NULL) return {};
        vector<int> result;
        stack<TreeNode *> node_stack;
        node_stack.push(root);
        while (!node_stack.empty()) {
            root = node_stack.top();
            result.push_back(root -> val);
            node_stack.pop();
            if (root -> right != NULL) node_stack.push(root -> right);
            if (root -> left != NULL) node_stack.push(root -> left); 
        }
        return result;
    }

    // 94. Binary Tree Inorder Traversal
    // https://leetcode.com/problems/binary-tree-inorder-traversal/
    // Recursion
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == NULL) return {};
        vector<int> result;
        
        vector<int> left = inorderTraversal(root -> left);
        result.insert(result.end(), left.begin(), left.end());

        result.push_back(root -> val);

        vector<int> right = inorderTraversal(root -> right);
        result.insert(result.end(), right.begin(), right.end());

        return result;
    }
    // Iteration
    vector<int> inorderTraversalIter(TreeNode* root) {
        if (root == NULL) return {};
        stack<TreeNode*> undone;
        vector<int> result;
        while(1) {
            while (root) {
                undone.push(root);
                root = root -> left;
            }
            if(undone.empty()) break;
            root = undone.top();
            undone.pop();
            result.emplace_back(root -> val);
            root = root -> right;
        }
        return result;
    }

    // 145. Binary Tree Postorder Traversal
    // https://leetcode.com/problems/binary-tree-postorder-traversal/
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == NULL) return {};
        vector<int> result;
        vector<int> left = postorderTraversal(root -> left);
        result.insert(result.end(), left.begin(), left.end());
        
        vector<int> right = postorderTraversal(root -> right);
        result.insert(result.end(), right.begin(), right.end());

        result.push_back(root -> val);

        return result;
    }
    // Iteration
    vector<int> postorderTraversalIter(TreeNode* root) {
        stack<TreeNode*> candidates;
        vector<int> result;
        TreeNode* last = NULL;
        while(1) {
            while(root) {
                candidates.push(root);
                root = root -> left;
            }

            if (candidates.empty()) break;
            TreeNode* cur = candidates.top();
            if (cur -> right && last != cur -> right) root = cur -> right;
            else{
                result.push_back(cur -> val);
                last = cur;
                candidates.pop();
            }
        }
        return result;
    }
};

// 705. Design HashSet
// https://leetcode.com/problems/design-hashset/
class MyHashSet {
private:
    int hasharray[1000001];

public:
    /** Initialize your data structure here. */
    MyHashSet() {
        
    }
    
    void add(int key) {;
        hasharray[key] = 1;
    }
    
    void remove(int key) {
        hasharray[key] = 0;
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        if (hasharray[key] == 1) return true;
        return false;
    }
};

// 706. Design HashMap
// https://leetcode.com/problems/design-hashmap/
class MyHashMap {
private:
    int hasharray[1000001];
public:
    /** Initialize your data structure here. */
    MyHashMap() {
        for (int i = 0; i < 1000001; i++) hasharray[i] = -1;
    }
    
    /** value will always be non-negative. */
    void put(int key, int value) {
        hasharray[key] = value;
    }
    
    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        return hasharray[key];
    }
    
    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        hasharray[key] = -1;
    }
};

// 380. Insert Delete GetRandom O(1)
// https://leetcode.com/problems/insert-delete-getrandom-o1/
class RandomizedSet {
private:
    unordered_set<int> randomized;
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (randomized.count(val) != 0) return false;
        randomized.insert(val);
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (randomized.count(val) != 0) {
            randomized.erase(val);
            return true;
        }
        return false;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        if (randomized.size() == 1) return *randomized.begin();
        int random = rand() % randomized.size();
        // This method is a bit slow, a faster way is to 
        // use a vector storing the values and a map with the pair of value and position in vector.
        return *next(randomized.begin(), random);
    }
};


class RandomClick {
public:
    // 1093. Statistics from a Large Sample
    // https://leetcode.com/problems/statistics-from-a-large-sample/
    vector<double> sampleStats(vector<int>& count) {
        vector<double> result(5);
        bool minflag = false, maxflag = false;
        int counts = 0;
        for (int i = 0; i < 256; i++) {
            if (!minflag && count[i] > 0) {
                result[0] = i;  // minimum
                minflag = true;
            }
            counts += count[i];
            result[2] += i * count[i];  // mean
            if (count[i] > count[result[4]]) result[4] = i; // mode
        }
        result[2] /= counts;
        int j = 0, k = 255, lc = count[j], rc = count[k];
        while (j < k) {
            if (!maxflag && count[k] > 0) {
                result[1] = k;  // maximum
                maxflag = true;
            }
            if (lc + rc == counts) break;
            if (lc > rc) {
                k--;
                rc += count[k];
            }
            else {
                j++;
                lc += count[j];
            }
        }
        if (lc == rc) result[3] = (j + k) / 2.0;
        else if (lc > rc) result[3] = j;
        else result[3] = k;
        return result;
    }

    // 1160. Find Words That Can Be Formed by Characters
    // https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/
    int countCharacters(vector<string>& words, string chars) {
        // Use a vector<int> dict[26] directly.
        unordered_map<char, int> dict;
        for (char c: chars) {
            if (dict.count(c) == 0) dict[c] = 0;
            dict[c]++;
        }

        int result = 0;
        for (string word: words) {
            unordered_map<char, int> dict_copy(dict);
            bool flag = true;
            for (char c: word) {
                if (dict_copy.count(c) == 0) {
                    flag = false;
                    break;
                }
                else if (dict_copy[c] == 0) {
                        flag = false;
                        break;
                    }
                    else dict_copy[c]--;
            }
            if (flag) result += word.size();
        }
        return result;
    }

    // 1161. Maximum Level Sum of a Binary Tree
    // https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/
    int maxLevelSum(TreeNode* root) {
        int idx = 0, result = 1, max = root -> val;
        vector<TreeNode*> line = {root};
        while(!line.empty()) {
            idx++;
            vector<TreeNode*> next_line;
            int cur_sum = 0;
            for (TreeNode* node: line) {
                cur_sum += node -> val;
                if (node -> left) next_line.emplace_back(node -> left);
                if (node -> right) next_line.emplace_back(node -> right);
            }
            if (cur_sum > max) {
                max = cur_sum;
                result = idx;
            }
            line = next_line;
        }
        return result;
    }
};

int main() {
    RandomClick Sol;
    TreeNode node1(7);
    TreeNode node2(-8);
    TreeNode node3(7);
    TreeNode node4(0);
    TreeNode root(1);
    root.left = &node3;
    root.right = &node4;
    node3.left = &node1;
    node3.right = &node2;
    int out = Sol.maxLevelSum(&root);
    cout << out << endl;
}