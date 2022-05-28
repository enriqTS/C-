void OneLine(string &text)
{
    for (int i = 0; i < text.length(); i++)
    {
        if ((int)text[i] == 10 || (int)text[i] == 13)
        {
            text[i] = 'E';
        }
    }
    text.erase(std::remove(text.begin(), text.end(), 'E'), text.end());
}