#include <iostream>

using namespace std;

const int tableSize = 9;

struct Node
{
    int table[tableSize][tableSize] = {0};
};

void showTable(int table[tableSize][tableSize])
{
    cout << "___________________________\n";
    for (int i = 0; i < tableSize; i++)
    {
        cout << "|";
        for (int j = 0; j < tableSize; j++)
        {
            cout << table[i][j] << ", ";
        }
        cout << "\b\b|\n";
    }
    cout << "---------------------------\n";
}

bool isCellValid(int row, int column, int table[][tableSize])
{

    int number = table[row][column];

    for (int i = 0; i < tableSize; i++)
    {
        if (i == row)
            continue;

        if (table[i][column] == number)
            return false;
    }

    for (int i = 0; i < tableSize; i++)
    {
        if (i == column)
            continue;

        if (table[row][i] == number)
            return false;
    }

    const int startRow = (row / 3) * 3;
    const int startcolmn = (column / 3) * 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (startRow + i == row && startcolmn + j == column)
                continue;

            if (table[startRow + i][startcolmn + j] == number)
                return false;
        }
    }
    return true;
}

void tableCopy(const int parent[][tableSize], int child[][tableSize])
{
    for (int i = 0; i < tableSize; i++)
    {
        for (size_t j = 0; j < tableSize; j++)
        {
            child[i][j] = parent[i][j];
        }
    }
}

void findTarget(int table[][tableSize], int result[])
{
    int targetRow = 0, targetColumn = 0;

    for (int i = 0; i < tableSize; i++)
    {
        for (int j = 0; j < tableSize; j++)
        {
            if (table[i][j] == 0)
            {
                result[0] = i;
                result[1] = j;

                targetRow = i;
                targetColumn = j;
                return;
            }
        }
    }
}

void dfs(Node node, int depth, int cutoff, int row, int column)
{
    if (!isCellValid(row, column, node.table))
        return;

    if (depth == cutoff)
    {
        showTable(node.table);
        return;
    }

    int target[2];
    findTarget(node.table, target);

    int targetRow = target[0], targetColumn = target[1];

    Node childs[9];

    for (int i = 0; i < 9; i++)
    {
        tableCopy(node.table, childs[i].table);
        childs[i].table[targetRow][targetColumn] = i + 1;
        dfs(childs[i], depth + 1, cutoff, targetRow, targetColumn);
    }
}

int cuttoffvalue(const int table[][tableSize])
{
    int count = 0;
    for (int i = 0; i < tableSize; i++)
    {
        for (int j = 0; j < tableSize; j++)
        {
            if (table[i][j] == 0)
                count++;
        }
    }
    return count;
}

void startDfs(Node root)
{
    int target[2];
    findTarget(root.table, target);

    int targetRow = target[0], targetColumn = target[1];

    Node childs[9];

    for (int i = 0; i < 9; i++)
    {
        tableCopy(root.table, childs[i].table);
        childs[i].table[targetRow][targetColumn] = i + 1;
        dfs(childs[i], 1, cuttoffvalue(root.table), targetRow, targetColumn);
    }
}

int main()
{
    cout << "Values =>\n";
    int table[tableSize][tableSize];
    for (int i = 0; i < tableSize; i++)
    {
        for (int j = 0; j < tableSize; j++)
        {
            cin >> table[i][j];
        }
    }

    Node root;
    tableCopy(table, root.table);

    startDfs(root);
    
    return 0;
}