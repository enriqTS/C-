class SuffixTrieNode
{
private:
    SuffixTrieNode *children[MAX_CHAR];
    list<int> *indexes;
    list<char> *words;

public:
    SuffixTrieNode()
    {
        words = new list<char>;
        indexes = new list<int>;
        for (int i = 0; i < MAX_CHAR; i++)
            children[i] = NULL;
    }

    void insertSuffix(string suffix, int index, char word);
    list<int> *search(string pat);
    list<char> *display(string pat);
};