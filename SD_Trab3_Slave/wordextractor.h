#ifndef WORDEXTRACTOR_H
#define WORDEXTRACTOR_H
#include <string>
typedef std::string String;

class WordExtractor
{
public:
    static int getWordCount(String input, char separator);
    static String getNthWord(String input, char separator, int n);
};

#endif // WORDEXTRACTOR_H
