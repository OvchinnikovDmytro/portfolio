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
    void livo()//метод що викликаЇтьс€ при рус≥ вл≥во
    {
        if (dx != 0)//аби не вийти за меж≥ масиву
        {
            tmp = grid[dy][dx];//зм≥щенн€ м'€ча в матриц≥
            grid[dy][dx]=grid[dy][dx-1];
            grid[dy][dx-1]=tmp;
            for (int i = 0; i <= blockWidht; i += speed)
            {
                window.clear(Color::White);
                sprite_ball.setPosition(dx*blockWidht-i,dy*blockWidht );//перем≥щенн€ м'€ча
                window.draw(sprite_ball);//в≥дмальовка
                for (int j = 0; j < 13; j++)
                {
                    sprite[j].setPosition(j*blockWidht,0 );//встановленн€ спрайт≥в ст≥ни та арок
                    window.draw(sprite[j]);//в≥дмальовка
                }
                window.display();
                usleep(75000);
            }
            dx--;//перем≥щуЇмо вл≥во на 1 пункт матриц≥ вл≥во(64 п≥ксел≥)
        }
    }
    void pravo()//метод що викликаЇтьс€ при рус≥ вправо
    {
        if (dx != 11)//аби не вийти за меж≥ масиву
        {
            tmp = grid[dy][dx];//зм≥щенн€ м'€ча в матриц≥
            grid[dy][dx]=grid[dy][dx+1];
            grid[dy][dx+1]=tmp;
            for (int i = 0; i <= blockWidht; i += speed)
            {
                window.clear(Color::White);
                sprite_ball.setPosition(dx*blockWidht+i,dy*blockWidht );//перем≥щенн€ м'€ча
                window.draw(sprite_ball);//в≥дмальовка
                for (int j = 0; j < 13; j++)
                {
                    sprite[j].setPosition(j*blockWidht,0 );//встановленн€ спрайт≥в ст≥ни та арок
                    window.draw(sprite[j]);//в≥дмальовка
                }
                window.display();
                usleep(75000);
            }
            dx++;//перем≥щуЇмо вправо на 1 пункт матриц≥ вправо(64 п≥ксел≥)
        }
    }
    void vverh()//метод що викликаЇтьс€ при рус≥ вгору
    {
        while(proc==1)//цикл що виконуЇтьс€ поки м1€ч не д≥йде до к≥нц€
        {
            if (dy == 1)//коли м'€ч д≥йде до передостаньоњ кл≥тинки в≥н перев≥р€Ї ск≥льки очок в≥н отримаЇ
            {
                if(grid[dy-1][dx]==4)//€кщо 4 то це ст≥нка отже гравець н≥чого не отримуЇ
                {
                    //printf("You missed");
                    speed=0;//швидк≥сть 0 аби воно вр≥залось в ст≥ну
                    stag++;//перех≥д на наступну стад≥ю
                    proc=0;//зак≥нченн€ та вих≥д з циклу
                    break;
                }
                if(grid[dy-1][dx]==3)//€кщо 3 то це найменша арка отже гравець отримуЇ 3 очка
                {
                    score+=3;//зб≥дьшуЇмо рахунок на 3
                    //printf("You scored 3 points");
                    dxtmp=5,dytmp=11;//використовуЇмо ц≥ зм≥нн≥ аби м'€ч не пригнув при прорисовц≥
                }
                if(grid[dy-1][dx]==2)//€кщо 2 то це середн€ арка отже гравець отримуЇ 2 очка
                {
                    score+=2;//зб≥дьшуЇмо рахунок на 2
                    //printf("You scored 2 points");
                    dxtmp=5,dytmp=11;//використовуЇмо ц≥ зм≥нн≥ аби м'€ч не пригнув при прорисовц≥
                }
                if(grid[dy-1][dx]==1)//€кщо 1 то це найб≥льша арка отже гравець отримуЇ 1 очка
                {
                    score+=1;//зб≥дьшуЇмо рахунок на 1
                    //printf("You scored 1 points");
                    dxtmp=5,dytmp=11;//використовуЇмо ц≥ зм≥нн≥ аби м'€ч не пригнув при прорисовц≥
                }
            }
            for (int i = 0; i <= blockWidht; i += speed)
            {
                window.clear(Color::White);
                sprite_ball.setPosition(dx*blockWidht,dy*blockWidht-i );//перем≥щенн€ м'€ча
                window.draw(sprite_ball);//в≥дмальовка
                for (int j = 0; j < 13; j++)
                {
                    sprite[j].setPosition(j*blockWidht,0 );//встановленн€ спрайт≥в ст≥ни та арок
                    window.draw(sprite[j]);//в≥дмальовка
                }
                window.display();
                usleep(30000);
            }
            dy--;//перем≥щуЇмо вверх на 1 пункт матриц≥ вгору(64 п≥ксел≥)
            if (dxtmp>0)//€кщо м'€ч попав в арку
            {
                dxtmp=0;
                dytmp=0;
                proc=0;//вих≥д з циклу
                stag++;//перех≥д на наступну стад≥ю
            }
        }
    }

int main()
{
	ball.loadFromFile("img/ball.png");//присвоюЇмо м'€чу його текстуру
	stage.loadFromFile("img/main.png");//присвоюЇмо екрану взаЇмод≥њ головний екран
	// Ћогическое представление игрового пол€
	srand(time(NULL));
    sprite_stage0.setTexture(stage);//присвоюЇмо екрану спрайт взаЇмод≥њ на головному екран≥
    sprite_ball.setTexture(ball);//присвоюЇмо м'€чу його спрайт


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color::White);
		if (stag==0)//при запуску
        {
            sprite_stage0.setPosition(0,0);//виставл€Їмо позиц≥ю спрайту на початок
            window.draw(sprite_stage0);
            window.display();//в≥дмальовка
            window.clear(Color::White);
            proc=1;//повертаЇмо значенн€ proc аби в гр≥ працювало перем≥щенн€ вгору
            dx=rand()%12;//присвоюЇмо випадкове значенн€ дх
            speed=8;//присвоюЇмо випадкове значенн€ швидкост≥
            dy=11;//присвоюЇмо значенн€ ду
            usleep(75000);
        }
		else if (stag==1)//п≥сл€ запуску виводить номер тепер≥шнього кидка
        {
            texture.loadFromFile("img/var1.png");//загружаЇм тектуру дл€ першого р≥вн€
            sprite_stage0.setTexture(stage);
            stage.loadFromFile("img/sproba1.png");//присвоЇнн€ текстури виводупершоњ спроби
            sprite_stage0.setPosition(0,0);
            window.draw(sprite_stage0);
            window.display();
            window.clear(Color::White);
            proc=1;//анулюванн€ прос аби можна було рухатись вгору
            dx=rand()%12;//присвоюЇмо випадкове значенн€ дх
            speed=8;//присвоюЇмо випадкове значенн€ швидкост≥
            dy=11;//присвоюЇмо значенн€ ду
            for (int j = 0; j < 13; j++)//виставл€нн€ частин арки та ст≥н на екран≥
            {
                sprite[j].setTexture(texture);
                sprite[j].setTextureRect(IntRect(j*blockWidht,0 , blockWidht, blockWidht));
            }
            for (int i = 0;i < 2;i++)//присвоюЇмо матриц≥ значенн€ ст≥н,арок,м'€ча
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
        else if (stag==2)//вив≥д екрану гри
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
            texture.loadFromFile("img/var2.png");//загрузка текстури 2 р≥вн€
            Sprite sprite[13];
            sprite_stage0.setTexture(stage);
            stage.loadFromFile("img/sproba2.png");//загрузка тектур виводу 2 спроби
            sprite_stage0.setPosition(0,0);
            window.draw(sprite_stage0);
            window.display();
            window.clear(Color::White);
            proc=1;
            dx=rand()%12;
            speed=8;
            dy=11;
            for (int j = 0; j < 13; j++)//загрузка текстур арок та стн≥ дл€ 2 р≥вн€
            {
                sprite[j].setTexture(texture);
                sprite[j].setTextureRect(IntRect(j*blockWidht,0 , blockWidht, blockWidht));
            }
            grid[0][0] = 4;//присвоЇнн€ матриц≥ значенн€ зг≥дно з р≥внем та розташуванн€м арок та ст≥н
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
        else if (stag==7)//к≥нець,виб≥р того €ку текстуру вивести взалежност≥ в≥д к≥лькост≥ очок
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
        if (event.type == sf::Event::KeyPressed)//обробка д≥й €кщо нажали кнопку
        {
            if ((stag==2)||(stag==4)||(stag==6))//п≥д час гри
            {
                if (event.key.code == sf::Keyboard::Left)//€кщо нажали л≥ву стр≥лку то виконуЇмо функц≥ю вл≥во
                {
                    livo();
                }

                if (event.key.code == sf::Keyboard::Right)//€кщо нажали вправо стр≥лку то виконуЇмо функц≥ю вправо
                {
                    pravo();
                }

                if (event.key.code == sf::Keyboard::Up)//€кщо нажали вгору стр≥лку то виконуЇмо функц≥ю вгору
                {
                    vverh();
                }
            }
            if ((stag==0)||(stag==1)||(stag==3)||(stag==5)||(stag==7))//п≥д час екран≥в взажмод≥њ
            {
                if (event.key.code == sf::Keyboard::LShift)
                {
                    stag++;//на наступний етап
                    usleep(75000);
                }
            }

        }
	}
    //printf("TOTAL SCORE %d\n",score);
	return 0;
}
