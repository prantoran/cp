// https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations

use std::collections::VecDeque;

impl Solution {
    pub fn count_non_decreasing_subarrays(nums: Vec<i32>, k: i32) -> i64 {
        let mut K = k as i64;
        let mut a = nums;
        a.reverse();
        
        let mut res = 0i64;
        let mut deque: VecDeque<usize> = VecDeque::new();
        let mut i = 0i32;

        for j in 0..a.len() {
            while let Some(&back) = deque.back() {
                if a[back] < a[j] {
                    let r = deque.pop_back().unwrap();
                    let l = if deque.is_empty() { i - 1 } 
                        else { *deque.back().unwrap() as i32 };
                    K -= ((r as i64 - l as i64) * (a[j] as i64 - a[r] as i64));
                } else {
                    break;
                }
            }

            deque.push_back(j);

            while K < 0 {
                let mut p = *deque.front().unwrap(); 
                K += (a[p] - a[i as usize]) as i64;
                if *deque.front().unwrap() == i as usize {
                    deque.pop_front();
                }
                i += 1;
            }
            res += (j as i32 - i + 1) as i64;
        }

        res
    }
}
