```

✍️ Author            :    Mostofa Morshed Sayeem
🌐 Profile           :    https://github.com/smmmsmo
📅 Date              :    Sat Jun 14 2025

🌐 Credits/Links     :    

```

# 📃 Petya and Strings
---
## ❓ Question / Description

zzz

**Input**  
zzz

**Output**  
zzz



| Sample Input | Sample Output |
|:-------------|:--------------|
| z            | z             |

---

## 🎀 C Code 🎀


```c
#include <stdio.h>
#include <string.h>

int main() {
    char str1[105];
    char str2[105];
    scanf("%s %s", str1, str2);

    // Convert uppercase to lowercase
    void ToLower(char* str) {
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] >= 'A' && str[i] <= 'Z') {
                str[i] += 32; 
            }
        }
    }
    ToLower(str1);
    ToLower(str2);

    int result = strcmp(str1, str2);

    if (result < 0) {
        printf("-1\n");
    } else if (result > 0) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;
}

```


| Program Input | Program Output |
|:--------------|:---------------|
| z             | z              |

---

## 🎀 C++ Code 🎀



```C++

zzz

```


| Program Input | Program Output |
|:--------------|:---------------|
| z             | z              |

---

## 🎀 Java Code 🎀



```java

zzz

```


| Program Input | Program Output |
|:--------------|:---------------|
| z             | z              |