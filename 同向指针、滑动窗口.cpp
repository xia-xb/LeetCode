/*
 * @Author: your name
 * @Date: 2021-06-25 21:31:42
 * @LastEditTime: 2021-06-27 23:58:01
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /LeetCode/同向指针、滑动窗口.cpp
 */

/* 27题移除元素 */
/* 双指针，让右指针指向不是val */
/* 当左指针等于val时交换 */
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.empty()) {
            return 0;
        }
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            while (left < right && nums[right] == val) {
                right--;
            }
            if (left < right && nums[left] == val) {
                swap(nums[left], nums[right]);
            }
            left++;
        }
        return nums[right] == val ? right : right + 1;
    }
};
/* 优化 */
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0, right = nums.size();
        while (left < right) {
            if (nums[left] == val) {
                nums[left] = nums[--right];
            } else {
                left++;
            }
        }
        return left;
    }
};

/* 26题删除有序数组中的重复项 */
/* 同向双指针 */
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int left = -1, right = 0;
        while (right < nums.size()) {
            if (left >= 0 && nums[right] == nums[left]) {
                right++;
            } else {
                nums[++left] = nums[right];
            }
        }
        return left + 1;
    }
};

/* 80题删除有序数组中的重复项II */
/* 同向双指针，通过map记录出现次数 */
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) {
            return nums.size();
        }
        int slow = 0, fast = 1;
        unordered_map<int, int> mp;
        mp[nums[0]]++;
        while (fast < nums.size()) {
            if (nums[fast] != nums[slow] ||
                (nums[fast] == nums[slow] && mp[nums[slow]] < 2)) {
                nums[++slow] = nums[fast];
                mp[nums[slow]]++;
            }
            fast++;
        }
        return slow + 1;
    }
};
/* 优化 */
/* 通过数组前后关系，避免使用map */
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) {
            return nums.size();
        }
        int slow = 0, fast = 1;
        while (fast < nums.size()) {
            if (nums[fast] != nums[slow] ||
                (nums[fast] == nums[slow] && slow == 0 ||
                 nums[slow] != nums[slow - 1])) {
                nums[++slow] = nums[fast];
            }
            fast++;
        }
        return slow + 1;
    }
};
/* 对上面判断逻辑进行优化 */
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) {
            return nums.size();
        }
        int slow = 2, fast = 2;
        while (fast < nums.size()) {
            if (nums[slow - 2] != nums[fast]) {
                nums[slow++] = nums[fast];
            }
            fast++;
        }
        return slow;
    }
};

/* 83题删除排序链表中的重复元素 */
/* 双指针 */
/* 注意最后尾指针的next需要指向空 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        ListNode *tail = head, *p = head;
        while (p != nullptr) {
            if (tail->val != p->val) {
                tail->next = p;
                tail = tail->next;
            }
            p = p->next;
        }
        tail->next = nullptr;
        return head;
    }
};

/* 82题删除排序链表中的重复元素II */
/* 双指针 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* newhead = new ListNode();
        ListNode *tail = newhead, *p = head, *q = head;
        while (p != nullptr) {
            q = p->next;
            if (q == nullptr || p->val != q->val) {
                tail->next = p;
                tail = tail->next;
                p = p->next;
            } else {
                while (q != nullptr && q->val == p->val) {
                    q = q->next;
                }
                p = q;
            }
        }
        tail->next = nullptr;
        return newhead->next;
    }
};

/* 611题有效的三角形的个数 */
/* 二分查找 */
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        if (nums.size() < 3) {
            return 0;
        }
        sort(nums.begin(), nums.end());
        int count = 0, n = nums.size();
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                int sum = nums[i] + nums[j];
                if (nums[j + 1] > sum) {
                    continue;
                }
                if (nums[n - 1] < sum) {
                    count += n - j - 1;
                    continue;
                }
                int left = j + 1, right = n - 1;
                while (left <= right) {
                    int mid = left + (right - left) / 2;
                    int midValue = nums[mid];
                    if (midValue == sum) {
                        right = mid - 1;
                    } else if (midValue < sum) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
                count += left - j - 1;
            }
        }
        return count;
    }
};
/* 双指针 */
/* 注意对于每个left,下一个left的right可以直接开始 */
/* 不用从left+1便利 */
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        if (nums.size() < 3) {
            return 0;
        }
        sort(nums.begin(), nums.end());
        int count = 0, n = nums.size();
        for (int i = 0; i < n - 2; i++) {
            if (nums[i] == 0) {
                continue;
            }
            int left = i + 1, right = left + 1;
            for (; left < n - 1; left++) {
                int sum = nums[i] + nums[left];
                while (right < n && sum > nums[right]) {
                    right++;
                }
                count += right - left - 1;
            }
        }
        return count;
    }
};

/* 3题无重复字符的最长字串 */
/* 滑动窗口 */
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0;
        int left = 0, right = 0;
        unordered_map<char, int> window;
        while (right < s.size()) {
            char c1 = s[right];
            window[c1]++;
            right++;

            while (window[c1] > 1) {
                window[s[left]]--;
                left++;
            }
            res = max(res, right - left);
        }
        return res;
    }
};

/* 30题串联所有单词的子串 */
/* 滑动窗口 */
/* 注意保证每个单词的个数刚好等于所要求个数 */
/* 并且以此为条件移动窗口左侧 */
/* 之后只需判断总的单词个数相等即可 */
/* 此外当出现单词不匹配时 */
/* 则重新开始，且直接从右侧开始即可 */
/* 因为左侧一定不会满足条件 */
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int wordNum = words.size(), wordsLength = words[0].size();
        unordered_map<string, int> needs;
        for (int i = 0; i < words.size(); i++) {
            needs[words[i]]++;
        }
        for (int start = 0; start < wordsLength; start++) {
            int left = start, right = start, count = 0;
            unordered_map<string, int> window;
            while (right + wordsLength <= s.size()) {
                string s1 = s.substr(right, wordsLength);
                right += wordsLength;
                if (!needs.count(s1)) {
                    left = right;
                    count = 0;
                    window.clear();
                } else {
                    window[s1]++;
                    count++;
                    while (window[s1] > needs[s1]) {
                        string s2 = s.substr(left, wordsLength);
                        if (needs.count(s2)) {
                            window[s2]--;
                            count--;
                        }
                        left += wordsLength;
                    }
                    if (count == words.size()) {
                        res.push_back(left);
                    }
                }
            }
        }
        return res;
    }
};

/* 76题最小覆盖子串 */
/* 滑动窗口 */
/* 注意后面比较子串长度时 */
/* 窗口的right在前面加1了，需要去除 */
class Solution {
public:
    string minWindow(string s, string t) {
        string res;
        unordered_map<char, int> needs;
        for (int i = 0; i < t.size(); i++) {
            needs[t[i]]++;
        }
        int left = 0, right = 0;
        unordered_map<char, int> window;
        int match = 0;
        while (right < s.size()) {
            char c1 = s[right];
            if (needs.count(c1)) {
                window[c1]++;
                if (window[c1] == needs[c1]) {
                    match++;
                }
            }
            right++;
            while (match == needs.size()) {
                if (res.empty() || right - left < res.size()) {
                    res = s.substr(left, right - left);
                }
                char c2 = s[left];
                if (needs.count(c2)) {
                    window[c2]--;
                    if (window[c2] < needs[c2]) {
                        match--;
                    }
                }
                left++;
            }
        }
        return res;
    }
};

/* 187题重复的DNA序列 */
/* 哈希表 */
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> res;
        if (s.size() < 10) {
            return res;
        }
        set<string> st;
        set<string> ans;
        for (int i = 0; i + 10 <= s.size(); i++) {
            string s1 = s.substr(i, 10);
            if (st.count(s1)) {
                if (!ans.count(s1)) {
                    res.push_back(s1);
                    ans.insert(s1);
                }
            } else {
                st.insert(s1);
            }
        }
        return res;
    }
};

/* 209题长度最小的子数组 */
/* 滑动窗口 */
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int length = 0;
        int left = 0, right = 0, sum = 0;
        while (right < nums.size()) {
            sum += nums[right++];
            while (sum >= target) {
                if (length == 0 || right - left < length) {
                    length = right - left;
                }
                sum -= nums[left++];
            }
        }
        return length;
    }
};
/* 前缀和+二分查找 */
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int length = 0;
        vector<int> sums(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            sums[i + 1] = sums[i] + nums[i];
        }
        for (int i = 1; i < sums.size(); i++) {
            int newTarget = sums[i] - target;
            int left = 1, right = i - 1;
            int position = -1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (sums[mid] == newTarget) {
                    position = mid;
                    break;
                } else if (sums[mid] < newTarget) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            position = position == -1 ? right : position;
            if (sums[position] <= newTarget) {
                if (length == 0 || i - position < length) {
                    length = i - position;
                }
            }
        }
        return length;
    }
};

/* 438题找到字符串中所有字母异位词 */
/* 滑动窗口 */
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int strLength = p.size();
        unordered_map<char, int> needs;
        for (char it : p) {
            needs[it]++;
        }
        int left = 0, right = 0;
        unordered_map<char, int> window;
        int match = 0;
        while (right < s.size()) {
            char c1 = s[right++];
            if (needs.count(c1)) {
                window[c1]++;
                if (window[c1] == needs[c1]) {
                    match++;
                }
            } else {
                left = right;
                window.clear();
                match = 0;
                continue;
            }
            while (window[c1] > needs[c1]) {
                char c2 = s[left];
                if (needs.count(c2)) {
                    if (window[c2] == needs[c2]) {
                        match--;
                    }
                    window[c2]--;
                }
                left++;
            }
            if (match == needs.size()) {
                res.push_back(left);
                match--;
                window[s[left]]--;
                left++;
            }
        }
        return res;
    }
};
/* 整理上面代码 */
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        int strLength = p.size();
        unordered_map<char, int> needs;
        for (char it : p) {
            needs[it]++;
        }
        int left = 0, right = 0;
        unordered_map<char, int> window;
        int match = 0;
        while (right < s.size()) {
            char c1 = s[right++];
            if (!needs.count(c1)) {
                left = right;
                window.clear();
                match = 0;
            } else {
                window[c1]++;
                if (window[c1] == needs[c1]) {
                    match++;
                }
                while (window[c1] > needs[c1]) {
                    char c2 = s[left++];
                    if (needs.count(c2)) {
                        if (window[c2] == needs[c2]) {
                            match--;
                        }
                        window[c2]--;
                    }
                }
                if (match == needs.size()) {
                    res.push_back(left);
                    match--;
                    window[s[left++]]--;
                }
            }
        }
        return res;
    }
};
/* 滑动窗口另一种思路 */
/* 直接固定窗口大小 */
/* 然后判断是否符合要求 */
/* 而不是改变窗口，寻找符合要求子串 */
/* 此外可以借鉴的是 */
/* 字符串只包含小写英文字母，类别有限 */
/* 可以使用数组代替哈希表，从而减少内存 */
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        if (p.size() > s.size() || s.empty()) {
            return res;
        }
        vector<int> needs(26);
        for (char it : p) {
            needs[it - 'a']++;
        }
        vector<int> window(26);
        for (int i = 0; i < p.size() - 1; i++) {
            window[s[i] - 'a']++;
        }
        int left = 0, right = p.size() - 1;
        while (right < s.size()) {
            window[s[right++] - 'a']++;
            if (window == needs) {
                res.push_back(left);
            }
            window[s[left++] - 'a']--;
        }
        return res;
    }
};