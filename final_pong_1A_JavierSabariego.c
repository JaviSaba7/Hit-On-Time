/*******************************************************************************************
*
*   HIT ON TIME
*
*   Created by Javier Sabariego with Raylib
*
********************************************************************************************/

#include "raylib.h"
typedef enum { NONE = 0, LOGO, TITLE, ABOUT, GAMEPLAY, WIN, LOSE } GameScreen;

int main()
{
    int screenWidth = 1280;
    int screenHeight = 720;
    bool pause = false;
    bool restart = false;
    bool shot = false;
    float timePlay = 0.0f;
    
    InitAudioDevice();
    InitWindow(screenWidth, screenHeight, "HIT ON TIME - by Javier Sabariego");
    
    //Audio loading: Sounds
    Sound logosound = LoadSound("resources/logo.ogg");
    Sound bouncing = LoadSound("resources/bounce.ogg");
    Sound loselive = LoadSound("resources/loselive.ogg");
    Sound collision = LoadSound("resources/collision.ogg");
    Sound shotsound = LoadSound("resources/shot.ogg");
    Sound nextlevel = LoadSound("resources/nextlevel.ogg");
    
    //Audio loading: Music
    Music song = LoadMusicStream("resources/song.mod");
    Music menusong = LoadMusicStream("resources/menusong.ogg");
    Music losesong = LoadMusicStream("resources/losesong.xm");
    Music winsong = LoadMusicStream("resources/winsong.mod");
    PlayMusicStream(song);
    PlayMusicStream(menusong);
    PlayMusicStream(winsong);
    PlayMusicStream(losesong);
    
    //Textures loading
    Texture2D logo = LoadTexture("resources/mylogo.png");
    Texture2D background = LoadTexture("resources/background.png");
    Texture2D title1 = LoadTexture("resources/title1.png");
    Texture2D title2 = LoadTexture("resources/title2.png");
    Texture2D title3 = LoadTexture("resources/title3.png");
    Texture2D level1 = LoadTexture("resources/level1.png");
    Texture2D level2 = LoadTexture("resources/level2.png");
    Texture2D level3 = LoadTexture("resources/level3.png");
    Texture2D level4 = LoadTexture("resources/level4.png");
    Texture2D level5 = LoadTexture("resources/level5.png");
    Texture2D level6 = LoadTexture("resources/level6.png");
    Texture2D level7 = LoadTexture("resources/level7.png");
    Texture2D level8 = LoadTexture("resources/level8.png");
    Texture2D level9 = LoadTexture("resources/level9.png");
    Texture2D level10 = LoadTexture("resources/level10.png");
    Texture2D about = LoadTexture("resources/about.png"); 
    Texture2D fondo = LoadTexture("resources/fondo.png"); 
    Texture2D titlefinal = LoadTexture("resources/titlefinal.png");
    Texture2D buttonStart = LoadTexture("resources/buttonStart.png");
    Texture2D win = LoadTexture("resources/win.png");
    Texture2D lose = LoadTexture("resources/lose.png");
    Texture2D restartscreen = LoadTexture("resources/restart.png");
    Texture2D buttonAbout = LoadTexture("resources/buttonAbout.png");
    Texture2D buttonExit = LoadTexture("resources/buttonExit.png");  
    Texture2D buttonBack = LoadTexture("resources/buttonBack.png");    
    
    //Font loading
    SpriteFont textfont = LoadSpriteFont("resources/font.ttf");
    
    //Buttons: Start
    int buttonStartMoveX = 0-200;
    Rectangle buttonStartFrame = {0, 0, buttonStart.width, buttonStart.height/3};
    Vector2 buttonStartRec = {screenWidth/2 - buttonStart.width/2, 150};
    int buttonState = 0;
    Vector2 buttonStartPosition = {buttonStartMoveX, screenHeight/2};
   
    //Buttons: About
    Rectangle buttonAboutFrame = {0, 0, buttonAbout.width, buttonAbout.height/3};
    Vector2 buttonAboutRec = {screenWidth/2 - buttonAbout.width/2, 150};
    Vector2 buttonAboutPosition = {screenWidth/2-buttonAbout.width/2, screenHeight/2+100};
 
    //Buttons: Exit
    int buttonExitMoveX = screenWidth;
    Rectangle buttonExitFrame = {0, 0, buttonExit.width, buttonExit.height/3};
    Vector2 buttonExitRec = {screenWidth/2 - buttonExit.width/2, 150};
    Vector2 buttonExitPosition = {buttonExitMoveX, screenHeight/2+200}; 
    
    //Buttons: Back
    Rectangle buttonBackFrame = {0, 0, buttonBack.width, buttonBack.height/3};
    Vector2 buttonBackRec = {screenWidth/2 - buttonBack.width/2, 150};
    Vector2 buttonBackPosition = {screenWidth/2-buttonBack.width+600, screenHeight/2+250};
    
    Vector2 mousePosition;
    int title1PositionY = -300;
    int title2PositionY = -300;
    int title3PositionY = -300;
    int framesCounter = 0;
    float logoAlpha = 0.0f;
    float aboutAlpha = 0.0f;
    int currentScreen = LOGO;
    int lives = 3;
    int level = 1;
    
    //Game colours
    Color color1 = DARKBLUE; //Principal colour
    Color color2 = LIME; //Secondary colour
    Color color3 = YELLOW; //Collision colour
    Color ballColor;
    Color boxColor = RED;
    Color boxColor2 = BLUE;
    //Recs
    Rectangle bar = {screenWidth/2 - 10, screenHeight/2 +160, 20, 60};
    Rectangle bar2 = {screenWidth/2-500, screenHeight/2 , 60, 80};
    Rectangle bar3 = {screenWidth/2+500, screenHeight/2 , 60, 80};
    Rectangle bar4 = {bar2.x, bar2.y , 50, 20};    
    Rectangle bar5 = {100, 50 , 200, 100};//Doors level 4
    Rectangle bar6 = {980, 50 , 200, 100};//Doors level 4 
    Rectangle bar8 = {0, screenHeight-200 , 200, 100};
    Rectangle bar7 = {0, screenHeight-200 , 20, 50};
    Rectangle bar9 = {screenWidth/2-200,0 , 400, 20};
    Rectangle box = {screenWidth/2 - 25, screenHeight/2 - 25, 50, 50};
    Rectangle box2 = {screenWidth/2 - 15, screenHeight/2 - 15, 30, 30};
    Rectangle box3 = {screenWidth/2 - 10, screenHeight/2-10, 20, 20}; 
    Rectangle recLevel2 = {screenWidth/2 - 10, screenHeight/2 +160, 20, 60}; 
    
    //Bars Speed
    int barSpeedY = 4;
    int barSpeedX = 4;
    int bar3SpeedY = 8;   
    int bar4SpeedX = 10; //Missile level 4  
    int bar5SpeedX = 30;   
    int bar6SpeedX = 30;    
    int bar7SpeedY = 30; //Missile level 5
    int bar8SpeedX = 20; //SpaceShip level 4
    
    //Positions
    Vector2 ballPosition;
    ballPosition.x = screenWidth/2;
    ballPosition.y = screenHeight/2;
    
    Vector2 ballPositionL6;
    ballPositionL6.x = screenWidth/2;
    ballPositionL6.y = screenHeight/2;
    
    Vector2 ballPosition2;
    ballPosition2.x = 100;
    ballPosition2.y = 600;
    
    Vector2 ballSpeed;
    ballSpeed.x = 10.0f;
    ballSpeed.y = 10.0f;
    
    Vector2 ballPositionL8;
    ballPositionL8.x = screenWidth/2;
    ballPositionL8.y = screenHeight/2;
    
    Vector2 ballPosition4;
    ballPosition4.x = 100;
    ballPosition4.y = 50;
    
    Vector2 ballSpeed4;
    ballSpeed4.x = -10.0f;
    ballSpeed4.y = -10.0f;
    
    Vector2 ballPositionL9;
    ballPositionL9.x = screenWidth/2;
    ballPositionL9.y = screenHeight/2;
    
    Vector2 ballSpeed5;
    ballSpeed5.x = 6.0f;
    ballSpeed5.y = 6.0f;
    
    Vector2 ballPosition5;
    ballPosition5.x = screenWidth/2;
    ballPosition5.y = screenHeight/2;
    
    Vector2 ballSpeed3;
    ballSpeed3.x = 20.0f;
    ballSpeed3.y = 20.0f;
    
    //Radius
    float ballRadius = 30.0f;
    float ballRadius2 = 200.0f;  
    float ballRadius3 = 5;
    float ballRadius4 = 5;
    float ballRadius5 = 5;
    int radius = 0; 
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {   
        
        // Update
        //----------------------------------------------------------------------------------
        switch (currentScreen)
        {
            case LOGO:
            {
                framesCounter++;
                if(framesCounter < 90)
                {
                    logoAlpha+=0.01111111;
                }
                if(framesCounter > 90 && framesCounter < 210) logoAlpha = 1.0f;
                if(framesCounter > 210) logoAlpha -=0.01111111;
                if(framesCounter == 300 ) 
                {
                    framesCounter = 0;
                    currentScreen = TITLE;
                }
                if(framesCounter == 10) PlaySound(logosound);
            } break;
            case TITLE:
            {   
               StopMusicStream(song);
               StopMusicStream(winsong);
               StopMusicStream(losesong);
               restart = false;
               logoAlpha+=0.01;
               lives = 3;
               framesCounter++;
               if(framesCounter > 0 && framesCounter < 150 && framesCounter) title1PositionY+=2;
               if(framesCounter > 170 && framesCounter < 320 && framesCounter) title2PositionY+=2;
               if(framesCounter > 290 && framesCounter < 440 && framesCounter) title3PositionY+=2;
                          
            //BUTTON SYSTEM: START
                if(framesCounter > 60 && buttonStartMoveX < screenWidth/2 - buttonStart.width/2 ) buttonStartMoveX+=2;
                Vector2 currentStartPos = {buttonStartMoveX, screenHeight/2};
                buttonStartPosition = currentStartPos;
                
                if(framesCounter > 60 && buttonExitMoveX > screenWidth/2 - buttonExit.width/2 ) buttonExitMoveX-=2;
                Vector2 currentExitPos = {buttonExitMoveX, screenHeight/2+200};
                buttonExitPosition = currentExitPos;
                    
                if(CheckCollisionPointRec(GetMousePosition(),(Rectangle){buttonStartPosition.x, buttonStartPosition.y, buttonStartFrame.width, buttonStartFrame.height}))//Comprobamos el punto que ueremos comprovar
                {
                    buttonStartFrame.y = buttonStart.height/3;
                    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                    {
                        buttonStartFrame.y = (buttonStart.height/3*2);
                    }
                    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        currentScreen = GAMEPLAY;
                        level = 1;
                        logoAlpha = 0;
                        framesCounter = 0;
                        lives=3;
                    }                  
                }
                else buttonStartFrame.y = 0;
                
                 //BUTTON SYSTEM: ABOUT
                if(CheckCollisionPointRec(GetMousePosition(),(Rectangle){buttonAboutPosition.x, buttonAboutPosition.y, buttonAboutFrame.width, buttonAboutFrame.height}))//Comprobamos el punto que ueremos comprovar
                {
                    buttonAboutFrame.y = buttonAbout.height/3;
                    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                    {
                        buttonAboutFrame.y = (buttonAbout.height/3*2);
                    }
                    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        currentScreen = ABOUT;
                    }  
                }
                else buttonAboutFrame.y = 0;
                
                 //BUTTON SYSTEM: EXIT
                if(CheckCollisionPointRec(GetMousePosition(),(Rectangle){buttonExitPosition.x, buttonExitPosition.y, buttonExitFrame.width, buttonExitFrame.height}))//Comprobamos el punto que ueremos comprovar
                {
                    buttonExitFrame.y = buttonExit.height/3;
                    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                    {
                        buttonExitFrame.y = (buttonExit.height/3*2);
                    }
                    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        CloseWindow();
                    }  
                }
                else buttonExitFrame.y = 0;
                UpdateMusicStream(menusong);
            } break;
            case ABOUT:
            {
                //BUTTON SYSTEM: ABOUT
                if(CheckCollisionPointRec(GetMousePosition(),(Rectangle){buttonBackPosition.x, buttonBackPosition.y, buttonBackFrame.width, buttonBackFrame.height}))//Comprobamos el punto que ueremos comprovar
                {
                    buttonBackFrame.y = buttonBack.height/3;
                    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                    {
                        buttonBackFrame.y = (buttonBack.height/3*2);
                    }
                    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    {
                        restart = true;
                    }
                }
                else buttonBackFrame.y = 0;
                
                if(restart)
                {   
                    framesCounter = 0;
                    title1PositionY = -300;
                    title2PositionY = -300;
                    title3PositionY = -300;
                    buttonExitMoveX = screenWidth;
                    buttonStartMoveX = 0-200; 
                    if (framesCounter < 60) currentScreen = TITLE;
                }
                DrawTexture(about, 0,  0 , WHITE);
                UpdateMusicStream(menusong);
            } break;
            case GAMEPLAY:
            {  
                if(pause)
                {
                    if((framesCounter/30)%2)  
                    {
                        DrawText("GAME PAUSED", screenWidth/2-180, 12, 50, LIME);
                    }
                } 
                StopMusicStream(menusong);
                framesCounter++;
                if(IsKeyPressed(KEY_P)) 
                {
                    pause = !pause; 
                }
                if(IsKeyPressed(KEY_R)) restart = true;
                if(lives < 1) 
                {
                    currentScreen = LOSE;
                    framesCounter = 0;
                }
                if(restart)
                {   
                    currentScreen = TITLE;
                    framesCounter = 0;
                    title1PositionY = -300;
                    title2PositionY = -300;
                    title3PositionY = -300;
                    buttonExitMoveX = screenWidth;
                    buttonStartMoveX = 0-200;
                    logoAlpha = 0.0f;
                    aboutAlpha = 0.0f;
                }
  
                if(!pause)
                {
                    timePlay = (float)framesCounter/60;
                    if((104.0f - timePlay) <= 0.0f)
                    {
                        timePlay = 104.0f;
                        currentScreen = LOSE;
                        framesCounter = 0;
                    }
                } 
                    switch(level)
                    {   
                        case 1: //LEVEL1
                        {   
                            if (framesCounter >0 && framesCounter < 100)
                            {
                                logoAlpha+=0.01111111;
                            }
                            if(framesCounter > 140) logoAlpha -=0.01;
                        
                            if (framesCounter > 250  && radius < 250)
                            {
                               radius+=1;
                              
                               if(pause) radius-=1;
                            }
                            if(radius == 250)
                            {
                                lives-=1;
                                radius =0;
                                PlaySound(loselive);
                                
                            }
                            if(IsKeyPressed(KEY_SPACE) && radius > 200 && radius < 250) 
                            {
                                framesCounter = 0;
                                level = 2;
                                radius = 0;
                                lives++;
                                logoAlpha=0;
                                PlaySound(nextlevel);
                            } 
                            if(IsKeyPressed(KEY_SPACE) && radius < 200) 
                            {
                                lives--;
                            }
                        }break;
                        case 2: //LEVEL2
                        {   
                            if (framesCounter >0 && framesCounter < 100)
                            {
                                logoAlpha+=0.01111111;
                            }
                            if(framesCounter > 140) logoAlpha -=0.01;
                            if(!pause)
                            {
                                recLevel2.y += barSpeedY;
                                if(((recLevel2.y + 60) > screenHeight -100) || (recLevel2.y < 100)) 
                                {
                                    barSpeedY *= -1;
                                }
                                if(IsKeyPressed(KEY_SPACE) && !(recLevel2.y  > 100 && recLevel2.y+150  < 450 && recLevel2.y ))
                                {
                                    lives--;
                                    PlaySound(loselive);
                                }                                
                                if (IsKeyPressed(KEY_SPACE))
                                {
                                    if(recLevel2.y  > 100 && recLevel2.y+150  < 450 && recLevel2.y )
                                    {
                                        level = 3;
                                        ballRadius = 30;
                                        framesCounter = 0;
                                        PlaySound(nextlevel);
                                        logoAlpha=0;
                                    }
                                }
                            }
                        }break;
                        case 3://LEVEL3
                        {
                            if(framesCounter >0 && framesCounter < 100)
                            {
                                logoAlpha+=0.01111111;
                            }
                            if(framesCounter > 140) logoAlpha -=0.01;
                            if(!pause)
                            {
                                ballPosition.x += ballSpeed.x;
                                ballPosition.y += ballSpeed.y;
                                if(((ballPosition.x + ballRadius) > screenWidth) || ((ballPosition.x - ballRadius) < 0)) 
                                {
                                    ballSpeed.x *= -1;
                                    if(framesCounter > 230)PlaySound(bouncing);
                                }
                                if(((ballPosition.y + ballRadius) > screenHeight) || ((ballPosition.y - ballRadius) < 0)) 
                                {
                                    ballSpeed.y *= -1;
                                    if(framesCounter > 230)PlaySound(bouncing);
                                }
                                if(CheckCollisionCircleRec(ballPosition, ballRadius, box))
                                {
                                    boxColor = color3;
                                    if(framesCounter > 230) PlaySound(collision);
                                    if(IsKeyPressed(KEY_SPACE))
                                    {
                                        level = 4;
                                        framesCounter = 0;
                                        PlaySound(nextlevel);
                                        logoAlpha=0;
                                    }
                                }
                                else boxColor = color2;
                                if((IsKeyPressed(KEY_SPACE) && (!CheckCollisionCircleRec(ballPosition, ballRadius, box))))
                                {
                                        lives--;
                                        PlaySound(loselive);
                                }
                            }
                        }break;
                        case 4://LEVEL4
                        {
                            if(framesCounter >0 && framesCounter < 100)
                            {
                                logoAlpha+=0.01111111;
                            }
                            if(framesCounter > 140) logoAlpha -=0.01;
                            if(!pause)
                            {
                                bar2.y += barSpeedY;
                                bar3.y += bar3SpeedY;
                                if(((bar2.y + 60) > screenHeight -100) || (bar2.y < 100)) 
                                {
                                    barSpeedY *= -1;
                                }
                                if(((bar3.y + 60) > screenHeight -100) || (bar3.y < 100)) 
                                {
                                    bar3SpeedY *= -1;
                                }
                                if(IsKeyPressed(KEY_SPACE)) 
                                {
                                   shot = true;
                                   bar4.x = bar2.x;
                                   bar4.y = bar2.y;
                                   PlaySound(shotsound);
                                } 
                                if(shot)
                                {
                                    DrawRectangle(bar4.x, bar4.y, bar4.width, bar4.height, color3);
                                    bar4.x += bar4SpeedX;
                                }
                                if(CheckCollisionRecs(bar4, bar3))
                                {
                                    if(framesCounter > 230) PlaySound(collision);
                                    DrawText("WIN", screenWidth/2-20, screenHeight/2, 50, WHITE);
                                    framesCounter = 0;
                                    shot = false;
                                    logoAlpha=0;
                                    level = 5;
                                    PlaySound(nextlevel);
                                }
                                if(bar4.x > screenWidth)
                                {
                                    shot = false;
                                    bar4.x = screenWidth/2-500;
                                    lives--;
                                    PlaySound(loselive);
                                }
                            }
                        }break;
                        case 5: //LEVEL5
                        {   
                            if(framesCounter >0 && framesCounter < 100)
                            {
                                logoAlpha+=0.01111111;
                            }
                            if(framesCounter > 140) logoAlpha -=0.01;
                            if(!pause)
                            {
                                bar5.x += bar5SpeedX;
                                bar6.x -= bar6SpeedX;
                                bar8.x += bar8SpeedX;
                                if(bar8.x < 0 || bar8.x+bar8.width > screenWidth)
                                {
                                    bar8SpeedX *= -1;
                                }
                                if(((bar5.x) < 0)|| bar5.x +bar5.width > screenWidth/2 )
                                {
                                    bar5SpeedX *= -1;
                                }
                                if(((bar6.x + bar6.width) > screenWidth)|| bar6.x < screenWidth/2 )
                                {
                                    bar6SpeedX *= -1;
                                }
                                if(IsKeyPressed(KEY_SPACE)) 
                                {
                                   shot = true;
                                   bar7.x = bar8.x+100;
                                   bar7.y = bar8.y;
                                   PlaySound(shotsound);
                                } 
                                if(shot)
                                {
                                    DrawRectangle(bar7.x, bar7.y, bar7.width, bar7.height, RED);
                                    bar7.y -= bar7SpeedY;
                                }
                                if(CheckCollisionRecs(bar7, bar9))
                                {
                                    framesCounter = 0;
                                    shot = false;
                                    logoAlpha=0;
                                    ballRadius = 0;
                                    level = 6;
                                    PlaySound(nextlevel);
                                }
                                if(CheckCollisionRecs(bar5, bar8))
                                {
                                    lives--;
                                    bar7.x = screenWidth;
                                    PlaySound(loselive);
                                }
                                if(CheckCollisionRecs(bar6, bar8))
                                {
                                    lives--;
                                    bar7.x = screenWidth;
                                    PlaySound(loselive);
                                }
                                if(bar7.y < 0)
                                {
                                    bar7.y = screenHeight/2-200;
                                    lives--;
                                    shot = false;
                                    PlaySound(loselive);
                                }
                            }
                        }break;
                        case 6: //LEVEL6
                        {   
                            if(framesCounter >0 && framesCounter < 100)
                            {
                                logoAlpha+=0.01111111;
                            }
                            if(framesCounter > 140) logoAlpha -=0.01;
                            if(!pause)
                            {
                                if(framesCounter >0 && framesCounter < 100)
                                {
                                    logoAlpha+=0.01111111;
                                }
                                if(framesCounter > 140) logoAlpha -=0.01;
                                if (framesCounter > 250  && ballRadius < 150)
                                {
                                   ballRadius+=1;
                                  
                                   if(pause) radius-=1;
                                }
                                if(ballRadius == 150)
                                {
                                    lives-=1;
                                    ballRadius =0;
                                }
                                if(IsKeyPressed(KEY_SPACE) && ballRadius > 130 && ballRadius < 150 ) 
                                {
                                    framesCounter = 0;
                                    level = 7;
                                    radius = 0;
                                    PlaySound(nextlevel);
                                    logoAlpha=0;
                                } 
                                if(IsKeyPressed(KEY_SPACE) && ballRadius < 130) 
                                {
                                    lives--;
                                    PlaySound(loselive);
                                }
                                if(IsKeyPressed(KEY_SPACE) && ballRadius > 130 && ballRadius < 150 ) 
                                {
                                    DrawText("WIN", screenWidth/2-100, screenHeight/2, 50, BLUE); 
                                } 
                                ballPositionL6.x += ballSpeed.x;
                                if(((ballPositionL6.x + 150) > screenWidth) || ((ballPositionL6.x - 150) < 0)) 
                                {
                                    ballSpeed.x *= -1;
                                }
                            }    
                        }break;
                        case 7:
                        {
                            if(framesCounter >0 && framesCounter < 100)
                            {
                                logoAlpha+=0.01111111;
                            }
                            if(framesCounter > 140) logoAlpha -=0.01;
                            if(!pause)
                            {
                               ballPosition.x += ballSpeed3.x;
                               ballPosition.y += ballSpeed3.y; 
                            }
                            if(((ballPosition.x + ballRadius3) > screenWidth) || ((ballPosition.x - ballRadius3) < 0)) 
                            {
                                ballSpeed3.x *= -1;
                                if(framesCounter > 230)PlaySound(bouncing);
                            }
                            if(((ballPosition.y + ballRadius3) > screenHeight) || ((ballPosition.y - ballRadius3) < 0)) 
                            {
                                ballSpeed3.y *= -1;
                                if(framesCounter > 230)PlaySound(bouncing);
                            }
                            if(CheckCollisionCircleRec(ballPosition, ballRadius3, box))
                            {
                                boxColor = color3;
                                if(framesCounter > 230) PlaySound(collision);
                                if(IsKeyPressed(KEY_SPACE))
                                {
                                    level = 8;
                                    PlaySound(nextlevel);
                                    framesCounter = 0;
                                    ballPosition.x = screenWidth/2;
                                    ballPosition.y = screenHeight/2;
                                    logoAlpha=0;
                                }
                            }
                            else boxColor = color2;
                            if((IsKeyPressed(KEY_SPACE) && (!CheckCollisionCircleRec(ballPosition, ballRadius3, box))))
                            {
                                    lives--;
                                    PlaySound(loselive);
                            }
                        }break;
                        case 8: //LEVEL2 Rectangle in zone
                        {   
                            if(framesCounter >0 && framesCounter < 100)
                            {
                                logoAlpha+=0.01111111;
                            }
                            if(framesCounter > 140) logoAlpha -=0.01;
                            if(!pause)
                            {
                                ballPositionL8.y += ballSpeed3.y;
                                if(((ballPositionL8.y + ballRadius3) > screenHeight) || ((ballPositionL8.y - ballRadius3) < 0)) 
                                {
                                    ballSpeed3.y *= -1;
                                    if(framesCounter > 230)PlaySound(bouncing);
                                }
                                if(CheckCollisionCircleRec(ballPositionL8, ballRadius3, box3))
                                {
                                    boxColor = color3;
                                    if(framesCounter > 230) PlaySound(collision);
                                    if(IsKeyPressed(KEY_SPACE))
                                    {
                                        level = 9;
                                        framesCounter = 0;
                                        PlaySound(nextlevel);
                                        logoAlpha=0;
                                    }
                                }
                                else boxColor = color2;
                                if((IsKeyPressed(KEY_SPACE) && (!CheckCollisionCircleRec(ballPositionL8, ballRadius3, box3))))
                                {
                                    lives--;
                                    if(framesCounter > 230)PlaySound(bouncing);
                                } 
                            }
                        }break;
                        case 9: //PULSE 1 tecla
                        {   
                            if(framesCounter >0 && framesCounter < 100)
                            {
                                logoAlpha+=0.01111111;
                            }
                            if(framesCounter > 140) logoAlpha -=0.01;
                            if(!pause)
                            {
                                bar.y += barSpeedY;
                                if(((bar.y + 60) > screenHeight -100) || (bar.y < 100)) 
                                {
                                    barSpeedY *= -1;
                                }
                                ballPositionL9.x += ballSpeed.x;
                                ballPositionL9.y += ballSpeed.y;
                                if(((ballPositionL9.x + ballRadius3) > screenWidth) || ((ballPositionL9.x - ballRadius3) < 0)) 
                                {
                                    ballSpeed.x *= -1;
                                    if(framesCounter > 230)PlaySound(bouncing);
                                }
                                if (((ballPositionL9.y + ballRadius3) > screenHeight) || ((ballPositionL9.y - ballRadius3) < 0)) 
                                {
                                    ballSpeed.y *= -1;
                                    if(framesCounter > 230)PlaySound(bouncing);
                                }
                                if(CheckCollisionCircleRec(ballPositionL9, ballRadius3, bar))
                                {
                                    boxColor = color3;
                                    if(framesCounter > 230) PlaySound(collision);
                                    if(IsKeyPressed(KEY_SPACE))
                                    {
                                        level = 10;
                                        framesCounter = 0;
                                        PlaySound(nextlevel);
                                        logoAlpha=0;
                                    }                                    
                                }
                                else boxColor = color2;
                                if(IsKeyPressed(KEY_SPACE))
                                {
                                    lives--;
                                    PlaySound(loselive);
                                }                                
                            }
                        }break;
                        case 10: 
                        {   
                            if(framesCounter >0 && framesCounter < 100)
                            {
                                logoAlpha+=0.01111111;
                            }
                            if(framesCounter > 140) logoAlpha -=0.01;                        
                            if(!pause)
                            {
                                ballPosition4.x += ballSpeed4.x;
                                ballPosition4.y += ballSpeed4.y;            
                                if(((ballPosition4.x + ballRadius4) > screenWidth) || ((ballPosition4.x - ballRadius4) < 0)) 
                                {
                                    ballSpeed4.x *= -1;
                                    if(framesCounter > 230)PlaySound(bouncing);
                                }
                                if(((ballPosition4.y + ballRadius4) > screenHeight) || ((ballPosition4.y - ballRadius4) < 0)) 
                                {
                                    ballSpeed4.y *= -1;
                                    if(framesCounter > 230)PlaySound(bouncing);
                                } 
                                ballPosition5.x += ballSpeed5.x;
                                ballPosition5.y += ballSpeed5.y;            
                                if(((ballPosition5.x + ballRadius5) > screenWidth) || ((ballPosition5.x - ballRadius5) < 0)) 
                                {
                                    ballSpeed5.x *= -1;
                                    if(framesCounter > 230)PlaySound(bouncing);
                                }
                                if(((ballPosition5.y + ballRadius5) > screenHeight) || ((ballPosition5.y - ballRadius5) < 0)) 
                                {
                                    ballSpeed5.y *= -1;
                                    if(framesCounter > 230)PlaySound(bouncing);
                                }
                                if(CheckCollisionCircles(ballPosition4, ballRadius4, ballPosition5, ballRadius5))
                                {
                                    ballColor = color3;
                                    if(framesCounter > 230) PlaySound(collision);
                                    if (IsKeyPressed(KEY_SPACE))
                                    {
                                        framesCounter = 0;
                                        currentScreen = WIN;
                                        logoAlpha=0;
                                    }
                                }
                                else ballColor = color1;                                
                                if(IsKeyPressed(KEY_SPACE) && (!CheckCollisionCircles(ballPosition4, ballRadius4, ballPosition5, ballRadius5)))
                                {
                                        
                                        PlaySound(loselive);
                                        lives--;
                                }
                            }
                        }break;
                    }
            UpdateMusicStream(song);
            } break;
            case LOSE:
            {
                
            } break;
            case WIN:
            {
  
            } break;
            default: break;
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            switch (currentScreen)
            {
                case LOGO:
                {
                    DrawTexture(logo, screenWidth/2 - logo.width/2,  screenHeight/2 - logo.height/2, Fade(WHITE, logoAlpha));
                    
                } break;
                case TITLE:
                {
                    DrawTexture(background, 0, 0, Fade(WHITE, logoAlpha));
                    DrawTextureRec(buttonStart, buttonStartFrame, buttonStartPosition, WHITE);
                    DrawTextureRec(buttonAbout, buttonAboutFrame, buttonAboutPosition, Fade(WHITE, aboutAlpha));
                    aboutAlpha+=0.005;
                    DrawTextureRec(buttonExit, buttonExitFrame, buttonExitPosition, WHITE);
                    if(framesCounter < 500)
                    {
                        DrawTexture(title1, screenWidth/2 -title1.width/2, title1PositionY, WHITE);
                        DrawTexture(title2, screenWidth/2 -title1.width/2, title2PositionY, WHITE);                    
                        DrawTexture(title3, screenWidth/2 -title1.width/2, title3PositionY, WHITE);
                    }
                    DrawText("(c) Developed by Javier Sabariego", screenWidth/2-170, 699, 20, color1);
                    if((framesCounter/30)%2 && framesCounter > 500 && framesCounter < 660) DrawTexture(titlefinal, screenWidth/2 -titlefinal.width/2, 60, WHITE);
                    if(framesCounter > 650) DrawTexture(titlefinal, screenWidth/2 -titlefinal.width/2, 60, WHITE);
                } break;
                case ABOUT:
                {
                    DrawTextureRec(buttonBack, buttonBackFrame, buttonBackPosition, WHITE);
                }break;
                case GAMEPLAY:
                {   
                    if(framesCounter > 245) DrawText(FormatText("%02.2f", (104.0f - timePlay)),screenWidth/2-60, 670, 50, RED);
                    switch(level)
                    {
                        case 1: //LEVEL1
                        {   
                            DrawTexture(level1,0 ,0 ,Fade(WHITE, logoAlpha));
                            DrawTextEx(textfont, "(C)", (Vector2){ 1220, 40},40, 2, color1);
                            DrawText("1/10", 10, 680, 40, BLUE);
                            if(lives == 3) DrawText("LIVES: 3", 10, 10, 40, BLUE);
                            if(lives == 2) DrawText("LIVES: 2", 10, 10, 40, BLUE);
                            if(lives == 1) DrawText("LIVES: 1", 10, 10, 40, BLUE);
                            if(framesCounter > 250)
                            {   
                                DrawCircle(screenWidth/2, screenHeight/2, 250, color2);
                                DrawCircle(screenWidth/2, screenHeight/2, 200, BLACK);
                                DrawCircle(screenWidth/2, screenHeight/2, radius, color1);
                            }
                            if(IsKeyPressed(KEY_SPACE) && radius > 200 && radius < 250 ) 
                            {
                                DrawText("WIN", screenWidth/2-100, screenHeight/2, 50, BLUE); 
                            } 
                        }break;
                        case 2: //LEVEL2
                        {   
                            DrawTexture(level2,0 ,0 ,Fade(WHITE, logoAlpha));
                            DrawTextEx(textfont, "(C)", (Vector2){ 1220, 40},40, 2, color1);
                            DrawText("2/10", 10, 680, 40, BLUE);
                            if (lives == 3) DrawText("LIVES: 3", 10, 10, 40, BLUE);
                            if (lives == 2) DrawText("LIVES: 2", 10, 10, 40, BLUE);
                            if (lives == 1) DrawText("LIVES: 1", 10, 10, 40, BLUE);
                            if(framesCounter > 250)
                            {   
                                DrawRectangle(screenWidth/2-150, 100, 300, 150, color2);
                                DrawRectangle(recLevel2.x, recLevel2.y, recLevel2.width, recLevel2.height, color1);
                            }  
                        }break;
                        case 3: //LEVEL3
                        {   
                            DrawTexture(level3,0 ,0 ,Fade(WHITE, logoAlpha));
                            DrawTextEx(textfont, "(C)", (Vector2){ 1220, 40},40, 2, color1);
                            DrawText("3/10", 10, 680, 40, BLUE);
                            if (lives == 3) DrawText("LIVES: 3", 10, 10, 40, BLUE);
                            if (lives == 2) DrawText("LIVES: 2", 10, 10, 40, BLUE);
                            if (lives == 1) DrawText("LIVES: 1", 10, 10, 40, BLUE);
                            if(framesCounter > 250)
                            {   
                                DrawCircleV(ballPosition, ballRadius, color1);
                                DrawRectangle(box.x, box.y, box.width, box.height, boxColor);
                            }
                        }break;
                        case 4: //LEVEL4
                        {   
                            DrawTexture(level4,0 ,0 ,Fade(WHITE, logoAlpha));
                            DrawTextEx(textfont, "(C)", (Vector2){ 1220, 40},40, 2, color1);
                            DrawText("4/10", 10, 680, 40, BLUE);
                            if (lives == 3) DrawText("LIVES: 3", 10, 10, 40, BLUE);
                            if (lives == 2) DrawText("LIVES: 2", 10, 10, 40, BLUE);
                            if (lives == 1) DrawText("LIVES: 1", 10, 10, 40, BLUE);
                            if(framesCounter > 250)
                            {   
                                DrawRectangle(bar2.x, bar2.y, bar2.width, bar2.height, color1);
                                DrawRectangle(bar3.x, bar3.y, bar3.width, bar3.height, color2);
                                DrawRectangle(bar2.x+20, bar2.y+30, 60,20, color1);                                
                            }
                        }break;
                        case 5: //LEVEL5
                        {   
                            DrawTexture(level5,0 ,0 ,Fade(WHITE, logoAlpha));
                            DrawTextEx(textfont, "(C)", (Vector2){ 1220, 40},40, 2, color1);
                            DrawText("5/10", 10, 680, 40, BLUE);
                            if (lives == 3) DrawText("LIVES: 3", 10, 10, 40, BLUE);
                            if (lives == 2) DrawText("LIVES: 2", 10, 10, 40, BLUE);
                            if (lives == 1) DrawText("LIVES: 1", 10, 10, 40, BLUE);
                            if(framesCounter > 250)
                            {   
                                DrawRectangle(bar5.x, bar5.y, bar5.width,bar5.height, color2);
                                DrawRectangle(bar6.x, bar6.y, bar6.width, bar6.height, color2);
                                DrawRectangle(bar8.x, bar8.y, bar8.width, bar8.height, color1);
                                DrawRectangle(bar8.x+bar8.width/2-10, bar8.y-20, 20,60, color1);
                                DrawRectangle(bar9.x, bar9.y, bar9.width,bar9.height, color3);
                            }                             
                        }break;
                        case 6: //LEVEL6
                        {   
                            DrawTexture(level6,0 ,0 ,Fade(WHITE, logoAlpha));
                            DrawTextEx(textfont, "(C)", (Vector2){ 1220, 40},40, 2, color1);
                            DrawText("6/10", 10, 680, 40, BLUE);
                            if (lives == 3) DrawText("LIVES: 3", 10, 10, 40, BLUE);
                            if (lives == 2) DrawText("LIVES: 2", 10, 10, 40, BLUE);
                            if (lives == 1) DrawText("LIVES: 1", 10, 10, 40, BLUE);
                            if(framesCounter > 250)
                            {   
                                DrawCircleV(ballPositionL6, 150, LIME);   
                                DrawCircleV(ballPositionL6, 130, BLACK);                                
                                DrawCircleV(ballPositionL6, ballRadius, BLUE);
                            }
                        }break;
                        case 7: //LEVEL7
                        {   
                            DrawTexture(level7, 0, 0,Fade(WHITE, logoAlpha));
                            DrawTextEx(textfont, "(C)", (Vector2){ 1220, 40},40, 2, color1);
                            DrawText("7/10", 10, 680, 40, BLUE);
                            if (lives == 3) DrawText("LIVES: 3", 10, 10, 40, BLUE);
                            if (lives == 2) DrawText("LIVES: 2", 10, 10, 40, BLUE);
                            if (lives == 1) DrawText("LIVES: 1", 10, 10, 40, BLUE);
                            if(framesCounter > 250)
                            {   
                                DrawCircleV(ballPosition, ballRadius3, color1);
                                DrawRectangle(box2.x, box2.y, box2.width, box2.height, boxColor);
                            }
                        }break;
                        case 8: //LEVEL7
                        {   
                            DrawTexture(level8,0 ,0 ,Fade(WHITE, logoAlpha));
                            DrawTextEx(textfont, "(C)", (Vector2){ 1220, 40},40, 2, color1);
                            DrawText("8/10", 10, 680, 40, BLUE);
                            if (lives == 3) DrawText("LIVES: 3", 10, 10, 40, BLUE);
                            if (lives == 2) DrawText("LIVES: 2", 10, 10, 40, BLUE);
                            if (lives == 1) DrawText("LIVES: 1", 10, 10, 40, BLUE);
                            if(framesCounter > 250)
                            {   
                                if ((framesCounter/30)%2) DrawCircleV(ballPositionL8, ballRadius3, color1);
                                DrawRectangle(box3.x, box3.y, box3.width, box3.height, boxColor);
                            }  
                        }break;
                        case 9: //LEVEL9
                        {   
                            DrawTexture(level9,0 ,0 ,Fade(WHITE, logoAlpha));
                            DrawTextEx(textfont, "(C)", (Vector2){ 1220, 40},40, 2, color1);
                            DrawText("9/10", 10, 680, 40, BLUE);
                            if (lives == 3) DrawText("LIVES: 3", 10, 10, 40, BLUE);
                            if (lives == 2) DrawText("LIVES: 2", 10, 10, 40, BLUE);
                            if (lives == 1) DrawText("LIVES: 1", 10, 10, 40, BLUE);
                            if(framesCounter > 250)
                            {   
                                DrawCircleV(ballPositionL9, ballRadius3, BLUE);
                                DrawRectangle(bar.x, bar.y, bar.width, bar.height, boxColor);
                            }
                        }break;
                        case 10: //LEVEL10
                        {   
                            DrawTexture(level10,0 ,0 ,Fade(WHITE, logoAlpha));
                            DrawTextEx(textfont, "(C)", (Vector2){ 1220, 40},40, 2, color1);
                            DrawText("10/10", 10, 680, 40, BLUE);
                            if (lives == 3) DrawText("LIVES: 3", 10, 10, 40, BLUE);
                            if (lives == 2) DrawText("LIVES: 2", 10, 10, 40, BLUE);
                            if (lives == 1) DrawText("LIVES: 1", 10, 10, 40, BLUE);
                            if(framesCounter > 250)
                            {   
                                DrawCircleV(ballPosition4, ballRadius4, ballColor);
                                DrawCircleV(ballPosition5, ballRadius5, ballColor);
                            }  
                        }break;
                    }
                } break;
                case WIN:
                {
                    framesCounter++;
                    DrawTexture(background, 0, 0, WHITE); 
                    if ((framesCounter/30)%2) DrawTexture(win, 0, 0, WHITE);  
                    DrawTexture(restartscreen, 0, 0, WHITE);                    
                    if (IsKeyPressed(KEY_R)) restart = true;
                    if (restart)
                    {   
                        framesCounter = 0;
                        title1PositionY = -300;
                        title2PositionY = -300;
                        title3PositionY = -300;
                        buttonExitMoveX = screenWidth;
                        buttonStartMoveX = 0-200; 
                        if (framesCounter < 60) currentScreen = TITLE;
                    }
                 UpdateMusicStream(winsong);   
                } break;
                case LOSE:
                {
                    framesCounter++;
                    DrawTexture(background, 0, 0, WHITE);
                    if ((framesCounter/30)%2) DrawTexture(lose, 0, 0, WHITE);
                    DrawTexture(restartscreen, 0, 0, WHITE);
                    if (IsKeyPressed(KEY_R)) restart = true;
                    if (restart)
                    {   
                        framesCounter = 0;
                        title1PositionY = -300;
                        title2PositionY = -300;
                        title3PositionY = -300;
                        buttonExitMoveX = screenWidth;
                        buttonStartMoveX = 0-200; 
                        if (framesCounter < 60) currentScreen = TITLE;
                    }
                UpdateMusicStream(losesong);
                } break;
                default: break;
            }
                ClearBackground(BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // Unload textures
    UnloadTexture(logo);
    UnloadTexture(background);
    UnloadTexture(title1);
    UnloadTexture(title2);
    UnloadTexture(title3);
    UnloadTexture(win);
    UnloadTexture(lose);
    UnloadTexture(titlefinal);
    UnloadTexture(level1);
    UnloadTexture(level2);
    UnloadTexture(level3);
    UnloadTexture(level4);
    UnloadTexture(level5);
    UnloadTexture(level6);
    UnloadTexture(level7);
    UnloadTexture(level8);
    UnloadTexture(level9);
    UnloadTexture(level10);
    UnloadTexture(fondo);
    UnloadTexture(buttonStart);     
    UnloadTexture(buttonAbout);
    UnloadTexture(buttonExit); 
    UnloadTexture(buttonBack); 
    UnloadTexture(about);   
    UnloadTexture(restartscreen);
    //Unload sounds and musics
    UnloadSound(logosound);
    UnloadSound(bouncing);
    UnloadSound(loselive);
    UnloadMusicStream(song);
    UnloadMusicStream(menusong);
    UnloadMusicStream(winsong);
    UnloadMusicStream(losesong);
    UnloadSound(collision);
    UnloadSound(shotsound);
    UnloadSound(nextlevel);
    CloseAudioDevice();
    
    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}