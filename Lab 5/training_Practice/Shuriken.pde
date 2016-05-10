//class to define an object that will travel across the screen at a predetermined
//speed to try and hit an object, otherwise flies off the screen
class Object{
  //the current coordinates of the item after it is thrown
  float coordX;
  float coordY;
  
  //the constant speed the item travels across the screen
  final float speedX=7;
  final float speedY=1;
  
  //constructor to set the current location of the cursor as the coordinates
  Object(float currentX, float currentY){
    coordX = currentX;
    coordY = currentY;
  }
  
  //as long as the location of the item is not the ground and it is not off the
  //side of the screen, it prints it and moves the item forward by the speed.
  void shoot(PImage something){
    if (coordX < 662 && coordY < 200){
      image(something, coordX, coordY);
      coordX += speedX;
      coordY += speedY;
    }
  }
}