#define do 0 //ド
#define re 1 //レ
#define mi 2 //ミ
#define fa 3 //ファ
#define so 4 //ソ
#define ra 5 //ラ
#define si 6 //シ
#define TX 7 //無音
#define s 500
#define l 1000

int fq[] = {262, 294, 330, 349, 392, 440, 494, 0};

int mo[45][2] = {{do,s},{re,s},{mi,l},{TX,l},{do,s},{re,s},{mi,l},{TX,s},
                   {so,s},{fa,s},{re,s},{do,s},{re,s},{mi,s},{re,l},{TX,l},
                   {so,s},{so,s},{mi,s},{so,s},{ra,s},{ra,s},{so,l},{TX,l},
                   {mi,s},{mi,s},{re,s},{re,s},{do,l}};

void setup() {
  for(int i = 0; i < 45; i++){
    tone(12,fq[mo[i][0]],mo[i][1]);
    delay(500);
  }
}

void loop() {
}
