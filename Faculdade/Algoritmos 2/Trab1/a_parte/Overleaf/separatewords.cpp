void SepareteWords(string &text)
{
    for (int i = 0; i < text.length(); i++)
    {
        if ((text[i] == ' ' || text[i + 1] == '\n') && text[i - 1] != ',')
        {
            text[i] = ',';
        }
    }
    text += ',';
}