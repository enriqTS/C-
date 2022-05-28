string showIndex(string text, SuffixTrie S)
{
    string aux = "";
    string indexs = "";

    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ',')
        {
            if (indexs.find(aux) >= indexs.length())
            {
                indexs += aux + ", " + S.search(aux) + "\n";
            }
            i++;
            aux = "";
        }
        if (text[i] != '\n')
        {
            aux += text[i];
        }
    }

    return indexs;
}