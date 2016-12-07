#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;

void setup() {
  Bridge.begin();
  Console.begin();
  server.listenOnLocalhost();
  server.begin();
char str[7][127] = {
    {"ＵＴＦ８→Ｓ－ＪＩＳ　全角日本語漢字変換テスト表"},
    {"、。〃¢‐　一倅怎瀁耀退！￥熙～"},
    {"※〒℃⇒⇔♪Ωαβγθπφ●○◎◆◇■□★☆"},//よく使われる記号
    {"①②③④⑤⑥⑦⑧⑨⑩⑪⑫⑬⑭⑮⑯⑰⑱⑲⑳ⅠⅡⅢⅣⅤⅥⅦⅧⅨⅩ"},//JIS １３区文字
    {"㍉㌔㌢㍍㌘㌧㌃㌶㍑㍗㌍㌦㌣㌫㍊㌻㎜㎝㎞㎎㎏㏄㎡〝〟№㏍℡"},//JIS １３区文字
    {"㊤㊥㊦㊧㊨㈱㈲㈹㍾㍽㍼㍻∮∑∟⊿∪∩∠⊥≡≒√∵∫"}, //JIS １３区文字
    {"半角/ABC 全角/ＡＢＣ　半角カナ/ｱｶｻﾀﾅﾜｦﾝ ｶﾞﾊﾟ ｧｨｩｪｫｬｭｮ"}
  };
   
  byte utf8_1, utf8_2, utf8_3;
  byte sjis[2];
  byte str_SJIS_b[7][127];
  uint32_t sp_addres;
 
  byte array_cnt = 0;
  byte fnt_cnt = 0;
  int sjis_cnt = 0;
 
  for(array_cnt = 0; array_cnt<7; array_cnt++){
    while(str[array_cnt][fnt_cnt] != '\0'){
      if(str[array_cnt][fnt_cnt]>=0xC2 && str[array_cnt][fnt_cnt]<=0xD1){//UTF8 2バイト文字の場合
        utf8_1 = str[array_cnt][fnt_cnt];
        utf8_2 = str[array_cnt][fnt_cnt+1];
        utf8_3 = 0x00;
        fnt_cnt = fnt_cnt + 2;
      }else if(str[array_cnt][fnt_cnt]>=0xE2 && str[array_cnt][fnt_cnt]<=0xEF){//UTF8 3バイト文字の場合
        utf8_1 = str[array_cnt][fnt_cnt];
        utf8_2 = str[array_cnt][fnt_cnt+1];
        utf8_3 = str[array_cnt][fnt_cnt+2];
        fnt_cnt = fnt_cnt +3;
      }else{
        utf8_1 = str[array_cnt][fnt_cnt];
        utf8_2 = 0x00;
        utf8_3 = 0x00;
        fnt_cnt = fnt_cnt + 1;
      }
   
      if(utf8_1>=0x20 && utf8_1<=0x7E){ //半角ASCII文字を判別
        sjis[0] = utf8_1;
      }else{
        UTF8_To_SJIS_cnv(utf8_1,utf8_2,utf8_3, &sp_addres); //UTF8コードからUTF8→Sjis変換テーブルファイルのアドレスを計算
        SPIFFS_Flash_UTF8SJIS_Table_Read(sp_addres, sjis); //変換テーブルファイル"Utf8Sjis.tbl"からShift_JISコード取得
      }
 
      if((sjis[0] >= 0x80 && sjis[0] <= 0x9F) || (sjis[0] >= 0xE0 && sjis[0] <= 0xF0)){ //全角文字
        str_SJIS_b[array_cnt][sjis_cnt] = sjis[0];
        str_SJIS_b[array_cnt][sjis_cnt+1] = sjis[1];
        sjis_cnt = sjis_cnt + 2;
      }else{ //半角はこちらに分類される
        str_SJIS_b[array_cnt][sjis_cnt] = sjis[0];
        sjis_cnt = sjis_cnt + 1;
      }
      Serial.println("----------------------");
      Serial.print("UTF-8 Code=");Serial.print(utf8_1,HEX);Serial.print(utf8_2,HEX);Serial.println(utf8_3,HEX);
      Serial.print("UTF-8 Binary=");Serial.write(utf8_1);Serial.write(utf8_2);Serial.write(utf8_3);Serial.println();
      Serial.print("Shift_JIS Code=");Serial.print(sjis[0],HEX);Serial.println(sjis[1],HEX);
      Serial.print("Shift_JIS Binary=");Serial.write(sjis[0]);Serial.write(sjis[1]);Serial.println();
    }
    str_SJIS_b[array_cnt][sjis_cnt] = '\0';
    fnt_cnt = 0;
    sjis_cnt = 0;
  }
 
  Serial.println("/////////////////////////////");
  for(array_cnt = 0; array_cnt<7; array_cnt++){
    sjis_cnt = 0;
    while(str_SJIS_b[array_cnt][sjis_cnt] != '\0'){ //Shift_JISバイト列をバイナリ出力
      Serial.write(str_SJIS_b[array_cnt][sjis_cnt]);
      sjis_cnt++;
    }
    Serial.println();
  }
}
//**************メインループ*********************************************
void loop() {
 
}
//***********UTF-8コードをSPIFFS内の変換テーブルを読み出してShift-JISコードに変換****
void UTF8_To_SJIS_cnv(byte utf8_1, byte utf8_2, byte utf8_3, uint32_t* spiffs_addrs)
{
  uint32_t UTF8uint = utf8_1*256*256 + utf8_2*256 + utf8_3;
   
  if(utf8_1>=0xC2 && utf8_1<=0xD1){ //0xB0からS_JISコード実データ。0x00-0xAFまではライセンス文ヘッダなのでそれをカット。
    *spiffs_addrs = ((utf8_1*256 + utf8_2)-0xC2A2)*2 + 0xB0; //文字"¢" UTF8コード C2A2～、S_jisコード8191
  }else if(utf8_1==0xE2 && utf8_2>=0x80){
    *spiffs_addrs = (UTF8uint-0xE28090)*2 + 0x1EEC; //文字"‐" UTF8コード E28090～、S_jisコード815D
  }else if(utf8_1==0xE3 && utf8_2>=0x80){
    *spiffs_addrs = (UTF8uint-0xE38080)*2 + 0x9DCC; //スペース UTF8コード E38080～、S_jisコード8140
  }else if(utf8_1==0xE4 && utf8_2>=0x80){
    *spiffs_addrs = (UTF8uint-0xE4B880)*2 + 0x11CCC; //文字"一" UTF8コード E4B880～、S_jisコード88EA
  }else if(utf8_1==0xE5 && utf8_2>=0x80){
    *spiffs_addrs = (UTF8uint-0xE58085)*2 + 0x12BCC; //文字"倅" UTF8コード E58085～、S_jisコード98E4
  }else if(utf8_1==0xE6 && utf8_2>=0x80){
    *spiffs_addrs = (UTF8uint-0xE6808E)*2 + 0x1AAC2; //文字"怎" UTF8コード E6808E～、S_jisコード9C83
  }else if(utf8_1==0xE7 && utf8_2>=0x80){
    *spiffs_addrs = (UTF8uint-0xE78081)*2 + 0x229A6; //文字"瀁" UTF8コード E78081～、S_jisコードE066
  }else if(utf8_1==0xE8 && utf8_2>=0x80){
    *spiffs_addrs = (UTF8uint-0xE88080)*2 + 0x2A8A4; //文字"耀" UTF8コード E88080～、S_jisコード9773
  }else if(utf8_1==0xE9 && utf8_2>=0x80){
    *spiffs_addrs = (UTF8uint-0xE98080)*2 + 0x327A4; //文字"退" UTF8コード E98080～、S_jisコード91DE
  }else if(utf8_1>=0xEF && utf8_2>=0xBC){
    *spiffs_addrs = (UTF8uint-0xEFBC81)*2 + 0x3A6A4; //文字"！" UTF8コード EFBC81～、S_jisコード8149
    if(utf8_1==0xEF && utf8_2==0xBD && utf8_3==0x9E){
      *spiffs_addrs = 0x3A8DE; // "～" UTF8コード EFBD9E、S_jisコード8160
    }
  }
}
 
//***********SPIFFSフラッシュ内のUTF8Sjis変換テーブル読み込み*************
void SPIFFS_Flash_UTF8SJIS_Table_Read(uint32_t addrs, byte *buf)
{
//  Dir dir = SPIFFS.openDir("/");//これは読み取り速度が遅くなるかもしれないのでコメントアウトしている
  File f2 = SPIFFS.open("/Utf8Sjis.tbl", "r");
  f2.seek(addrs,SeekSet);
  buf[0] = f2.read();
  buf[1] = f2.read();
}
