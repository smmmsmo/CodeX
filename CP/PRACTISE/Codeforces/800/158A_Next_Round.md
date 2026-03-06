```

✍️ Author            :    Mostofa Morshed Sayeem
🌐 Profile           :    https://github.com/smmmsmo
📅 Date              :    Sat May 31 2025

🌐 Credits/Links     :    https://codeforces.com/problemset/problem/158/A

```

# 📃 158A_Next Round
---
## ❓ Question / Description

"Contestant who earns a score equal to or greater than the k-th place finisher's score will advance to the next round, as long as the contestant earns a positive score..." — an excerpt from contest rules.

A total of n participants took part in the contest (n ≥ k), and you already know their scores. Calculate how many participants will advance to the next round.

**Input**  
The first line of the input contains two integers n and k (1 ≤ k ≤ n ≤ 50) separated by a single space.

The second line contains n space-separated integers a1, a2, ..., an (0 ≤ ai ≤ 100), where ai is the score earned by the participant who got the i-th place. The given sequence is non-increasing (that is, for all i from 1 to n - 1 the following condition is fulfilled: ai ≥ ai + 1).


**Output**  
Output the number of participants who advance to the next round.



| Sample Input    | Sample Output |
|:----------------|:--------------|
| 8 5 <br> 10  9  8  7  7  7  5  5  | <br> 6        |
| 4 2 <br> 0 0 0 0                  | <br> 0        |

---

## 🎀 C Code 🎀


```c
#include <stdio.h>

int main() {
    int n, k;
    int arr[105];
    int arr2[105];
    int count = 0;

    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int j = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= arr[k - 1]) {
            if (arr[i] > 0) {
                arr2[j] = arr[i];
                j++;
                count++;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}

```


| Program Input | Program Output |
|:--------------|:---------------|
|   z           |   z            |

---

## 🎀 C++ Code 🎀



```C++

zzz

```


| Program Input | Program Output |
|:--------------|:---------------|
|   z           |   z            |

---

## 🎀 Java Code 🎀



```java

zzz

```


| Program Input | Program Output |
|:--------------|:---------------|
|   z           |   z            |