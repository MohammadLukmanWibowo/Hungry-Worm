#include < iostream >
#include < conio.h >

using namespace std;
bool gameover;
const int width = 50; //Lebar Area
const int height = 20; //Tinggi Area
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; //maksimum elemen
int nTail; //variabel ekor
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN }; //Kontrol
eDirecton dir;

void Setup() {
    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;

    //Menampilkan Buah Secara Random
    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0;
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "_"; //Tembok Horizontal
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "|"; //Tembok Vertikal
            if (i == y && j == x)
                cout << "0"; //Kepala Cacing
            else if (i == fruitY && j == fruitX)
                cout << "%"; //Buah
            else {

                //print ekor
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; print = true; //Ekor Cacing
                    }
                }
                if (!print) cout << " ";
            }
            if (j == width - 1)
                cout << "|"; //Tembok Vertikal
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "_"; //Tembok Horizontal
    cout << endl;
    cout << "Score:" << score << endl;
}

//Input Kontrol
void Input()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;

        case 'd':
            dir = RIGHT;
            break;

        case 'w':
            dir = UP;
            break;

        case 's':
            dir = DOWN;
            break;

        case 'x': //Keluar permainan
            gameover = true;
            break;
        }
    }
}

void algorithm()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    //ekor mengikuti kepala
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    //Tombol Kontrol
    switch (dir) {
    case LEFT:
        x--;
        break;

    case RIGHT:
        x++;
        break;

    case UP:
        y--;
        break;

    case DOWN:
        y++;
        break;

    default:
        break;
    }

    //Menabrak dinding = gameover
    if (x > width || x < 0 || y > height || y < 0)
        gameover = true;

    //if (x >= width) x = 0; else if (x < 0) x = width - 1;
    //if (y >= height) y = 0; else if (y < 0) y = height - 1;

    //menabrak dirinya sendiri = gameover
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = true;

    //Penambahan Score dan menampilkan buah baru
    if (x == fruitX && y == fruitY) {
        score += 1; //Mendapatkan 1 score ketika berhasil memakan buah
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++; //penambahan ekor
    }
}

int main()
{
    Setup();
    while (!gameover) {
        Draw();
        Input();
        algorithm();
    }
    return 0;
}