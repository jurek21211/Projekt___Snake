#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>


#define WIDTH 20
#define HEIGHT 20


int x, y, foodX, foodY, score, tailLength;
int tailX[100], tailY[100];
char name[50], answer = 'Y';


bool gameOver, reset, boost;
enum direction {
    STOP, LEFT, RIGHT, UP, DOWN
};
enum direction dir;

void introduction();

void setup();

void draw();

void input();

void logic();

void over();

int main() {
    reset = true;
    introduction();
    Sleep(2 * 1000);

    while (reset) {
        setup();
        while (!gameOver) {
            draw();
            input();
            logic();
            Sleep(30);

        }
        over();
    }

    return 1;
}

void introduction() {
    printf("\n"
           " .----------------.  .-----------------. .----------------.  .----------------.  .----------------. \n"
           "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n"
           "| |    _______   | || | ____  _____  | || |      __      | || |  ___  ____   | || |  _________   | |\n"
           "| |   /  ___  |  | || ||_   \\|_   _| | || |     /  \\     | || | |_  ||_  _|  | || | |_   ___  |  | |\n"
           "| |  |  (__ \\_|  | || |  |   \\ | |   | || |    / /\\ \\    | || |   | |_/ /    | || |   | |_  \\_|  | |\n"
           "| |   '.___`-.   | || |  | |\\ \\| |   | || |   / ____ \\   | || |   |  __'.    | || |   |  _|  _   | |\n"
           "| |  |`\\____) |  | || | _| |_\\   |_  | || | _/ /    \\ \\_ | || |  _| |  \\ \\_  | || |  _| |___/ |  | |\n"
           "| |  |_______.'  | || ||_____|\\____| | || ||____|  |____|| || | |____||____| | || | |_________|  | |\n"
           "| |              | || |              | || |              | || |              | || |              | |\n"
           "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n"
           " '----------------'  '----------------'  '----------------'  '----------------'  '----------------' ");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("Tell us your name: ");
    scanf("%s", &name);
    printf("\n");
    printf("\n");
    printf("Welcome: %s! It is time to begin!", name);
    printf("\n");
    printf("\n");
    printf("Use [W, S, A, D] to control SNAKE.");
    printf("\n");
    printf("Use [J] to boost speed");
    printf("\n");
    printf("\n");
    printf("Let us prepare everything...");
}


void setup() {
    gameOver = false;
    dir = STOP;

    //center snake at the beginning
    x = WIDTH / 2;
    y = HEIGHT / 2;

    //placing first fruit
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
    score = 0;
    tailLength = 0;
    reset = true;
    boost = false;
}

void draw() {
    system("cls");
    // top border
    for (int i = 0; i < WIDTH; i++)
        printf("#");
    printf("\n");

    //walls

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            if (j == 0 || j == (WIDTH - 1))
                printf("#");
            if (i == y && j == x) {
                printf("%d", tailLength / 10);
            } else if (i == foodY && j == foodX)
                if (foodY < HEIGHT - 2 && foodX < WIDTH - 2 && foodY > 2 && foodX > 2) {
                    printf("Q");
                } else {
                    foodX = rand() % WIDTH;
                    foodY = rand() % HEIGHT;
                }

            else {
                bool print = false;
                for (int k = 0; k < tailLength; k++) {

                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        print = true;
                    }

                }
                if (!print)
                    printf(" ");
            }

        }
        printf("\n");
    }

    //bottom border

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    printf("<Score:> %d", score);
}

void input() {
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
            case 'x':
                gameOver = true;
                break;
            case 'j':
                boost = true;
                break;
        }
    }
}

void logic() {

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2x, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2x = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2x;
        prevY = prev2Y;

    }

    if (dir == LEFT) {
        if (boost) {
            x -= 2;
            boost = false;
        }else
            x -= 1;
    }
    if (dir == RIGHT) {
        if (boost) {
            x += 2;
            boost = false;
        }else
            x += 1;
    }
    if (dir == UP) {
        if (boost) {
            y -= 2;
            boost = false;
        }else
            y -= 1;
    }


    if (dir == DOWN) {
        if (boost) {
            y += 2;
            boost = false;
        }else
            y += 1;

    }

//booster



//teleport to oposite side of the game field
    if (x >= WIDTH)
        x = 0;
    else if (x < 0)
        x = WIDTH - 1;

    if (y >= HEIGHT)
        y = 0;
    else if (y < 0)
        y = HEIGHT - 1;

    for (
            int i = 0;
            i < tailLength;
            i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }
    if (x == foodX && y == foodY) {
        score += 100;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        tailLength += 1;
    }
}

void over() {
    system("cls");
    printf("\n"
           "  ___    __    __  __  ____    _____  _  _  ____  ____ \n"
           " / __)  /__\\  (  \\/  )( ___)  (  _  )( \\/ )( ___)(  _ \\\n"
           "( (_-. /(__)\\  )    (  )__)    )(_)(  \\  /  )__)  )   /\n"
           " \\___/(__)(__)(_/\\/\\_)(____)  (_____)  \\/  (____)(_)\\_)");

    if (score > 2000) {
        printf("\n");
        printf("\n");
        printf("You have managed to complete your task.\n");
        printf("It was not that hard, isn't it?\n");
        printf("\nYou have got %d points?\n", score);
        printf("\nYou reacher snake level:  %d \n", tailLength / 10);
        printf("Want to try again?: Y(es) or N(o)");

    } else if (score >= 1000 && score <= 2000) {
        printf("\n");
        printf("\n");
        printf("You were almost there.\n");
        printf("But the task turned out to be overwhelming. That's a pity.");
        printf("\nYou got %d points?\n", score);
        printf("\nYou reacher snake level:  %d \n", tailLength / 10);
        printf("It's ok. Want to try again?: Y(es) or N(o)");
    } else if (score < 1000) {
        printf("\n");
        printf("\n");
        printf("Really!? You died that fast?!\n");
        printf("\n");
        printf("You got %d points?\n", score);
        printf("\nYou reacher snake level:  %d \n", tailLength / 10);
        printf("It's ok. It happens. Want to try again?: Y(es) or N(o)");

    }

    while (true) {
        scanf("%s", &answer);
        if (answer == 'Y') {
            break;
        } else if (answer == 'N') {
            reset = false;
            break;
        } else {
            printf("\nWrong answer. Type 'Y' or 'N': ");
            scanf("%s", &answer);
        }
    }
}