#include "StickerSheet.h"
int main() {
  cs225::Image _base, _sticker, _res;
  _base.readFromFile("StickerFiles/NorthFace.png");
  _sticker.readFromFile("StickerFiles/jze.png");
  cs225::StickerSheet _sheet(_base, 1);
  _sheet.addSticker(_sticker, 20, 20);
  _res = _sheet.render();
  _res.writeToFile("myImage.png");
  return 0;
}
