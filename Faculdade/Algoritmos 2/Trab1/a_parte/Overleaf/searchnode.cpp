list<int> *SuffixTrieNode::search(string s)
{
    if (s.length() == 0)
        return indexes;
    if (children[s.at(0)] != NULL)
        return (children[s.at(0)])->search(s.substr(1));
    else
        return NULL;
}