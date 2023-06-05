bool load(const char *dictionary)
{
    FILE *open_dictionary = fopen(dictionary,"r");
    if (open_dictionary == NULL)
    {
        return false;
    }
    char Dword[LENGTH + 1];
    while(fscanf(open_dictionary,"%s", Dword) != EOF)
    {
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            return false;
        }
        strcpy(newNode -> word, Dword);
        newNode -> next = NULL;
        int index = hash(Dword);

        if (table[index] == NULL)
        {
            table[index] = newNode;
        }
        else
        {
            newNode -> next = table[index];
            table[index] = newNode;
        }
        Count_size++;
    }