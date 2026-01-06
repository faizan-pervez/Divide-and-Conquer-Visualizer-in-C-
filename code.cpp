#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <string>
using namespace std;

int g_maxPrintDepth = 12;
int g_stepLimitSize = 25;
int g_seed = 0;
int g_quickPivotMode = 1;

// ======== Merge Sort Variables ============
long long mergeTreeCalls = 0;
long long mergeSortCalls = 0;
long long mergeComparisons = 0;
int maxMergeDepth = 0;

// ======== Quick Sort Variables =============
long long quickTreeCalls = 0;
long long quickSortCalls = 0;
long long quickComparisons = 0;
int maxQuickDepth = 0;

// ======== Binary Search Variable ============
long long bsTreeCalls = 0;
int maxBSDdepth = 0;

void header();
void menu();
void clearScreen();
void mergeSort();
void quickSort();
void binarySearch();
int inputCheck(const string &prompt, int low, int high);
bool readYesNo(const string &prompt);
vector<int> generateData(int n, int datatype);
void printArray(const vector<int> &a);
void mergeSortTree(int l, int r, int depth);
void indent(int depth);
bool YesNo(const string &prompt, bool defVal);
void mergeSortActual(vector<int> &a, int l, int r, int depth, bool showSteps);
void mergeCombine(vector<int> &a, int l, int m, int r, bool showSteps);
bool isSorted(const vector<int> &a);
void quickSortTreeSim(vector<int> a, int l, int r, int depth);
int partitionLomuto(vector<int> &a, int l, int r, bool showSteps);
void quickSortActual(vector<int> &a, int l, int r, int depth, bool showSteps);
void binarySearchTree(const vector<int> &a, int l, int r, int key, int depth);
int binarySearchIterative(const vector<int> &a, int key, int &steps);
void setColor(int color);

int main()
{
    system("cls");
    header();
    while (true)
    {
        menu();
        string option;
        cout << "Enter Your Choice: ";
        cin >> option;
        if (option == "1")
        {
            mergeSort();
            clearScreen();
            header();
        }
        else if (option == "2")
        {
            quickSort();
            clearScreen();
            header();
        }
        else if (option == "3")
        {
            binarySearch();
            clearScreen();
            header();
        }
        else if (option == "4")
        {
            break;
        }
    }
}

void header()
{
    setColor(11);
    cout << "******************************************************************" << endl;
    cout << "           DIVIDE-AND-CONQUER RECURSION TREE VISUALIZER           " << endl;
    cout << "******************************************************************" << endl;
    cout << endl;
}

void menu()
{
    setColor(10);
    cout << "1.Merge Sort" << endl;
    cout << "2.Quick Sort " << endl;
    cout << "3.Binary Search " << endl;
    cout << "4.Exit" << endl
         << endl;
}

void mergeSort()
{
    system("cls");
    header();
    setColor(12);
    cout << "----------------------------------" << endl;
    cout << "             MERGE SORT           " << endl;
    cout << "----------------------------------" << endl;
    cout << endl;

    setColor(14);
    int n = inputCheck("Enter array size n", 1, 200);
    int datatype = inputCheck("Dataset type (1=random, 2=sorted, 3=reverse, 4=nearly)", 1, 4);

    bool showTree = readYesNo("Show recursion tree?");
    bool doSort = readYesNo("Run actual merge sort?");

    vector<int> a = generateData(n, datatype);

    cout << endl
         << "Input Array: ";
    printArray(a);
    cout << endl
         << endl;

    mergeTreeCalls = 0;

    setColor(7);
    if (showTree)
    {
        cout << "----- Merge Sort Recursion Tree (depth limit " << g_maxPrintDepth << ") -----" << endl;
        mergeSortTree(0, n - 1, 0);
        cout << endl;
        cout << "Tree Calls: " << mergeTreeCalls << endl
             << endl;
    }

    if (doSort)
    {
        setColor(14);
        bool showSteps = YesNo("Show step-by-step merges? (small n recommended)", (n <= 30));
        setColor(7);
        if (showSteps && n > g_stepLimitSize)
        {
            cout << "n is large. Step-by-step OFF to prevent spam." << endl;
            showSteps = false;
        }

        mergeSortCalls = 0;
        mergeComparisons = 0;
        maxMergeDepth = 0;

        vector<int> b = a;
        mergeSortActual(b, 0, n - 1, 0, showSteps);

        cout << endl;
        cout << "Sorted Array: ";
        printArray(b);
        cout << endl;
        cout << "Sorted OK? " << (isSorted(b) ? "YES" : "NO");
        cout << endl;

        cout << "Actual mergeSort calls: " << mergeSortCalls << endl;
        cout << "Comparisons: " << mergeComparisons << endl;
        cout << "Max recursion depth: " << maxMergeDepth << endl;
        cout << endl;
        setColor(4);
        cout << "Complexity: O(n log n)" << endl;
    }
    setColor(14);
    cout << endl;
    cout << "--------------------------------------------------------------";
    cout << endl;
    setColor(5);
}

void quickSort()
{
    system("cls");
    header();
    setColor(12);
    cout << "----------------------------------" << endl;
    cout << "             QUICK SORT           " << endl;
    cout << "----------------------------------" << endl;
    cout << endl;

    setColor(14);
    int n = inputCheck("Enter array size n", 1, 200);
    int datatype = inputCheck("Dataset type (1=random, 2=sorted, 3=reverse, 4=nearly)", 1, 4);

    g_quickPivotMode = inputCheck("Pivot mode (1=last, 2=middle)", 1, 2);

    bool showTree = readYesNo("Show recursion tree?");
    bool doSort = readYesNo("Run actual merge sort?");

    vector<int> a = generateData(n, datatype);

    cout << endl
         << "Input Array: ";
    printArray(a);
    cout << endl
         << endl;

    quickTreeCalls = 0;

    setColor(7);
    if (showTree)
    {
        cout << "--- Quick Sort Recursion Tree (depth limit " << g_maxPrintDepth << ") ---" << endl;
        vector<int> copy = a;
        quickSortTreeSim(copy, 0, n - 1, 0);
        cout << endl;
        cout << "Tree Calls: " << quickTreeCalls << endl;
        cout << endl;
    }

    if (doSort)
    {
        setColor(14);
        bool showSteps = YesNo("Show step-by-step partitions? (small n recommended)", (n <= 30));
        setColor(7);
        if (showSteps && n > g_stepLimitSize)
        {
            cout << "n is large. Step-by-step OFF to prevent spam." << endl;
            showSteps = false;
        }

        quickSortCalls = 0;
        quickComparisons = 0;
        maxQuickDepth = 0;

        vector<int> b = a;
        quickSortActual(b, 0, n - 1, 0, showSteps);

        cout << endl
             << "Sorted Array: ";
        printArray(b);
        cout << endl;
        cout << "Sorted OK? " << (isSorted(b) ? "YES" : "NO") << endl;

        cout << "Actual quickSort calls: " << quickSortCalls << endl;
        cout << "Comparisons: " << quickComparisons << endl;
        cout << "Max recursion depth: " << maxQuickDepth << endl;
        cout << endl;
        setColor(4);
        cout << "Best/Average: O(n log n)" << endl;
        cout << "Worst: O(n^2)" << endl;
    }
    setColor(14);
    cout << endl;
    cout << "--------------------------------------------------------------";
    cout << endl;
    setColor(5);
}

void binarySearch()
{
    system("cls");
    header();
    setColor(12);
    cout << "----------------------------------" << endl;
    cout << "           BINARY SEARCH          " << endl;
    cout << "----------------------------------" << endl;
    cout << endl;

    setColor(14);
    int n = inputCheck("Enter array size n (sorted array will be created)", 1, 1000);

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        a[i] = i * 2;
    }

    cout << "Array sample: ";
    printArray(a);
    cout << endl;

    int key = inputCheck("Enter search key", -100000, 100000);
    bool showTree = readYesNo("Show recursion tree?");

    bsTreeCalls = 0;
    maxBSDdepth = 0;

    setColor(7);
    if (showTree)
    {
        cout << endl;
        cout << "--- Binary Search Recursion Tree (depth limit " << g_maxPrintDepth << ") ---" << endl;
        binarySearchTree(a, 0, n - 1, key, 0);
        cout << endl
             << "Tree Calls: " << bsTreeCalls << endl;
        cout << "Max recursion depth: " << maxBSDdepth << endl;
    }

    int steps = 0;
    int idx = binarySearchIterative(a, key, steps);

    cout << endl;
    setColor(9);
    cout << "--- Iterative Binary Search ---" << endl;
    if (idx == -1)
        cout << "Not Found (steps=" << steps << ")" << endl;
    else
        cout << "Found at index " << idx << " (steps=" << steps << ")" << endl;

    cout << endl;
    setColor(4);
    cout << "Complexity: O(log n)" << endl;
    cout << "Precondition: Array must be sorted." << endl;

    setColor(14);
    cout << endl;
    cout << "--------------------------------------------------------------";
    cout << endl;
    setColor(5);
}

void clearScreen()
{
    cout << endl;
    cout << "Press any key to continue...";
    getch();
    system("cls");
}

int inputCheck(const string &prompt, int low, int high)
{
    while (true)
    {
        string size;
        cout << prompt << " (" << low << "-" << high << "): ";
        cin >> size;

        int x = stoi(size);
        if (x < low || x > high)
        {
            cout << "Invalid input! Try again." << endl;
            continue;
        }
        return x;
    }
}

bool readYesNo(const string &prompt)
{
    while (true)
    {
        cout << prompt << " (y/n): ";
        string s;
        cin >> s;
        char c = (char)tolower(s[0]);
        if (c == 'y')
        {
            return true;
        }
        if (c == 'n')
        {
            return false;
        }
        cout << "Invalid. Try again." << endl;
    }
}

vector<int> generateData(int n, int datatype)
{
    vector<int> a(n);

    if (datatype == 1) // random
    {
        for (int i = 0; i < n; i++)
        {
            a[i] = rand() % (n * 10 + 10);
        }
    }
    else if (datatype == 2) // sorted
    {
        for (int i = 0; i < n; i++)
        {
            a[i] = i;
        }
    }
    else if (datatype == 3) // reverse
    {
        for (int i = 0; i < n; i++)
        {
            a[i] = n - 1 - i;
        }
    }
    else // nearly sorted
    {
        for (int i = 0; i < n; i++)
        {
            a[i] = i;
        }
        if (n >= 6)
        {
            swap(a[n / 3], a[n / 3 + 1]);
            swap(a[n / 2], a[n / 2 + 1]);
        }
    }
    return a;
}

void printArray(const vector<int> &a)
{
    cout << "[";
    for (int i = 0; i < (int)a.size(); i++)
    {
        cout << a[i];
        if (i + 1 < (int)a.size())
        {
            cout << ", ";
        }
    }
    cout << "]";
}

void indent(int depth)
{
    for (int i = 0; i < depth; i++)
    {
        cout << "   ";
    }
}

void mergeSortTree(int l, int r, int depth)
{
    mergeTreeCalls++;

    if (depth <= g_maxPrintDepth)
    {
        indent(depth);
        cout << "mergeSort (" << l << "," << r << ")\n";
    }

    if (l >= r)
    {
        return;
    }

    int m = (l + r) / 2;
    mergeSortTree(l, m, depth + 1);
    mergeSortTree(m + 1, r, depth + 1);
}

bool YesNo(const string &prompt, bool defVal)
{
    while (true)
    {
        cout << prompt << " (y/n): ";
        string s;
        cin >> s;
        cout << endl;
        if (s.empty())
        {
            return defVal;
        }
        cout << endl;
        char c = (char)tolower(s[0]);
        if (c == 'y')
        {
            return true;
        }
        if (c == 'n')
        {
            return false;
        }
        cout << "Invalid. Try again." << endl;
    }
}

void mergeSortActual(vector<int> &a, int l, int r, int depth, bool showSteps)
{
    mergeSortCalls++;
    if (depth > maxMergeDepth)
    {
        maxMergeDepth = depth;
    }

    if (l >= r)
    {
        return;
    }

    int m = (l + r) / 2;
    mergeSortActual(a, l, m, depth + 1, showSteps);
    mergeSortActual(a, m + 1, r, depth + 1, showSteps);

    mergeCombine(a, l, m, r, showSteps);
}

void mergeCombine(vector<int> &a, int l, int m, int r, bool showSteps)
{
    vector<int> temp;
    temp.reserve(r - l + 1);

    int i = l;
    int j = m + 1;

    while (i <= m && j <= r)
    {
        mergeComparisons++;
        if (a[i] <= a[j])
        {
            temp.push_back(a[i]);
            i++;
        }
        else
        {
            temp.push_back(a[j]);
            j++;
        }
    }

    while (i <= m)
    {
        temp.push_back(a[i]);
        i++;
    }

    while (j <= r)
    {
        temp.push_back(a[j]);
        j++;
    }

    for (int k = 0; k < (int)temp.size(); k++)
    {
        a[l + k] = temp[k];
    }

    if (showSteps)
    {
        cout << "Merge [" << l << "," << r << "] => ";
        printArray(a);
        cout << "\n";
    }
}

bool isSorted(const vector<int> &a)
{
    for (int i = 1; i < (int)a.size(); i++)
    {
        if (a[i - 1] > a[i])
        {
            return false;
        }
    }
    return true;
}

void quickSortTreeSim(vector<int> a, int l, int r, int depth)
{
    quickTreeCalls++;

    if (depth <= g_maxPrintDepth)
    {
        indent(depth);
        cout << "quickSort(" << l << "," << r << ")\n";
    }

    if (l >= r)
        return;

    int p = partitionLomuto(a, l, r, false);

    quickSortTreeSim(a, l, p - 1, depth + 1);
    quickSortTreeSim(a, p + 1, r, depth + 1);
}

int partitionLomuto(vector<int> &a, int l, int r, bool showSteps)
{
    int pivotIndex = r;

    if (g_quickPivotMode == 2)
    {
        pivotIndex = (l + r) / 2;
    }

    int pivotValue = a[pivotIndex];

    swap(a[pivotIndex], a[r]);

    int i = l - 1;

    for (int j = l; j < r; j++)
    {
        quickComparisons++;
        if (a[j] <= pivotValue)
        {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[r]);

    if (showSteps)
    {
        cout << "Partition [" << l << "," << r << "] pivot=" << pivotValue << " => ";
        printArray(a);
        cout << "\n";
    }
    return i + 1;
}

void quickSortActual(vector<int> &a, int l, int r, int depth, bool showSteps)
{
    quickSortCalls++;
    if (depth > maxQuickDepth)
    {
        maxQuickDepth = depth;
    }
    if (l >= r)
    {
        return;
    }
    int p = partitionLomuto(a, l, r, showSteps);
    quickSortActual(a, l, p - 1, depth + 1, showSteps);
    quickSortActual(a, p + 1, r, depth + 1, showSteps);
}

void binarySearchTree(const vector<int> &a, int l, int r, int key, int depth)
{
    bsTreeCalls++;
    if (depth > maxBSDdepth)
        maxBSDdepth = depth;

    if (depth <= g_maxPrintDepth)
    {
        indent(depth);
        cout << "BS(" << l << "," << r << ")" << endl;
    }

    if (l > r)
    {
        if (depth <= g_maxPrintDepth)
        {
            indent(depth);
            cout << "Not Found" << endl;
        }
        return;
    }

    int m = (l + r) / 2;

    if (depth <= g_maxPrintDepth)
    {
        indent(depth);
        cout << "mid=" << m << " val=" << a[m] << endl;
    }

    if (a[m] == key)
    {
        if (depth <= g_maxPrintDepth)
        {
            indent(depth);
            cout << "FOUND at index " << m << endl;
        }
        return;
    }

    if (key < a[m])
    {
        binarySearchTree(a, l, m - 1, key, depth + 1);
    }
    else
    {
        binarySearchTree(a, m + 1, r, key, depth + 1);
    }
}

int binarySearchIterative(const vector<int> &a, int key, int &steps)
{
    int l = 0;
    int r = (int)a.size() - 1;
    steps = 0;

    while (l <= r)
    {
        steps++;
        int m = (l + r) / 2;
        if (a[m] == key)
            return m;
        if (key < a[m])
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
