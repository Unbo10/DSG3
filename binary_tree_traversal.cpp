#include <iostream>

using namespace std;

int** find_subtree(int* pre, int* ino, int* sub_tree, int root) {

}

int* postorder(int** info)  {
    //* info[0] = pre, info[1] = ino, info[2] = left, info[3] = right, info[4][0] = root
    if ((sizeof(info[2])/4) == 1) {
        return info[2];
    }
    else {
        return postorder(find_subtree(info[0], info[1], info[2], info[4][0])) + postorder(find_subtree(info[0], info[1], info[2], info[4][0])) + info[4];
    }
}

int main() {
    int n = 0;
    cin >> n;
    int pre[n], ino[n];
    for (int i = 0; i < n; i++) {
        cin >> pre[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> ino[i];
    }
    postorder(pre, ino);

    return 0;
}