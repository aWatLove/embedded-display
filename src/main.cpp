#include <Arduino.h>


// веб сервер
#include <WiFi.h>
#include <ESPAsyncWebServer.h>


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "painlessMesh.h"

// Имя и пароль для точки доступа
const char* ssid = "RISOVALKA";
const char* password = "1234567890";

// Создание веб-сервера
AsyncWebServer server(80);

// mesh
// настройка mesh сети
#define MESH_PREFIX "picturka"
#define MESH_PASSWORD "picturka"
#define MESH_PORT 5555

// метод-заглушка
void sendMessage() ; // чтобы PlatformIO работал

Scheduler userScheduler;
painlessMesh  mesh;
Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );
 
void sendMessage() {
  String msg = "ping from screen";
  msg += mesh.getNodeId();
  mesh.sendBroadcast( msg );
  taskSendMessage.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
}


String formattedString; // для сообщения



// контролер
enum JoystickDirectionTypes
{
  CENTER,
  DOWN,
  UP,
  LEFT,
  RIGHT,
  DOWN_LEFT,
  DOWN_RIGHT,
  UP_LEFT,
  UP_RIGHT
};


// экран
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



unsigned char bitmap_image [] PROGMEM = {
  // 'DIYables-icon', 128x64px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// управление

#define JOYSTICK_STATE_INDEX 0
int lastJoystickState;
#define JOYSTICK_BUTTON_INDEX 1
int joystickButtonValue;
#define ALONE_BUTTON_INDEX 2
int aloneButtonValue;
#define ENCODER_VALUE_INDEX 3
int encoderValue;
int lastEncoderValue;
#define ENCODER_BUTTON_INDEX 4
int encoderButtonValue;
#define BLUE_BUTTON_INDEX 5
int blueButtonValue;
#define WHITE_BUTTON_INDEX 6
int whiteButtonValue;
#define RED_BUTTON_INDEX 7
int redButtonValue;
#define YELLOW_BUTTON_INDEX 8
int yellowButtonValue;


bool curBitState = false;
int curBitStateArr[10][10];

int curXCoord = 0;
int curYCoord = 0;


void setBit(unsigned char *bitmap, int x, int y, bool value) {
    // Определяем индекс байта
    int byteIndex = (y * SCREEN_WIDTH + x) / 8;
    // Определяем позицию бита в байте
    int bitIndex = x % 8;

    if (value) {
        // Устанавливаем бит в 1
        bitmap[byteIndex] |= (1 << (7 - bitIndex));
    } else {
        // Устанавливаем бит в 0
        bitmap[byteIndex] &= ~(1 << (7 - bitIndex));
    }
}

bool getBit(const unsigned char *bitmap, int x, int y) {
    // Определяем индекс байта
    int byteIndex = (y * SCREEN_WIDTH + x) / 8;
    // Определяем позицию бита в байте
    int bitIndex = x % 8;

    // Читаем байт из PROGMEM
    unsigned char byte = pgm_read_byte(&bitmap[byteIndex]);

    // Возвращаем значение конкретного бита
    return (byte & (1 << (7 - bitIndex))) != 0;
}

void getCurBitArr() {
  int curEncoderValue = encoderValue;
  for (size_t i = 0; i < curEncoderValue+1; i++)
  {
    for (size_t j = 0; j < curEncoderValue+1; j++)
    {
        if (getBit(bitmap_image, curXCoord+i, curYCoord+j)) {
            curBitStateArr[i][j] = 2;
        } else {
            curBitStateArr[i][j] = 1;
        }
    }
    
  }
}


void setCurBitArr() {
    for (size_t i = 0; i < lastEncoderValue+1; i++)
  {
    for (size_t j = 0; j < lastEncoderValue+1; j++)
    {
        if (curBitStateArr[i][j] == 2) {
          setBit(bitmap_image, curXCoord+i, curYCoord+j, true);
        } else if (curBitStateArr[i][j] == 1) {
          setBit(bitmap_image, curXCoord+i, curYCoord+j, false);
        }
    }
    
  }
}

void printBit(bool isPrint) {
  for (size_t i = 0; i < lastEncoderValue+1; i++)
  {
    for (size_t j = 0; j < lastEncoderValue+1; j++)
    {
      setBit(bitmap_image, curXCoord+i, curYCoord+j, isPrint);
    }
  }
  getCurBitArr();
  // setBit(bitmap_image, curXCoord, curYCoord, isPrint);
  // curBitState = isPrint;
}

void clearCanvas() {
  for (size_t i = 0; i < SCREEN_WIDTH; i++)
  {
    for (size_t j = 0; j < SCREEN_HEIGHT; j++)
    {
      setBit(bitmap_image, i, j, false);
    }
  }
  getCurBitArr();
}

void invertCanvas() {
  setCurBitArr();
    for (size_t i = 0; i < SCREEN_WIDTH; i++)
  {
    for (size_t j = 0; j < SCREEN_HEIGHT; j++)
    {
      if (getBit(bitmap_image, i, j)) {
        setBit(bitmap_image, i, j, false);
      } else {
        setBit(bitmap_image, i, j, true);
      }
    }
  }
  getCurBitArr();
}

// Функция для отрисовки битмапа в HTML
String drawBitmapHTML() {
    String html = "<button id=\"download\" style=\"background-color: #700ea9; color: #fff; font-size: 16px; border: none; border-radius: 1rem; padding: 0.5rem 1rem; margin-top: 1.5rem; margin-bottom: 1.5rem;\">Скачать изображение</button>";
    html += "<canvas id='canvas' style='border-radius: 1rem; border: 2px solid #700ea9; box-shadow: 4px 3px 11px 0px #700ea963' width='" + String(SCREEN_WIDTH) + "' height='" + String(SCREEN_HEIGHT) + "'></canvas>";
    html += "<script>";
    html += "const canvas = document.getElementById('canvas');";
    html += "const ctx = canvas.getContext('2d');";
    html += "const imageData = ctx.createImageData(" + String(SCREEN_WIDTH) + ", " + String(SCREEN_HEIGHT) + ");";
    html += "const data = new Uint8Array([";
    for (size_t i = 0; i < sizeof(bitmap_image); i++) {
        html += "0x" + String(bitmap_image[i], HEX);
        if (i < sizeof(bitmap_image) - 1) html += ",";
    }
    html += "]);";
    html += "for (let i = 0; i < data.length * 8; i++) {";
    html += "  const byteIndex = Math.floor(i / 8);";
    html += "  const bitIndex = i % 8;";
    html += "  const color = (data[byteIndex] & (1 << (7 - bitIndex))) ? 0 : 255;";
    html += "  const pixelIndex = i * 4;";
    html += "  imageData.data[pixelIndex] = color;";     // Red
    html += "  imageData.data[pixelIndex + 1] = color;"; // Green
    html += "  imageData.data[pixelIndex + 2] = color;"; // Blue
    html += "  imageData.data[pixelIndex + 3] = 255;";   // Alpha
    html += "}";
    html += "ctx.putImageData(imageData, 0, 0);";
    html += "document.getElementById('download').addEventListener('click', () => {";
    html += "  const link = document.createElement('a');";
    html += "  link.download = 'image.png';";
    html += "  link.href = canvas.toDataURL('image/png');";
    html += "  link.click();";
    html += "});";
    html += "</script>";
    return html;
}

// Требуется для painlessMesh
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  formattedString = msg.c_str();




  int curJoystickState = ((String)formattedString.charAt(JOYSTICK_STATE_INDEX)).toInt();
  joystickButtonValue = ((String)formattedString.charAt(JOYSTICK_BUTTON_INDEX)).toInt();
  aloneButtonValue = ((String)formattedString.charAt(ALONE_BUTTON_INDEX)).toInt();
  encoderValue = ((String)formattedString.charAt(ENCODER_VALUE_INDEX)).toInt();
  encoderButtonValue = ((String)formattedString.charAt(ENCODER_BUTTON_INDEX)).toInt();
  blueButtonValue = ((String)formattedString.charAt(BLUE_BUTTON_INDEX)).toInt();
  whiteButtonValue = ((String)formattedString.charAt(WHITE_BUTTON_INDEX)).toInt();
  redButtonValue = ((String)formattedString.charAt(RED_BUTTON_INDEX)).toInt();
  yellowButtonValue = ((String)formattedString.charAt(YELLOW_BUTTON_INDEX)).toInt();





  if (lastJoystickState != curJoystickState) {
    switch (curJoystickState)
    {
      case DOWN:
        if ( curYCoord < SCREEN_HEIGHT-1 - encoderValue ) {
          // setBit(bitmap_image, curXCoord, curYCoord, curBitState);
          setCurBitArr();
          curYCoord++;
          // curBitState=getBit(bitmap_image, curXCoord, curYCoord);
          getCurBitArr();
        }
        break;
      case UP:
        if ( curYCoord > 0 ) {
          // setBit(bitmap_image, curXCoord, curYCoord, curBitState);
          setCurBitArr();
          curYCoord--;
          getCurBitArr();
          // curBitState=getBit(bitmap_image, curXCoord, curYCoord);
        }
        break;
      case LEFT:
        if ( curXCoord > 0 ) {
          // setBit(bitmap_image, curXCoord, curYCoord, curBitState);
          setCurBitArr();
          curXCoord--;
          getCurBitArr();
          // curBitState=getBit(bitmap_image, curXCoord, curYCoord);
        }
        break;
      case RIGHT:
        if ( curXCoord < SCREEN_WIDTH-1 - encoderValue ) {
          setCurBitArr();
          // setBit(bitmap_image, curXCoord, curYCoord, curBitState);
          curXCoord++;
          getCurBitArr();
          // curBitState=getBit(bitmap_image, curXCoord, curYCoord);
        }
        break;
      case DOWN_LEFT:
        if ( curYCoord < SCREEN_HEIGHT-1 - encoderValue && curXCoord > 0 ) {
          setCurBitArr();
          // setBit(bitmap_image, curXCoord, curYCoord, curBitState);
          curYCoord++;
          curXCoord--;
          getCurBitArr();
          // curBitState=getBit(bitmap_image, curXCoord, curYCoord);
        }
        break;
      case DOWN_RIGHT:
        if ( curYCoord < SCREEN_HEIGHT-1 - encoderValue && curXCoord < SCREEN_WIDTH-1 - encoderValue ) {
          setCurBitArr();
          // setBit(bitmap_image, curXCoord, curYCoord, curBitState);
          curYCoord++;
          curXCoord++;
          getCurBitArr();
          // curBitState=getBit(bitmap_image, curXCoord, curYCoord);
        }
        break;
      case UP_LEFT:
        if ( curYCoord > 0 && curXCoord > 0 ) {
          setCurBitArr();
          // setBit(bitmap_image, curXCoord, curYCoord, curBitState);
          curYCoord--;
          curXCoord--;
          getCurBitArr();
          // curBitState=getBit(bitmap_image, curXCoord, curYCoord);
        }
        break;
      case UP_RIGHT:
        if ( curYCoord > 0 && curXCoord < SCREEN_WIDTH-1 - encoderValue ) {
          setCurBitArr();
          // setBit(bitmap_image, curXCoord, curYCoord, curBitState);
          curYCoord--;
          curXCoord++;
          getCurBitArr();
          // curBitState=getBit(bitmap_image, curXCoord, curYCoord);
        }
        break;
      default:
        break;
    }
  }



  if (blueButtonValue != 0) {
    printBit(true);
  }

  if (whiteButtonValue != 0) {
    printBit(false);
  }

  if (redButtonValue != 0) {
    clearCanvas();
  }

  if (yellowButtonValue != 0) {
    invertCanvas();
  }

}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}
void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}
void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(115200);
  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000); // wait two seconds for initializing
  oled.setCursor(0, 0);

// mesh
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // установите перед функцией init() чтобы выдавались приветственные сообщения
 
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
 
  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();


  oled.clearDisplay(); // clear display


  // Сервер
   // Запуск точки доступа
    WiFi.softAP(ssid, password);
    Serial.println("Access Point Started");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    // Обработчик для главной страницы
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        String html = "<!DOCTYPE html><html><body><div style=\"padding-left: 5rem;\">";
        html += "<h1 style=\"font-family: monospace; font-size: 33px; margin-bottom: 1rem;\">ESP32 Bitmap Viewer</h1>";
        html += "<p style=\"font-size: 20px; margin-bottom: 2rem;\">Вы можете увидеть своё творение!🎉</p>";
        html += drawBitmapHTML();
        // html += "<br><a href='/download'>Download Bitmap</a>";
        html += "</div></body></html>";
        request->send(200, "text/html", html);
    });

// // Обработчик для скачивания битмапа
// server.on("/download", HTTP_GET, [](AsyncWebServerRequest* request) {
//     // Создаем ответ, используя данные из PROGMEM
//     AsyncWebServerResponse* response = request->beginResponse_P(
//         200,
//         "application/octet-stream",
//         reinterpret_cast<const uint8_t*>(bitmap_image), // Преобразование указателя
//         sizeof(bitmap_image)
//     );
//     // Добавляем заголовок для скачивания
//     response->addHeader("Content-Disposition", "attachment; filename=bitmap.bin");
//     // Отправляем ответ
//     request->send(response);
// });

  // Настройка маршрута для скачивания
  server.on("/download", HTTP_GET, [](AsyncWebServerRequest* request) {
    AsyncWebServerResponse* response = request->beginResponse_P(
      200,
      "application/octet-stream",
      reinterpret_cast<const uint8_t*>(bitmap_image),
      sizeof(bitmap_image)
    );
    response->addHeader("Content-Disposition", "attachment; filename=bitmap.bmp");
    request->send(response);
  });

    // Запуск веб-сервера
    server.begin();
}


void loop() {

  oled.clearDisplay();
  mesh.update ();

if (millis()%500 == 0) {
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    if (lastEncoderValue != encoderValue) {
    if (curXCoord + encoderValue < SCREEN_WIDTH && curYCoord + encoderValue < SCREEN_HEIGHT) {
      if (lastEncoderValue < encoderValue) {
        setCurBitArr();
        getCurBitArr();
      } else if (lastEncoderValue > encoderValue) {
        setCurBitArr();

        for (size_t i = 0; i < 10; i++)
        {
          for (size_t j = 0; j < 10; j++)
          {
            curBitStateArr[i][j] = 0;
          }  
        }
        getCurBitArr();
      }

      lastEncoderValue = encoderValue;
    }
  }


  if (curBitState) {
    curBitState = false;
  } else {
    curBitState = true;
  }

  for (size_t i = 0; i < lastEncoderValue+1; i++)
  {
    for (size_t j = 0; j < lastEncoderValue+1; j++)
    {
        if (getBit(bitmap_image, curXCoord+i, curYCoord+j)) {
          setBit(bitmap_image, curXCoord+i, curYCoord+j, false);
          // curBitState = false;
        } else {
          setBit(bitmap_image, curXCoord+i, curYCoord+j, true); 
          // curBitState = true;
        }
    }
    
  }
  

  // if (getBit(bitmap_image, curXCoord, curYCoord)) {
  //   setBit(bitmap_image, curXCoord, curYCoord, false);
  // } else {
  //   setBit(bitmap_image, curXCoord, curYCoord, true); 
  // }
}
  

  if (millis()%100 == 0) {
    oled.drawBitmap(0, 0, bitmap_image, 128, 64, WHITE);
    oled.display();
  }
//   delay(1000);


//   // invert display
//   // oled.invertDisplay(1);
//   // delay(1000);
}


