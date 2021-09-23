#include "raylib.h"

#include "GameScreen2.h"
#include "MenuScreen.h"
#include "game.h"
#include "Game Over.h"
#include "StopScreen.h"



extern int highscore;

extern Player player;

extern int activeEnemies;

extern Enemy enemy[NUM_MAX_ENEMIES];

extern int activeEnemies2;

extern Enemy enemy2[NUM_MAX_ENEMIES];

extern bool ScreenChangeto1;

extern bool ScreenChangeto2;

extern  Bullet bullet[NUM_SHOOTS];

extern Asteroid asteroid[NUM_MAX_ASTEROIDS];

extern int activeAsteroids;

extern Boss boss[NUM_MAX_ENEMIES];

extern int hits;

extern int activeEnemies3;

extern bool BossMoving;

extern Rectangle StopBoss;

extern Bullet bullet2[NUM_SHOOTS];

extern int framescounter;

extern Flotte flotte[NUM_SHOOTS];

extern int framescounter2;

extern int framescounter3;

extern int seconds;

extern int minutes;

extern bool changeto2;
extern bool changeto1;

extern Planet planet;


Game::GameScreen2::GameScreen2() {
    // Your screen initialization code here...
    Vector2 vec = { 100.0f, 100.0f };
    this->sprites.push_back(
        std::make_unique<Game::Sprite>(LoadTexture("assets/graphics/background.png"),
            vec,
            true)
    );


    ScreenChangeto2 = false;

    //Texuren Umgebung
    background2 = LoadTexture("assets/graphics/background2.png");
    Planet1 = LoadTexture("assets/graphics/planet1.png");
    Planet3 = LoadTexture("assets/graphics/planet12.png");
    Spaces = LoadTexture("assets/graphics/Spaces.png");
    Lives = LoadTexture("assets/graphics/Lives.png");


    //Planet initialisieren

    planet.position2.x = 1000 / 2;
    planet.position2.y = 1175;
    planet.radius = 350;



    // Load Asteroid texture
    asteroidtexture = LoadTexture("assets/graphics/asteroid.png");

    

    bullettext = LoadTexture("assets/graphics/bullet.png");


    //Planet initialisieren

    planet.position.x = 1000 / 2;
    planet.position.y = 1175;
    planet.radius = 350;



    //Spieler initialisieren
    // Load player ship texture
    playerTexture = LoadTexture("assets/graphics/player2.png");

   

    bullettext2 = LoadTexture("assets/graphics/bullet.png");

  


    // Load Boss ship texture
    BossTexture = LoadTexture("assets/graphics/BossTop.png");

    waveTop = LoadTexture("assets/graphics/streifen2.png");
    change2 = LoadTexture("assets/graphics/change2.png");
    // Gegner initialisieren

    // Load alien ship texture
    alienTexture = LoadTexture("assets/graphics/alien2.png");
    alienTexture2 = LoadTexture("assets/graphics/Test2.png");

   
}


Game::GameScreen2::~GameScreen2() {
    // Your screen cleanup code here...
    UnloadTexture(sprites[0]->texture);
    UnloadTexture(background2);
    UnloadTexture(playerTexture);
    UnloadTexture(alienTexture);
    UnloadTexture(alienTexture2);
    UnloadTexture(Lives);
    UnloadTexture(Spaces);
}


void Game::GameScreen2::ProcessInput() {
    // Your process input code here...
    if (IsKeyPressed(KEY_M)) currentScreen = Game::StopScreen::getInstance();

    //SWAP
    if (IsKeyPressed(KEY_TAB)) currentScreen = Game::GameScreen::getInstance();

    // Spieler bewegen (links-rechts)
    if (IsKeyDown(KEY_RIGHT))
        player.pos.w += player.speed.w;
    if (IsKeyDown(KEY_LEFT))
        player.pos.w -= player.speed.w;




}

void Game::GameScreen2::Update() {
    // Your update game code here...

    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy[i].rect.x = enemy[i].pos2.x;
        enemy[i].rect.y = enemy[i].pos2.y;
    }

    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy2[i].rect.x = enemy2[i].pos2.x;
        enemy2[i].rect.y = enemy2[i].pos2.y;
    }

    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        bullet[i].rect.x = bullet[i].pos2.x;
        bullet[i].rect.y = bullet[i].pos2.y;

  

        bullet2[i].rect.x = bullet2[i].pos2.x;
        bullet2[i].rect.y = bullet2[i].pos2.y;

        flotte[i].rect2.x = flotte[i].pos2.x;
        flotte[i].rect2.y = flotte[i].pos2.y;
    }

 
    for (int i = 0; i < NUM_MAX_ASTEROIDS; i++)
    {
        asteroid[i].rect.x = asteroid[i].pos2.x;
        asteroid[i].rect.y = asteroid[i].pos2.y;
    }

    player.rect.x = player.pos.w;
    player.rect.y = player.pos.z;

    for (int i = 0; i < NUM_MAX_ASTEROIDS; i++)
    {
    boss[i].rect.x = boss[i].pos2.x;
    boss[i].rect.y = boss[i].pos2.y;
    }

    if (ScreenChangeto2 == false )
    {
        for (int i = 0; i < NUM_MAX_ENEMIES; i++)
        {
            enemy[i].pos2.y = 1000 - enemy[i].pos1.x;
            enemy2[i].pos2.y = 1000 - enemy2[i].pos1.x;
        }
        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            bullet[i].pos2.y = 1000 - bullet[i].pos1.x;
            bullet2[i].pos2.y = 1000 - bullet2[i].pos1.x;
            flotte[i].pos2.y = 1000 - flotte[i].pos1.x;
           
            
        
            
            flotte[i].pos2.x = GetRandomValue(200, 730);

            if (flotte[i].active)
            {
                changeto2 = true;
                flotte[i].rect2.width = 70;
            }
        
        }

        for (int i = 0; i < NUM_MAX_ASTEROIDS; i++)
        {
            asteroid[i].pos2.y = 1000 - asteroid[i].pos1.x;
            asteroid[i].pos2.x = GetRandomValue(200, 800);
        }

        for (int i = 0; i < NUM_MAX_ENEMIES; i++)
        {
           boss[i].pos2.y = 860 - boss[i].pos1.x;
           boss[i].speed.w = -2;
        }


        ScreenChangeto2 = true;
        ScreenChangeto1 = false;
    }

   


   //# Spieler

        //Spieler an Wänden einschränken
        if ((player.pos.w) >= 850) player.pos.w = 850 - 1;
        if ((player.pos.w) <= 150) player.pos.w = 150 + 1;


        //TIMER

        if (BossMoving == true) {

            framescounter3++;
        }

        if (seconds == -1)
        {
            seconds = 59;
            minutes--;
        }

        //SECONDS
           // Every two seconds (120 frames) a new random value is generated
        if (((framescounter3 / 60) % 2) == 1)
        {
            framescounter3 = 0;

            seconds--;


        }

        if (minutes == -1)
        {
            currentScreen = Game::GameOver::getInstance();
        }



        //flotte
        framescounter2++;

        // Every two seconds (120 frames) a new random value is generated
        if (((framescounter2 / 600) % 2) == 1)
        {
            changeto2 = false;
            framescounter2 = 0;


            for (int i = 0; i < 1; i++)
            {
                if (!flotte[i].active)
                {
                    // Movement

                    flotte[i].pos2.x = 0;
                    flotte[i].pos2.y = -50;
                    flotte[i].rect2.width = 1000;
                    flotte[i].active = true;

                    break;


                }
            }
        }


        if (changeto2 == true)
        {
            for (int i = 0; i < 1; i++)
            {
                flotte[i].rect2.width = 70;
            }
        }

        if (changeto2 == false)
        {
            for (int i = 0; i < 1; i++)
            {
                flotte[i].rect2.width = 1000;
            }
        }

        // Shoot logic
        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (flotte[i].active)
            {
                // Movement
                flotte[i].pos2.y += flotte[i].speed.y;

                if (flotte[i].pos2.y >= 1050) //Flotte über Screen hinaus
                {
                    flotte[i].active = false;
                }

                //Flotte 
                if (CheckCollisionRecs(flotte[i].rect2, player.rect))
                {
                   flotte[i].active = false;

                   player.lives--;

                }
            }

          

        }





        // BULLETS 2

        if (BossMoving == true)
        {
            
        framescounter++;

        // Every two seconds (120 frames) a new random value is generated
        if (((framescounter / 15) % 2) == 1)
        {

            framescounter = 0;


            for (int i = 0; i < 5; i++)
            {
                if (!bullet2[i].active)
                {
                    // Movement


                    bullet2[i].pos2.x = boss[i].pos2.x + 18;
                    bullet2[i].pos2.y = boss[i].pos2.y + 5;
                    bullet2[i].active = true;

                    break;


                }
            }
        }
        }


        // Shoot logic
        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (bullet2[i].active)
            {
                // Movement
                bullet2[i].pos2.y += bullet2[i].speed.y;

                // Kollision mit enemy
                for (int j = 0; j < activeEnemies; j++)
                {
                    if (boss[j].active)
                    {
                        //BOSSGEGNER 
                        if (CheckCollisionRecs(bullet[i].rect, boss[j].rect))
                        {
                            bullet[i].active = false;

                            boss[j].lives--;
                        }
                        //BOSSGEGNER 
                        if (CheckCollisionRecs(bullet2[i].rect, player.rect))
                        {
                            bullet2[i].active = false;

                            player.lives--;
                        }

                    }

                    if (bullet2[i].pos2.y >= 1000) //Bullet über Screen hinaus
                    {
                        bullet2[i].active = false;
                    }
                }
            }
        }



 


       

   



        // Asteroid Verhalten(Spawnverhalten)
        for (int i = 0; i < activeAsteroids; i++)
        {
            if (asteroid[i].active)
            {
                asteroid[i].pos2.x += asteroid[i].speed.y;
                asteroid[i].pos2.y += asteroid[i].speed.x;



                if (CheckCollisionRecs(player.rect, asteroid[i].rect))
                {
                    player.lives--;
                    asteroid[i].pos2.x = GetRandomValue(-60, -200);      //Spawnbereich neuer Asteroid
                    asteroid[i].pos2.y = GetRandomValue(-50, -250);

                }
            }
            if (asteroid[i].pos2.x >= 1040  || asteroid[i].pos2.y >= 1050) //asteroid über Screen hinaus
            {
                asteroid[i].pos2.x = GetRandomValue(-60, -200);      //Spawnbereich neuer Asteroid
                asteroid[i].pos2.y = GetRandomValue(-50, -250);
            }

        }




      

  //Bullets
        if (IsKeyPressed(KEY_SPACE)) {




            for (int i = 0; i < NUM_SHOOTS; i++)
            {
                if (!bullet[i].active)
                {
                    // Movement
                   

                    bullet[i].pos2.x = player.pos.w + player.rect.width / 4 +7;
                    bullet[i].pos2.y = player.pos.z + 5;
                    bullet[i].active = true;

                    break;


                }
            }
        }



        // Shoot logic
        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (bullet[i].active)
            {
                // Movement
                bullet[i].pos2.y -= bullet[i].speed.y;

                // Kollision mit enemy
                for (int j = 0; j < activeEnemies || j < activeEnemies2; j++)
                {
                    if (enemy[j].active || enemy2[j].active)
                    {
                        if (CheckCollisionRecs(bullet[i].rect, enemy[j].rect))
                        {
                            bullet[i].active = false;
                            enemy[j].pos2.x = GetRandomValue(200, 800);      //Spawnbereich neuer Gegner x
                            enemy[j].pos2.y = GetRandomValue(-150, -300);     //Spawnbereich neuer Gegner y
                            highscore++;




                        }

                        if (CheckCollisionRecs(bullet[i].rect, enemy2[j].rect))
                        {
                            bullet[i].active = false;
                          
                            enemy2[j].lives--;
                        }

                        if (enemy2[j].lives == 0)
                        {
                              highscore++;
                            enemy2[j].lives = 2;
                            enemy2[j].pos2.x = GetRandomValue(1100, 1600);      //Spawnbereich neuer Gegner x
                            enemy2[j].pos2.y = GetRandomValue(200, 672);     //Spawnbereich neuer Gegner y

                        }
                    }

                    if (bullet[i].pos2.y >= 1000) //Bullet über Screen hinaus
                    {
                        bullet[i].active = false;
                    }
                }
            }
        }



    // Spieler Kollision  mit Enemy -> verliert 1 Leben
    for (int j = 0; j < activeEnemies || j < activeEnemies2; j++)
    {
        if (enemy[j].active | enemy2[j].active)
        {
            if (CheckCollisionRecs(player.rect, enemy[j].rect))
            {
                player.lives--;
                enemy[j].pos2.x = GetRandomValue(200, 736);      //Spawnbereich neuer Gegner x
                enemy[j].pos2.y = GetRandomValue(-200, -400);     //Spawnbereich neuer Gegner y
            }
            if (CheckCollisionRecs(player.rect, enemy2[j].rect))
            {
                player.lives--;
                enemy2[j].pos2.x = GetRandomValue(200, 736);      //Spawnbereich neuer Gegner x
                enemy2[j].pos2.y = GetRandomValue(-200, -400);     //Spawnbereich neuer Gegner y
            }
        }
    }





    //UPDATE SECTION -- BOSSGEGNER

    if (highscore == 20) {
        BossMoving = true;


        for (int i = 0; i < activeEnemies || i < activeEnemies2; i++)
        {
            enemy[i].speed.z = 0;
            enemy[i].pos2.x += enemy[i].speed.w;
            enemy2[i].speed.z = 0;
            enemy2[i].pos2.x += enemy[i].speed.w;
        }
    }
    //Boss 
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {

        if (BossMoving == true) {
           
            boss[i].pos2.y += boss[i].speed.z;
            flotte[i].active = false;
        }

        boss[i].rect.x = boss[i].pos2.x;
        boss[i].rect.y = boss[i].pos2.y;


        
        boss[i].pos2.x += boss[i].speed.w;


        //// Check walls collision for bouncing
        if ((boss[i].pos2.x >= (730)) || (boss[i].pos2.x <= 200)) boss[i].speed.w *= -1.0f;
        if ((boss[i].pos2.y <= (0)) && boss[i].speed.z < 0) boss[i].speed.z *= -1.0f;

        if ((boss[i].pos2.y >= (100)))  boss[i].speed.z *= -1.0f, boss[i].pos2.x += boss[i].speed.w, boss[i].speed.z = -0.5, boss[i].speed.w = -2;







    }





    // Enemy Verhalten(Spawnverhalten)
    for (int i = 0; i < activeEnemies || i < activeEnemies2; i++)
    {
        if (enemy[i].active)
        {
            enemy[i].pos2.y +=  enemy[i].speed.z;
           
            

            if (CheckCollisionPointCircle(enemy[i].pos2, planet.position2, 350))     //         //Kollision Planet mit Enemy
            {
              enemy[i].pos2.x = GetRandomValue(200, 800);
                enemy[i].pos2.y = GetRandomValue(-150, -300);
               planet.landed--;

            }
        }

        if (enemy2[i].active)
        {
            enemy2[i].pos2.y += enemy2[i].speed.z;

            if (CheckCollisionPointCircle(enemy2[i].pos2, planet.position2, 350))    //         //Kollision Planet mit Enemy2
            {
                enemy2[i].pos2.x = GetRandomValue(200, 800);
                enemy2[i].pos2.y = GetRandomValue(-150, -300);
                planet.landed--;

            }
        }


    }

    if (boss->lives == 0) {
        currentScreen = Game::GameOver::getInstance();
    }

    if (player.lives == 0 || planet.landed == 0) {
        currentScreen = Game::GameOver::getInstance();


       /* player.lives = 3;
        planet.landed = 5;
        activeEnemies = 1;
        activeEnemies2 = 0;*/

        for (int i = 0; i < activeEnemies; i++)
        {
            boss[i].active = false;
            enemy[i].active = false;
            enemy2[i].active = false;
            asteroid[i].active = false;
            flotte[i].active = false;

        }

        for (int i = 0; i < activeEnemies; i++)
        {
            if (enemy[i].active)
            {
               /* enemy[i].active = false;
                enemy2[i].active = false;
                boss[i].active = false;*/
                enemy2[i].rect.x = GetRandomValue(1020, 2000);
                enemy[i].rect.y = GetRandomValue(200, 700);
            }
        }
    }




}



void Game::GameScreen2::Draw() {
    // Your drawing code here...
    ClearBackground(BLACK);
    //Hitbox Planet
    DrawCircleV(planet.position2, planet.radius, RED);
    //Hintergrund
    DrawTexture(background2, 0, 0, WHITE);


    //Planet1
    DrawTexture(Planet1, 150, 715, WHITE);

    //Planet3
    DrawTexture(Planet3, 95, -500, WHITE);


    //BUllet zeichnen
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (bullet[i].active)
            DrawTexture(bullettext2, bullet[i].pos2.x, bullet[i].pos2.y, WHITE);
    }

    //BUllet2 zeichnen
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (bullet2[i].active)
            /* DrawRectangleRec(bullet[i].rect, bullet[i].color);*/
            DrawTexture(bullettext2, bullet2[i].pos2.x, bullet2[i].pos2.y, WHITE);

        //Flotte zeichnen

        if (changeto2 == false)
        {
            if (flotte[i].active)
            {
                /* DrawRectangleRec(bullet[i].rect, bullet[i].color);*/
                DrawTexture(waveTop, flotte[i].pos2.x, flotte[i].pos2.y, WHITE);

            }
        }

        if (changeto2 == true)
        {
            DrawTexture(change2, flotte[i].pos2.x, flotte[i].pos2.y, WHITE);
           
        }

       
    }

 

    //Player zeichnen
    DrawTexture(playerTexture, player.pos.w, player.pos.z, WHITE);

    //Gegner zeichnen
    for (int i = 0; i < activeEnemies; i++)
    {
        if (enemy[i].active)
            DrawTexture(alienTexture, enemy[i].pos2.x, enemy[i].pos2.y, WHITE);
    }

    //Gegner2 zeichnen
    for (int i = 0; i < activeEnemies2; i++)
    {
        if (enemy2[i].active)
            DrawTexture(alienTexture2, enemy2[i].pos2.x, enemy2[i].pos2.y, WHITE);
    }

    //Asteroiden zeichnen
    for (int i = 0; i < activeAsteroids; i++)
    {
        if (asteroid[i].active)
            DrawTexture(asteroidtexture, asteroid[i].pos2.x, asteroid[i].pos2.y, WHITE);
        
    }

    //Boss zeichnen
    for (int i = 0; i < activeEnemies3; i++)
    {
        if (boss[i].active)
            DrawTexture(BossTexture, boss[i].pos2.x, boss[i].pos2.y, WHITE);
    }


    //Anzeigen
    // 
       //TIMER
    if (BossMoving == true)
    {
        DrawText("Timer", 459, 27, 30, LIGHTGRAY);
        DrawText(TextFormat("%02i:", minutes), 460, 57, 35, LIGHTGRAY);
        DrawText(TextFormat(" %02i", seconds), 493, 57, 35, LIGHTGRAY);

    }


    DrawText(" M - pause", 70, 20, 20, LIGHTGRAY);
    DrawText(" TAB - Switch Cam", 70, 60, 20, LIGHTGRAY);
    // DrawText("Lives", 415, 180, 30, RED);
     //DrawText("Space", 415, 220, 30, DARKBLUE);
    // DrawText(TextFormat("Lives: %02i", player.lives), 425, 180, 30, RED);
    // DrawText(TextFormat("Space: %02i", planet.landed), 425, 220, 25, BLUE);
    DrawText(TextFormat("Score: %02i", highscore), 820, 140, 35, LIGHTGRAY);
    //Live Anzeige
    if (player.lives == 3) {
        DrawTexture(Lives, 900, 215, WHITE);
        DrawTexture(Lives, 930, 215, WHITE);
        DrawTexture(Lives, 960, 215, WHITE);
    }
    if (player.lives == 2) {
        DrawTexture(Lives, 930, 215, WHITE);
        DrawTexture(Lives, 960, 215, WHITE);
    }
    if (player.lives == 1) {
        DrawTexture(Lives, 960, 215, WHITE);
    }

    //Space Anzeige 
    if (planet.landed == 5) {
        DrawTexture(Spaces, 820, 180, WHITE);
        DrawTexture(Spaces, 855, 180, WHITE);
        DrawTexture(Spaces, 890, 180, WHITE);
        DrawTexture(Spaces, 925, 180, WHITE);
        DrawTexture(Spaces, 960, 180, WHITE);
    }
    if (planet.landed == 4) {
        DrawTexture(Spaces, 855, 180, WHITE);
        DrawTexture(Spaces, 890, 180, WHITE);
        DrawTexture(Spaces, 925, 180, WHITE);
        DrawTexture(Spaces, 960, 180, WHITE);
    }
    if (planet.landed == 3) {
        DrawTexture(Spaces, 890, 180, WHITE);
        DrawTexture(Spaces, 925, 180, WHITE);
        DrawTexture(Spaces, 960, 180, WHITE);
    }
    if (planet.landed == 2) {
        DrawTexture(Spaces, 925, 180, WHITE);
        DrawTexture(Spaces, 960, 180, WHITE);
    }
    if (planet.landed == 1) {
        DrawTexture(Spaces, 960, 180, WHITE);
    }









}

