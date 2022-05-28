class SuffixTrie
{
private:
    SuffixTrieNode root;

public:
    SuffixTrie(string txt)
    {
        for (int i = 0; i < txt.length(); i++)
            root.insertSuffix(txt.substr(i), i, txt[i]);
    }

    string search(string pat);
    string display(string pat);
};