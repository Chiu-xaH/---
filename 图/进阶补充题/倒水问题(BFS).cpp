#include <iostream>
#include <queue>
#define MAX 100
using namespace std;
/*
��ˮ���⣺
���� 2 ��û�п̶���������������������ݻ���������ֻ������ƿװ�� L ����ˮ��������ԣ�������裬��������ԣ������ No Solution
*/
struct Pool {
    //�������ӵ�������ˮ
    int x,y,l;
    string s;
} current;

queue<Pool> Queue;
bool visited[MAX][MAX];

void init(int L) {
    for(int i = 0;i < L;i++) {
        for(int j = 0;j < L;j++) {
            visited[i][j] = false;
        }
    }
}
//BFS 
/*��ˮ�޷�8�ֲ�����
1 ��Xװ��
2 ��Yװ��
3 ��X����
4 ��Y����
5 X��Y�е�ˮ��X���꣬Yû�б�װ��
6 X��Y�е�ˮ��Y��װ��
7 Y��X�е�ˮ��Y���꣬Xû�б�װ��
8 Y��X�е�ˮ��X��װ����
*/
string BFS(int maxX, int maxY, int target) {
    Pool current;
    current.x = 0;
    current.y = 0;
    current.l = target;
    current.s = "";
    //���
    Queue.push(current);
    visited[current.x][current.y] = true;

    while (!Queue.empty()) {
        //����
        Pool current = Queue.front();
        Queue.pop();

        // ����ҵ�Ŀ��ˮ��
        if (current.x == current.l || current.y == current.l)
            return current.s;

        // 1. ��Xװ��
        if (!visited[maxX][current.y]) {
            Pool next = current;
            next.x = maxX;
            next.s += "��Xװ��\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 2. ��Yװ��
        if (!visited[current.x][maxY]) {
            Pool next = current;
            next.y = maxY;
            next.s += "��Yװ��\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 3. ��X����
        if (!visited[0][current.y]) {
            Pool next = current;
            next.x = 0;
            next.s += "��X����\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 4. ��Y����
        if (!visited[current.x][0]) {
            Pool next = current;
            next.y = 0;
            next.s += "��Y����\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 5. ��X�е�ˮ����Y�У�X���꣬Yû��װ��
        if (current.x + current.y <= maxY && !visited[0][current.x + current.y]) {
            Pool next = current;
            next.y = current.x + current.y;
            next.x = 0;
            next.s += "��X�е�ˮ����Y��,X����,Yû��װ��\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 6. ��X����Y�У�Y��װ��
        if (current.x + current.y > maxY && !visited[current.x + current.y - maxY][maxY]) {
            Pool next = current;
            next.x = current.x + current.y - maxY;
            next.y = maxY;
            next.s += "��X����Y��,Y��װ��\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 7. ��Y�е�ˮ����X�У�Y���꣬Xû��װ��
        if (current.x + current.y <= maxX && !visited[current.x + current.y][0]) {
            Pool next = current;
            next.x = current.x + current.y;
            next.y = 0;
            next.s += "��Y�е�ˮ����X��,Y����,Xû��װ��\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }

        // 8. ��Y����X�У�X��װ��
        if (current.x + current.y > maxX && !visited[maxX][current.y + current.x - maxX]) {
            Pool next = current;
            next.y = current.x + current.y - maxX;
            next.x = maxX;
            next.s += "��Y����X��,X��װ��\n";
            visited[next.x][next.y] = true;
            Queue.push(next);
        }
    }

    return "�޽�";
}

int main() {
    int x, y, l;
    cout << "����������������X��Y��ˮ����L\n";
    cin >> x >> y >> l;
    init(l);  // ��ʼ�����ʱ������
    string result = BFS(x,y,l);
    cout << result << endl;
}
