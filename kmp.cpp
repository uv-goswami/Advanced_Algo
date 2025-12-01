

#include <iostream>
#include <string>
#include <vector>
using namespace std;


void computeLPSArray(const string& pattern, int M, vector<int>& lps) {
    int len = 0;  
    lps[0] = 0;   
    int i = 1;    
    while (i < M) {
        if (pattern[i] == pattern[len]) {
           
            len++;
            lps[i] = len;
            i++;
        } else {
            
            if (len != 0) {
                len = lps[len - 1];
            } else {
                
                lps[i] = 0;
                i++;
            }
        }
    }
}

.
void KMPSearch(const string& text, const string& pattern) {
    int N = text.length();    
    int M = pattern.length(); 

    vector<int> lps(M);  
    computeLPSArray(pattern, M, lps);  

    int i = 0;  
    int j = 0;  
    bool found = false;  

    while (i < N) {
        if (pattern[j] == text[i]) {
           
            j++;
            i++;
        }

        if (j == M) {
           
            cout << "Pattern found at index " << i - j << endl;
            found = true;
            j = lps[j - 1];  
        } else if (i < N && pattern[j] != text[i]) {
           
            if (j != 0) {
                j = lps[j - 1];  
            } else {
                i++;  
            }
        }
    }

    if (!found) {
        cout << "Pattern not found" << endl;
    }
}

int main() {
    string text, pattern;
    
    cout << "Enter text: ";
    getline(cin, text);
    
    cout << "Enter pattern: ";
    getline(cin, pattern);
    
    KMPSearch(text, pattern);
    
    return 0;
}
