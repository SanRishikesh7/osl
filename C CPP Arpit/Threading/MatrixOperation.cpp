#include <iostream>
#include <pthread.h>
#include <bits/stdc++.h>
#include "../cpp-text-table/TextTable.h"

#define THREADS 3
using namespace std;

vector<vector<int>> matrixA;
vector<vector<int>> matrixB;
vector<vector<int>> resultAddition;
vector<vector<int>> resultSubtraction;

void *addMatrix(void *thread_id)
{
    int val = *(int *)thread_id;

    int startRow = (val * matrixA.size()) / THREADS;
    int endRow = ((val + 1) * matrixA.size()) / THREADS;
    int i, j;
    for (i = startRow; i < endRow; i++)
    {
        for (j = 0; j < matrixA[0].size(); j++)
        {
            resultAddition[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }

    pthread_exit(NULL);
}

void *subMatrix(void *thread_id)
{
    int val = *(int *)thread_id;

    int startRow = (val * matrixA.size()) / THREADS;
    int endRow = ((val + 1) * matrixA.size()) / THREADS;
    int i, j;
    for (i = startRow; i < endRow; i++)
    {
        for (j = 0; j < matrixA[0].size(); j++)
        {
            resultSubtraction[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }

    pthread_exit(NULL);
}

void printMatrix(vector<vector<int>> matrix)
{
    TextTable t('-', '|', '+');
    for (auto i : matrix)
    {
        for (auto j : i)
        {
            t.add(to_string(j));
        }
        t.endOfRow();
    }

    t.setAlignment(6, TextTable::Alignment::RIGHT);
    cout << t;
}

vector<vector<int>> takeInput(const string &filename)
{

    vector<vector<int>> tokens;
    ifstream stream(filename);
    string token;

    while (getline(stream, token))
    {
        istringstream iss(token);
        string temp;
        vector<int> temp1;

        while (getline(iss, temp, ','))
        {
            temp1.push_back(stoi(temp));
        }

        tokens.push_back(temp1);
    }

    return tokens;
}

int main()
{
    matrixA = takeInput("inputs/matrixA.txt");
    matrixB = takeInput("inputs/matrixB.txt");

    pthread_t threads[THREADS];
    int thread_ids[THREADS];

    resultAddition.resize(matrixA.size(), vector<int>(matrixA[0].size(), 0));
    resultSubtraction.resize(matrixA.size(), vector<int>(matrixA[0].size(), 0));

    for (int i = 0; i < THREADS; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, addMatrix, &thread_ids[i]);
    }

    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < THREADS; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, subMatrix, &thread_ids[i]);
    }

    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    cout << "Addition matrix is: " << endl;
    printMatrix(matrixA);

    cout << "Subtraction matrix is: " << endl;
    printMatrix(matrixB);

    cout << "Resultant Addition matrix is: " << endl;
    printMatrix(resultAddition);

    cout << "Resultant Subtraction matrix is: " << endl;
    printMatrix(resultSubtraction);
}
