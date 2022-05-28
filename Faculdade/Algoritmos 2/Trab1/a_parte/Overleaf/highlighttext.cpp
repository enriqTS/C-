void HighlightText(string positions, string text, int sizeWord)
{
    int numP = 0;
    positions += ",";
    int i;
    for (i = 0; i < positions.length(); i++)
    {
        if (positions[i] == ',')
        {
            numP++;
        }
    }
    int is[numP];
    int j = 0;

    string aux = "";
    for (int i = 0; i < positions.length(); i++)
    {
        if (positions[i] == ',')
        {
            is[j] = stoi(aux);
            aux = "";
            j++;
        }
        else
        {
            aux += positions[i];
        }
    }

    j = 0;

    for (i = 0; i < text.length(); i++)
    {
        if (is[j] != i)
        {
            cout << text[i];
        }
        else
        {
            printf("\033[31m");
            for (int k = 0; k < sizeWord; k++)
            {
                cout << text[i];
                i++;
            }
            printf("\033[0m");
            if (is[j + 1] != i)
            {
                cout << text[i];
            }
            j++;
        }
    }
    cout << endl;
}