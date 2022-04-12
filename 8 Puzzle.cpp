# include "iGraphics.h"

#include <time.h>

#define N 3

void Single_Text(double x, double y, char *str, void* font=GLUT_BITMAP_TIMES_ROMAN_24)
{
    glRasterPos3d(x, y, 0);
    int i=0;
    glutBitmapCharacter(font, str[i]); // GLUT_BITMAP_TIMES_ROMAN_24

}


int new_blank_row,new_blank_col;
int blank_row,blank_col;



int position_x[N][N] = {150,250,350,150,250,350,150,250,350};
int position_y[N][N] = {350,350,350,250,250,250,150,150,150};
char new_board[N][N] = {'1',  '2',  '3','4',  '5',  '6','7',  '8', '_'};




char apply_move(unsigned char key)
{

    for (int row = 0; row < N; ++row)
    {
        for (int col = 0; col < N; ++col)
        {
            if(new_board[row][col] == '_')
            {
                blank_row = row;
                blank_col = col;
            }

        }
    }
    new_blank_row = blank_row;
    new_blank_col = blank_col;



    switch (key)
    {
        case GLUT_KEY_UP:
            new_blank_row = blank_row + 1;
            break;
        case GLUT_KEY_DOWN:
            new_blank_row = blank_row - 1;
            break;
        case GLUT_KEY_RIGHT:
            new_blank_col = blank_col - 1;
            break;
        case GLUT_KEY_LEFT:
            new_blank_col = blank_col + 1;
            break;
    }

    if ((new_blank_row >= 0 && new_blank_row < 3) && (new_blank_col >= 0 && new_blank_col < 3))
    {
        new_board[blank_row][blank_col] = new_board[new_blank_row][new_blank_col];
        new_board[new_blank_row][new_blank_col] = '_';

    }


}


void shuffle_board()
{

    srand(time(NULL));
    for (int i = 0; i < 100; ++i)
    {
        int shuffler = rand() % 4;
        switch (shuffler)
        {
            case 0:
                apply_move(GLUT_KEY_UP);
                break;
            case 1:
                apply_move(GLUT_KEY_DOWN);
                break;
            case 2:
                apply_move(GLUT_KEY_RIGHT);
                break;
            case 3:
                apply_move(GLUT_KEY_LEFT);
                break;

        }

    }
}



void check_win()
{
    char board[N][N] = {{'1',  '2',  '3' },
                        {'4',  '5',  '6' },
                        {'7',  '8', '_'}
    };

    int count =0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {

            if(board[i][j] == new_board[i][j])
            {
                count++;
            }
        }
    }
    if(count==9)
    {
        iText(200,450,"You Win!!!",GLUT_BITMAP_TIMES_ROMAN_24);

    }

}



void store_last_board(int button, int state)
{
    FILE *f1;
    f1 = fopen("current_board.txt", "w");

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            fprintf(f1, "%c ", new_board[i][j]);
        }
        fprintf(f1, "\n");
    }

}

void access_last_board()
{

    FILE *f1;
    f1 = fopen("current_board.txt", "r");

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            fscanf(f1, "%c ", &new_board[i][j]);
        }
    }

}




/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    //place your drawing codes here
    iClear();
    //PlaySound("C:\\MinGW\\IGraphics-master\\p_sound.wav",NULL,SND_ASYNC);

    check_win();
    iSetColor(252,250,3);
    iRectangle(50,445,67,20);
    iText(51,451,"New Game");
    iText(25,41,"Exit");
    iText(130,41,"Use arrow Key to move digits",GLUT_BITMAP_9_BY_15);
    iRectangle(23,38,35,14);
    iText(404,43,"Resume");
    iRectangle(402,38,51,14);


    iSetColor(20,200,255);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            iRectangle(100+100*i,100+100*j,100,100);
        }
    }


    iSetColor(244,255,36);


    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if(new_board[i][j] == '_')
            {
                Single_Text(position_x[i][j], position_y[i][j], " ");

            }
            else
            {
                Single_Text(position_x[i][j], position_y[i][j], &new_board[i][j]);
            }
        }
    }



}


/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
//    printf("x = %d, y= %d\n",mx,my);

}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if((mx>=50 && mx<=114) && (my>=450 && my<=470))
        {
            shuffle_board();
        }
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if((mx>=24 && mx<=55) && (my>=40 && my<=53))
        {
            store_last_board(button,state);
            exit(0);
        }
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if((mx>=402 && mx<=453) && (my>=41 && my<=55))
        {
            access_last_board();
        }
    }


}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key == '0')
    {
        exit(0);
    }

    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
    apply_move(key);
    //place your codes for other keys here*/
}


int main()
{
    //PlaySound("C:\\MinGW\\IGraphics-master\\p_sound.wav",NULL,SND_ASYNC |SND_LOOP);
    shuffle_board();
    iInitialize(500, 500, "8 Puzzle!");

    return 0;
}
