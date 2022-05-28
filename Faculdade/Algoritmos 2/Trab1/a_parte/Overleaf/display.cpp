string SuffixTrie::display(string pat)
{
    list<int> *result = root.search(pat);

    string aux = "";

    if (result == NULL)
    {
        cout << "Palavra não encontrada"
             << endl;
        return "";
    }

    else
    {
        string aux2;
        list<int>::iterator i;
        int patLen = pat.length();
        for (i = result->begin(); i != result->end(); ++i)
        {
            aux2 = *i - patLen;
            aux += to_string(*i - patLen);
        }
    }
    aux.pop_back();
    return aux;
}