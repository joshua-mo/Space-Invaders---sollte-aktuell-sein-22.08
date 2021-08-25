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

    //Anzahl aktive Asteroiden 

    //activeAsteroids = 2;

    //Asteroid 



    //for (int i = 0; i < NUM_MAX_ASTEROIDS; i++)
    //{
    //    asteroid[i].rect.width = 50;
    //    asteroid[i].rect.height = 64;
    //    asteroid[i].rect.x = GetRandomValue(1060, 1200);      //Spawnbereich neuer Asteroid
    //    asteroid[i].rect.y = GetRandomValue(0, 800);
    //    asteroid[i].speed.x = 3;
    //    asteroid[i].speed.y = 1; //Geschwindigkeit Gegner
    //    asteroid[i].active = true;
    //}




    //Planet initialisieren

    planet.position.x = 1000 / 2;
    planet.position.y = 1175;
    planet.radius = 350;



    //Spieler initialisieren
    // Load player ship texture
    playerTexture = LoadTexture("assets/graphics/player2.png");

    //// Spieler (Viereck) initialisieren
    //player.rect.x = 800 / 2.0f;

    //player.rect.width = 35;
    //player.rect.height = 35;
    //player.speed.x = 7;
    //player.speed.y = 5;
    //player.color = WHITE;


    // Bullets initialisieren

    bullettext2 = LoadTexture("assets/graphics/bullet.png");

    //for (int i = 0; i < NUM_SHOOTS; i++)
    //{
    //    bullet[i].pos.x = player.rect.x + 29;                  //Bullet zentrieren
    //    bullet[i].rect.y = player.rect.y + player.rect.height / 4;
    //    bullet[i].rect.width = 5;
    //    bullet[i].rect.height = 10;
    //    bullet[i].speed.x = 0;
    //    bullet[i].speed.y = -10;
    //    bullet[i].active = false;
    //    bullet[i].color = MAROON;
    //}




    // Gegner initialisieren

    // Load alien ship texture
    alienTexture = LoadTexture("assets/graphics/alien2.png");
    alienTexture2 = LoadTexture("assets/graphics/Test2.png");

    //Anzahl aktive Gegner 


 /*    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy[i].pos.z = 1000 - enemy[i].pos.x;
        enemy2[i].pos.z = 1000 - enemy2[i].pos.x;

    }*/


    ////Schwerer Gegner
    //for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    //{
    //    enemy2[i].rect.width = 128;
    //    enemy2[i].rect.height = 120;
    //    enemy2[i].rect.x = GetRandomValue(200, 672);
    //    enemy2[i].rect.y = GetRandomValue(-1000, -20);
    //    enemy2[i].speed.x = 5;
    //    enemy2[i].speed.y = 2; //Geschwindigkeit Gegner
    //    enemy2[i].active = true;
    //    enemy2[i].gothit = false;
    //}

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
    }

    for (int i = 0; i < NUM_MAX_ASTEROIDS; i++)
    {
        asteroid[i].rect.x = asteroid[i].pos2.x;
        asteroid[i].rect.y = asteroid[i].pos2.y;
    }

    player.rect.x = player.pos.w;
    player.rect.y = player.pos.z;

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

        }

        for (int i = 0; i < NUM_MAX_ASTEROIDS; i++)
        {
            asteroid[i].pos2.y = 1000 - asteroid[i].pos1.x;
            asteroid[i].pos2.x = GetRandomValue(200, 800);
        }


        ScreenChangeto2 = true;
        ScreenChangeto1 = false;
    }

   


   //# Spieler

      //Spieler an Wänden einschränken
        if ((player.rect.x + 54) >= 800) player.rect.x = 800 - 54;          
        else if (player.rect.x <= -10) player.rect.x = -10;
        if ((player.rect.x) <= 200) player.rect.x = 200 + 1;         
   

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

                        if (enemy2[j].gothit == true)
                        {

                            if (CheckCollisionRecs(bullet[i].rect, enemy2[j].rect))
                            {
                                bullet[i].active = false;
                                enemy2[j].pos2.x = GetRandomValue(200, 800);      //Spawnbereich neuer Gegner x
                                enemy2[j].pos2.y = GetRandomValue(-150, -300);     //Spawnbereich neuer Gegner y
                                highscore++;
                                enemy2[j].gothit = false;
                            }
                        }
                        if (CheckCollisionRecs(bullet[i].rect, enemy2[j].rect))
                        {
                            enemy2[j].gothit = true;
                            bullet[i].active = false;
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



    if (player.lives == 0 || planet.landed == 0) {
        currentScreen = Game::GameOver::getInstance();


        player.lives = 3;
        planet.landed = 5;
        activeEnemies = 1;
        activeEnemies2 = 0;

        for (int i = 0; i < activeEnemies; i++)
        {
            if (enemy[i].active)
            {
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
    DrawTexture(Planet3, 100, -600, WHITE);


    //BUllet zeichnen
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (bullet[i].active)
            DrawTexture(bullettext2, bullet[i].pos2.x, bullet[i].pos2.y, WHITE);
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


    //Anzeigen
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

