string SuffixTrie::search(string pat)
{
    list<int> *result = root.search(pat);

    string aux = "";

    if (result == NULL)
    {
        return "";
    }

    else
    {
        list<int>::iterator i;
        int patLen = pat.length();
        for (i = result->begin(); i != result->end(); ++i)
            aux += to_string(*i - patLen) + ",";
    }
    aux.pop_back();
    return aux;
}