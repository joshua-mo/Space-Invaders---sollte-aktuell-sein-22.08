#include "raylib.h"

#include "GameScreen.h"
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



extern Bullet bullet2[NUM_SHOOTS];

extern int framescounter;

extern Flotte flotte[NUM_SHOOTS];

extern int framescounter2;

extern int framescounter3;

extern bool changeto1;

extern bool changeto2;

extern int seconds;

extern int minutes;

extern Planet planet;


Game::GameScreen::GameScreen() {
    // Your screen initialization code here...
    Vector2 vec = {100.0f, 100.0f};
    this->sprites.push_back(
        std::make_unique<Game::Sprite>(LoadTexture("assets/graphics/background.png"),
            vec,
            true)
    );

    ScreenChangeto1 = true;

    //Texuren Umgebung
    background = LoadTexture("assets/graphics/background.png");
    Planet1 = LoadTexture("assets/graphics/planet1.png");
    Planet2 = LoadTexture("assets/graphics/planet2.png");
    Spaces = LoadTexture("assets/graphics/Spaces.png");
    Lives = LoadTexture("assets/graphics/Lives.png");


 

    //INIT SECTION -- ASTEROID    

    // Load Asteroid texture
    asteroidtexture = LoadTexture("assets/graphics/asteroid.png");

    //Anzahl aktive Asteroiden 

    activeAsteroids = 2;

    for (int i = 0; i < NUM_MAX_ASTEROIDS; i++)
    {
        asteroid[i].rect.width = 64;
        asteroid[i].rect.height = 64;
        asteroid[i].rect.x = GetRandomValue(1060, 1200);      //Spawnbereich neuer Asteroid
        asteroid[i].rect.y = GetRandomValue(0, 800);
        asteroid[i].pos1.x = GetRandomValue(1060, 1200);      //Spawnbereich neuer Asteroid
        asteroid[i].pos1.y = GetRandomValue(0, 800);
        asteroid[i].pos2.x = GetRandomValue(1060, 1200);      //Spawnbereich neuer Asteroid
        asteroid[i].pos2.y = GetRandomValue(0, 800);
        asteroid[i].speed.x = 3;
        asteroid[i].speed.y = 1; //Geschwindigkeit Gegner
        asteroid[i].active = true;
    }


    //INIT SECTION -- PLANET

    planet.position.x = -175;
    planet.position.y = 500;
    planet.position2.x = 500;
    planet.position2.y = 1175;
    planet.radius = 350;
       

 //INIT SECTION -- PLAYER

    //Spieler initialisieren
    // Load player ship texture
    playerTexture = LoadTexture("assets/graphics/player.png");      

    // Spieler (Viereck) initialisieren
    player.pos.x = 250;
    player.pos.y = 800 / 2.0f;
    player.pos.z = 750;
    player.pos.w = 500;
    player.rect.width = 35;
    player.rect.height = 35;
    player.speed.x = 7;
    player.speed.y = 5;
    player.speed.z = 5;
    player.speed.w = 7;
    player.lives = 3;
    player.color = WHITE;


    //INIT SECTION -- BULLETS

   

    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        bullet[i].pos1.x = player.pos.x + player.rect.width / 4;
        bullet[i].pos1.y = player.pos.y + 5;                                //Bullet zentrieren
        bullet[i].pos2.x = player.pos.w + player.rect.width / 4;
        bullet[i].pos2.y = player.pos.z + 5;
        bullet[i].rect.width = 10;
        bullet[i].rect.height = 5;
        bullet[i].speed.x = +10;
        bullet[i].speed.y = +10;
        bullet[i].active = false;
        bullet[i].color = MAROON;
    }

    //INIT SECTION -- BULLETS2

    bullettext = LoadTexture("assets/graphics/bullet2.png");

    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        bullet2[i].pos1.x = boss[i].pos1.x + player.rect.width / 4;
        bullet2[i].pos1.y = boss[i].pos1.x + 5;                                //Bullet zentrieren
        bullet2[i].pos2.x = boss[i].pos2.y + player.rect.width / 4;
        bullet2[i].pos2.y = boss[i].pos2.y + 5;
        bullet2[i].rect.width = 20;
        bullet2[i].rect.height = 10;
        bullet2[i].speed.x = 10;
        bullet2[i].speed.y = 10;
        bullet2[i].active = false;
        bullet2[i].color = MAROON;
    }

//INIT SECTION -- BOSSGEGNER

    // Load alien ship texture
    BossTexture = LoadTexture("assets/graphics/BossSide.png");

    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        boss[i].rect.width = 140;
        boss[i].rect.height = 140;
        boss[i].pos1.x = 1100;      //Spawnbereich neuer Gegner x
        boss[i].pos1.y = 260;
        boss[i].pos2.x = 430;
        boss[i].pos2.y = -200;
        boss[i].speed.x = 1;
        boss[i].speed.y = 2; //Geschwindigkeit Gegner
        boss[i].speed.z = 2;
        boss[i].speed.w = 0;
        boss[i].speed1 = { 5.0f, 5.0f };
        boss[i].lives = 30;

        boss[i].active = true;
    }

  

  

    waveSide = LoadTexture("assets/graphics/streifen.png");
    change = LoadTexture("assets/graphics/change.png");
    
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        flotte[i].pos1.x = boss[i].pos1.x + player.rect.width / 4;
        flotte[i].pos1.y = 0;                                //Bullet zentrieren
        flotte[i].pos2.x = 0;
        flotte[i].pos2.y = boss[i].pos2.x + player.rect.width / 4;
        flotte[i].rect.width = 25;
        flotte[i].rect.height = 1000;
        flotte[i].rect2.width = 1000;
        flotte[i].rect2.height = 25;
        flotte[i].speed.x = +5;
        flotte[i].speed.y = +5;
        flotte[i].active = false;
        flotte[i].color = BLACK;
    }

    // Gegner initialisieren

    // Load alien ship texture
    alienTexture = LoadTexture("assets/graphics/alien.png");
    alienTexture2 = LoadTexture("assets/graphics/Test.png");

    //Anzahl aktive Gegner 
    
        activeEnemies = 1;
        activeEnemies2 = 0;
        activeEnemies3 = 1;
    
  
    //Einfacher Gegner
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy[i].rect.width = 50;
        enemy[i].rect.height = 64;

        enemy[i].pos1.x = GetRandomValue(1100, 1600);      //Spawnbereich neuer Gegner x
        enemy[i].pos1.y = GetRandomValue(200, 700);
        enemy[i].pos2.x = GetRandomValue(200, 700);
        enemy[i].pos2.y = GetRandomValue(200, 700);
        enemy[i].speed.x = 4; 
        enemy[i].speed.y = 4; //Geschwindigkeit Gegner
        enemy[i].speed.z = 4;
        enemy[i].speed.w = 4; 
       

        enemy[i].active = true;
    }
    //Schwerer Gegner
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy2[i].rect.width = 120;
        enemy2[i].rect.height = 128;
        enemy2[i].pos1.x = GetRandomValue(1100, 1600);      //Spawnbereich neuer Gegner x
        enemy2[i].pos1.y = GetRandomValue(200, 700);
        enemy2[i].pos2.x = GetRandomValue(200, 700);
        enemy2[i].pos2.y = GetRandomValue(200, 700);
        enemy2[i].speed.x = 2;
        enemy2[i].speed.y = 2; //Geschwindigkeit Gegner
        enemy2[i].speed.z = 2;
        enemy2[i].speed.w = 2;
        enemy2[i].active = true;
      
    }

  }


Game::GameScreen::~GameScreen() {
    // Your screen cleanup code here...
    UnloadTexture(sprites[0]->texture);
    UnloadTexture(background);
    UnloadTexture(playerTexture);
    UnloadTexture(alienTexture);
    UnloadTexture(alienTexture2);
    UnloadTexture(Lives);
    UnloadTexture(Spaces);
}


void Game::GameScreen::ProcessInput() {
    // Your process input code here...
    if (IsKeyPressed(KEY_M)) currentScreen = Game::StopScreen::getInstance();
    //SWAP
    if (IsKeyPressed(KEY_TAB)) currentScreen = Game::GameScreen2::getInstance();
    // Spieler bewegen (links-rechts)
    if (IsKeyDown(KEY_DOWN))
        player.pos.y += player.speed.y;
    if (IsKeyDown(KEY_UP))
        player.pos.y -= player.speed.y;

   


}

void Game::GameScreen::Update() {
    // Your update game code here...



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

   

    //UPDATE SECTION -- BOSSGEGNER
    if (highscore == 20) {
        BossMoving = true;
       

            for (int i = 0; i < activeEnemies || i < activeEnemies2; i++)
            {
                    enemy[i].speed.x = 0;
                    enemy[i].pos1.y += enemy[i].speed.y;
                    enemy2[i].speed.x = 0;
                    enemy2[i].pos1.y += enemy2[i].speed.y;
            }
    }
    //Boss 
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {

        if (BossMoving == true) {
            boss[i].pos1.x -= boss[i].speed.x;
            flotte[i].active = false;
        }

        boss[i].rect.x = boss[i].pos1.x;
        boss[i].rect.y = boss[i].pos1.y;

        boss[i].pos1.y += boss[i].speed.y;       

        //// Check walls collision for bouncing
        if ((boss[i].pos1.y >= (730)) || (boss[i].pos1.y <= 200)) boss[i].speed.y *= -1.0f;
        if ((boss[i].pos1.x >= (860)) && boss[i].speed.x < 0) boss[i].speed.x *= -1.0f;

        if ((boss[i].pos1.x <= (800)))  boss[i].speed.x *= -1.0f, boss[i].pos1.y += boss[i].speed.y, boss[i].speed.x = - 0.25;

    

 
    }

  
    //flotte

    framescounter2++;

    // Every two seconds (120 frames) a new random value is generated
    if (/*IsKeyPressed(KEY_F)*/ ((framescounter2 / 600) % 2) == 1)
    {
            changeto1 = false;
        framescounter2 = 0;


        for (int i = 0; i < 1; i++)
        {
            if (!flotte[i].active)
            {
                // Movement



                flotte[i].pos1.x = 1050;
                flotte[i].pos1.y = 0;
                flotte[i].rect.height = 1000;
                flotte[i].active = true;

              
                break;
            }
        }
    }

    if (changeto1 == true)
    {
        for (int i = 0; i < 1; i++)
        {
            flotte[i].rect.width = 70;
        }
    }

    if (changeto1 == false)
    {
        for (int i = 0; i < 1; i++)
        {
            flotte[i].rect.width = 1000;
        }
    }



    // Shoot logic
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (flotte[i].active)
        {
            // Movement
            flotte[i].pos1.x -= flotte[i].speed.x;

            if (flotte[i].pos1.x <= -200) //Bullet über Screen hinaus
            {
                flotte[i].active = false;
              
                
            }

            //Flotte 
            if (CheckCollisionRecs(flotte[i].rect, player.rect))
            {
                flotte[i].active = false;

                player.lives--;

               
               
               // flotte[i].pos1.x = 1050;
                //flotte[i].pos1.y = 0;
            }
        }

        
    }




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


                bullet2[i].pos1.x = boss[i].pos1.x + 18;
                bullet2[i].pos1.y = boss[i].pos1.y + 5;
                bullet2[i].active = true;

                break;


            }
        }
    }
    }



    // Shoot logic2
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        if (bullet2[i].active)
        {
            // Movement
            bullet2[i].pos1.x -= bullet2[i].speed.x;

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

                if (bullet2[i].pos1.x <= -100) //Bullet über Screen hinaus
                {
                    bullet2[i].active = false;
                }
            }
        }
    }

   


    
    
    //UPDATE SECTION -- SCREENSWAP ALLE ELEMENTE

    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy[i].rect.x = enemy[i].pos1.x;
        enemy[i].rect.y = enemy[i].pos1.y;
    }

    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy2[i].rect.x = enemy2[i].pos1.x;
        enemy2[i].rect.y = enemy2[i].pos1.y;
    }

    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        bullet[i].rect.x = bullet[i].pos1.x;
        bullet[i].rect.y = bullet[i].pos1.y;

        bullet2[i].rect.x = bullet2[i].pos1.x;
        bullet2[i].rect.y = bullet2[i].pos1.y;

        flotte[i].rect.x = flotte[i].pos1.x;
        flotte[i].rect.y = flotte[i].pos1.y;
    }

    for (int i = 0; i < NUM_MAX_ASTEROIDS; i++)
    {
        asteroid[i].rect.x = asteroid[i].pos1.x;
        asteroid[i].rect.y = asteroid[i].pos1.y;

    }

    player.rect.x = player.pos.x;
    player.rect.y = player.pos.y;

   
  


    if (ScreenChangeto1 == false)
    {
        for (int i = 0; i < NUM_MAX_ENEMIES; i++)
        {
            enemy[i].pos1.x = 1000 - enemy[i].pos2.y;
            enemy2[i].pos1.x = 1000 - enemy2[i].pos2.y;
        }
        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            bullet[i].pos1.x = 1000 - bullet[i].pos2.y;
            bullet2[i].pos1.x = 1000 - bullet2[i].pos2.y;
            flotte[i].pos1.x = 1000 - flotte[i].pos2.y;
            flotte[i].rect.height = 70;
           
            flotte[i].pos1.y = GetRandomValue(200, 730);

            if (flotte[i].active)
            {
                changeto1 = true;
                flotte[i].rect.height = 70;
            }
        

            
        }

        for (int i = 0; i < NUM_MAX_ASTEROIDS; i++)
        {
            asteroid[i].pos1.x = 1000 - asteroid[i].pos2.y;

        }

        for (int i = 0; i < NUM_MAX_ENEMIES; i++)
        {
            boss[i].pos1.x = 860 - boss[i].pos2.y;
          
        }

        ScreenChangeto2 = false;
        ScreenChangeto1 = true;
    }
 
   
   //Spieler
    player.pos.x = 250;
      //Spieler an Wänden einschränken
 if ((player.pos.y) >= 850) player.pos.y = 850 - 1;
 if ((player.pos.y) <= 150) player.pos.y = 150 + 1;

 // Asteroid Verhalten(Spawnverhalten)
 for (int i = 0; i < activeAsteroids; i++)
 {
     if (asteroid[i].active)
     {
         asteroid[i].pos1.x -= asteroid[i].speed.x;
         asteroid[i].pos1.y += asteroid[i].speed.y;



         if (CheckCollisionRecs(player.rect, asteroid[i].rect))
         {
             player.lives--;
             asteroid[i].pos1.x = GetRandomValue(1060, 1200);      //Spawnbereich neuer Asteroid
             asteroid[i].pos1.y = GetRandomValue(0, 800);

         }
     }
     if (asteroid[i].pos1.x <= -50 || asteroid[i].rect.y >= 1050) //asteroid über Screen hinaus
     {
         asteroid[i].pos1.x = GetRandomValue(1060, 1200);      //Spawnbereich neuer Asteroid
         asteroid[i].pos1.y = GetRandomValue(0, 800);
     }

 }

 //Bullets
 if (IsKeyPressed(KEY_SPACE)) {

    


     for (int i = 0; i < NUM_SHOOTS; i++)
     {
         if (!bullet[i].active)
         { 
                // Movement
               

                 bullet[i].pos1.x = player.pos.x + 18;
                 bullet[i].pos1.y = player.pos.y + 5;
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
         bullet[i].pos1.x += bullet[i].speed.x;

         // Kollision mit enemy
         for (int j = 0; j < activeEnemies || j < activeEnemies2;  j++)
         {
             if (enemy[j].active || enemy2[j].active)
             {
                 if (CheckCollisionRecs(bullet[i].rect, enemy[j].rect))
                 {
                     bullet[i].active = false;
                     enemy[j].pos1.x = GetRandomValue(1100, 1600);      //Spawnbereich neuer Gegner x
                     enemy[j].pos1.y = GetRandomValue(200, 736);     //Spawnbereich neuer Gegner y
                     highscore++;
              
                 
                 }
               
                 

                     if (CheckCollisionRecs(bullet[i].rect, enemy2[j].rect))
                     {
                         bullet[i].active = false;
                       
                         enemy2[j].lives--;
                     }
                 
                         if (enemy2[j].lives == 0)
                         {
                             enemy2[j].lives = 2;
                             enemy2[j].pos1.x = GetRandomValue(1100, 1600);      //Spawnbereich neuer Gegner x
                             enemy2[j].pos1.y = GetRandomValue(200, 672);     //Spawnbereich neuer Gegner y
                             highscore++;
                         }
             }

                 if (bullet[i].pos1.x >= 1000) //Bullet über Screen hinaus
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
                     enemy[j].pos1.x = GetRandomValue(1020, 2000);      //Spawnbereich neuer Gegner x
                     enemy[j].pos1.y = GetRandomValue(200, 736);     //Spawnbereich neuer Gegner y
                 }
                 if (CheckCollisionRecs(player.rect, enemy2[j].rect))
                 {
                     player.lives--;
                     enemy2[j].pos1.x = GetRandomValue(1020, 2000);      //Spawnbereich neuer Gegner x
                     enemy2[j].pos1.y = GetRandomValue(200, 772);     //Spawnbereich neuer Gegner y
                     enemy2[j].lives = 2;
                 }
             }
         }

    

             
         



    
  

    // Enemy Verhalten(Spawnverhalten)
    for (int i = 0; i < activeEnemies || i < activeEnemies2; i++)
    {
        if (enemy[i].active)
        {
            enemy[i].pos1.x -= enemy[i].speed.x;

            if (CheckCollisionPointCircle(enemy[i].pos1, planet.position, 350))    //         //Kollision Planet mit Enemy
            {
                enemy[i].pos1.x = GetRandomValue(1020, 2000);
                enemy[i].pos1.y = GetRandomValue(200, 736);
                planet.landed--;

            }
        }

        if (enemy2[i].active)
        {
            enemy2[i].pos1.x -= enemy2[i].speed.x;

            if (CheckCollisionPointCircle(enemy2[i].pos1, planet.position, 350))   //         //Kollision Planet mit Enemy2
            {
                enemy2[i].pos1.x = GetRandomValue(1020, 2000);
                enemy2[i].pos1.y = GetRandomValue(200, 672);
                enemy2[i].lives = 2;
                planet.landed--;

            }
        }


    }

    if (highscore == 5) {
        activeEnemies = 1;
        activeEnemies2 = 1;
    }
    if (highscore == 15) {
        activeEnemies = 2;
        activeEnemies2 = 1;

    }
    if (highscore == 35) {
        activeEnemies = 3;
        activeEnemies2 = 1;

    }
    if (highscore == 45) {
        activeEnemies = 4;
        activeEnemies2 = 1;

    }
    if (highscore == 60) {
        activeEnemies = 5;
        activeEnemies2 = 1;

    }
    if (highscore == 90) {
        activeEnemies = 5;
        activeEnemies2 = 2;

    }

    if (boss->lives == 0) {
        currentScreen = Game::GameOver::getInstance();
    }
 
    if (player.lives == 0 || planet.landed == 0) {
        currentScreen = Game::GameOver::getInstance();


    /*    player.lives = 3;
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



void Game::GameScreen::Draw() {
    // Your drawing code here...
    ClearBackground(BLACK);
    //Hitbox Planet
    DrawCircleV(planet.position, planet.radius, RED);
    //Hintergrund
    DrawTexture(background, 0, 0, WHITE);

    //Planet1
    DrawTexture(Planet1, -480, 80, WHITE);

    //Planet2
    DrawTexture(Planet2, 800, 80, WHITE);
   
         
     //BUllet zeichnen
     for (int i = 0; i < NUM_SHOOTS; i++)
     {
         if (bullet[i].active)
             /* DrawRectangleRec(bullet[i].rect, bullet[i].color);*/
             DrawTexture(bullettext, bullet[i].pos1.x, bullet[i].pos1.y, WHITE);
     }
     //BUllet2 zeichnen
     for (int i = 0; i < NUM_SHOOTS; i++)
     {
         if (bullet2[i].active)
             /* DrawRectangleRec(bullet[i].rect, bullet[i].color);*/
             DrawTexture(bullettext, bullet2[i].pos1.x, bullet2[i].pos1.y, WHITE);

         //Flotte zeichnen

         if (changeto1 == false)
         {
             if (flotte[i].active)

                 DrawTexture(waveSide, flotte[i].pos1.x, flotte[i].pos1.y, WHITE);
         }
         if (changeto1 == true)
         {
             DrawTexture(change, flotte[i].pos1.x, flotte[i].pos1.y, WHITE);

         }


     }


     
     //Player zeichnen
     DrawTexture(playerTexture, player.pos.x, player.pos.y, WHITE);

     //Boss zeichnen
     for (int i = 0; i < activeEnemies3; i++)
     {
         if (boss[i].active)
             DrawTexture(BossTexture, boss[i].rect.x, boss[i].rect.y, WHITE);
     }

     //Gegner zeichnen
     for (int i = 0; i < activeEnemies; i++)
     {
         if (enemy[i].active)
             DrawTexture(alienTexture, enemy[i].rect.x, enemy[i].rect.y, WHITE);        
     }

    

     //Gegner2 zeichnen
     for (int i = 0; i < activeEnemies2; i++)
     {
         if (enemy2[i].active)
             DrawTexture(alienTexture2, enemy2[i].rect.x, enemy2[i].rect.y, WHITE);       
     }
     //Asteroiden zeichnen
     for (int i = 0; i < activeAsteroids; i++)
     {
         if (asteroid[i].active)
             DrawTexture(asteroidtexture, asteroid[i].rect.x, asteroid[i].rect.y, WHITE);
     }




     //Anzeigen



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
     DrawText(TextFormat("Score: %02i", highscore), 820, 25, 35, LIGHTGRAY);

  /*   for (int hr = h; hr > 0; hr--)
     {
         DrawText(TextFormat("Time: %02i", hr), 500, 100, 60, RED);
         DrawText(TextFormat("Time: %02i", min), 500, 100, 60, RED);
         DrawText(TextFormat("Time: %02i", s), 500, 100, 60, RED);

     }*/
     
     //Live Anzeige
     if (player.lives == 3) {
         DrawTexture(Lives, 900, 100, WHITE);
         DrawTexture(Lives, 930, 100, WHITE);
         DrawTexture(Lives, 960, 100, WHITE);
     }
     if (player.lives == 2) {
         DrawTexture(Lives, 930, 100, WHITE);
         DrawTexture(Lives, 960, 100, WHITE);
     }
     if (player.lives == 1) {
         DrawTexture(Lives, 960, 100, WHITE);
     }

     //Space Anzeige 
     if (planet.landed == 5) {
         DrawTexture(Spaces, 820, 65, WHITE);
         DrawTexture(Spaces, 855, 65, WHITE);
         DrawTexture(Spaces, 890, 65, WHITE);
         DrawTexture(Spaces, 925, 65, WHITE);
         DrawTexture(Spaces, 960, 65, WHITE);
     }
     if (planet.landed == 4) {
         DrawTexture(Spaces, 855, 65, WHITE);
         DrawTexture(Spaces, 890, 65, WHITE);
         DrawTexture(Spaces, 925, 65, WHITE);
         DrawTexture(Spaces, 960, 65, WHITE);
     }
     if (planet.landed == 3) {
         DrawTexture(Spaces, 890, 65, WHITE);
         DrawTexture(Spaces, 925, 65, WHITE);
         DrawTexture(Spaces, 960, 65, WHITE);
     }
     if (planet.landed == 2) {
         DrawTexture(Spaces, 925, 65, WHITE);
         DrawTexture(Spaces, 960, 65, WHITE);
     }
     if (planet.landed == 1) {
         DrawTexture(Spaces, 960, 65, WHITE);
     }


     
}

