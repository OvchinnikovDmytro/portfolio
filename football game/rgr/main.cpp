#include <SFML/Graphics.hpp>
#include <time.h>
#include <unistd.h>
#include <conio.h>
using namespace sf;

	RenderWindow window(VideoMode(768, 768), "The Game!");
	int blockWidht = 64;
    Texture texture;
    Texture ball;
    Texture stage;
    Sprite sprite[13];
	Sprite sprite_ball;
	Sprite sprite_stage0;
    int grid[12][12] = { 0 };
    int dx=6,dy=11,tmp;
    int dxtmp=0,dytmp=0;
    int stag=0;
    int speed = 8;
    int score = 0;
    int proc = 1;
    void livo()//����� �� ����������� ��� ��� ����
    {
        if (dx != 0)//��� �� ����� �� ��� ������
        {
            tmp = grid[dy][dx];//������� �'��� � �������
            grid[dy][dx]=grid[dy][dx-1];
            grid[dy][dx-1]=tmp;
            for (int i = 0; i <= blockWidht; i += speed)
            {
                window.clear(Color::White);
                sprite_ball.setPosition(dx*blockWidht-i,dy*blockWidht );//���������� �'���
                window.draw(sprite_ball);//����������
                for (int j = 0; j < 13; j++)
                {
                    sprite[j].setPosition(j*blockWidht,0 );//������������ ������� ���� �� ����
                    window.draw(sprite[j]);//����������
                }
                window.display();
                usleep(75000);
            }
            dx--;//��������� ���� �� 1 ����� ������� ����(64 �����)
        }
    }
    void pravo()//����� �� ����������� ��� ��� ������
    {
        if (dx != 11)//��� �� ����� �� ��� ������
        {
            tmp = grid[dy][dx];//������� �'��� � �������
            grid[dy][dx]=grid[dy][dx+1];
            grid[dy][dx+1]=tmp;
            for (int i = 0; i <= blockWidht; i += speed)
            {
                window.clear(Color::White);
                sprite_ball.setPosition(dx*blockWidht+i,dy*blockWidht );//���������� �'���
                window.draw(sprite_ball);//����������
                for (int j = 0; j < 13; j++)
                {
                    sprite[j].setPosition(j*blockWidht,0 );//������������ ������� ���� �� ����
                    window.draw(sprite[j]);//����������
                }
                window.display();
                usleep(75000);
            }
            dx++;//��������� ������ �� 1 ����� ������� ������(64 �����)
        }
    }
    void vverh()//����� �� ����������� ��� ��� �����
    {
        while(proc==1)//���� �� ���������� ���� �1�� �� ���� �� ����
        {
            if (dy == 1)//���� �'�� ���� �� ������������ ������� �� �������� ������ ���� �� ������
            {
                if(grid[dy-1][dx]==4)//���� 4 �� �� ����� ���� ������� ����� �� ������
                {
                    //printf("You missed");
                    speed=0;//�������� 0 ��� ���� �������� � ����
                    stag++;//������� �� �������� �����
                    proc=0;//��������� �� ����� � �����
                    break;
                }
                if(grid[dy-1][dx]==3)//���� 3 �� �� �������� ���� ���� ������� ������ 3 ����
                {
                    score+=3;//�������� ������� �� 3
                    //printf("You scored 3 points");
                    dxtmp=5,dytmp=11;//������������� �� ���� ��� �'�� �� ������� ��� ����������
                }
                if(grid[dy-1][dx]==2)//���� 2 �� �� ������� ���� ���� ������� ������ 2 ����
                {
                    score+=2;//�������� ������� �� 2
                    //printf("You scored 2 points");
                    dxtmp=5,dytmp=11;//������������� �� ���� ��� �'�� �� ������� ��� ����������
                }
                if(grid[dy-1][dx]==1)//���� 1 �� �� �������� ���� ���� ������� ������ 1 ����
                {
                    score+=1;//�������� ������� �� 1
                    //printf("You scored 1 points");
                    dxtmp=5,dytmp=11;//������������� �� ���� ��� �'�� �� ������� ��� ����������
                }
            }
            for (int i = 0; i <= blockWidht; i += speed)
            {
                window.clear(Color::White);
                sprite_ball.setPosition(dx*blockWidht,dy*blockWidht-i );//���������� �'���
                window.draw(sprite_ball);//����������
                for (int j = 0; j < 13; j++)
                {
                    sprite[j].setPosition(j*blockWidht,0 );//������������ ������� ���� �� ����
                    window.draw(sprite[j]);//����������
                }
                window.display();
                usleep(30000);
            }
            dy--;//��������� ����� �� 1 ����� ������� �����(64 �����)
            if (dxtmp>0)//���� �'�� ����� � ����
            {
                dxtmp=0;
                dytmp=0;
                proc=0;//����� � �����
                stag++;//������� �� �������� �����
            }
        }
    }

int main()
{
	ball.loadFromFile("img/ball.png");//���������� �'��� ���� ��������
	stage.loadFromFile("img/main.png");//���������� ������ �����䳿 �������� �����
	// ���������� ������������� �������� ����
	srand(time(NULL));
    sprite_stage0.setTexture(stage);//���������� ������ ������ �����䳿 �� ��������� �����
    sprite_ball.setTexture(ball);//���������� �'��� ���� ������


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color::White);
		if (stag==0)//��� �������
        {
            sprite_stage0.setPosition(0,0);//����������� ������� ������� �� �������
            window.draw(sprite_stage0);
            window.display();//����������
            window.clear(Color::White);
            proc=1;//��������� �������� proc ��� � �� ��������� ���������� �����
            dx=rand()%12;//���������� ��������� �������� ��
            speed=8;//���������� ��������� �������� ��������
            dy=11;//���������� �������� ��
            usleep(75000);
        }
		else if (stag==1)//���� ������� �������� ����� ����������� �����
        {
            texture.loadFromFile("img/var1.png");//�������� ������� ��� ������� ����
            sprite_stage0.setTexture(stage);
            stage.loadFromFile("img/sproba1.png");//��������� �������� ����������� ������
            sprite_stage0.setPosition(0,0);
            window.draw(sprite_stage0);
            window.display();
            window.clear(Color::White);
            proc=1;//���������� ���� ��� ����� ���� �������� �����
            dx=rand()%12;//���������� ��������� �������� ��
            speed=8;//���������� ��������� �������� ��������
            dy=11;//���������� �������� ��
            for (int j = 0; j < 13; j++)//����������� ������ ���� �� ��� �� �����
            {
                sprite[j].setTexture(texture);
                sprite[j].setTextureRect(IntRect(j*blockWidht,0 , blockWidht, blockWidht));
            }
            for (int i = 0;i < 2;i++)//���������� ������� �������� ���,����,�'���
            {
                grid[0][i] = 4;
            }
            for (int i = 2;i < 5;i++)
            {
                grid[0][i] = 1;
            }
            for (int i = 5;i < 7;i++)
            {
                grid[0][i] = 4;
            }
            for (int i = 7;i < 9;i++)
            {
                grid[0][i] = 2;
            }
            grid[0][9] = 4;
            grid[0][10] = 3;
            grid[0][11] = 4;
            grid[11][dx] = 8;
        }
        else if (stag==2)//���� ������ ���
        {
            for (int j = 0; j < 13; j++)
            {
                sprite[j].setPosition(j*blockWidht,0 );
                window.draw(sprite[j]);
            }
            sprite_ball.setPosition(dx*blockWidht,dy*blockWidht );
            window.draw(sprite_ball);
            window.display();
            window.clear(Color::White);
        }
        else if (stag==3)
        {
            texture.loadFromFile("img/var2.png");//�������� �������� 2 ����
            Sprite sprite[13];
            sprite_stage0.setTexture(stage);
            stage.loadFromFile("img/sproba2.png");//�������� ������ ������ 2 ������
            sprite_stage0.setPosition(0,0);
            window.draw(sprite_stage0);
            window.display();
            window.clear(Color::White);
            proc=1;
            dx=rand()%12;
            speed=8;
            dy=11;
            for (int j = 0; j < 13; j++)//�������� ������� ���� �� ��� ��� 2 ����
            {
                sprite[j].setTexture(texture);
                sprite[j].setTextureRect(IntRect(j*blockWidht,0 , blockWidht, blockWidht));
            }
            grid[0][0] = 4;//��������� ������� �������� ����� � ����� �� ������������� ���� �� ���
            for (int i = 1;i <= 3;i++)
            {
                grid[0][i] = 1;
            }
            for (int i = 4;i <= 5;i++)
            {
                grid[0][i] = 4;
            }
            grid[0][6] = 3;
            for (int i = 7;i <= 9;i++)
            {
                grid[0][i] = 4;
            }

            for (int i = 10;i <= 11;i++)
            {
                grid[0][i] = 2;
            }
            grid[11][dx]=8;
        }
        else if (stag==4)
        {
            for (int j = 0; j < 13; j++)
            {
                sprite[j].setPosition(j*blockWidht,0 );
                window.draw(sprite[j]);
            }
            sprite_ball.setPosition(dx*blockWidht,dy*blockWidht );
            window.draw(sprite_ball);
            window.display();
            window.clear(Color::White);
        }
        else if (stag==5)
        {
            texture.loadFromFile("img/var3.png");
            Sprite sprite[13];
            sprite_stage0.setTexture(stage);
            stage.loadFromFile("img/sproba3.png");
            sprite_stage0.setPosition(0,0);
            window.draw(sprite_stage0);
            window.display();
            window.clear(Color::White);
            proc=1;
            dx=rand()%12;
            speed=8;
            dy=11;
            for (int j = 0; j < 13; j++)
            {
                sprite[j].setTexture(texture);
                sprite[j].setTextureRect(IntRect(j*blockWidht,0 , blockWidht, blockWidht));
            }
            grid[0][0] = 4;
            grid[0][1] = 3;
            grid[0][2] = 4;
            for (int i = 3;i <= 4;i++)
            {
                grid[0][i] = 2;
            }
            for (int i = 5;i <= 7;i++)
            {
                grid[0][i] = 4;
            }
            for (int i = 8;i <= 10;i++)
            {
                grid[0][i] = 1;
            }
            grid[0][11] = 4;
            grid[11][dx]=8;
        }
        else if (stag==6)
        {
            for (int j = 0; j < 13; j++)
            {
                sprite[j].setPosition(j*blockWidht,0 );
                window.draw(sprite[j]);
            }
            sprite_ball.setPosition(dx*blockWidht,dy*blockWidht );
            window.draw(sprite_ball);
            window.display();
            window.clear(Color::White);
        }
        else if (stag==7)//�����,���� ���� ��� �������� ������� ���������� �� ������� ����
        {
            if (score == 0)
            {
                stage.loadFromFile("img/score0.png");
            }
            else if (score == 1)
            {
                stage.loadFromFile("img/score1.png");
            }
            else if (score == 2)
            {
                stage.loadFromFile("img/score2.png");
            }
            else if (score == 3)
            {
                stage.loadFromFile("img/score3.png");
            }
            else if (score == 4)
            {
                stage.loadFromFile("img/score4.png");
            }
            else if (score == 5)
            {
                stage.loadFromFile("img/score5.png");
            }
            else if (score == 6)
            {
                stage.loadFromFile("img/score6.png");
            }
            else if (score == 7)
            {
                stage.loadFromFile("img/score7.png");
            }
            else if (score == 8)
            {
                stage.loadFromFile("img/score8.png");
            }
            else if (score == 9)
            {
                stage.loadFromFile("img/score9.png");
            }

            sprite_stage0.setPosition(0,0);
            window.draw(sprite_stage0);
            window.display();
            window.clear(Color::White);
            usleep(75000);
        }
        if (event.type == sf::Event::KeyPressed)//������� �� ���� ������ ������
        {
            if ((stag==2)||(stag==4)||(stag==6))//�� ��� ���
            {
                if (event.key.code == sf::Keyboard::Left)//���� ������ ��� ������ �� �������� ������� ����
                {
                    livo();
                }

                if (event.key.code == sf::Keyboard::Right)//���� ������ ������ ������ �� �������� ������� ������
                {
                    pravo();
                }

                if (event.key.code == sf::Keyboard::Up)//���� ������ ����� ������ �� �������� ������� �����
                {
                    vverh();
                }
            }
            if ((stag==0)||(stag==1)||(stag==3)||(stag==5)||(stag==7))//�� ��� ������ ������䳿
            {
                if (event.key.code == sf::Keyboard::LShift)
                {
                    stag++;//�� ��������� ����
                    usleep(75000);
                }
            }

        }
	}
    //printf("TOTAL SCORE %d\n",score);
	return 0;
}
