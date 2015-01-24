
//
//  CloseWords.h
//  Close Words
//

#ifndef CloseWords_h
#define CloeseWords_h

#include <string>
#include <unordered_set>

class CloseWords {
public:
    static std::unordered_set<std::string> getCloseWords(std::string str) {
        std::unordered_set<std::string> words;

        std::unordered_set<std::string> w1 = getCloseWordsToMany(str);
        std::unordered_set<std::string> w2 = getCloseWordsMissing(str);
        std::unordered_set<std::string> w3 = getCloseWordsWrong(str);
        std::unordered_set<std::string> w4 = getCloseWordsSwap(str);

        words.insert(w1.begin(), w1.end());
        words.insert(w2.begin(), w2.end());
        words.insert(w3.begin(), w3.end());
        words.insert(w4.begin(), w4.end());

        return words;
    }

private:
    static std::unordered_set<std::string> getCloseWordsToMany(std::string str) {
        std::unordered_set<std::string> words;

        for (int i = 0; i < str.size(); i++) {
            std::string tmp = str;
            tmp.erase(tmp.begin() + i);
            words.insert(tmp);
        }

        return words;
    }

    static std::unordered_set<std::string> getCloseWordsMissing(std::string str) {
        std::unordered_set<std::string> words;
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz'";

        for (int i = 0; i < str.size() + 1; i++) {
            for(char c : alphabet) {
                std::string tmp = str;
                tmp.insert(tmp.begin() + i, c);
                words.insert(tmp);
            }
        }

        return words;
    }

    static std::unordered_set<std::string> getCloseWordsWrong(std::string str) {
        std::unordered_set<std::string> words;
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz'";

        for (int i = 0; i < str.size(); i++) {
            for(char c : alphabet) {
                if (str.at(i) != c) {
                    std::string tmp = str;
                    tmp.at(i) = c;
                    words.insert(tmp);
                }
            }
        }

        return words;
    }

    static std::unordered_set<std::string> getCloseWordsSwap(std::string str) {
        std::unordered_set<std::string> words;

        for (int i = 0; i < str.size() - 1; i++) {
            std::string tmp = str;

            if (str.at(i) != str.at(i + 1)) {
                char c = tmp.at(i);
                tmp.at(i) = tmp.at(i + 1);
                tmp.at(i + 1) = c;

                words.insert(tmp);
            }
        }

        return words;
    }
};

#endif
