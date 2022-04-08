#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

struct NodeTree {
    int key;
    NodeTree *Left;
    NodeTree *Right;
};

struct Tree {
    NodeTree *Top;
};


void CreateTree(Tree &t) {
    t.Top = nullptr;
}

bool FindNode(Tree &t, int k) {
    NodeTree *current;
    current = t.Top;
    while (current != nullptr) {
        if (k == current->key) {
            return true;
        }
        if (k < current->key) {
            current = current->Left;
            continue;
        }
        if (k > current->key) {
            current = current->Right;
        }
    }
    return false;
}

void AddNode(Tree &t, int k) {
    if (FindNode(t, k)) {
        return;
    }
    NodeTree *node;
    node = new NodeTree;
    node->Left = nullptr;
    node->Right = nullptr;
    node->key = k;
    if (t.Top == nullptr) {
        t.Top = node;
    } else {
        NodeTree *current;
        current = t.Top;
        NodeTree *prev;
        prev = nullptr;
        while (current != nullptr) {
            prev = current;
            if (k < current->key) {
                current = current->Left;
                continue;
            }
            if (k > current->key) {
                current = current->Right;
            }
        }
        if ((prev != nullptr) && (k < prev->key)) {
            prev->Left = node;
        }
        if ((prev != nullptr) && (k > prev->key)) {
            prev->Right = node;
        }
    }
}


void DeleteNode(Tree &t, int k) {
    NodeTree *current;
    current = t.Top;
    NodeTree *prev;
    prev = nullptr;
    while ((current != nullptr) && (current->key != k)) {
        prev = current;
        if (k < current->key) {
            current = current->Left;
            continue;
        }
        if (k > current->key) {
            current = current->Right;
        }
    }
    if (current == nullptr) {
        return;
    }
    if ((current->Left == nullptr) && (current->Right == nullptr)) {
        if (k == t.Top->key) {
            t.Top = nullptr;
        }
        delete current;
        if ((prev != nullptr) && (k < prev->key)) {
            prev->Left = nullptr;
        }
        if ((prev != nullptr) && (k > prev->key)) {
            prev->Right = nullptr;
        }
        return;
    }
    if ((current->Left != nullptr) && (current->Right == nullptr)) {
        if (k == t.Top->key) {
            t.Top = current->Left;
        }
        if ((prev != nullptr) && (k < prev->key)) {
            prev->Left = current->Left;
        }
        if ((prev != nullptr) && (k > prev->key)) {
            prev->Right = current->Left;
        }
        delete current;
        return;
    }
    if ((current->Left == nullptr) && (current->Right != nullptr)) {
        if (k == t.Top->key) {
            t.Top = current->Right;
        }
        if ((prev != nullptr) && (k < prev->key)) {
            prev->Left = current->Right;
        }
        if ((prev != nullptr) && (k > prev->key)) {
            prev->Right = current->Right;
        }
        delete current;
        return;
    }
    if ((current->Left != nullptr) && (current->Right != nullptr)) {
        NodeTree *instead;
        int instead_key;
        instead = current->Right;
        while (instead->Left != nullptr) {
            instead = instead->Left;
        }
        instead_key = instead->key;
        DeleteNode(t, instead_key);
        current->key = instead_key;
        return;
    }
}

bool IsTreeEmpty(Tree &t) {
    return (t.Top == nullptr);
}



void print(NodeTree *&node, int h) {
    if (node != nullptr) {
        print(node->Right, h + 1);
        for (int i = 0; i < h; i++)
            cout << "    ";
        cout << node->key << endl;
        print(node->Left, h + 1);

    }
}

void PrintTree(Tree &t) {
    print(t.Top, 1);
}

void DirectTravel(NodeTree *node) {
    if (node == nullptr) {
        return;
    }
    cout << node->key << " ";
    DirectTravel(node->Left);
    DirectTravel(node->Right);
}

void ReverseTravel(NodeTree *node) {
    if (node == nullptr) {
        return;
    }
    ReverseTravel(node->Left);
    ReverseTravel(node->Right);
    cout << node->key << " ";
}

void SymmetricTravel(NodeTree *node) {
    if (node == nullptr) {
        return;
    }
    ReverseTravel(node->Left);
    cout << node->key << " ";
    ReverseTravel(node->Right);
}

double SummTree(NodeTree *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->key + SummTree(node->Left) + SummTree(node->Right);
}

//void DeleteTree(Tree &t) {
//    while (!IsTreeEmpty(t)) {
//        DeleteNode(t, t.Top->key);
//    }
//}

void DeleteTree(NodeTree *node) {
    if (node != nullptr) {
        if (node->Left != nullptr)
            DeleteTree(node->Left);
        if (node->Right != nullptr)
            DeleteTree(node->Right);
        delete node;
    }
}


int main() {
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Tree tr{};
    CreateTree(tr);
    int num = 0;
    int quant = 0;
    int select = 0;
    while ((select < 1) || (select > 3)) {
        cout << "1 - Файл" << endl << "2 - Ввести вручную" << endl << "3 - Заполнить случайными числами" << endl
             << "Выберите=";
        cin >> select;
        cout << endl;
    }
    if (select == 1) {
        ifstream FileIn("File.txt", ios_base::in);
        while (FileIn >> num) {
            AddNode(tr, num);
            quant++;
        }
        FileIn.close();
    }
    if (select == 2) {
        cout << "Введите кол-во" << endl;
        cin >> quant;
        cout << "Значение" << endl;
        for (int count = 1; count <= quant; count++) {
            cin >> num;
            AddNode(tr, num);

        }
    }
    if (select == 3) {
        while ((quant < 1)) {
            cout << "Введите кол-во" << endl;
            cin >> quant;
            srand(time(nullptr));
            for (int count = 1; count <= quant; count++) {
                AddNode(tr, rand() % 1000 + 1);
            }
        }
    }
    cout << "Дерево : ";
    PrintTree(tr);
    cout << endl;
    cout << "Дерево среднее : " << SummTree(tr.Top) / quant << endl;
    DeleteTree(tr.Top);
}
