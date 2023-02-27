#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image Drake;
  Drake.readFromFile("Drake.png");

  Image Due;
  Due.readFromFile("due.png");

  Image Do;
  Do.readFromFile("Do.png");

  StickerSheet meme(Drake, 2);
  meme.addSticker(Due, 650, 150);
  meme.addSticker(Do, 650, 750);

  Image Pic = meme.render();

  Pic.writeToFile("myImage.png");

  return 0;
}
