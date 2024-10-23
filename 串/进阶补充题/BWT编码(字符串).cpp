#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

//����ԭ�ĵ�ѭ������
vector<string> generateCyclicRotations(const string &text) {
    int n = text.size();
    vector<string> rotations;
    for (int i = 0;i < n;i++) {
        // ÿ�����ɵ��ַ�����i��ʼ��ѭ��ƴ��
        rotations.push_back(text.substr(i) + text.substr(0, i));
    }
    return rotations;
}
//����
pair<string, int> encrypt(const string &text) {
    vector<string> rotations = generateCyclicRotations(text);
    vector<pair<string, int>> rotationsWithIndex; // �洢ѭ�����к�ԭʼ����

    for (int i = 0; i < rotations.size(); i++) {
        rotationsWithIndex.push_back({rotations[i], i});
    }

    // ����
    stable_sort(rotationsWithIndex.begin(), rotationsWithIndex.end());

    string ciphertext;
    int originalIndex = 0; // ԭ�����ڵ�����
    for (int i = 0; i < rotationsWithIndex.size(); i++) {
        ciphertext += rotationsWithIndex[i].first.back(); // ȡ���һ���ַ�
        if (rotationsWithIndex[i].second == 0) {
            originalIndex = i; // ��¼ԭ����������λ��
        }
    }

    return {ciphertext, originalIndex};
}
//����
string decrypt(const string &ciphertext,int index) {
    int n = ciphertext.size();
    vector<string> table(n, string(n, ' '));
    //�����ؽ������
    for (int i = 0; i < n; i++) {
        //�����ĵ�ÿ���ַ��ӵ�ÿ���ַ�����ǰ��
        for (int j = 0; j < n; j++) {
            table[j] = ciphertext[j] + table[j];
        }
        stable_sort(table.begin(), table.end());
    }
    return table[index]; 
}

int main() {
    string text,mode;
    int index;
    cout << "���������(e)�����(d)ģʽ: ";
    cin >> mode;

    if (mode == "e") {
        cout << "����ԭ��: ";
        cin >> text;
        auto [encrypted, index] = encrypt(text);
        cout << "���ܺ�: " << encrypted << " ������: " << index << endl;
    } else if (mode == "d") {
        cout << "��������: ";
        cin >> text;
        cout << "����������: ";
        cin >> index;
        string decrypted = decrypt(text, index);
        cout << "���ܺ�: " << decrypted << endl;
    } else {
        cout << "��Ч!" << endl;
    }

    return 0;
}
