void RemoveTextSigns(string &text)
{
    for (int i = 0; i < text.length(); i++)
    {
        if (ispunct(text[i]))
            text[i] = ' ';
    }
}