void SuffixTrieNode::insertSuffix(string s, int index, char word)
{
    indexes->push_back(index);
    words->push_back(word);

    if (s.length() > 0)
    {
        char cIndex = s.at(0);
        if (children[cIndex] == NULL)
            children[cIndex] = new SuffixTrieNode();
        children[cIndex]->insertSuffix(s.substr(1), index + 1, s[word + 1]);
    }
}