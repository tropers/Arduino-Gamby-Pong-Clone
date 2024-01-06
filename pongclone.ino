#include<Gamby.h>

#define maxwidth 95
#define maxheight 63

GambyGraphicsMode gamby;

// GAME SPRITES

PROGMEM prog_uchar pong[] = {
  2, 16,
  B11111111, B11111111,
  B11111111, B11111111
};

PROGMEM prog_uchar ball[] = {
  4, 4,
  B11111111,
  B11111111
};

// SCORES

PROGMEM prog_uchar score_zero[] = {
  4, 8,
  B01111110,
  B11000011,
  B11000011,
  B01111110
};

PROGMEM prog_uchar score_one[] = {
  4, 8,
  B11001100,
  B11111111,
  B11111111,
  B11000000
};

PROGMEM prog_uchar score_two[] = {
  4, 8,
  B11000110,
  B11100011,
  B11111011,
  B11001110
};

PROGMEM prog_uchar score_three[] = {
  4, 8,
  B11011011,
  B11011011,
  B11111111,
  B01100110
};

PROGMEM prog_uchar score_four[] = {
  4, 8,
  B00111100,
  B00110011,
  B11111111,
  B00110000
};

PROGMEM prog_uchar score_five[] = {
  4, 8,
  B11001111,
  B11011011,
  B11011011,
  B01110011
};

PROGMEM prog_uchar score_six[] = {
  4, 8,
  B01111100,
  B11001110,
  B11011011,
  B01110011
};

PROGMEM prog_uchar score_seven[] = {
  4, 8,
  B11100011,
  B01110011,
  B00111011,
  B00001111
};

PROGMEM prog_uchar score_eight[] = {
  4, 8,
  B01110110,
  B11001011,
  B11001011,
  B01110110
};

PROGMEM prog_uchar score_nine[] = {
  4, 8,
  B11001110,
  B11011011,
  B01110011,
  B00111110
};


int pong1x = 4;
int pong1y = maxheight/2-pong[1];

int score1 = 0;

int pong2x = maxwidth - 4;
int pong2y = maxheight/2-pong[1];

int score2 = 0;

int pedalspeed = 3;

int ballx = maxwidth/2;
int bally = maxheight/2;

int ballspeed = 2;

int ballxvel = -ballspeed;
int ballyvel = ballspeed;

void setup() {
  gamby.drawPattern = PATTERN_BLACK;
  randomSeed(5136);
}

void loop() {
  // game speed
  delay(40);
  
  gamby.readInputs();
  
  // MOVE PADDLE 1
  if (gamby.inputs & DPAD_DOWN) {
    if (pong1y+pong[1] > maxheight) {
      pong1y = maxheight-pong[1];
    } else {
      pong1y+=pedalspeed;
    }
  } else if (gamby.inputs & DPAD_UP) {
    if (pong1y < 0) {
      pong1y = 0;
    } else {
      pong1y-=pedalspeed;
    }
  }
  
  // MOVE PADDLE 2
  if (gamby.inputs & BUTTON_4) {
    if (pong2y+pong[1] > maxheight) {
      pong2y = maxheight-pong[1];
    } else {
      pong2y+=pedalspeed;
    }
  } else if (gamby.inputs & BUTTON_1) {
    if (pong2y < 0) {
      pong2y = 0;
    } else {
      pong2y-=pedalspeed;
    }
  }
  
  // CHECK COLLISION FOR BALL
  if (ballx < 0) {
    int rand = random(0, 100);
    
    if (rand <= 50) {
      ballxvel = -ballspeed;
    } else {
      ballxvel = ballspeed;
    }
    
    rand = random(0, 100);
    
    if (rand <= 50) {
      ballyvel = -ballspeed;
    } else {
      ballyvel = ballspeed;
    }
    
    tone(9, 500, 50);
    delay(50);
    
    if (score2 + 1 > 9) {
      score2 = 0;
      while (true) {
        tone(9, 500, 50);
        delay(50);
      }
    } else {
      score2++;
    }
    ballx = maxwidth/2;
    bally = maxheight/2;
  } else if (ballx > maxwidth-ball[0]) {
    int rand = random(0, 100);
    
    if (rand <= 50) {
      ballxvel = -1;
    } else {
      ballxvel = 1;
    }
    
    rand = random(0, 100);
    
    if (rand <= 50) {
      ballyvel = -1;
    } else {
      ballyvel = 1;
    }
    
    tone(9, 500, 50);
    delay(50);
    
    if (score1 + 1 > 9) {
      score1 = 0;
      while (true) {
        tone(9, 500, 50);
        delay(50);
      }
    } else {
      score1++;
    }
    ballx = maxwidth/2;
    bally = maxheight/2;
  } else if (bally < 0) {
    ballyvel = ballspeed;
  } else if (bally > maxheight-ball[1]) {
    ballyvel = -ballspeed;
  } else if (ballx <= pong1x + 2) {
    if (bally >= pong1y && bally <= pong1y+pong[1]) {
      ballxvel = ballspeed;
    }
  } else if (ballx >= pong2x - 2) {
    if (bally >= pong2y && bally <= pong2y+pong[1]) {
      ballxvel = -ballspeed;
    }
  }
  
  ballx += ballxvel; // change ball direction
  bally += ballyvel;
    
  gamby.drawSprite(pong1x, pong1y, pong); // draw pedal 1
  gamby.drawSprite(pong2x, pong2y, pong); // draw pedal 2
  
  // DISPLAY SCORES
  
  switch (score1) {
    case 0:
      gamby.drawSprite(20, 4, score_zero);
      break;
    case 1:
      gamby.drawSprite(20, 4, score_one);
      break;
    case 2:
      gamby.drawSprite(20, 4, score_two);
      break;
    case 3:
      gamby.drawSprite(20, 4, score_three);
      break;
    case 4:
      gamby.drawSprite(20, 4, score_four);
      break;
    case 5:
      gamby.drawSprite(20, 4, score_five);
      break;
    case 6:
      gamby.drawSprite(20, 4, score_six);
      break;
    case 7:
      gamby.drawSprite(20, 4, score_seven);
      break;
    case 8:
      gamby.drawSprite(20, 4, score_eight);
      break;
    case 9:
      gamby.drawSprite(20, 4, score_nine);
      break;
  }
  
  switch (score2) {
    case 0:
      gamby.drawSprite(maxwidth - 20, 4, score_zero);
      break;
    case 1:
      gamby.drawSprite(maxwidth - 20, 4, score_one);
      break;
    case 2:
      gamby.drawSprite(maxwidth - 20, 4, score_two);
      break;
    case 3:
      gamby.drawSprite(maxwidth - 20, 4, score_three);
      break;
    case 4:
      gamby.drawSprite(maxwidth - 20, 4, score_four);
      break;
    case 5:
      gamby.drawSprite(maxwidth - 20, 4, score_five);
      break;
    case 6:
      gamby.drawSprite(maxwidth - 20, 4, score_six);
      break;
    case 7:
      gamby.drawSprite(maxwidth - 20, 4, score_seven);
      break;
    case 8:
      gamby.drawSprite(maxwidth - 20, 4, score_eight);
      break;
    case 9:
      gamby.drawSprite(maxwidth - 20, 4, score_nine);
      break;
  }
  
  
  gamby.drawSprite(ballx, bally, ball);
  gamby.update();
  gamby.clearScreen();
}
