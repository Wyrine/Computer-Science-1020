/* Kirolos Shahat
3/14/16
Lab 5, Processing
This program is a shuriken shooting program. The way it works is that while the cursor is located before
the vertical location of 100 the cursor is a nina star. If you press while the cursor is a ninja star then
the ninja star is thrown and the goal is to hit the dummy. If the dummy is successfully hit, a sound plays and
the game resets.
*/

//sound library to be used
import ddf.minim.*;
//defining a Minim class
Minim minim;
AudioPlayer player;
//the images used in the program
PImage dummy;
PImage shuriken;
PImage field;
//a loop condition to see if an item has been shot or if the target has been hit
boolean clicked = false;
//the current location once shooting is about to be done.
float currentX;
float currentY;
//an object class instance of a shuriken
Object shuri;

void setup(){
  //declaring the size of the window
 size (659, 223);
 //declaring the sound file to be used
 minim = new Minim(this);
 player = minim.loadFile("hit.mp3");
 //loading the background, shuriken, and the dummy images
 field = loadImage("field.png");
 shuriken = loadImage("shuriken.png");
 dummy = loadImage("dummy.png");
}

void draw(){
  //loading the background and the dummy onto the screen
  background (field);
  image(dummy, 500, 100);
  //if the mouse is in the correct location
  if(mouseX < 100){
    //the cursor becomes a shuriken
    cursor(shuriken);
    //if the mouse is pressed while it is a shuriken
    if (mousePressed == true){
      currentX = mouseX;
      currentY = mouseY;
      //creates a new object class
      shuri = new Object(currentX, currentY);
      //sets the loop condition to true
      clicked = true;
    }
  }//otherwise the cursor is normal
  else {
    cursor(0);
  }//the shuriken movement loop
  if(clicked){
    //calls the shoot function in the Object class
    shuri.shoot(shuriken);
    //rewinds the music file to be at the beginning
    player.rewind();
    //if the dummy has been reached
    if ((shuri.coordX > 530 && shuri.coordX <550) && (shuri.coordY > 85 && shuri.coordY <175)){
        //plays the playback file
        player.play();
        //updates the loop condition to false
        clicked = false;
    }
    //if hits ground or goes out of bounds the loop condition becomes false
    if (shuri.coordX > 662 || shuri.coordY > 160){
      clicked = false;
    }
  }
}